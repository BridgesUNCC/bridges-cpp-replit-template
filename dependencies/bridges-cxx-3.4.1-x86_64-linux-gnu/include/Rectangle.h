#include "DataStructure.h"
#include "Symbol.h"
#include <vector>


using namespace std;

#ifndef  RECTANGLE_H

#define RECTANGLE_H

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class defines a rectangle and is part of the symbol collection.
		 *		A rectangle has height and width
		 *
		 * @author Kalpathi Subramanian
		 * @date 12/23/18, 7/12/19
		 *
		 */
		class Rectangle : public Symbol {
			private:
				// Rectangle specification: lower left corner and dimensions
				double ll_x = 0., ll_y = 0., width = 1.0, height = 1.0;
				
			public:
				/**
				 *  @brief default constructor - rectangle with lower left
				 *	 at origin and unit length sides
				 */
				Rectangle() {
					setRectangle(0., 0., 1., 1.);
				}

				/**
				 * @brief create rectangle with width w and height h
				 * @param w  width
				 * @param h  height
				 */
				Rectangle (double w, double h) {
					setRectangle (0., 0., w, h);
				}

				/**
				 * @brief create rectangle with width w and height h
				 *   and located at given position
				 * @param locx  rect lower left - x coord
				 * @param locy  rect lower left - y coord
				 * @param w  width
				 * @param h  height
				 */
				Rectangle (double llx, double lly, double w, double h) {
					setRectangle (llx, lly, w, h);
				}

				/**
				 *	@brief This method gets the shape type name
				 *
				 *  @return shape type
				 */
				virtual string getShapeType() const override {
					return "rect";
				}

				/**
				 * @brief This method gets the rectangle width
				 *
				 * @return width
				 */
				float getWidth() {
					return width;
				}
				/**
				 * @brief This method sets the shape width
				 *
				 * @param w  width
				 */
				void setWidth(double w) {
					if (w <= 0.) {
						throw "Illegal Size Value! Please enter a value in the range(0-300)";
					}
					width = w;
				}

				/**
				 * @brief This method gets the rectangle height
				 *
				 * @return height
				 */
				float getHeight() {
					return height;
				}
				/**
				 * @brief This method sets the shape height
				 *
				 * @param h  height
				 */
				void setHeight(double h) {
					if (h <= 0.) {
						throw "Illegal Size Value! Please enter a value in the range(0-300)";
					}
					height = h;
				}

				/*
				 * @brief This method sets the location and size of the rectangle
				 *
				 * @pram locx  x coordinate of location
				 * @pram locy  y coordinate of location
				 * @param w  width of rectangle
				 * @param h  height of rectangle
				 *
				 * @return none
				 */
				void setRectangle(double llx, double lly, double w, double h) {
				  setLL(llx, lly);
					setWidth(w);
					setHeight(h);
				}
		  void setLL(double llx, double lly) {
		    ll_x = llx;
		    ll_y = lly;
		  }

		  double getLLX () const {
		    return ll_x;
		  }

		  double getLLY () const {
		    return ll_y;
		  }
		  
				/**
				 * @brief This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				virtual const string getSymbolRepresentation() const override {

					string shape_json = getSymbolAttributeRepresentation();

					// set up width and height of rectangles
					shape_json += 
						QUOTE + "lowerleftcorner" + QUOTE + COLON + 
						OPEN_BOX + 
							to_string(ll_x) + COMMA + to_string(ll_y) +
						CLOSE_BOX + COMMA +
						QUOTE + "width" + QUOTE + COLON + to_string(width) + COMMA +
						QUOTE + "height" + QUOTE + COLON + to_string(height) +
						CLOSE_CURLY;

					return shape_json;

				}
		};
	}
} // namespace bridges

#endif
