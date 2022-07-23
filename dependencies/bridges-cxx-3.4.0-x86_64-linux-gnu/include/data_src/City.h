#ifndef CITY_H

#define CITY_H

#include <string>

using std::string;


namespace bridges {
	namespace dataset {

		class City {
			/**
			 * @brief Class that holds data of a city
 			 * 
			 * A user would not normally create a City object but 
			 * rather obtain one from calling bridges::DataSource::getUSCities() or
             *   bridges::DataSource::getWorldCities()
			 *
			 * A tutorial on how to use the City dataset is available at: 
			 *  https://bridgesuncc.github.io/tutorials/USCities.html (to be done!)
			 *
			 * Each city object ccontains the city name, state, country, time zone, 
			 *  elevation, population and lat/long location information.
			 *
			 * @author Kalpathi Subramanian
			 *
			 * @date 6/7/22
			 */

			private:
				string city, state, country, time_zone;
				int elevation, population;
				float latit, longit;   // city location

			public:
				/**
				 *  Constructors
				 */
				City() {
					city = state = country = time_zone = string();
					elevation = population = 0;
					latit = longit = 0.;
				}
				City (string cty, string st, string cntry, string tm_zone,
						int elev, int pop, float lat, float lon) {
					city = cty;
					state = st;
					country = cntry;
					time_zone = tm_zone;
					elevation = elev;
					population = pop;
					latit = lat;
					longit = lon;
				}

				string getCity() {
					return city;
				}

				void setCity(string c) {
					city = c;
				}

				string  getState() {
					return state;
				}

				void  setState(string st) {
					state = st;;
				}

				string getCountry() {
					return country;
				}

				void setCountry(string cntry) {
					country = cntry;
				}

				string getTimeZone() {
					return time_zone;
				}

				void setTimeZone(string tz){
					time_zone = tz;
				}

				float  getLatitude() {
					return latit;
				}

				void setLatitude(float lat) {
					latit = lat;
				}

				float  getLongitude()  {
					return longit;
				}

				void setLongitude(float lon) {
					longit = lon;
				}
				float  getPopulation()  {
					return population;
				}

				void setPopulation(int pop) {
					population = pop;
				}

				int  getElevation()  {
					return elevation;
				}

				void setElevation(int elev) {
					elevation = elev;
				}
		};
	};
};
#endif
