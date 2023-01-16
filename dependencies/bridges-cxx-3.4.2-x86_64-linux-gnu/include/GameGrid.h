
#include <string>
using namespace std;

#ifndef GAME_GRID_H
#define GAME_GRID_H 1

#include "Grid.h"
#include "Color.h"
#include "base64.h"

namespace bridges {
	namespace game {
		enum class NamedColor : unsigned char {
			aliceblue,
			antiquewhite,
			aqua,
			aquamarine,
			azure,
			beige,
			bisque,
			black,
			blanchedalmond,
			blue,
			blueviolet,
			brown,
			burlywood,
			cadetblue,
			chartreuse,
			chocolate,
			coral,
			cornflowerblue,
			cornsilk,
			crimson,
			cyan,
			darkblue,
			darkcyan,
			darkgoldenrod,
			darkgray,
			darkgreen,
			darkgrey,
			darkkhaki,
			darkmagenta,
			darkolivegreen,
			darkorange,
			darkorchid,
			darkred,
			darksalmon,
			darkseagreen,
			darkslateblue,
			darkslategray,
			darkslategrey,
			darkturquoise,
			darkviolet,
			deeppink,
			deepskyblue,
			dimgray,
			dimgrey,
			dodgerblue,
			firebrick,
			floralwhite,
			forestgreen,
			fuchsia,
			gainsboro,
			ghostwhite,
			gold,
			goldenrod,
			gray,
			grey,
			green,
			greenyellow,
			honeydew,
			hotpink,
			indianred,
			indigo,
			ivory,
			khaki,
			lavender,
			lavenderblush,
			lawngreen,
			lemonchiffon,
			lightblue,
			lightcoral,
			lightcyan,
			lightgoldenrodyellow,
			lightgray,
			lightgreen,
			lightgrey,
			lightpink,
			lightsalmon,
			lightseagreen,
			lightskyblue,
			lightslategray,
			lightslategrey,
			lightsteelblue,
			lightyellow,
			lime,
			limegreen,
			linen,
			magenta,
			maroon,
			mediumaquamarine,
			mediumblue,
			mediumorchid,
			mediumpurple,
			mediumseagreen,
			mediumslateblue,
			mediumspringgreen,
			mediumturquoise,
			mediumvioletred,
			midnightblue,
			mintcream,
			mistyrose,
			moccasin,
			navajowhite,
			navy,
			oldlace,
			olive,
			olivedrab,
			orange,
			orangered,
			orchid,
			palegoldenrod,
			palegreen,
			paleturquoise,
			palevioletred,
			papayawhip,
			peachpuff,
			peru,
			pink,
			plum,
			powderblue,
			purple,
			red,
			rosybrown,
			royalblue,
			saddlebrown,
			salmon,
			sandybrown,
			seagreen,
			seashell,
			sienna,
			silver,
			skyblue,
			slateblue,
			slategray,
			slategrey,
			snow,
			springgreen,
			steelblue,
			tan,
			teal,
			thistle,
			tomato,
			turquoise,
			violet,
			wheat,
			white,
			whitesmoke,
			yellow,
			yellowgreen
		};

		enum class NamedSymbol : unsigned char {
			none,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			a,
			b,
			c,
			d,
			e,
			f,
			g,
			h,
			i,
			j,
			k,
			l,
			m,
			n,
			o,
			p,
			q,
			r,
			s,
			t,
			u,
			v,
			w,
			x,
			y,
			z,
			zero,
			one,
			two,
			three,
			four,
			five,
			six,
			seven,
			eight,
			nine,
			empty0,
			circle,
			square,
			diamond,
			triangle_down,
			triangle_up,
			triangle_left,
			triangle_right,
			man,
			woman,
			cat,
			pawn,
			knight,
			bishop,
			rook,
			queen,
			king,
			arrow_right,
			arrow_left,
			arrow_up,
			arrow_down,
			star,
			droplet,
			heart,
			lightning,
			thoughtbubble,
			speechbubble,
			flower,
			square_thatch,
			circle_x,
			circle_x2,
			circle_segment,
			empty1,
			sword,
			horn_helmet,
			astro_helmet,
			target,
			empty2,
			waves,
			rain,
			drink,
			paperclip,
			elephant,
			cowboyhat,
			ballcap,
			flag,
			bomb,
			bear,
			giraffe,
			bug1,
			bug2,
			bug3,
			magnifying_glass,
			fishes,
			duck,
			sloth,
			bird,
			apple,
			carrot,
			lemon,
			pepper,
			onion,
			potion1,
			potion2,
			bow_and_arrow,
			campfire,
			donut,
			monitor
		};

