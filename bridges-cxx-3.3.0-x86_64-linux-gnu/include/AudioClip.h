
#include "Bridges.h"
#include "AudioChannel.h"
#include <math.h>
#include "rapidjson/stringbuffer.h"
#include "base64.h"
#include <string>
#include <fstream>

#include <iostream>
using namespace std;

namespace bridges {

	// WAVE file header format
	struct WaveHeader {
		unsigned char riff[4];				// RIFF string
		unsigned int overall_size	;		// overall size of file in bytes
		unsigned char wave[4];				// WAVE string
		unsigned char fmt_chunk_marker[4];	// fmt string with trailing null char
		unsigned int length_of_fmt;			// length of the format data
		unsigned int format_type;			// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
		unsigned int channels;				// no.of channels
		unsigned int sample_rate;			// sampling rate (blocks per second)
		unsigned int byterate;				// SampleRate * NumChannels * BitsPerSample/8
		unsigned int block_align;			// NumChannels * BitsPerSample/8
		unsigned int bits_per_sample;		// bits per sample, 8- 8bits, 16- 16 bits etc
		unsigned char data_chunk_header[4];	// DATA string or FLLR string
		unsigned int data_size;				// NumSamples * NumChannels *
		// BitsPerSample/8 - size of the
		// next chunk that will be read

	};

	namespace datastructure {
		/**
		 * @brief This class provides support for reading, modifying,
		 *	and playing audio waveforms.
		 *
		 * This class provides a way to represent an AudioClip (think of a
		 * .WAV file) in Bridges as waveforms.
		 *
		 * An AudioClip can be composed of multiple channels: a stereo sound
		 * would be composed of 2 channels (Left and Right), a mono sound
		 * would be composed of a single channel. A 5.1 sound would be
		 * composed of 6 channels. When building an AudioClip from a file, the
		 * number of channels is taken from the file; some constructors have a
		 * numChannels that enables to pass the number of channels
		 * explicitly. If unsure, one can know how many channels are in an
		 * audio clip using getNumChannels().
		 *
		 * Each channel is essentially a 1D signal. That is to say, it is an
		 * array of values that represent how far the membrane of a speaker
		 * should be from its resting position. The quality of the sound is
		 * controlled by two parameters: sampling rate and sampling depth.
		 *
		 * Sampling rate tells how many positions per second are encoded by
		 * the AudioClip. It is expressed in Hertz. CD quality is 44100Hz;
		 * while walkie-talkies use 8000Hz. It is set automatically if read
		 * from a file; or it can be passed as the sampleRate parameter to
		 * some of the constructors. The sampling rate can be obtained from an
		 * AudioClip using getSampleRate().
		 *
		 * The length of an AudioClip is expressed in number of samples. So if
		 * an AudioClip is composed of 16,000 samples with a sampling rate of
		 * 8000Hz, the clip would be 2 seconds long. The number of samples
		 * can obtained with getSampleCount(); it is set from a file or can be
		 * passed as the sampleCount parameter of some of the constructor.
		 *
		 * The sampling depth indicates how many different positions the
		 * membrane can take. It is typically expressed in bits with supported
		 * values being 8-bit, 16-bit, 24-bit, and 32-bit. If a clip is
		 * encoded with a depth of 8 bits, the membrane can take 2^8 different
		 * position ranging from -128 to +127, with 0 being the resting
		 * position. The sampling depth is read from files or passed as the
		 * sampleBits parameter of the constructor. The sampling depth of an
		 * existing clip can be obtained with getSampleBits().
		 *
		 * The individual samples are accessed with the getSample() and
		 * setSample() functions. The samples are integer values in the
		 * [-2^(getSampleBits()-1) ; 2^(getSampleBits()-1)[ range. The
		 * functions allow to specify for channel and sample index.
		 *
		 *
		 *
		 *
		 * @sa There is a tutorial for processing audio at
		 * https://bridgesuncc.github.io/tutorials/AudioClip.html
		 *
		 *
		 * @author Luke Sloop, Kalpathi Subramanian, Erik Saule
		 * @date  2020
		 *
		 * Acknowledgements: The Wav file parser is adapted from Amit Sengupta's
		 *  C version, posted at  TRUELOGIC BLOG,
		 *	http://truelogic.org/wordpress/2015/09/04/parsing-a-wav-file-in-c/
		 *
		 *  It was converted into C++ in this implementation.
		 *
		**/
		class AudioClip : public DataStructure {
				const bool debug = false;
			private:
				int sampleCount;
				int numChannels;
				int sampleRate;
				int sampleBits;
				vector<AudioChannel> channels;

