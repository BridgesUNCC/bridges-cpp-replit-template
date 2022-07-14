
#include <string>
using namespace std;

#ifndef COLOR_GRID_H
#define COLOR_GRID_H 1

#include "Grid.h"
#include "Color.h"
#include "base64.h"

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This is a class in BRIDGES for representing an image.
		 *
		 * @author David Burlinson, Kalpathi Subramanian
		 *
		 * There is a tutorial about ColorGrid :
		 * https://bridgesuncc.github.io/tutorials/Grid.html
		 **/
		class ColorGrid : public Grid<Color> {
			private:
				int debug() const {
					return 0;
				}
				Color baseColor = Color("black");

				/**
				 * @brief initializes the grid with the passed color
				 *
				 * @param col - Color object
				 *
				 **/
				void initializeGrid (const Color& col) {
					// fill elements with base color
					for (int i = 0; i < gridSize[0]; i++)
						for (int j = 0; j < gridSize[1]; j++)
							grid[i][j] = col;
				}

			public:
				virtual const string getDStype() const override {
					return "ColorGrid";
				}

				/**
				 * ColorGrid constructors
				 *
				 **/
				ColorGrid () : Grid<Color> () {
					initializeGrid(baseColor);
				}

				/**
				 * Grid constructor with size arguments
				 *
				 * @param rows the number of rows of the grid
				 * @param cols the number of columns of the grid
				 **/
				ColorGrid (int rows, int cols) : Grid<Color> (rows, cols) {
					initializeGrid(baseColor);
				}

				/**
				 * Grid constructor with size and color string argument
				 *
				 * @param rows - int representing the number of rows of the grid
				 * @param cols - int representing the number of columns of the grid
				 * @param color - Color object to use as default color
				 *
				 **/
				ColorGrid (int rows, int cols, Color color) : Grid<Color> (rows, cols) {
					baseColor = color;
					initializeGrid(color);
				}


				/**
				 * Copy Constructor
				 **/
				ColorGrid (const ColorGrid& cg)
					: Grid<Color> (cg),
					  baseColor(cg.baseColor) {
				}

				ColorGrid& operator= (const ColorGrid& cg) {
					Grid::operator=(cg);

					this->baseColor = cg.baseColor;

					return *this;
				}

				/**
				 *	Get the height of the color grid
				 *
				 *	@return the height (number of rows) of the grid
				 */
				int getHeight() {
					return gridSize[0];
				}

				/**
				 *	Get the width of the color grid
				 *
				 *	@return the width (number of columns) of the grid
				 */
				int getWidth() {
					return gridSize[1];
				}

			private:

				/**
				 * Returns a vector of BYTEs that is a RAW encoding of the ColorGrid
				 */
				std::vector<BYTE> getRAWencoding() const {
					std::vector<BYTE> byte_buf(4 * gridSize[0] * gridSize[1]);

					int k = 0;
					for (int i = 0; i < gridSize[0]; i++) {
						for (int j = 0; j < gridSize[1]; j++) {
							byte_buf[k++] = grid[i][j].getRed();
							byte_buf[k++] = grid[i][j].getGreen();
							byte_buf[k++] = grid[i][j].getBlue();
							byte_buf[k++] = grid[i][j].getAlpha();
						}
					}
					return byte_buf;

				}

				/**
				 * Returns a vector of BYTEs that is an RLE encoding of the ColorGrid
				 */
				std::vector<BYTE> getRLEencoding() const {
					std::vector<BYTE> vec;

					int count = 0;
					int totalcount = 0;
					BYTE r, g, b, a;

					auto commit = [&]() {
						if (count == 0)
							return;

						totalcount += count;

						BYTE repeat = (BYTE) (count - 1);

						if (debug() > 1)
							std::cerr << "RLEencodingstream: " << (int)repeat << " " << (int)r << " " << (int)g << " " << (int)b << " " << (int)a << std::endl;

						vec.push_back(repeat);
						vec.push_back(r);
						vec.push_back(g);
						vec.push_back(b);
						vec.push_back(a);

						count = 0;
					};

					int pos = 0;
					while (pos < gridSize[0]*gridSize[1]) {

						int posX = pos / gridSize[1];
						int posY = pos % gridSize[1];
						BYTE lr = grid[posX][posY].getRed();
						BYTE lg = grid[posX][posY].getGreen();
						BYTE lb = grid[posX][posY].getBlue();
						BYTE la = grid[posX][posY].getAlpha();

						if (count == 0) {
							count = 1;
							r = lr;
							g = lg;
							b = lb;
							a = la;
						}
						else {
							if (r == lr &&
								g == lg &&
								b == lb &&
								a == la) { //same color than previous pixel
								count++;
							}
							else { //different color than previous pixel
								commit();
								count = 1;
								r = lr;
								g = lg;
								b = lb;
								a = la;
							}
						}

						if (count == 256) {
							commit();
						}

						pos++;
					}
					//there could be something uncommitted at this point.
					commit();

					if (totalcount != gridSize[0]*gridSize[1])
						throw "what happened in RLE construction?";

					if (debug())
						std::cerr << "RLE length: " << vec.size()
							<< " raw length: " << gridSize[0]*gridSize[1] * 4
							<< " Compression rate:" << (float)(vec.size()) / (gridSize[0]*gridSize[1] * 4)
							<< std::endl;
					return vec;
				}

				//public:
				/**
				 * get the JSON representation of the color grid
				 *
				 * @return the JSON representation of the color grid
				 **/
				virtual const string getDataStructureRepresentation () const override {
					using bridges::JSONUtil::JSONencode;

					// Maintain a bytebuffer for the byte representations of each grid color
					std::vector<BYTE> byte_buf = getRLEencoding();
					std::string encoding = "RLE";
					if ((int)(byte_buf.size()) > gridSize[0]*gridSize[1] * 4) {
						encoding = "RAW";
						byte_buf = getRAWencoding();
						if (debug())
							std::cerr << "encoding ColorGrid as RAW" << std::endl;
					}
					else {
						if (debug())
							std::cerr << "encoding ColorGrid as RLE" << std::endl;
					}

					// set the grid dimensions for the visualizer
					// get the base64 representation of the color array
					string grid_json  =
						QUOTE + "encoding" + QUOTE + COLON + QUOTE + encoding + QUOTE + COMMA +
						QUOTE + "dimensions" + QUOTE + COLON +
						OPEN_BOX +
						JSONencode(gridSize[0]) + COMMA + JSONencode(gridSize[1]) +
						CLOSE_BOX + COMMA +

						QUOTE + "nodes" + QUOTE + COLON +
						OPEN_BOX + QUOTE +
						base64::encode (&(byte_buf[0]), byte_buf.size()) +
						QUOTE + CLOSE_BOX +
						CLOSE_CURLY;


					return grid_json;
				}


		};
	}
} // end namespace bridges

#endif