		/**
		 * @brief This class represents a single cell of the Game Grid.
		 *
		 * This class is part of the Bridges Game API
		 * Each cell of the game grid contains background and foreground colors,
		 * and a symbol. Refer to the  NamedColor and NamedSymbol definitions
		 * for a list of colors and symbols that can be used.
		 *
		 * @sa See the detailed BRIDGES game tutorial for examples at
		 * https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		 *
		 * @author Erik Saule,
		 * @date 2018, 2019, 12/28/20
		 */
		class GameCell {
				NamedColor bg;
				NamedColor fg;
				NamedSymbol symbol;

			public:
				/// constructor
				GameCell() {
					bg = NamedColor::black;
					fg = NamedColor::white;
					symbol = NamedSymbol::none;
				}

				/// constructor
				/// @param bg background color
				/// @param fg foreground color
				/// @param symbol symbol a this cell
				GameCell(NamedColor bg, NamedColor fg, NamedSymbol symbol) {
					this->bg = bg;
					this->fg = fg;
					this->symbol = symbol;
				}

				/**
				 *  @brief Set background color using NamedColor Enum argument
				 *  @param bg - Named Color from the NamedColor enum
				 */
				void setBGColor(NamedColor bg) {
					this->bg = bg;
				}

				/**
				 *  @brief Set foreground color using NamedColor Enum argument
				 *  @param fg - Named Color from the NamedColor enum
				 */
				void setFGColor(NamedColor fg) {
					this->fg = fg;
				}

				/**
				 *  @brief Set symbol using int argument
				 *  @param s - Named symbol
				 */
				void setSymbol(NamedSymbol s) {
					this->symbol = s;
				}

				/**
				 *  @brief Get background color of cell
				 *  @return background color of cell
				 */
				NamedColor getBGColor() const {
					return bg;
				}

				/**
				 *  @brief Get foreground color of cell
				 *  @return foreground color of cell
				 */
				NamedColor getFGColor() const {
					return fg;
				}

				/**
				 *  @brief Get cell symbol
				 *  @return symbol at this cell
				 */
				NamedSymbol getSymbol() const {
					return symbol;
				}

		};



		//TODO: implement RLE encoding
		/**
		 * @brief This is a class in BRIDGES for representing an (n x n)game grid.
		 *
		 *	This class is part of the Bridges Game API
		 *
		 * @sa See the detailed Bridges game tutorial for examples at
		 * https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		 *
		 * @author Erik Saule,
		 * @date 2018, 2019, 12/28/20
		 *
		 */
		class GameGrid : public Grid<GameCell> {
			private:
				std::string encoding = "raw";

				void initializeGrid() {
					for (int i = 0; i < gridSize[0]; i++) {
						for (int j = 0; j < gridSize[1]; j++) {
							setBGColor(i, j, NamedColor::black);
							setFGColor(i, j, NamedColor::black);
							setSymbol(i, j, NamedSymbol::none);
						}
					}
				}
			public:


				/**
				 *  Set background color of a cell using an enum argument
				 *
				 *  @param row, col - integer indices specifying the position to modify
				 *  @param color - Named Color enum argument to set the background at the chosen position
				 */
				void setBGColor(int row, int col, NamedColor color) {
					(*this)[row][col].setBGColor(color);
				}

