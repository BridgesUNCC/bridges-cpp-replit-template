#ifndef BRIDGES_H
#define BRIDGES_H

#include <iostream>
#include <algorithm>
using namespace std;

#include "DataStructure.h" //string, using std
#include "ServerComm.h" //vector

#include <JSONutil.h>
#include <alltypes.h>
#include <chrono>



namespace bridges {
	using namespace bridges::datastructure;

	namespace game {
		class SocketConnection;
	}
	/**
	 * @brief This class contains methods to connect and transmit a user's
	 *  data structure representation to the Bridges server
	 *
	 * If the FORCE_BRIDGES_APIKEY environment variable is set,
	 * use the environment variable as APIkey in all cases.
	 *
	 * If the FORCE_BRIDGES_USERNAME environment variable is set,
	 * use the environment variable as username in all cases.
	 *
	 * If the FORCE_BRIDGES_ASSIGNMENT environment variable is set,
	 * use the environment variable as assignment number in all cases.
	 *
	 * If the FORCE_BRIDGES_APISERVER environment variable is set,
	 * use the environment variable as API server in all cases.
	 *
	 * @author Kalpathi Subramanian, Dakota Carmer, Erik Saule
	 * @date  7/26/15, 6/5/17, 10/30/18, 7/12/19
	 */
	class Bridges {
		private:
			static bool profile() {
				return false;
			}


			static string getDefaultServerURL() {
				return "http://bridges-cs.herokuapp.com";
			}

			bool jsonFlag = false;   				// if JSON is to be printed

			bool post_visualization_link = true;	// post flag of visualization url

			string user_name = string(),
				   api_key = string(); 				// user credentials

			string description = string();			// visualization description

			string title = string();							// title of visualization

			unsigned int assn_num = 0;				// assignment id

			DataStructure* ds_handle = nullptr;  	// data structure handle

			string server_url = "http://bridges-cs.herokuapp.com";

			string BASE_URL = server_url + "/assignments/";

			// map overlay options
			string map_overlay_options[3] = {"cartesian", "albersusa", "equirectangular"};
			bool map_overlay = false;
			string coord_system_type = "cartesian";

			// world coordinate window
			vector<double> wc_window;

			unsigned int lastAssignNum = 0, subAssignNum = 0;


		public:
			Bridges() {
				Bridges (0, "", "");
			}
			/**
			 * @brief constructor to bridges
			 *
			 * If the FORCE_BRIDGES_APIKEY environment variable is set,
			 * use the environment variable as APIkey in all cases.
			 *
			 * If the FORCE_BRIDGES_USERNAME environment variable is set,
			 * use the environment variable as username in all cases.
			 *
			 * @param name Bridges username
			 * @param key Bridges APIKey of the name account. (Note that it is not the password, but the API Key one can find in the user profile.)
			 **/
			Bridges (const string& name, const string& key) {
				Bridges (0, name, key);
			}
			/**
			 * @brief constructor to bridges
			 *
			 *
			 * If the FORCE_BRIDGES_APIKEY environment variable is set,
			 * use the environment variable as APIkey in all cases.
			 *
			 * If the FORCE_BRIDGES_USERNAME environment variable is set,
			 * use the environment variable as username in all cases.
			 *
			 * If the FORCE_BRIDGES_ASSIGNMENT environment variable is set,
			 * use the environment variable as assignment number in all cases.
			 *
			 * If the FORCE_BRIDGES_APISERVER environment variable is set,
			 * use the environment variable as API server in all cases.
			 *
			 * @param num assignment ID
			 * @param name Bridges username
			 * @param key Bridges APIKey of the name account. (Note that it is not the password, but the API Key one can find in the user profile.)
			 **/
			Bridges (unsigned int num, const string& name, const string& key) {
				setAssignment(num);
				setUserName(name);
				setApiKey(key);
				setServer("live");
			}

			/**
			 *
			 *	@return flag indicating if JSON should be printed upon visualization
			 *
			 */
			bool getVisualizeJSONFlag() const {
				return jsonFlag;
			}

