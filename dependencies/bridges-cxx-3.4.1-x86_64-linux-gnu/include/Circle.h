#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;

#ifndef  CIRCLE_H

#define CIRCLE_H


namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class defines a circle and is part of the symbol collection.
		 *      A circle  has a radius
		 *
		 * @author Kalpathi Subramanian
		 * @date 12/24/18, 7/12/19
		 *
		 */
		class Circle : public Symbol {
			private:
				double center_x, center_y;
				double radius = 1.;

			public:

				/**
				 *  constructors
				 */
				Circle () {
					setCircle(0., 0., 1.);
				}

				/**
				 *  Create a circle of radius r
				 *  @param  r : radius
				 */
				Circle (double r) {
					setCircle (0., 0., r);
				}

				/**
				 *	Create a circle with  both location and radius
				 *  @param  locx, locy : center of circle
				 *  @param  r : radius
				 */
				Circle (double cx, double cy, double r) {
					center_x = cx; center_y = cy;
					if (r < 0.)
						throw "Illegal value for radius. Must be positive";
					radius = r;
				}

				/**
				 *	This method gets the type of the shape
				 *
				 *  @return shape type
				 */
				virtual string getShapeType()  const override {
					return "circle";
				}

				/**
				 * @brief This method returns the radius of the circle
				 *
				 * @return radius 
				 */
				double getRadius() {
					return radius;
				}
				/**
				 * @brief This method sets the radius of the circle
				 *
				 * @param r radius
				 */
				void setRadius(double r) {
					if (r < 0.)
						throw "Illegal value for radius. Must be positive";
					radius = r;
				}

				/**
				 * @brief This method sets the circle dimensions
				 *
				 * @param locx  x coordinat of location
				 * @param locy  y coordinat of location
				 * @param r  radius
				 */
				void setCircle (double cx, double cy, double r) {
				  setCenter(cx,cy);
					if (r < 0.)
						throw "Illegal value for radius. Must be positive";
					radius = r;
				}
				void setCenter (double cx, double cy) {
					center_x = cx;
					center_y = cy;
				}

		  
		  double getCenterX() const {
		    return center_x;
		  }
		  double getCenterY() const {
		    return center_y;
		  }
		  
				/**
				 * This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				const string getSymbolRepresentation() const override {

					string shape_json = getSymbolAttributeRepresentation();

					shape_json +=
						QUOTE + "center" + QUOTE + COLON + 
						OPEN_BOX + 
								to_string(center_x) + COMMA + to_string(center_y) +
						CLOSE_BOX + COMMA +
						QUOTE + "r" + QUOTE + COLON + to_string(radius) + CLOSE_CURLY;

					return shape_json;

				}
		};
	}
} // namespace bridges

#endif