				union ShortByteUnion {
					signed short asShort;
					unsigned char asBytes[2];
				};

			public:
				/**
				* @brief create an audio clip
				*
				* creates an AudioClip with numChannels channels, sampleCount samples at sampleRate Hz with a depth of sampleBits
				*
				**/

				AudioClip(int sampleCount, int numChannels, int sampleBits, int sampleRate) {
					if (sampleCount > 1000000000) {
						throw "sampleCount must be less than 1 million";
					}


					if (sampleBits != 8 && sampleBits != 16 && sampleBits != 24 && sampleBits != 32) {
						throw "sampleBits must be either 8, 16, 24, or 32";
					}

					if (numChannels <= 0) {
						throw "numChannels should be positive";
					}

					if (sampleRate <= 0) {
						throw "sampleRate should be positive";
					}



					this->sampleCount = sampleCount;
					this->numChannels = numChannels;
					this->channels = vector<AudioChannel>();

					for (int i = 0; i < numChannels; i++) {
						this->channels.push_back( AudioChannel(sampleCount));

						for (int j = 0; j < sampleCount; j++) {
							this->channels[i].setSample(j, 0);
						}
					}

					this->sampleRate = sampleRate;
					this->sampleBits = sampleBits;
				}

				virtual const string getDStype() const override {
					return "Audio";
				}

				/**
				 * @brief create an audio clip from a File
				 *
				 * @param wave_file name of the file (should be a Wave file)
				 *
				 **/
				AudioClip(const string& wave_file) {
					parseWaveFile (wave_file);

				}

				virtual const string getDataStructureRepresentation() const override final {
					using bridges::JSONUtil::JSONencode;

					int len = numChannels * sampleCount * (sampleBits / 8);
					std::vector<BYTE> byteBuff;

					int checkSampleBits = sampleBits;

					for (int i = 0; i < sampleCount; i++) {
						for (int c = 0; c < numChannels; c++) {
							int num = getSample(c, i);
							//uint32_t s = ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
							if (this->sampleBits == 8) {
								byteBuff.push_back(num & 0x000000FF);
							}
							else if (this->sampleBits == 16) {
								ShortByteUnion sbu;
								sbu.asShort = (uint16_t)num;
								byteBuff.push_back(sbu.asBytes[0]);
								byteBuff.push_back(sbu.asBytes[1]);
							}
							else if (this->sampleBits == 32 || this->sampleBits == 24) {
								// Some browsers cannot play 32 bit audio files so use 16
								int minmax = (int)((pow(2, sampleBits) / 2) - 1);
								int minmax16 = (int)((pow(2, 16) / 2) - 1);

								num = (int)((num / (float)minmax) * minmax16) & 0xFFFF;

								ShortByteUnion sbu;
								sbu.asShort = (uint16_t)num;
								byteBuff.push_back(sbu.asBytes[0]);
								byteBuff.push_back(sbu.asBytes[1]);
								checkSampleBits = 16;
							}
						}
					}

					string b64str = base64::encode(&(byteBuff[0]), byteBuff.size());

					string jsonString = QUOTE + "encoding" + QUOTE + COLON + QUOTE + "RAW" + QUOTE + COMMA +
						QUOTE + "numChannels" + QUOTE + COLON + JSONencode(this->numChannels) + COMMA +
						QUOTE + "sampleRate" + QUOTE + COLON + JSONencode(this->sampleRate) + COMMA +
						QUOTE + "bitsPerSample" + QUOTE + COLON + JSONencode(checkSampleBits) + COMMA +
						QUOTE + "numSamples" + QUOTE + COLON + JSONencode(this->sampleCount) + COMMA +
						QUOTE + "samples" + QUOTE + COLON + QUOTE + b64str + QUOTE + CLOSE_CURLY;

					return jsonString;
				}