			/**
			 *  This method is used to suppress the visualization link that is
			 *  usually printed to the console
			 *
			 *  @param link_url flag that controls if the link is printed
			 *				to console
			 *	@return none
			 *
			 */
			void  postVisualizationLink(bool link_url) {
				post_visualization_link = link_url;
			}

			/**
			 *
			 *	@param flag indicating if JSON should be printed upon visualization
			 *
			 */
			void setVisualizeJSONFlag(bool flag) {
				jsonFlag = flag;
			}

			/**
			 *
			 *  Get user name
			 *	@return reference to member holding the BRIDGES username credential
			 *			for the server
			 *
			 */
			const string& getUserName() const {
				return user_name;
			}
			/**
			 *  @brief Set user name.
			 *
			 *
			 * If the FORCE_BRIDGES_USERNAME environment variable is set,
			 * use the environment variable as username in all cases.
			 *
			 *  @param  name   BRIDGES user id to set
			 */
			void setUserName(string name) {
				char* force = getenv("FORCE_BRIDGES_USERNAME");
				if (force != nullptr) {
					name = force;
				}

				user_name = name;
			}
			/**
			 *  Get API key credentials
			 *	@return BRIDGES api key credential for the server
			 *
			 */
			const string& getApiKey()  const {
				return api_key;
			}
			/**
			 * @brief Set API key credentials
			 *
			 * If the FORCE_BRIDGES_APIKEY environment
			 * variable is set, use the environment
			 * variable as key and disregard the
			 * parameter.
			 *
			 *	@param key API key to set for user
			 */
			void setApiKey(string key) {
				char* force = getenv("FORCE_BRIDGES_APIKEY");
				if (force != nullptr) {
					key = force;
				}
				api_key = key;
			}
			/**
			 *  Return assignmet id
			 *
			 *	@return assignment number for holding the visualization on the server
			 *
			 */
			unsigned int getAssignment() const {
				return assn_num;
			}
			/**
			 *  Set the assignment number
			 *
			 * If the FORCE_BRIDGES_ASSIGNMENT environment variable is set,
			 * use the environment variable as assignment number in all cases.
			 *
			 *	@param num  assignment number to set
			 *
			 */
			void setAssignment(unsigned int num) {
				char* force = getenv("FORCE_BRIDGES_ASSIGNMENT");
				if (force != nullptr) {
					num = std::atoi(force);
				}

				assn_num =  num;

				if (assn_num != lastAssignNum) { 		// reset if a new assignment
					lastAssignNum = assn_num;
					subAssignNum = 0;
				}
			}
			/**
			 *  Get the visualization title
			 *
			 *	@return title of visualization
			 *
			 */

			const string& getTitle() const {
				return title;
			}

			/**
			 *
			 *	Set  title of visualization
			 *
			 *  @param t  title of visualization
			 *
			 */
			void setTitle(const string& t) {
				title = t;
			}
			/**
			 *  Get visualization description
			 *	@return description of visualization
			 */

			const string& getDescription() const {
				return description;
			}
			/**
			 *  Set visualization description
			 *	@return descr description of visualization
			 */
			void setDescription(const string& descr) {
				description = descr;
			}

			/**
			 *
			 *  set handle to data structure
			 *
			 *  @param ds pointer to user's data Structure
			 *
			 */
			void setDataStructure(DataStructure *ds) {
				ds_handle = ds;
			}

			/**
			 *
			 *  set handle to data structure
			 *
			 *  @param ds reference to user's data Structure
			 *
			 */
			void setDataStructure(DataStructure &ds) {
				setDataStructure(&ds);
			}


			/**
			 *
			 *  @return member holding the data structure handle
			 *
			 */
			DataStructure* getDataStructure() {
				return ds_handle;
			}


