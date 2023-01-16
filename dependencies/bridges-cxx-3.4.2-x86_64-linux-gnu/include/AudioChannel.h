
#include <vector>
/**
 * @brief class that represents an audio channel.
 *
 *	Used along with the BRIDGESaudio API
 */

class AudioChannel {
	private:
		std::vector<int> data;

	public:
		AudioChannel(int sampleCount) {
			data = std::vector<int>(sampleCount);
		}

		int getChannelSize() const {
			return data.size();
		}

		int getSample(int index) const {
			return data[index];
		}

		void setSample(int index, int val) {
			data[index] = val;
		}
};
