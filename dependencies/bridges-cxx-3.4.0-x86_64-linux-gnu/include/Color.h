#ifndef COLOR_H
#define COLOR_H

#include <iostream> //cerr
#include <array> //array
#include <regex> //regex
#include <unordered_map> //unordered_map
#include <cmath> //log

#include <sstream>
#include <iomanip>

#include "DataStructure.h" //string, using std
#include <JSONutil.h>


namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class represents Color, and supports rgba, hexadecimal and named
		 *color values
		 *
		 * This class contains functions for the manipulation of a Color representation.
		 *
		 * Supported rgba colors are integer representations of each color channel,
		 * in the range of [0,255].
		 * rgb input is also supported, and given a default alpha value of 255 (opaque)
		 *
		 * Supported Hexadecimal colors are in the form "#RRGGBBAA", "#RRGGBB", "#RGBA", or "#RGB".
		 * With R,G,B and A, representing the Red, Green, Blue, and Alpha color channels
		 * respectivly,
		 * in hexadecimal digits(0-9a-f, base 16) prefixed by '#'.
		 * "#RGBA" and "#RGB" are shorthand versions of "#RRGGBBAA" and "#RRGGBB", where each
		 * channel pair is the same.
		 * If no alpha channel is provided, a default of 'ff'(opaque) will be used
		 *
		 * Supported named colors are as follows and illustrated at
		 * Supported named colors are listed here: https://drafts.csswg.org/css-color-3/#svg-color
		 *

		 * <b> aliceblue, antiquewhite,
		 * cyan, aquamarine, azure, beige, bisque, black, blanchedalmond, blue, blueviolet, brown, burlywood, cadetblue, chartreuse, chocolate, coral, cornflowerblue, cornsilk, crimson, darkblue, darkcyan, darkgoldenrod, darkgrey, darkgreen, darkkhaki, darkmagenta, darkolivegreen, darkorange, darkorchid, darkred, darksalmon, darkseagreen, darkslateblue, darkslategrey, darkturquoise, darkviolet, deeppink, deepskyblue, dimgrey, dodgerblue, firebrick, floralwhite, forestgreen, magenta, gainsboro, ghostwhite, gold, goldenrod, grey, green, greenyellow, honeydew, hotpink, indianred, indigo, ivory, khaki, lavender, lavenderblush, lawngreen, lemonchiffon, lightblue, lightcoral, lightcyan, lightgoldenrodyellow, lightgrey, lightgreen, lightpink, lightsalmon, lightseagreen, lightskyblue, lightslategrey, lightsteelblue, lightyellow, lime, limegreen, linen, maroon, mediumaquamarine, mediumblue, mediumorchid, mediumpurple, mediumseagreen, mediumslateblue, mediumspringgreen, mediumturquoise, mediumvioletred, midnightblue, mintcream, mistyrose, moccasin, navajowhite, navy, oldlace, olive, olivedrab, orange, orangered, orchid, palegoldenrod, palegreen, paleturquoise, palevioletred, papayawhip, peachpuff, peru, pink, plum, powderblue, purple, red, rosybrown, royalblue, saddlebrown, salmon, sandybrown, seagreen, seashell, sienna, silver, skyblue, slateblue, slategrey, snow, springgreen, steelblue, tan, teal, thistle, tomato, turquoise, violet, wheat, white, whitesmoke, yellow, yellowgreen
		 * </b>
		 *
		 * All named colors have are fully opaque by default.
		 *
		 * Default Color is opaque white
		 *
		 * @date 7/8/19, Kalpathi Subramanian
		 */
		class Color {
			private:
				// The named colors' rgba channel value mappings
				static const unordered_map<string, const array<int, 4>>&
				ColorNames() {
					static unordered_map<string, const array<int, 4>> cn {

						{	{"aliceblue", {{240, 248, 255, 255}}},
							{"antiquewhite", {{250, 235, 215, 255}}},
							{"cyan", {{0, 255, 255, 255}}},
							{"aquamarine", {{127, 255, 212, 255}}},
							{"azure", {{240, 255, 255, 255}}},
							{"beige", {{245, 245, 220, 255}}},
							{"bisque", {{255, 228, 196, 255}}},
							{"black", {{0, 0, 0, 255}}},
							{"blanchedalmond", {{255, 235, 205, 255}}},
							{"blue", {{0, 0, 255, 255}}},
							{"blueviolet", {{138, 43, 226, 255}}},
							{"brown", {{165, 42, 42, 255}}},
							{"burlywood", {{222, 184, 135, 255}}},
							{"cadetblue", {{95, 158, 160, 255}}},
							{"chartreuse", {{127, 255, 0, 255}}},
							{"chocolate", {{210, 105, 30, 255}}},
							{"coral", {{255, 127, 80, 255}}},
							{"cornflowerblue", {{100, 149, 237, 255}}},
							{"cornsilk", {{255, 248, 220, 255}}},
							{"crimson", {{220, 20, 60, 255}}},
							{"darkblue", {{0, 0, 139, 255}}},
							{"darkcyan", {{0, 139, 139, 255}}},
							{"darkgoldenrod", {{184, 134, 11, 255}}},
							{"darkgrey", {{169, 169, 169, 255}}},
							{"darkgreen", {{0, 100, 0, 255}}},
							{"darkkhaki", {{189, 183, 107, 255}}},
							{"darkmagenta", {{139, 0, 139, 255}}},
							{"darkolivegreen", {{85, 107, 47, 255}}},
							{"darkorange", {{255, 140, 0, 255}}},
							{"darkorchid", {{153, 50, 204, 255}}},
							{"darkred", {{139, 0, 0, 255}}},
							{"darksalmon", {{233, 150, 122, 255}}},
							{"darkseagreen", {{143, 188, 143, 255}}},
							{"darkslateblue", {{72, 61, 139, 255}}},
							{"darkslategrey", {{47, 79, 79, 255}}},
							{"darkturquoise", {{0, 206, 209, 255}}},
							{"darkviolet", {{148, 0, 211, 255}}},
							{"deeppink", {{255, 20, 147, 255}}},
							{"deepskyblue", {{0, 191, 255, 255}}},
							{"dimgrey", {{105, 105, 105, 255}}},
							{"dodgerblue", {{30, 144, 255, 255}}},
							{"firebrick", {{178, 34, 34, 255}}},
							{"floralwhite", {{255, 250, 240, 255}}},
							{"forestgreen", {{34, 139, 34, 255}}},
							{"magenta", {{255, 0, 255, 255}}},
							{"gainsboro", {{220, 220, 220, 255}}},
							{"ghostwhite", {{248, 248, 255, 255}}},
							{"gold", {{255, 215, 0, 255}}},
							{"goldenrod", {{218, 165, 32, 255}}},
							{"grey", {{128, 128, 128, 255}}},
							{"green", {{0, 128, 0, 255}}},
							{"greenyellow", {{173, 255, 47, 255}}},
							{"honeydew", {{240, 255, 240, 255}}},
							{"hotpink", {{255, 105, 180, 255}}},
							{"indianred", {{205, 92, 92, 255}}},
							{"indigo", {{75, 0, 130, 255}}},
							{"ivory", {{255, 255, 240, 255}}},
							{"khaki", {{240, 230, 140, 255}}},
							{"lavender", {{230, 230, 250, 255}}},
							{"lavenderblush", {{255, 240, 245, 255}}},
							{"lawngreen", {{124, 252, 0, 255}}},
							{"lemonchiffon", {{255, 250, 205, 255}}},
							{"lightblue", {{173, 216, 230, 255}}},
							{"lightcoral", {{240, 128, 128, 255}}},
							{"lightcyan", {{224, 255, 255, 255}}},
							{"lightgoldenrodyellow", {{250, 250, 210, 255}}},
							{"lightgrey", {{211, 211, 211, 255}}},
							{"lightgreen", {{144, 238, 144, 255}}},
							{"lightpink", {{255, 182, 193, 255}}},
							{"lightsalmon", {{255, 160, 122, 255}}},
							{"lightseagreen", {{32, 178, 170, 255}}},
							{"lightskyblue", {{135, 206, 250, 255}}},
							{"lightslategrey", {{119, 136, 153, 255}}},
							{"lightsteelblue", {{176, 196, 222, 255}}},
							{"lightyellow", {{255, 255, 224, 255}}},
							{"lime", {{0, 255, 0, 255}}},
							{"limegreen", {{50, 205, 50, 255}}},
							{"linen", {{250, 240, 230, 255}}},
							{"maroon", {{128, 0, 0, 255}}},
							{"mediumaquamarine", {{102, 205, 170, 255}}},
							{"mediumblue", {{0, 0, 205, 255}}},
							{"mediumorchid", {{186, 85, 211, 255}}},
							{"mediumpurple", {{147, 112, 219, 255}}},
							{"mediumseagreen", {{60, 179, 113, 255}}},
							{"mediumslateblue", {{123, 104, 238, 255}}},
							{"mediumspringgreen", {{0, 250, 154, 255}}},
							{"mediumturquoise", {{72, 209, 204, 255}}},
							{"mediumvioletred", {{199, 21, 133, 255}}},
							{"midnightblue", {{25, 25, 112, 255}}},
							{"mintcream", {{245, 255, 250, 255}}},
							{"mistyrose", {{255, 228, 225, 255}}},
							{"moccasin", {{255, 228, 181, 255}}},
							{"navajowhite", {{255, 222, 173, 255}}},
							{"navy", {{0, 0, 128, 255}}},
							{"oldlace", {{253, 245, 230, 255}}},
							{"olive", {{128, 128, 0, 255}}},
							{"olivedrab", {{107, 142, 35, 255}}},
							{"orange", {{255, 165, 0, 255}}},
							{"orangered", {{255, 69, 0, 255}}},
							{"orchid", {{218, 112, 214, 255}}},
							{"palegoldenrod", {{238, 232, 170, 255}}},
							{"palegreen", {{152, 251, 152, 255}}},
							{"paleturquoise", {{175, 238, 238, 255}}},
							{"palevioletred", {{219, 112, 147, 255}}},
							{"papayawhip", {{255, 239, 213, 255}}},
							{"peachpuff", {{255, 218, 185, 255}}},
							{"peru", {{205, 133, 63, 255}}},
							{"pink", {{255, 192, 203, 255}}},
							{"plum", {{221, 160, 221, 255}}},
							{"powderblue", {{176, 224, 230, 255}}},
							{"purple", {{128, 0, 128, 255}}},
							{"red", {{255, 0, 0, 255}}},
							{"rosybrown", {{188, 143, 143, 255}}},
							{"royalblue", {{65, 105, 225, 255}}},
							{"saddlebrown", {{139, 69, 19, 255}}},
							{"salmon", {{250, 128, 114, 255}}},
							{"sandybrown", {{244, 164, 96, 255}}},
							{"seagreen", {{46, 139, 87, 255}}},
							{"seashell", {{255, 245, 238, 255}}},
							{"sienna", {{160, 82, 45, 255}}},
							{"silver", {{192, 192, 192, 255}}},
							{"skyblue", {{135, 206, 235, 255}}},
							{"slateblue", {{106, 90, 205, 255}}},
							{"slategrey", {{112, 128, 144, 255}}},
							{"snow", {{255, 250, 250, 255}}},
							{"springgreen", {{0, 255, 127, 255}}},
							{"steelblue", {{70, 130, 180, 255}}},
							{"tan", {{210, 180, 140, 255}}},
							{"teal", {{0, 128, 128, 255}}},
							{"thistle", {{216, 191, 216, 255}}},
							{"tomato", {{255, 99, 71, 255}}},
							{"turquoise", {{64, 224, 208, 255}}},
							{"violet", {{238, 130, 238, 255}}},
							{"wheat", {{245, 222, 179, 255}}},
							{"white", {{255, 255, 255, 255}}},
							{"whitesmoke", {{245, 245, 245, 255}}},
							{"yellow", {{255, 255, 0, 255}}},
							{"yellowgreen", {{154, 205, 50, 255}}}
						}
					};
					return cn;
				}

				// The rgba channel values of this Color
				array<int, 4> channels{{255, 255, 255, 255}};
			public:
				/**
				 *  Default constructor
				 *  Defaults to black
				 */
				Color() {
					setRed(0);
					setGreen(0);
					setBlue(0);
					setAlpha(255);
				}
				/**
				 * Constructs a color with the specified rgba color channel values [0,255].
				 * If no alpha channel is provided, the default of 255(opaque) is used.
				 *
				 * @param r The red channel
				 * @param g The green channel
				 * @param b The blue channel
				 * @param a The alpha channel(default 255)
				 */
				Color(const int r, const int g, const int b, const int a = 255) {
					setValue(r, g, b, a);
				}
				/**
				 * Constructs a color from a named color or a "#hexadecimal" [0-F](base 16)
				 * of the form "#RRGGBBAA", "#RRGGBBAA", "#RGBA", or "#RGB".
				 * Named colors and "#hexadecimals" missing an alpha channel are made opaque.
				 *
				 * @param name The named color or "#hexadecimal" value
				 */
				Color(const string& name) {
					setValue(name);
				}
				/**
				 * Equality Comparison Operator
				 * @return True if both Colors represent the same Color, false if not
				 */
				bool operator==(const Color& that) const {
					return channels == that.channels;
				}
				/**
				 * Inequality Comparison Operator
				 * @return False if both Colors represent the same Color, true if not
				 */
				bool operator!=(const Color& that) const {
					return channels != that.channels;
				}
				/** @return True if fully opaque, false if not */
				bool isOpaque()  const {
					return getAlpha() == 255;
				}
				/**
				 *  Checks for transparency
				 *	@return True if fully transparent, false if not
				 */
				bool isTransparent() const {
					return getAlpha() == 0;
				}

				/**
				 * Get red component
				 * @return rgba value of the red channel [0,255]
				 */
				int getRed() const {
					return channels.at(0);
				}
				/**
				 *  Get green component
				 *	@return rgba value of the green channel [0,255]
				 */
				int getGreen() const {
					return channels.at(1);
				}
				/**
				 *  Get blue component
				 *	@return rgba value of the blue channel [0,255]
				 */
				int getBlue()  const {
					return channels.at(2);
				}
				/**
				 *  Get alpha component
				 * @return rgba value of the alpha channel [0,255]
				 */
				int getAlpha() const {
					return channels.at(3);
				}

				/** @return The "#hexadecimal" representation ("#RRGGBBAA") of this color */
				string getHexValue() const {
					std::stringstream ss;
					ss << "#";
					ss << std::hex << std::setfill('0') << std::setw(2) << getRed();
					ss << std::hex << std::setfill('0') << std::setw(2) << getGreen();
					ss << std::hex << std::setfill('0') << std::setw(2) << getBlue();
					ss << std::hex << std::setfill('0') << std::setw(2) << getAlpha();

					return ss.str();
				}
				/**
				 *	Sets red channel to "r"
				 *	@param r rgba value to set red channel
				 */
				void setRed(int r) {
					setChannel(r, 0);
				}
				/**
				 *	Sets green channel to "g"
				 * 	@param g rgba value to set green channel
				 */
				void setGreen(int g) {
					setChannel(g, 1);
				}
				/**
				 *	Sets blue channel to "b"
				 *	@param b rgba value to set blue channel
				 */
				void setBlue(int b) {
					setChannel(b, 2);
				}
				/**
				 *	Sets alpha channel to "a"
				 *	@param a rgba value to set alpha channel
				 */
				void setAlpha(int a) {
					setChannel(a, 3);
				}

				/**
				 * Sets this color's value to the specified rgba color channel values [0,255].
				 * If no alpha channel is provided, the default of 255(opaque) is used.
				 *
				 * @param r rgba value to set the red channel
				 * @param g rgba value to set the green channel
				 * @param b rgba value to set the blue channel
				 * @param a rgba value to set the alpha channel
				 */
				void setValue(int r, int g, int b, int a = 255) {
					setRed(r);
					setGreen(g);
					setBlue(b);
					setAlpha(a);
				}
				/**
				 * Sets this color's value to the value of a named color or a "#hexadecimal"
				 *  [0-F](base 16) of the form "#RRGGBBAA", "#RRGGBBAA", "#RGBA", or "#RGB".
				 * Named colors and "#hexadecimals" missing an alpha channel are made opaque.
				 *
				 * @param name The named color or "#hexadecimal" value
				 * @throw string If name is an invalid color
				 */
				void setValue(string name) {
					//marking static to avoid rebuilding the regexp every time.
					//greedy, so checks for 8(RRGGBBAA), then 6(RRGGBB) then 4(RGBA) then 3(RGB)
					static const regex HEX_RANGE("^#([[:xdigit:]]{8}|[[:xdigit:]]{6}|[[:xdigit:]]{3,4})$");

					for (char& c : name) {
						c = (char) tolower((unsigned char)c);   //convert to lowercase
					}
					auto it = ColorNames().find(name);

					if (it != ColorNames().end()) {
						channels = it->second;   //Named value
					}
					else if (regex_match(name, HEX_RANGE)) { //#Hex value
						name.erase(0, 1); //removes "#"
						// alpha value, overwritten if present by loop number
						// of chars representing a channel
						channels.at(3) = 255;
						const int chanChars = (name.size() == 3 || name.size() == 4) ? 1 : 2;
						//unit place scale factor, handles channel size variance
						const int chanMultiplier = (chanChars == 1) ? 17 : 1;
						for (size_t i = 0; i < name.size() / chanChars; i++) {
							//converts and save hex val to rgba val
							channels.at(i) = (int) strtol(name.substr(i * chanChars,
										chanChars).c_str(), nullptr, 16) * chanMultiplier;
						}
					}
					else { //invalid color
						string errStr = "Invalid Color: " + name + "\nMust be a hexadecimal(#RRGGBBAA, #RRGGBB, #RGBA, or #RGB) color representation\nOr one of these supported named colors: ";
						for (const auto& p : ColorNames()) {
							errStr += " \"" + p.first + "\"";
						}
						errStr += "\n";
						throw errStr;
					}
				}
				const string getRepresentation () const {
					return string(
							"[" + 	to_string(getRed()) + "," +
							to_string(getGreen()) + "," +
							to_string(getBlue()) + "," +
							to_string(getAlpha()) +
							"]");
				}
				/**
				* Gets the CSS representation of this color
				*
				* @return a JSON vector of 4 dimensions that represents a CSS color in RGBA space, that is to say R, G, and B are between 0 and 255; and A is between 0 and 1
				*
				*/
				const string getCSSRepresentation() const {
					using bridges::JSONUtil::JSONencode;
					if (this->isTransparent()) {
						//leaves off other channels if transparent
						return "[0, 0, 0, 0.0]";
					}
					const string strCSS =
						JSONencode(this->getRed()) + "," +
						JSONencode(this->getGreen()) + "," +
						JSONencode(this->getBlue()) + "," +
						JSONencode( ((float) (this->getAlpha()) / 255.0f));

					return OPEN_BOX + strCSS + CLOSE_BOX;
				}

			private:

				/**
				 * Sets the channel specified by "channel" to "value"
				 *
				 * @param channel The channel to change
				 * @param value The rgba value to set the channel to
				 * @throw string Throw if value is invalid
				 */
				void setChannel(const int& value, const int& channel) {
					(value < 0 || 255 < value)
					? throw "Invalid channel parameter: " + to_string(value) +
					" Must be in the [0,255] range"
					: channels.at(channel) = value;
				}
		};//end of color class
	}
};//end of bridge namespace
#endif
