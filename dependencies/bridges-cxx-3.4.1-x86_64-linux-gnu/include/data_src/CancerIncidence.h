#ifndef CANCER_INCIDENCE_H

#define CANCER_INCIDENCE_H
#include <string>

using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 *  @brief A class representing the attributes for cancer incidence.
		 *
		 * 	From the United States Cancer Statistics as part of the U.S. Center for
		 *	Disease Control, the following data set focuses on the crude rate for
		 *	all types of cancer reported for different demograpic groups.
		 *	Significant groupings include age, gender, race and geographical area.
		 *
		 * 	One does not typically create an object from this type, but 
		 *	rather obtain them by calling 
		 *	bridges::DataSource::getCancerIncidenceData()

		 *  @sa Refer to tutorial examples on how to use this dataset: 
		 *	https://bridgesuncc.github.io/tutorials/Data_CancerIncidence.html <br>
		 *  Data: Courtesy of Corgis Datasets, 2017
		 *	Link: http://www.cdc.gov/cancer/npcr/uscs/download_data.htm
		 *
		 *  @author Kalpathi Subramanian
		 *	@date June, 2017
		 *
		 */

		class CancerIncidence {

			private:

				double age_adjusted_rate;		// expected cancer rate, adjusted for age
				double age_adjusted_rate_ci[2];	// confidence interval-lower,upper
				double crude_rate;				// cancer rate adjusted by population
				double crude_rate_ci[2];		// confidence interval

				int count;					// incidence count
				int year;					// reporting year
				int population;				// population of this area

				string gender; 				 // gender (male, female, male and female
				string race;
				string event_type;				 // incidence, mortality
				string affected_area;			 // location, typically, state

				double loc[2];		 	// location (cartesian coords


			public:
				CancerIncidence () {
					loc[0] = loc[1]  = 0.0;
					age_adjusted_rate_ci[0] = age_adjusted_rate_ci[1] = 0.0;
					crude_rate_ci[0] = crude_rate_ci[1] = 0.0;
				}

				/**
				 * Get the expected cancer rate, adjusted for age of participants.
				 *
				 * @return cancer rate
				 *
				 */
				double getAgeAdjustedRate() const {
					return age_adjusted_rate;
				}

				/**
				 * Set age adjusted cancer rate
				 *
				 * @param[in] aar age adjusted rate
				 */
				void setAgeAdjustedRate(double aar) {
					age_adjusted_rate = aar;
				}

				/**
				 * Get the expected cancer rate confidence interval(lower),
				 *	adjusted for age of participants.
				 *
				 * @return cancer confidence interval (lower) rate
				 *
				 */
				double getAgeAdjustedCI_Lower() const {
					return age_adjusted_rate_ci[0];
				}

				/**
				 * Set age adjusted cancer conf interval (lower)
				 *
				 * @param[in] ci_l age adjusted cancer conf interval (lower)
				 *
				 */
				void setAgeAdjustedCI_Lower(double ci_l) {
					age_adjusted_rate_ci[0] = ci_l;
				}

				/**
				 * Get the expected cancer rate confidence interval(upper),
				 *	adjusted for age of participants.
				 *
				 * @return cancer conf interval (lower) rate
				 */
				double getAgeAdjustedCI_Upper() const {
					return age_adjusted_rate_ci[1];
				}

				/**
				 * Set age adjusted cancer conf interval (upper)
				 *
				 * @param[in] ci_u age adjusted cancer conf interval (upper)
				 */
				void setAgeAdjustedCI_Upper(double ci_u) {
					age_adjusted_rate_ci[1] = ci_u;
				}

				/**
				 * Get the cancer rate, adjusted for population
				 *
				 * @return crude cancer rate
				 */
				double getCrudeRate() const {
					return crude_rate;
				}
				/**
				 * Set cancer rate, adjusted for population
				 *
				 * @param[in] cr cancer rate
				 */
				void setCrudeRate(double cr) {
					crude_rate = cr;
				}

				/**
				 * Get the expected cancer crude rate confidence interval(lower),
				 * adjusted for age of participants.
				 *
				 * @return cancer conf interval (lower) rate
				 */
				double getCrudeRate_CI_Lower() const {
					return crude_rate_ci[0];
				}

				/**
				 * Set age adjusted cancer crude conf interval (lower)
				 *
				 * @param[in] cr_l age adjusted cancer crude conf interval (lower)
				 */
				void setCrudeRate_CI_Lower(double cr_l) {
					crude_rate_ci[0] = cr_l;
				}
				/**
				 * Get the expected cancer crude rate confidence interval(upper),
				 * adjusted for age of participants.
				 *
				 * @return cancer crude rate CI (upper) rate
				 *
				 */
				double getCrudeRate_CI_Upper() const {
					return crude_rate_ci[1];
				}

				/**
				 * @brief Set crude rate CI (upper)
				 *
				 * @param[in] cr_u upper bound for crude rate confidence interval
				 *
				 */
				void setCrudeRate_CI_Upper(double cr_u) {
					crude_rate_ci[1] = cr_u;
				}

				/**
				 * @brief Get the year of this cancer record
				 *
				 * @return year of the record
				 */
				int getYear() const {
					return year;
				}

				/*
				 * @brief Set the year of this cancer record
				 *
				 * @param[in] y  year
				 */
				void setYear(int y) {
					year = y;
				}
				/**
				 * @brief Get the gender of the group
				 *
				 * @return gender, can be "male", "female", "male and female"
				 */
				string getGender() const {
					return gender;
				}
				/**
				 * @brief Set gender of the record
				 *
				 * @param[in] g gender to set
				 */
				void setGender(const string& g) {
					gender = g;
				}

				/**
				 * @brief Get the race of the group
				 *
				 * @return race (All Races, etc)
				 */
				string getRace() const {
					return race;
				}
				/**
				 * @brief Set race
				 *
				 * @param[in] r
				 */
				void setRace(const string& r) {
					race = r;
				}

				/**
				 * @brief Get the event type (incidence, mortality, etc)
				 *
				 * @return event type
				 */
				string getEventType() const {
					return event_type;
				}
				/**
				 * @brief Set event type
				 *
				 * @param et event type
				 */
				void setEventType(const string& et) {
					event_type = et;
				}

				/**
				 * @brief Get the population size
				 *
				 * @return population
				 */
				int getPopulation() const {
					return population;
				}

				/**
				 * @brief Set population size
				 *
				 * @param pop population
				 */
				void setPopulation(int pop) {
					population = pop;
				}

				/**
				 * @brief Get the cancer incidence area (state, region, etc)
				 *
				 * @return area
				 */
				string getAffectedArea() const {
					return affected_area;
				}

				/**
				 * @brief Set cancer incidenc area
				 *
				 * @param[in] area
				 */
				void setAffectedArea(const string& area) {
					affected_area = area;
				}

				/**
				 * @brief Get the number of people affected in this group
				 *
				 * @return incidence count
				 */
				int getCount() const {
					return count;
				}
				/**
				 * @brief Set cancer incidence count
				 *
				 * @param c cancer incidence count
				 */
				void setCount(int c) {
					count = c;
				}

				/**
				 * Get the X coordinate of location
				 *
				 * @return x coordinate
				 */
				double getLocationX() const {
					return loc[0];
				}
				/**
				 *	@brief Set location (X coord)
				 *
				 *	@param locX  X coordinate of location
				 */
				void setLocationX (double locX) {
					loc[0] = locX;
				}

				/**
				 * @brief Get the Y coordinate of location
				 *
				 * @return y coordinate
				 */
				double getLocationY() const {
					return loc[1];
				}

				/**
				 *	@brief Set location (Y coord)
				 *
				 *	@param locY  Y coordinate of location
				 */
				void setLocationY (double locY) {
					loc[1] = locY;
				}
		};
	}
}	// namespace bridges

#endif