			/**
			 *  Set server type
			 *
			 * If the FORCE_BRIDGES_APISERVER environment variable is set,
			 * use the environment variable as API server in all cases.
			 *
			 *  @param  server_type server to which to connect.
			 *      Options are: ['live', 'local', 'games', 'clone'], and 'live'
			 *		is the default;
			 *
			 */
			void setServer(string server_type) {
			  char* force = getenv("FORCE_BRIDGES_APISERVER");
				if (force != nullptr) {
					server_type = force;
				}

				if (server_type == "live")
					server_url = "http://bridges-cs.herokuapp.com";
				else if (server_type == "clone")
					server_url = "http://bridges-clone.herokuapp.com";
				else if (server_type == "games")
					server_url = "http://bridges-games.herokuapp.com";
				else if (server_type == "local")
					server_url = "http://127.0.0.1:3000";

				BASE_URL = server_url + "/assignments/";
			}

			/**
			 *  @brief Turns on map overlay for subsequent visualizations - used with
			 *	location specific datasets.
			 *
			 *  @param overlay_flag   true to display the map overlay
			 *
			 */
			void setMapOverlay (bool overlay_flag) {
				map_overlay = overlay_flag;
			}

			/**
			 *  Sets the coordinate system type for location specific data;
			 *	default is cartesian
			 *
			 *	@param coord    this is the desired coordinate space argument
			 *		Options are: ['cartesian', 'albersusa', 'equirectangular', 'window'].
			 *		'cartesian' is the default
			 *
			 **/
			void setCoordSystemType (string coord) {
				std::transform(coord.begin(), coord.end(), coord.begin(), ::tolower);
				if (coord == "cartesian" || coord == "albersusa" || coord == "equirectangular"
					|| coord == "window")
					coord_system_type = coord;
				else  {
					cout << "Unrecognized coordinate system \'" + coord + "\', defaulting to "
						<< "cartesian. Options:";
					for (auto proj : map_overlay_options)
						cout <<  + "\t" ;
					coord_system_type = "cartesian";
				}
			}
			/**
			 *  Gets the coordinate system type for location specific datasets
			 *
			 *	@return coord system type ; will be one of
			 *	['cartesian', 'albersUsa', 'equirectangular']. 'cartesian'
			 *
			 **/
			const string&  getCoordSystemType () {
				return coord_system_type;
			}

			/**
			 *  Sets the world coordinate window defining the space of the user
			 *	defined objects (or nodes)
			 *
			 *  @param xmin   minimum window x
			 *  @param ymin   minimum window y
			 *  @param xmax   maximum window x
			 *  @param ymax   maximum window y
			 *
			 **/
			void setWindow (int xmin, int xmax, int ymin, int ymax) {
				setWindow(double(xmin), double(xmax), double(ymin), double(ymax));
			}

			/**
			 *  @brief sets the world coordinate window defining the space of the user
			 *	defined objects (or nodes)
			 *
			 *  @param xmin   minimum window x
			 *  @param ymin   minimum window y
			 *  @param xmax   maximum window x
			 *  @param ymax   maximum window y
			 *
			 **/
			void setWindow (double xmin, double xmax, double ymin, double ymax) {
				wc_window.clear();
				wc_window.push_back(xmin);
				wc_window.push_back(xmax);
				wc_window.push_back(ymin);
				wc_window.push_back(ymax);
			}

