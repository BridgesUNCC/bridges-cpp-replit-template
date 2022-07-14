#ifndef JSON_UTIL_
#define JSON_UTIL_

#include <sstream>

struct rapidjson_exception {
	std::string why;
	std::string filename;
	int linenumber;

	rapidjson_exception(const std::string & why, const std::string& filename, const int linenumber)
		: why(why), filename(filename), linenumber(linenumber) {}

	operator std::string() const {
		std::stringstream ss;
		ss << why << " " << filename << " " << linenumber;
		return ss.str();
	}
};

#define RAPIDJSON_ASSERT(x) if (!( x )) { throw rapidjson_exception( #x, __FILE__, __LINE__ ) ;}
#define RAPIDJSON_ASSERT_THROWS

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bridges {


	namespace JSONUtil {
		///encodes whatever C++ primary type: int, float, double, bool, unsigned long int into its basic proper JSON format.
		///
		///This also works for std::string and char*: that is to say, for a string, it is escaped properly and surrounded by quotes

		template <typename T>
		inline std::string JSONencode(const T& d) {
			rapidjson::Value s;
			s.Set(d);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			std::string ss = output;
			return ss;
		}


		template <>
		inline std::string JSONencode<std::string> (const std::string& str) {

			rapidjson::Value s;
			s.SetString(rapidjson::StringRef(str.c_str()));


			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			std::string ss = output;
			return ss;
		}

		inline std::string JSONencode (const char* str) {
			rapidjson::Value s;
			s.SetString(rapidjson::StringRef(str));


			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			s.Accept(writer);

			const char* output = buffer.GetString();

			std::string ss = output;
			return ss;
		}


		//precision=-1 means to use max precision.
		//otherwise number of digits to use
		inline std::string JSONencode(const double& d, int precision = -1) {
			rapidjson::Value s;
			s.Set(d);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			if (precision > 0 )
				writer.SetMaxDecimalPlaces(precision);
			s.Accept(writer);

			const char* output = buffer.GetString();

			std::string ss = output;
			return ss;
		}

		//precision=-1 means to use max precision.
		//otherwise number of digits to use
		inline std::string JSONencode(const float& d, int precision = -1) {
			rapidjson::Value s;
			s.Set(d);

			rapidjson::StringBuffer buffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
			if (precision > 0 )
				writer.SetMaxDecimalPlaces(precision);
			s.Accept(writer);

			const char* output = buffer.GetString();

			std::string ss = output;
			return ss;
		}



	}
}

#endif
