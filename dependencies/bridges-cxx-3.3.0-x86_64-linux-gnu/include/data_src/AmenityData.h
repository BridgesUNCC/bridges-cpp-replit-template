#ifndef OSM_AMENITY_DATA

#define OSM_AMENITY_DATA


#include "Amenities.h"
#include <vector>

/**
 * @brief  Class that holds Open Street Map Amenity Data
 *
 * This class holds the data for all the amenities requested by the user
 *
 * Usually this class is not created by the user but returned by 
 *	bridges::DataSource::getAmenityData()

 * @sa Check out the tutorial on getting amenity data at 
 *		https://bridgesuncc.github.io/tutorials/Data_Amenity.html
 * @author Kalpathi Subramanian
 *
 * @date 1/28/21
 */
class AmenityData {

	private:

		// vector to hold amenity data, that will be returned
		// by the query
		vector<Amenities> data;

		// location information - lat/long bounding box
		double minLat;
		double minLon;
		double maxLat;
		double maxLon;

		// number of amenities
		int count;

	public:

		/**
		 * Default Constructor
		 */
		AmenityData() {
			data.clear();
			minLat = 0;
			minLon = 0;
			maxLat = 0;
			maxLon = 0;
			count = 0;
		}

		/**
		 * Constructor
		 *
		 * @param data  amenity data
		 * @param minLat  minimum latitude
		 * @param minLon  minimum longitude
		 * @param maxLat  maximum latitude
		 * @param maxLon  maximum longitude
		 * @param count  number of amenities
		 */

		AmenityData(vector<Amenities> amenities, double minLat, double minLon,
			double maxLat, double maxLon, int count) {
			data = amenities;
			setMinLat(minLat);
			setMinLon(minLon);
			setMaxLat(maxLat);
			setMaxLon(maxLon);
			setCount(count);
		}

		/**
		 * get Amenity data
		 * @return amenity data
		 */
		vector<Amenities> getAmenities() {
			return data;
		}

		/**
		 * set  Amenity data
		 * @param amenity amenity data to be added
		 */
		void addAmenities(Amenities amenity) {
			data.push_back(amenity);
		}

		/**
		 * get the minimum latitude  of this amenity data
		 * @return  latitude minimum
		 */

		double getMinLat() {
			return minLat;
		}

		/**
		 * set the minimum latitude  of this amenity data
		 * @param minLat  latitude minimum to be set
		 */
		void setMinLat(double lat) {
			minLat = lat;
		}

		/**
		 * get the minimum longitude  of this amenity data
		 * @return  longitude minimum
		 */
		double getMinLon() {
			return minLon;
		}

		/**
		 * set the minimum longitude  of this amenity data
		 * @param minLon  longitude minimum to be set
		 */
		void setMinLon(double longitude) {
			minLon = longitude;
		}
		/**
		 * get the maximum latitude  of this amenity data
		 * @return  latitude maximum
		 */

		double getMaxLat() {
			return maxLat;
		}

		/**
		 * set the maximum latitude  of this amenity data
		 * @param maxLat  latitude maximum to be set
		 */
		void setMaxLat(double lat) {
			maxLat = lat;
		}

		/**
		 * get the maximum longitude  of this amenity data
		 * @return  longitude maximum
		 */
		double getMaxLon() {
			return maxLon;
		}

		/**
		 * set the maximum longitude  of this amenity data
		 * @param maxLon  longitude maximum to be set
		 */
		void setMaxLon(double longitude) {
			maxLon = longitude;
		}

		/**
		 * get the count of amenities
		 * @param count of amenities
		 */
		int getCount() {
			return count;
		}


		/**
		 * set the count of amenities
		 * @param count  amenity count to be set
		 */
		void setCount(int c) {
			count = c;
		}
};

#endif
