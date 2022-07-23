
#ifndef SONG_H
#define SONG_H


namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Song object, used along with the Songs data source.
		 *
		 * This is a convenience class provided for  users who wish to use this
		 * data source as part of their application. It provides an API that makes
		 * it easy to access the attributes of this data set.
		 *
		 * The Song object is typically obtained from calling 
		 * bridges::DataSource::getSongData() or 
		 *  bridges::DataSource::getSong().
		 *
		 * @sa Refer to tutorial for example of using this feature: 
		 *	https://bridgesuncc.github.io/tutorials/Data_Song_Lyrics.html
		 *
		 *
		 * @author David Burlinson, C++ port: Kalpathi Subramanian
		 * @date   5/24/18
		 *
		 */

		class Song {
			private:
				string 	artist, // song author
						song,	// song title
						album,	// album title
						lyrics,	// full lyrics
						release_date;

			public:
				/**
				 * Default constructor
				 */
				Song()
					: artist(""), song(""), album(""), lyrics(""),
					  release_date("") {
				}

				/**
				     * @brief Song constructor
				     *
				     * @param artist  artist of song
				     * @param song    song title
				     * @param album   album title
				     * @param lyrics  lyrics of song (string)
				     * @param release_date  date released
				     */
				Song(const string& artist, const string& song, const
					string& album, const string& lyrics,
					const string& release_date)
					: artist(artist), song(song), album(album), lyrics(lyrics),
					  release_date(release_date) {
				}
				/**
				  *   Get song artist
				  *   @return artist of song
				  */

				string getArtist() const {
					return artist;
				}
				/**
				 *   Set song artist
				 *   @param artist artist to set
				 */


				void setArtist (const string& artist) {
					this->artist = artist;
				}

				/**
				 *   Get song title
				 *   @return title of song (string)
				 */
				string getSongTitle() const {
					return song;
				}

				/**
				 *   Set song title
				 *   @param song song title  to set
				 */
				void setSongTitle(const string& song) {
					this->song = song;
				}

				/**
				 *   Get album title containing the song
				 *   @return album title  (string)
				 */

				string getAlbumTitle() const {
					return album;
				}
				/**
				 *   Set song album
				 *   @param album song album  to set
				 */
				void setAlbumTitle(const string& album) {
					this->album = album;
				}

				/**
				 *   Get lyrics of the song
				 *   @return lyrics of  song (string)
				 */
				string getLyrics() const {
					return lyrics;
				}

				/**
				 *   Set song lyrics
				 *   @param lyrics of song to set
				 */
				void setLyrics(const string& lyrics) {
					this->lyrics = lyrics;
				}

				/**
				 *   Get release date  of the song
				 *   @return release date of  song (string)
				 */
				string getReleaseDate() const {
					return release_date;
				}

				/**
				 *   Set release date of song
				 *   @param release_date date of release to set
				 */
				void setReleaseDate(const string& release_date) {
					this->release_date = release_date;
				}
		};
	}
} // namespace bridges

#endif
