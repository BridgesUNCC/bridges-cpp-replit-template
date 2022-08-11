#ifndef CITY_H

#define CITY_H

#include <string>

using std::string;


namespace bridges {
	namespace dataset {

			/**
			 * @brief Class that holds data of a city
			 *
			 * A user would not normally create an City object but
			 * rather obtain one from calling bridges::DataSource::getUSCities(),
			 * bridges::DataSource::getWorldCities() (to come)
			 *
			 * A tutorial on how to use the City objects is available at:
			 *  https://bridgesuncc.github.io/tutorials/Data_USCities.html 
			 *
			 * Each city object contains the city name, state, country, time zone, elevation,
			 *  population and lat/long location information.
			 *
			 * @author Kalpathi Subramanian
			 *
			 * @date 6/7/22
			 */
		class City {

			private:
				string city, state, country, time_zone;
				int elevation, population;
				float latit, longit;   // city location

			public:
				/**
				 *  Constructors
				 */
		  City() = default;
		  
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

				string getCity() const{
					return city;
				}

				void setCity(string c) {
					city = c;
				}

				string  getState() const{
					return state;
				}

				void  setState(string st) {
					state = st;
				}

				string getCountry() const{
					return country;
				}

				void setCountry(string cntry) {
					country = cntry;
				}

				string getTimeZone() const{
					return time_zone;
				}

				void setTimeZone(string tz){
					time_zone = tz;
				}

				float  getLatitude() const{
					return latit;
				}

				void setLatitude(float lat) {
					latit = lat;
				}

				float  getLongitude()  const{
					return longit;
				}

				void setLongitude(float lon) {
					longit = lon;
				}
				float  getPopulation()const  {
					return population;
				}

				void setPopulation(int pop) {
					population = pop;
				}

				int  getElevation() const {
					return elevation;
				}

				void setElevation(int elev) {
					elevation = elev;
				}
		};
	};
};
#endif