			/**
			 *
			 * 	Sends relevant meta-data and representation of the data structure to the BRIDGES server,
			 *	and upon successful completion, prints the URL to display the Bridges visualization.
			 *
			 */
			void visualize() {
				std::chrono::time_point<std::chrono::system_clock> start;
				std::chrono::time_point<std::chrono::system_clock> end;
				std::chrono::time_point<std::chrono::system_clock> jsonbuild_start;
				std::chrono::time_point<std::chrono::system_clock> jsonbuild_end;
				std::chrono::time_point<std::chrono::system_clock> httprequest_start;
				std::chrono::time_point<std::chrono::system_clock> httprequest_end;

				if (profile())
					start = std::chrono::system_clock::now();


				if (getAssignment() != lastAssignNum) { 		// reset if a new assignment
					lastAssignNum = getAssignment();
					subAssignNum = 0;
				}
				if (subAssignNum == 99) {
					cout << "#sub-assignments limit(99) exceeded, visualization not generated .."
						<< endl;
					return;
				}
				if (!ds_handle) {
					cerr << "Error: Data Structure handle null! Visualization not generated.";
					return;
				}

				//
				// get the JSON of the data structure
				// each data structure is responsible for generating its JSON
				//
				if (profile())
					jsonbuild_start = std::chrono::system_clock::now();

				string ds_json = getJSONHeader() + ds_handle->getDataStructureRepresentation();
				if (profile())
					jsonbuild_end = std::chrono::system_clock::now();

				//
				// print JSON if flag is on
				//
				if (getVisualizeJSONFlag()) {
					cout << "JSON[" + ds_handle->getDStype() + "]:\t" << ds_json << endl;
				}

				if (profile())
					httprequest_start = std::chrono::system_clock::now();

				try {						// send the JSON of assignment to the server
					ServerComm::makeRequest(BASE_URL + to_string(getAssignment()) + "." +
						(subAssignNum > 9 ? "" : "0") + to_string(subAssignNum) + "?apikey=" + getApiKey() +
						"&username=" + getUserName(), {"Content-Type: text/plain"}, ds_json);

					if (post_visualization_link) {
						cout << "Success: Assignment posted to the server. " << endl
							<< "Check out your visualization at:" << endl << endl
							<< BASE_URL + to_string(getAssignment()) + "/" + getUserName() << endl << endl;
					}
					subAssignNum++;
				}
				catch (const string& error_str) {
					cerr << "\nPosting assignment to the server failed!" << endl
						<< error_str << endl << endl;
					cerr << "Provided Bridges Credentials:" << endl <<
						"\t User Name: " << getUserName() << endl <<
						"\t API Key: " << getApiKey() << endl <<
						"\t Assignment Number: " << getAssignment() << endl;
				}
				if (profile())
					httprequest_end = std::chrono::system_clock::now();



				if (profile()) {
					end = std::chrono::system_clock::now();

					std::chrono::duration<double> totaltime = end - start;
					std::chrono::duration<double> jsonbuildtime = jsonbuild_end - jsonbuild_start;
					std::chrono::duration<double> httptime = httprequest_end - httprequest_start;
					std::cerr << "total visualize() time:" << totaltime.count() << " seconds"
						<< " (including JSON build time: " << jsonbuildtime.count() << " seconds"
						<< " and HTTP request time: " << httptime.count() << " seconds)."
						<< std::endl;
				}
			}

		private:
			string getServerURL() const {
				return server_url;
			}


			string getJSONHeader () {
				using bridges::JSONUtil::JSONencode;

				string json_header = OPEN_CURLY +
					QUOTE + "visual" + QUOTE + COLON + JSONencode(ds_handle->getDStype()) + COMMA +
					QUOTE + "title" + QUOTE + COLON + JSONencode(getTitle()) + COMMA +
					QUOTE + "description" + QUOTE + COLON + JSONencode( getDescription()) + COMMA +
					QUOTE + "map_overlay" + QUOTE + COLON + ((map_overlay) ? "true" : "false") + COMMA +
					QUOTE + "coord_system_type" + QUOTE + COLON + JSONencode(getCoordSystemType()) +
					COMMA;

				if (wc_window.size() == 4) {		// world coord window has been specified
					json_header += QUOTE + string("window") + QUOTE + COLON + OPEN_BOX;
					json_header += std::to_string(wc_window[0]) + COMMA +
						std::to_string(wc_window[1]) + COMMA +
						std::to_string(wc_window[2]) + COMMA + std::to_string(wc_window[3]);
					json_header += CLOSE_BOX + COMMA;

				}

				return json_header;
			}

			friend DataSource;
			friend bridges::game::SocketConnection;
	};	//end of class Bridges

}	// end of bridges namespace
#endif
