#ifndef GAME_H

#define GAME_H

#include <string>

using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Game object, used along with the Games data source.
		 *
		 * This is a convenience class provided for  users who wish to use this
		 * data source as part of their application. It provides an API that makes
		 * it easy to access the attributes of this data set.
		 *
		 * Each game record has title, platform on which it can be played,
		 * rating,  and a list of genres.

		 * One would not normally create an object of this type, but 
		 *	rather obtain them through a call to 
		 * 	bridges::DataSource::getGameData().
		 *
		 * @sa Refer to tutorial examples on how to use this dataset: 
		 *	https://bridgesuncc.github.io/tutorials/Data_IGN_Games.html
		 *
		 * @author Kalpathi Subramanian
		 * @date   2/1/17, 12/26/20
		 *
		 */

		class Game {
			private:
				string title;			// game
				string platform;		// game platform type
				double rating;			// game rating
				vector<string> genre;	// game type/category

			public:
				/**
				 * Constructor
				 */

				Game()
					: title(""), platform(""), rating(0), genre() {
				}
				/**
				 * Constructor
				 *
				 * @param title title of game
				 * @param platform platform on which it can be played (String)
				 * @param rating  rating of game (double)
				 * @param genre  genres of game (vector of strings)
				 */


				Game(const string& title, const string& platform, double rating,
					const vector<string>& genre)
					: title(title), platform(platform), rating(rating), genre(genre) {
				}

				/**
				 * get title of game
				 * @return title of game (string)
				 */

				string getTitle() const {
					return title;
				}
				/**
				 * set title of game
				 * @param title game title to be set (string)
				 */
				void setTitle (const string& title) {
					this->title = title;
				}
				/**
				 * get platform type of game
				 * @return platform types (string)
				 */

				string getPlatformType() const {
					return platform;
				}
				/**
				 * set platform type  of game
				 * @param platform platform type to be set (string)
				 */

				void setPlatformType(const string& platform) {
					this->platform = platform;
				}
				/**
				 * get rating of game
				 * @return rating (double)
				 */
				double getRating() const {
					return rating;
				}
				/**
				 * set rating of game
				 * @param rating rating to be set (double)
				 */
				void setRating(double rating) {
					this->rating = rating;
				}
				/**
				* set genres of game
				* @param genre genres to be set (vector of strings)
				*/

				vector<string> getGameGenre() const {
					return genre;
				}
				/**
				* set genres of game
				* @param genre genres to be set (vector of strings)
				*/
				void setGameGenre(const vector<string>& genre) {
					this->genre = genre;
				}
		};
	}
} // namespace bridges

#endif
