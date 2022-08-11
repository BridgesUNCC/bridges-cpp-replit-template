#ifndef SERVER_COMM_H
#define SERVER_COMM_H

#include <string>
#include <vector>
using namespace std;
#include <curl/curl.h> //curl
#include "./data_src/EarthquakeUSGS.h"
#include "./data_src/Game.h"
#include "./data_src/Shakespeare.h"
#include "./data_src/GutenbergBook.h"
#include "./data_src/CancerIncidence.h"
#include "./data_src/ActorMovieIMDB.h"
#include "./data_src/Song.h"

namespace bridges {
  struct HTTPException : public std::exception{
    std::string url; //URL hit that generated the exception
    long httpcode; // The returned HTTP code
    std::string headers; //The headers returned by the HTTP server
    std::string data; //The data returned by the HTTP server

    std::string what_str;
    HTTPException (std::string url,
		   long httpcode,
		   std::string headers,
		   std::string data)
      :url(url), httpcode(httpcode), headers(headers), data(data) {
      what_str = std::string("HTTPException raised when hitting ") + url +"\n"+
	"HTTP code: "+to_string(httpcode)+"\n"+
	headers + "\n"+
	data;
    }
    ~HTTPException() = default;
    virtual const char* what() const noexcept {
      return what_str.c_str();
    }
  };
  
  /**
	 *	@brief This is a class for handling calls to the BRIDGES server to transmit
	 *		JSON to the server and subsequent visualization. It is not
	 *		intended for external use
	 */
	class ServerComm {
			//Used to access to this class private functions
			friend class Bridges;
			friend class DataSource;

			ServerComm() = delete; //Prevents instantiation

			/** CURL WRITE FUNCTION PLACEHOLDER (TODO - Replace with something
			 * 		better)
			 */
			static size_t curlWriteFunction(void *contents, size_t size,
				size_t nmemb, void *results) {
				size_t handled = size * nmemb;
				if (results) {
					((string*)results)->append((char*)contents, handled);
				}
				return handled;
			}
			/**
			 * Uses Easy CURL library to execute a simple request.
			 *
			 * @param url The url destination for the request
			 * @param headers The headers for the request
			 * @param data The content sent in POST requests
			 * @throw string Thrown if curl request fails
			 */
			static string makeRequest(const string& url, const vector<string>&
				headers, const string& data = "") {
				string results;
				string returned_headers;
				// first load curl enviornment (only need be called
				// once in entire session tho)
				curl_global_init(CURL_GLOBAL_ALL);
				CURL* curl = curl_easy_init(); // get a curl handle
				if (curl) {
					char error_buffer[CURL_ERROR_SIZE];
					CURLcode res;
					//setting verbose
					if (0) {
						res = curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
					}
					// setting error buffer
					res = curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";

					// set the URL to GET from
					res = curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					//pass pointer to callback function
					res = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &results);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					//sends all data to this function
					res = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteFunction);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";
					//sends all header to this function
					res = curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curlWriteFunction);
					//pass pointer to callback function
					res = curl_easy_setopt(curl, CURLOPT_HEADERDATA, &returned_headers);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";					
					// We should not set
					// CURLOPT_FAILONERROR because
					// we want the full content of
					// the returned document and
					// headers that may contain
					// useful information
					//
					// res = curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
					// if (res != CURLE_OK)
					//   throw "curl_easy_setopt failed";
					if (data.length() > 0) {
						// Now specify the POST data
						res = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
						// Now specify the POST data size
						res = curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, data.length());
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
						//  a post request
						res = curl_easy_setopt(curl, CURLOPT_POST, 1L);
						if (res != CURLE_OK)
							throw "curl_easy_setopt failed";
					}

					struct curl_slist* curlHeaders = nullptr;
					for (const string& header : headers) {
						curlHeaders = curl_slist_append(curlHeaders, header.c_str());
					}
					res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);
					if (res != CURLE_OK)
						throw "curl_easy_setopt failed";

					// Perform the request, res will get the return code
					res = curl_easy_perform(curl);

					curl_slist_free_all(curlHeaders);

					if (res != CURLE_OK) {

					  string footer = string("Root cause: ")+string("curl_easy_perform() failed.\n")
					    + "Curl Error Code "	+ to_string(res) + "\n" + curl_easy_strerror(res) + "\n"
					    + "ErrorBuffer: " + error_buffer+"\n"
					    + "Headers: " + returned_headers + "\n"
					    + "Results: " + results + "\n";
					  throw footer;
					}

					if (res == CURLE_OK) {
					  long httpcode = -1;
					  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpcode);

					  if (httpcode >= 300) {
					    throw HTTPException(url, httpcode, returned_headers, results);
					  }					  


					  
					}
					curl_easy_cleanup(curl);
				}
				else {
					throw "curl_easy_init() failed!\nNothing retrieved from server.\n";
				}

				curl_global_cleanup();
				return results;
			}

			static std::string encodeURLPart (const std::string& s) {
				std::string returnstr;

				curl_global_init(CURL_GLOBAL_ALL);
				CURL* curl = curl_easy_init(); // get a curl handle

				char* encodedstr = curl_easy_escape (curl, s.c_str(), 0);
				returnstr = encodedstr;

				curl_free(encodedstr);

				curl_easy_cleanup(curl);
				curl_global_cleanup();

				return returnstr;
			}
	}; //server comm


}// namespace bridges
#endif