				/**
				 * @brief returns the number of channels of the clip
				 * @return  the number of channels of the clip (1 for mono, 2 for stereo, ...)
				 **/
				int getNumChannels() const {
					return this->numChannels;
				}
				/**
				* @brief returns the sampling rate of the clip
				 * @return  the sampling rate of the clip in Hertz. (CD quality is 44100Hz for instance)
				 **/

				int getSampleRate() const {
					return this->sampleRate;
				}

				/**
				* @brief returns the number of samples in the clip
				 *
				 * The length of the clip in second is getSampleCount()/((double) getSampleRate())
				 *
				 * @return  the number of samples in the clip
				 **/
				int getSampleCount() const {
					return this->sampleCount;
				}


				/**
				* @brief returns the sampling depth.
				*
				* The sampling depth indicates how many bits are used to
				* encode each individual samples. The values supported are
				* only 8, 16, 24, and 32.
				*
				* All samples must be in the [-2^(getSampleBits()-1) ;
				* 2^(getSampleBits()-1)) range. that is to say, for 8-bit, in
				* the [-256;255] range.
				*
				* @return the sampling depth.
				**/
				int getSampleBits() const {
					return this->sampleBits;
				}

				/**
				* @brief access a particular sample

				* @param channelIndex the index of the channel that will be accessed (in the [0;getNumChannels()-1] range).
				* @param sampleIndex the index of the sample that will be accessed (in the [0;getSampleCount()-1] range).
				* @return the sample value (in [-2^(getSampleBits()-1) ;  2^(getSampleBits()-1)) range).
				*
				**/