				NamedColor getBGColor(int row, int col) const {
					return (*this)[row][col].getBGColor();
				}

				NamedColor getFGColor(int row, int col) const {
					return (*this)[row][col].getFGColor();
				}

				NamedSymbol getSymbol(int row, int col) const {
					return (*this)[row][col].getSymbol();
				}


				/**
				 *  Set foreground color of a cell using an enum argument
				 *
				 *  @param row, col - integer indices specifying the position to modify
				 *  @param color - Named Color enum argument to set the foreground at the chosen position
				 */
				void setFGColor(int row, int col, NamedColor color) {
					(*this)[row][col].setFGColor(color);
				}

				/**
				 *  Set the symbol of a cell using an enum argument
				 *
				 *  @param row, col - integer indices specifying the position to modify
				 *  @param symbol - the symbol to set
				 */
				void setSymbol(int row, int col, NamedSymbol symbol) {
					(*this)[row][col].setSymbol(symbol);
				}


				/**
				 *  Draw a symbol at the specified location
				 *  @param row, col - integer indices specifying the position to modify
				 *  @param symbol  Symbol to draw
				 *  @param color Color to draw the symbol in
				 */
				void drawSymbol(int row, int col,
					NamedSymbol symbol, NamedColor color) {
					setFGColor(row, col, color);
					setSymbol(row, col, symbol);
				}


				virtual const string getDStype() const override {
					return "GameGrid";
				}

				/**
				 * GameGrid constructors
				 *
				 **/
				GameGrid (int nbrow = 10, int nbcol = 10)
				  : Grid<GameCell> (nbrow, nbcol) {
					initializeGrid();
				}

		  GameGrid (const GameGrid &) = delete;

		  virtual ~GameGrid() = default;
		  
			private:

				//public:

				string getRAWRepresentation() const {
					using bridges::JSONUtil::JSONencode;

					std::vector<unsigned char> bgbuf;
					std::vector<unsigned char> fgbuf;
					std::vector<unsigned char> symbolbuf;

					for (int i = 0; i < gridSize[0]; i++) {
						for (int j = 0; j < gridSize[1]; j++) {
							bgbuf.push_back(static_cast<unsigned char>(getBGColor(i, j)));
							fgbuf.push_back(static_cast<unsigned char>(getFGColor(i, j)));
							symbolbuf.push_back(static_cast<unsigned char>(getSymbol(i, j)));
						}
					}

					std::string bgstr = base64::encode (&(bgbuf[0]), bgbuf.size());
					std::string fgstr = base64::encode (&(fgbuf[0]), fgbuf.size());
					std::string symbolstr = base64::encode (&(symbolbuf[0]), symbolbuf.size());


					std::string ret;
					// Add the representation of the gamegrid
					ret += QUOTE + "bg" + QUOTE + COLON + QUOTE + bgstr + QUOTE + COMMA;
					ret += QUOTE + "fg" + QUOTE + COLON + QUOTE + fgstr + QUOTE + COMMA;
					ret += QUOTE + "symbols" + QUOTE + COLON + QUOTE + symbolstr + QUOTE;

					return ret;
				}

			public:
				/**
				 * get the JSON representation of the game grid
				 *
				 * @return the JSON representation of the game grid
				 **/
				virtual const string getDataStructureRepresentation () const override {
					std::string json_str;
					// specify the encoding
					json_str = QUOTE + "encoding" + QUOTE + COLON + QUOTE + encoding + QUOTE + COMMA;

					// specify the dimensions of the gamegrid
					json_str += QUOTE + "dimensions" + QUOTE + COLON +
						OPEN_BOX + std::to_string(gridSize[0]) + "," + std::to_string(gridSize[1]) + CLOSE_BOX + COMMA;


					json_str += getRAWRepresentation();

					return json_str + CLOSE_CURLY;
				}


		};
	}
} // end namespace bridges

#endif
