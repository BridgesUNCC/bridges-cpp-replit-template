#ifndef CACHE_H
#define CACHE_H

#ifndef _WIN32
#include <unistd.h>
#endif
#ifdef _WIN32
#include <direct.h>
#endif

namespace bridges {


	class CacheException : std::exception {
	};

	class Cache {
		public:
			virtual bool inCache(const std::string & docName) noexcept(false) = 0;
			virtual std::string getDoc (const std::string & docName) noexcept(false) = 0;
			//store content under docname
			virtual void putDoc (const std::string & docName,
				const std::string & content) noexcept(false) = 0;
	};

	class SimpleCache : public Cache {
		private:
			std::string cacheDir;

			std::string getFilename(const std::string & docName) {
				return cacheDir + "/" + docName; //TODO: bad things can happen if docName contains / or .. or stuff like that

			}

			//return whether s is a directory (true) or does not exist (false). all other cases are exception
			bool directoryExist(const std::string &s) {
				struct stat buffer;
				int ret = stat (s.c_str(), &buffer);

				if (ret == 0) { //file exist
					if ((buffer.st_mode & S_IFMT) == S_IFDIR) { //Not using S_ISDIR because VS2017 does not support it.
						return true;
					}
					else {
						throw CacheException(); //s exist but is not a directory
					}
				}

				return false;
			}

			//make a directory called s or throw an exception
			void makeDirectory (const std::string &s) {
#ifndef _WIN32
				int ret = mkdir(s.c_str(), 0700);
#endif
#ifdef _WIN32
				int ret = _mkdir(s.c_str());
#endif


				if (ret != 0)
					throw CacheException();
			}

		public:
			SimpleCache() {
				char * home = getenv("HOME"); // a reasonable location on unixes
				if (home == nullptr)
					home = getenv("LOCALAPPDATA"); // a reasonnable location on windowses

				if (home != nullptr)
					cacheDir += std::string(home) + "/";

				cacheDir += ".cache/bridges_data/cxx/";
				//probably should check directory existence here, but exception in constructors are weird.
			}

			virtual ~SimpleCache() = default;

			//is docName in the cache
			virtual bool inCache(const std::string & docName) noexcept(false) override {
				std::string filename = getFilename(docName);

				std::ifstream in(filename);

				return in.is_open();
			}

			//return the content of docName which is in the cache
			virtual std::string getDoc (const std::string & docName) noexcept(false) override {
				std::string filename = getFilename(docName);

				std::ifstream in(filename);

				if (!in.good() || !(in.is_open()))
					throw CacheException();


				std::string contents;
				in.seekg(0, std::ios::end);
				contents.resize(in.tellg());
				in.seekg(0, std::ios::beg);
				in.read(&contents[0], contents.size());
				if (! (in.good()))
					throw CacheException();
				in.close();
				return (contents);

			}

			//store content under docname
			virtual void putDoc (const std::string & docName,
				const std::string & content) noexcept(false) override {
				if (!directoryExist(cacheDir))
					makeDirectory(cacheDir);

				std::string filename = getFilename(docName);


				std::ofstream out(filename);
				if (!out.good() || !(out.is_open()))
					throw CacheException();

				out << content.c_str(); //this assumes string isn't binary
				if (!out.good() || !(out.is_open()))
					throw CacheException();

			}

			/// @brief evicts a document from the cache
			///
			/// @param docName document to evict
			/// @return true on success
			bool evict(const std::string& docName) {
				string f = cacheDir;
				f.append(docName);

				return std::remove(f.c_str()) == 0;
			}
	};


	class lruCache : public Cache {

			int maxCache;
			std::vector<std::string> v;
			SimpleCache ca;
		public:
			lruCache(int maxFileNumber = 30)
				: maxCache(maxFileNumber) {
			}

			virtual ~lruCache() = default;

			virtual std::string getDoc (const std::string& hash_value) override { //returns LRU vector from cache file
				string content;
				getLRU();
				content = ca.getDoc(hash_value);
				updateLRU(hash_value);
				saveLRU();
				return content;
			}

			virtual bool inCache(const std::string& hash_value) override {
				if (ca.inCache(hash_value)) {
					return true;
				}
				return false;
			}

			virtual void putDoc(const std::string& hash_value, const std::string& content) override { //puts hash value at front of LRU vector
				getLRU();
				ca.putDoc(hash_value, content);
				updateLRU(hash_value);

				//checks size of vector and pops lru off
				if (v.size() >= maxCache + 1) { // keeps maxCache local maps
					if (ca.evict(v[v.size() - 1]))
						v.pop_back();
				}
				saveLRU();
				return;
			}



		private:
			void updateLRU(std::string hash_value) {
				for (auto it = v.begin(); it != v.end(); ) {
					if (*it == hash_value) {
						v.erase(it); //removes old hash vlaue location in vector
						break;
					}
					else {
						++it;
					}
				}
				v.insert(v.begin(), hash_value); //puts hash value in the front of the vector
				return;
			}
			void getLRU() {
				v.clear();
				if (ca.inCache("lru")) {
					string vector_string = ca.getDoc("lru"); //Imported LRU
					std::istringstream ss(vector_string);
					std::string token;
					//Parses string and turns it into vector
					while (std::getline(ss, token, ',')) {
						v.push_back(token);
					}
				}
				return;
			}

			void saveLRU() {
				//Saves the vector to file
				string out_vector;
				int x = 0;
				for (auto s : v) {
					if (x == 0) { //prevents , from being first character
						out_vector = s;
						x++;
					}
					else {
						out_vector = out_vector + "," + s;
					}
				}
				ca.putDoc("lru", out_vector);
			}
	};
}

#endif
