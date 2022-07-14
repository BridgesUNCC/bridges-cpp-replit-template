#ifndef MOVIEACTOR_WIKIDATA_H
#define MOVIEACTOR_WIKIDATA_H

namespace bridges {
	namespace dataset {
		/**
		 * @brief This is a helper class for accessing actor-movie data 
		 *	from Wikidata.

		 * 	Note that the end user will not create an object of that type in 
		 *	regular circumstances. But rather, ActorMovieWikidata objects 
		 *	are returned by bridges::DataSource::getWikidataActorMovie()
		 *
		 *  @sa Exemple of how to access that type of data is provided at: 
		 *		https://bridgesuncc.github.io/tutorials/Data_WikiDataActor.html
		 *
		 * @author Erik Saule
		 * @date  12/28/20
		 */
		// Since the data always comes from wikidata, we could strip the
		// prefix http://www.wikidata.org/entity/ from the entities to gain
		// memory. Should we?
		class MovieActorWikidata {
				std::string movieURI;
				std::string actorURI;
				std::string movieName;
				std::string actorName;

			public:
				/**
				 * default constructor
				 */
				MovieActorWikidata() {
				}

				/**
				 * set the movie URI
				 * @param mu  movie uri to set
				 */
				void setMovieURI (std::string mu) {
					movieURI = mu;
				}

				/**
				 * set the actor URI
				 * @param au  actor uri to set
				 */
				void setActorURI (std::string au) {
					actorURI = au;
				}

				/**
				 * set the movie name
				 * @param mn  movie name to set
				 */
				void setMovieName (std::string mn) {
					movieName = mn;
				}

				/**
				 * set the actor name
				 * @param an  actor name to set
				 */
				void setActorName (std::string an) {
					actorName = an;
				}

				/**
				 * get the movie URI
				 * @return movie uri
				 */
				const std::string& getMovieURI() const {
					return movieURI;
				}

				/**
				 * get the actor URI
				 * @return actor uri
				 */
				const std::string& getActorURI() const {
					return actorURI;
				}

				/**
				 * get the movie name
				 * @return movie  name
				 */
				const std::string& getMovieName() const {
					return movieName;
				}

				/**
				 * get the actor name
				 * @return actor name
				 */
				const std::string& getActorName() const {
					return actorName;
				}
		};
	}
}


#endif
