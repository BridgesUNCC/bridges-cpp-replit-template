
#ifndef SONG_H
#define SONG_H


namespace bridges {
/**
 * @brief  A Song object, used along with the Songs data source.
 *
 * This is a convenience class provided for  users who wish to use this
 * data source as part of their application. It provides an API that makes
 * it easy to access the attributes of this data set.
 *
 * Refer to tutorial examples to using this data source in data structure
 * assignments.
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
			Song()
				: artist(""), song(""), album(""), lyrics(""), release_date("") {
			}

			Song(const string& artist, const string& song, const string& album, const string& lyrics,
				const string& release_date)
				: artist(artist), song(song), album(album), lyrics(lyrics), release_date(release_date) {
			}

			string getArtist() const {
				return artist;
			}

			void setArtist (const string& artist) {
				this->artist = artist;
			}

			string getSongTitle() const {
				return song;
			}
			void setSongTitle(const string& song) {
				this->song = song;
			}

			string getAlbumTitle() const {
				return album;
			}
			void setAlbumTitle(const string& album) {
				this->album = album;
			}

			string getLyrics() const {
				return lyrics;
			}
			void setLyrics(const string& lyrics) {
				this->lyrics = lyrics;
			}

			string getReleaseDate() const {
				return release_date;
			}
			void setReleaseDate(const string& release_date) {
				this->release_date = release_date;
			}
	};

} // namespace bridges

#endif