				int getSample(int channelIndex, int sampleIndex) const {
					return channels.at(channelIndex).getSample(sampleIndex);
				}
				/**
				* @brief change a particular sample

				 * @param channelIndex the index of the channel that will be accessed (in the [0;getNumChannels()-1] range).
				 * @param sampleIndex the index of the sample that will be accessed (in the [0;getSampleCount()-1] range).
				 * @param value the sample value (in [-2^(getSampleBits()-1) ;  2^(getSampleBits()-1)) range).
				 *
				 **/
				void setSample(int channelIndex, int sampleIndex, int value) {
					if (value >= pow(2, getSampleBits() - 1) ||
						value <  -pow(2, getSampleBits() - 1))
						throw "Audio value Out of Bound";

					channels[channelIndex].setSample(sampleIndex, value);
				}
			private:
				/**
				 *
				 * Acknowledgements: This Wav file parser is adapted from Amit Sengupta's
				 *  C version, posted at  TRUELOGIC BLOG,
				 *	http://truelogic.org/wordpress/2015/09/04/parsing-a-wav-file-in-c/
				 *
				 *  It was converted into C++ in this implementation.
				 **/
				void parseWaveFile (const string & wave_file) {
					// Read and parse an audio file in WAVE format

					// open file
					ifstream infile;
					infile.open (wave_file.c_str(), ios::binary | ios::in);
					if (infile.fail()) {
						throw "Could not open " + wave_file;
					}

					// read the header data of the input WAVE file
					WaveHeader wave_header = readWaveHeader(infile);

					long size_of_each_sample = (wave_header.channels *
							wave_header.bits_per_sample) / 8;

					// read the audio data
					if (this->sampleCount > 1000000000) {
						throw "sampleCount must be less than 1 million";
					}

					// create storage for the audio data
					//this->channels.resize(this->numChannels);
					for (int i = 0; i < numChannels; i++) {
						this->channels.push_back( AudioChannel(this->sampleCount));
					}

					// read sample data by chunks, if PCM
					if (wave_header.format_type == 1) { // Only PCM handled
						long i = 0;
						char data_buffer[size_of_each_sample];
						int  size_is_correct = true;

						// make sure that the bytes-per-sample is completely divisible
						// by num.of channels
						long bytes_in_each_channel = (size_of_each_sample / wave_header.channels);
						if ((bytes_in_each_channel * wave_header.channels) != size_of_each_sample) {
							cout << "Error: Incorrect chunk size.. " <<  bytes_in_each_channel
								<< ", " <<  wave_header.channels << ", " <<  size_of_each_sample << "\n";
							size_is_correct = false;
						}

						if (size_is_correct) {
							// the valid amplitude range for values based on the bits per sample
							long low_limit = 0l;
							long high_limit = 0l;

							switch (wave_header.bits_per_sample) {
								case 8:
									low_limit = -128;
									high_limit = 127;
									break;
								case 16:
									low_limit = -32768;
									high_limit = 32767;
									break;
								case 24:
									low_limit = -16777216;
									high_limit = 16777215;
									break;
								case 32:
									low_limit = -2147483648;
									high_limit = 2147483647;
									break;
							}
							for (int sample = 0; sample < this->sampleCount;
								sample++) {
								int amplitude;
								if (!infile.fail()) {
									for (int ch = 0; ch < wave_header.channels;
										ch++ ) {
										// read signal amplitude
										infile.read(data_buffer, bytes_in_each_channel);
										// convert data from big endian to little
										// endian based on bytes in each channel sample
										switch (bytes_in_each_channel) {
											case 1:
												amplitude = data_buffer[0] & 0x00ff;
												amplitude -= 128; //in wave, 8-bit are unsigned, so shifting to signed
												break;
											case 2:
												amplitude =
													(data_buffer[0] & 0x00ff) |
													(data_buffer[1] << 8);
												break;
											case 3:
												amplitude =
													(data_buffer[0] & 0x00ff) |
													((data_buffer[1] & 0x00ff) << 8) |
													(data_buffer[2] << 16);
												break;
											case 4:
												amplitude =
													(data_buffer[0] & 0x00ff) |
													((data_buffer[1] & 0x00ff) << 8) |
													((data_buffer[2] & 0x00ff) << 16) |
													(data_buffer[3] << 24);
												break;
										}
										this->setSample(ch, sample, amplitude);
									}
								}
								else {
									cout << "Error reading file\n.";
									break;
								}
							}
						}
					}
					infile.close();
				}

