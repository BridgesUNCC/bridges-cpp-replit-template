#ifndef EARTHQUAKEUSGS_H

#define EARTHQUAKEUSGS_H

#include <string>

using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  Class that hold earthquake data, for use with USGIS retrieved quake data.
		 *
		 * Class that holds earthquake USGIS data. BRIDGES uses scripts to continually monitor
		 * USGIS site (tweets) and retrieve the latest quake data for use in student projects.
		 *
		 * Kalpathi Subramanian, 2/18/18
		 */


		class EarthquakeUSGS {
			private:
				double magnitude;		// earthquake magnitude
				double latit;			// earthquake location
				double longit;			// (lat/long)
				string location;		// location of quake
				string title;			// combo info of quake
				string url;				// url for more info
				string time;				// date

				// access by date
				mutable int year, month, day,  hour, minu, sec; //calling min minu to bypass a VS macro
				mutable bool date_correct;

#ifdef _WIN32
				//visual studio 2017 has not yet adopted the posix gmtime_r but has its platform specific gmtime_s.
				//this function converts the call (though drops error handling)
				void gmtime_r(time_t* eq_time, struct tm *eqt) const {
					gmtime_s(eqt, eq_time);
				}
#endif

				/**
				 *  Construct the epoch time of the quake - used internally to get
				 *	actual date - year, month, day, etc
				 *
				 */
				void getDate () const {
					if (date_correct)
						return;
					// get eq's epoch time
					string s = getTime();

					long epoch_time = std::stol(getTime());
					time_t eq_time = epoch_time / 1000;

					// convert to time_t

					struct tm reqt;
					struct tm *eqt = &reqt;
					gmtime_r(&eq_time, eqt);

					year = eqt->tm_year + 1900;
					month = eqt->tm_mon;
					day = eqt->tm_mday;
					hour = eqt->tm_hour;
					sec = eqt->tm_sec;
					minu = eqt->tm_min;

					date_correct = true;
				}

			public:

				EarthquakeUSGS()
					: magnitude(0.0), latit(0.0), longit(0.0),
					  location(""), title(""), url(""), time(""),
					  year(0), month(0), day(0), hour(0), minu(0), sec(0),
					  date_correct(false) {
				}

				EarthquakeUSGS(double magnitude, double longit, double latit,
					const string& location, const string& title, const string& url, const string& time)
					: magnitude(magnitude), latit(latit), longit(longit),
					  location(location), title(title), url(url), time(time),
					  year(0), month(0), day(0), hour(0), minu(0), sec(0),
					  date_correct(false) {
				}

				EarthquakeUSGS(const EarthquakeUSGS *eq)
					: magnitude(eq->magnitude), latit(eq->latit), longit(eq->longit),
					  location(eq->location), title(eq->title), url(eq->url), time(eq->time),
					  year(0), month(0), day(0), hour(0), minu(0), sec(0),
					  date_correct(false) {
				}

				/**
				 *  @brief return the epoch time of the quake
				 *
				 *  @return time
				 */

				string getTime() const {
					return time;
				}


				/**
				 * @brief returns the real date in a string format
				 *
				 *  @return the real date in format "Month Day Year Hour:Minute:Seconds"
				 */
				string getDateStr() const {
					getDate();
					string mstr;

					switch (month) {
						case 0 :
							mstr = "Jan. ";
							break;
						case 1 :
							mstr = "Feb. ";
							break;
						case 2 :
							mstr = "Mar. ";
							break;
						case 3 :
							mstr = "Apr. ";
							break;
						case 4 :
							mstr = "May ";
							break;
						case 5 :
							mstr = "Jun. ";
							break;
						case 6 :
							mstr = "Jul. ";
							break;
						case 7 :
							mstr = "Aug. ";
							break;
						case 8 :
							mstr = "Sept. ";
							break;
						case 9 :
							mstr = "Oct. ";
							break;
						case 10 :
							mstr = "Nov. ";
							break;
						case 11 :
							mstr = "Dec. ";
							break;
						default :
							mstr = "???. ";
							break;
					}

					// put into a string
					string date_str = "  " + mstr + to_string(day) + "  " + to_string(year) +
						"  " + to_string(hour) + ":" + to_string(minu) + ":" + to_string(sec);

					return date_str;
				}

				/**
				 *	@brief set epoch time
				 *
				 *	@param tm time as epoch
				 *
				 */
				void setTime (const string& tm) {
					// process tm to convert to a date
					time = tm;
					date_correct = false;
				}

				/**
				 *	@brief get year of quake
				 *
				 *	@return year of the quake
				 */
				int getYear() const {
					getDate();

					return year;
				}
				/**
				 *	@brief get month of quake
				 *
				 *	@return month of the quake
				 */
				int getMonth() const {
					getDate();

					return month;
				}
				/**
				 *	@brief get day of quake
				 *
				 *	@return day of the quake
				 */
				int getDay() const {
					getDate();

					return day;
				}
				/**
				 *	@brief get hour of quake
				 *
				 *	@return hour of the quake
				 */
				int getHour() const {
					getDate();

					return hour;
				}
				/**
				 *	@brief get minutes of quake
				 *
				 *	@return minutes of the quake
				 */
				int getMinutes() const {
					getDate();

					return minu;
				}
				/**
				 *	@brief get seconds of quake
				 *
				 *	@return get seconds of the quake
				 */
				int getSeconds() const {
					getDate();

					return sec;
				}

				/**
				 *	@brief get latitude of quake
				 *
				 *	@return latitude of the quake
				 */
				float getLatit() const {
					return (float) this->latit;
				}
				/**
				 *	@brief set latitude
				 *
				 *	@param[in] latit latitude
				 */
				void setLatit(float latit) {
					this->latit = latit;
				}
				/**
				 *	@brief get longitude of quake location
				 *
				 *	@return longitude of the quake
				 */
				float getLongit() const {
					return (float) longit;
				}
				/**
				 *	@brief set longitude of quake location
				 *
				 *	@param[in] longit longitude of the quake
				 */
				void setLongit(float longit) {
					this->longit = longit;
				}
				/**
				 *	@brief get quake location.
				 *
				 * This is astring describing location (typically a city or something of the sort)
				 *
				 *	@return location as a string
				 */
				string getLocation() const {
					return location;
				}
				/**
				 *	@brief set quake location (string)
				 *
				 *	@param[in] location location
				 */
				void setLocation(string location) {
					this->location = location;
				}
				/**
				 *	@brief get quake title
				 *
				 * Typically a one line description of the quake
				 *
				 *	@return title
				 */
				string getTitle() const {
					return this->title;
				}
				/**
				 *	@brief set quake title
				 *
				 *	@param[in] title quake title
				 */
				void setTitle(const string& title) {
					this->title = title;
				}
				/**
				 *	@brief get quake url
				 *
				 *	@return USGIS url about the quake
				 */
				string getUrl() const {
					return url;
				}
		  
				/**
				 *	@brief set quake url
				 *
				 *	@param[in] url USGIS url of the quake
				 *
				 */
				void setUrl(const string& url) {
					this->url = url;
				}
				/**
				 *	@brief get quake magnitude
				 *
				 *	@return magnitude of the scale on Richter scale
				 */
				double getMagnitude() const {
					return this->magnitude;
				}
				/**
				 *	@brief set quake magnitude
				 *
				 *	@param[in] magnitude magnitude of the quake on Richter scale
				 */
				void setMagnitude(double magnitude) {
					this->magnitude = magnitude;
				}
		};
	}
} // namespace bridges

#endif
