
#ifndef AMENITIES

#define AMENITIES
/**
 * @brief  Class that hold Open Street Map Amenity data
 *
 * This class holds the individual information for each amenity requested

 * Usually this class is not created by the user but part of an AmenityData 
 * object returned by bridges::DataSource::getAmenityData()

 * @sa Check out the tutorial on getting amenity data at 
 *		https://bridgesuncc.github.io/tutorials/Data_Amenity.html
 *
 * @author Kalpathi Subramanian
 * @date  1/28/21
 */

#include <string>

class Amenities {

	private:
		long id_val;
		double lat;
		double lon;
		string name;
		vector<string> other;

	public:
		/**
		 * Default Constructor
		 */
		Amenities() {
			id_val = 0;
			lat = 0;
			lon = 0;
			name = "";
			other.clear();
		}

		/**
		 * Constructor
		 * @param id_val  Amenity ID as stored in Open Street Maps
		 * @param lat  Latitude of Amenity
		 * @param lon  Longitude of Amenity
		 * @param name  Name of Amenity as found in Open Street Maps
		 * @param other  List of special values that may have come with the amenity
		 */
		Amenities (double id_val, double lat, double lon, string name,
			vector<string> other) {
			setId(id_val);
			setLat(lat);
			setLon(lon);
			setName(name);
			setOther(other);
		}


		/**
		 * get the ID  of this amenity
		 * @return ID value
		 */
		long getId() {
			return id_val;
		}

		/**
		 * set the ID value of this amenity
		 * @param id_val ID value to set
		 */
		void setId(long id) {
			id_val = id;
		}

		/**
		 * get the latitude  of this amenity data
		 * @return amenity data latitude
		 */
		double getLat() {
			return lat;
		}

		/**
		 * set the latitude  value of this amenity
		 * @param lat latitude position to set
		 */
		void setLat(double latitude) {
			lat = latitude;
		}

		/**
		 * get the longitude  of this amenity data
		 * @return amenity data longitude
		 */
		double getLon() {
			return lon;
		}

		/**
		 * set the longitude  value of this amenity
		 * @param lon longitude position to set
		 */
		void setLon(double longitude) {
			lon = longitude;
		}

		/**
		 * get the name  of this amenity data
		 * @return name of this amenity
		 */
		string getName() {
			return name;
		}

		/**
		 * set the name of this amenity
		 * @param name name of amenity to set
		 */
		void setName(string n) {
			name = n;
		}

		/**
		 * get the extra data present for certain amenities
		 * @return list of extra data
		 */
		vector<string> getOther() {
			return other;
		}

		/**
		 * set the extra data present for certain amenities
		 * @param other
		 */
		void setOther(vector<string> oth) {
			other = oth;
		}
};

#endif
