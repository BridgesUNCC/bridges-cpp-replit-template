#ifndef IMDB_H

#define IMDB_H

#include <string>

using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 *	@brief A class to hold actor movie data -- using IMDB dataset
		 *
		 *  This dataset has a set of actor-movie pairs with movie rating and
		 *   genres, possibly. There are two datasets, the first has 1813 actor
		 *   movie pairs and no other attribute data. The second also has
		 *	 movie ratings and genres.
		 *
		 *  A user typically does not create an ActorMovieIMDB object. 
		 *	They are usually returned by 
		 *  bridges::DataSource::getActorMovieIMDBData() and 
		 *	bridges::DataSource::getActorMovieIMDBData2()
		 *
		 * 	@sa Check out the tutorial on the IMDB dataset at 
		 *	https://bridgesuncc.github.io/tutorials/Data_IMDB.html
		 *
		 *	@author Kalpathi Subramanian
		 *	@date 2/18/18, 12/28/20
		 *
		 */
		class ActorMovieIMDB {

			private:
				string actor, movie;
				double rating;
				vector<string> genres;

			public:
				ActorMovieIMDB () {
					actor = movie = "";
					rating = 0.0;
				}

				/**
				 * This method initializes an actor movie object with an actor/movie pair.
				 *
				 *	@param[in] a actor
				 *	@param[in] m movie
				 */
				ActorMovieIMDB(const string& a, const string& m) {
					actor = a;
					movie = m;
					rating = 0.0;
				}


				/**
				 * This method initializes an actor movie object with an actor/movie pair.
				 *
				 *	@param[in] a actor
				 *	@param[in] m movie
				 *	@param[in] r rating
				 *	@param[in] genr genres
				 */
				ActorMovieIMDB(const string& a, const string& m, float r, const vector<string>& genr) {
					actor = a;
					movie = m;
					rating = r;
					genres = genr;
				}

				/**
				 * @brief Get actor name
				 *
				 * @return actor name
				 */
				string getActor() const {
					return actor;
				}
				/**
				 * @brief Set actor name
				 *
				 * @param a actor name
				 *
				 */
				void setActor (const string& a) {
					actor = a;
				}

				/**
				 * @brief Get movie name
				 *
				 * @return movie name
				 */
				string getMovie() const {
					return movie;
				}

				/**
				 * @brief xSet movie name
				 *
				 * @param[in] m movie name
				 */
				void setMovie (const string& m) {
					movie = m;
				}

				/**
				 * @brief Get movie rating
				 *
				 * @return movie rating
				 */
				double getMovieRating() const {
					return rating;
				}

				/**
				 * @brief Set movie rating
				 *
				 * @param[in] r movie rating
				 */
				void setMovieRating(double r) {
					rating = r;
				}

				/**
				 * @brief Get movie genres
				 *
				 * @return movie genres [vector of strings]
				 */
				vector<string> getGenres() const {
					return genres;
				}

				/**
				 * @brief Set movie genres
				 *
				 * @param[in] g vector of movie genres
				 */
				void setGenres(const vector<string>& g) {
					genres = g;
				}

		};
	}
} // namespace bridges

#endif