				//For information on the wave header, see: http://soundfile.sapp.org/doc/WaveFormat/
				//But be careful that this URL ignores the possibility that other chunks may exist such as the fact, ce, playlist, and data list chunks. see https://en.wikipedia.org/wiki/WAV and https://en.wikipedia.org/wiki/Resource_Interchange_File_Format for details.
				//It appears this is a complete specification: http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/Docs/riffmci.pdf
				// this function reads/parse the RIFF/WAVE formated file and stops reading at the beginning of the data chunk after reading its header
				WaveHeader readWaveHeader(ifstream& infile) {

					// read file header
					WaveHeader  wave_header;

					infile.read ((char *)wave_header.riff, 4);

					if (wave_header.riff[0] != 'R' ||
						wave_header.riff[1] != 'I' ||
						wave_header.riff[2] != 'F' ||
						wave_header.riff[3] != 'F')
						throw "malformed RIFF header";


					unsigned char *buffer = new  unsigned char[4];
					infile.read ((char*) buffer,  4);

					// convert little endian to big endian 4 byte int
					wave_header.overall_size  = buffer[0] | (buffer[1] << 8) |
						(buffer[2] << 16) | (buffer[3] << 24);

					if (debug)
						std::cout << "overall size: " << wave_header.overall_size << std::endl;

					infile.read ((char*) wave_header.wave,  4);

					if (wave_header.wave[0] != 'W' ||
						wave_header.wave[1] != 'A' ||
						wave_header.wave[2] != 'V' ||
						wave_header.wave[3] != 'E')
						throw "format is not WAVE";


					infile.read ((char*) wave_header.fmt_chunk_marker,  4);
					if (wave_header.fmt_chunk_marker[0] != 'f' ||
						wave_header.fmt_chunk_marker[1] != 'm' ||
						wave_header.fmt_chunk_marker[2] != 't' ||
						wave_header.fmt_chunk_marker[3] != ' ')
						throw "malformed wave file";


					infile.read ((char *) buffer, 4);
					wave_header.length_of_fmt = buffer[0] | (buffer[1] << 8) |
						(buffer[2] << 16) | (buffer[3] << 24);

					if (debug)
						std::cout << "length of format: " << wave_header.length_of_fmt << std::endl;

					char *buffer2 = new  char[2];
					infile.read (buffer2, 2);
					wave_header.format_type = buffer2[0] | (buffer2[1] << 8);

					string format_name = "";
					switch (wave_header.format_type) {
						case 1 :
							format_name = "PCM";
							break;
						case 6 :
							format_name = "A-law";
							break;
						case 7 :
							format_name = "Mu-law";
							break;
						default:
							throw "unsupported format";

					}

					infile.read (buffer2, 2);
					wave_header.channels = buffer2[0] | (buffer2[1] << 8);
					this->numChannels = wave_header.channels;

					if (debug)
						std::cout << "numChannels: " << numChannels << std::endl;


					infile.read ((char *) buffer, 4);
					wave_header.sample_rate = buffer[0] | (buffer[1] << 8) |
						(buffer[2] << 16) | (buffer[3] << 24);
					this->sampleRate = wave_header.sample_rate;

					if (debug)
						std::cout << "sampleRate: " << sampleRate << std::endl;

					infile.read ((char *) buffer, 4);
					wave_header.byterate = buffer[0] | (buffer[1] << 8) |
						(buffer[2] << 16) | (buffer[3] << 24);

					if (debug)
						std::cout << "byte rate: " << wave_header.byterate << std::endl;

					infile.read (buffer2, 2);
					wave_header.block_align = buffer2[0] | (buffer2[1] << 8);

					infile.read (buffer2, 2);
					wave_header.bits_per_sample = buffer2[0] | (buffer2[1] << 8);

					this->sampleBits = wave_header.bits_per_sample;

					if (debug)
						std::cout << "sample Bits: " << sampleBits << std::endl;

					if (wave_header.byterate !=
						wave_header.sample_rate * wave_header.channels * wave_header.bits_per_sample / 8)
						throw "malformed wave file";

					//The next sub-chunk of the RIFF format should be the data subchunk.
					//but in some case, there are meta data found first.
					//skipping any sub-chunk that is not the data sub-chunk
					bool data_chunk_found = false;
					while (!data_chunk_found) {
						infile.read ((char *)wave_header.data_chunk_header, 4);

						infile.read ((char *) buffer, 4);
						wave_header.data_size = buffer[0] | (buffer[1] << 8) |
							(buffer[2] << 16) | (buffer[3] << 24);

						if (wave_header.data_chunk_header[0] != 'd' ||
							wave_header.data_chunk_header[1] != 'a' ||
							wave_header.data_chunk_header[2] != 't' ||
							wave_header.data_chunk_header[3] != 'a') {
							//skip sub chunk
							int padding = (wave_header.data_size % 2 ? 0 : 1);
							infile.ignore(wave_header.data_size + padding);
						}
						else
							data_chunk_found = true;
					}



					// calculate no.of samples
					long num_samples = (8 * wave_header.data_size) /
						(wave_header.channels * wave_header.bits_per_sample);
					this->sampleCount = num_samples;

					if (debug)
						std::cout << "sample Count: " << this->sampleCount << std::endl;



					long size_of_each_sample = (wave_header.channels *
							wave_header.bits_per_sample) / 8;



					delete[] buffer;
					delete[] buffer2;

					if (!infile)
						throw "malformed RIFF header";

					return wave_header;
				}
		};
	}
}
