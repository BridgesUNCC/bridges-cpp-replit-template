#include "DataStructure.h"
#include "Symbol.h"
#include <vector>

using namespace std;


#ifndef  POLYLINE_H

#define POLYLINE_H

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class defines a polyline and is part of the symbol collection.
		 *      A polyline has a set of vertices with the vertices connect by line
		 *		segments.
		 *
		 * @author David Burlinson, Kalpathi Subramanian
		 * @date 12/23/18, 7/12/19, 12/28/20
		 *
		 */

		class Polyline : public Symbol {

			protected:
				// points of the polyline
				vector<float> points;

			public:
				/**
				 *	@brief default constructor
				 */
				Polyline () {
					points.clear();
				}

				/**
				 *  @brief Construct a polyline from sequence of points
				 *  @param  pts  point sequence
				 */
				Polyline (vector<float> pts) {
					setPolyline(pts);
				}

				/**
				 *	@brief This method gets the type of the shape
				 *
				 *  @return the shape type
				 */
				virtual string getShapeType()  const override {
					return "polyline";
				}

				/**
				 * @brief This method adds a point to the polyline
				 *
				 * @param x, y : X, Y coordinates of the point
				 */
				void addPoint(float x, float y) {
					if 	((x > -INFINITY) && (x < INFINITY) &&
						(y > -INFINITY) && (y < INFINITY)) {
						points.push_back(x);
						points.push_back(y);
					}
					else {
						throw "Invalid points for polyline!";
					}
				}
				/**
				 * @brief This method returns the point list of the polyline
				 *
				 * @return points  point list of the polygon - sequence of x, y values
				 */
				vector<float> getPoints() {
					return points;
				}

				/**
				 *  @brief Construct a polyline from sequence of points
				 *  @param  pts  point sequence
				 */
				void setPolyline (vector<float> pts) {
					points = pts;
				}

				/**
				 *	@brief Get center of polyline - use its bounding box
				 *	@param[out] center of the polyline to be returned
				 */
				void getCenter(float *center) {
					float bbox[4];
					bbox[0] = bbox[1] = INFINITY;
					bbox[2] = bbox[3] = -INFINITY;
					for (int k = 0; k < points.size(); k += 2) {
						if (points[k] < bbox[0])
							bbox[0] = points[k];
						if (points[k] > bbox[2])
							bbox[2] = points[k];
						if (points[k + 1] < bbox[1])
							bbox[1] = points[k + 1];
						if (points[k + 1] > bbox[3])
							bbox[3] = points[k + 1];
					}
					center[0] = bbox[0] + (bbox[2] - bbox[0]) / 2.;
					center[1] = bbox[1] + (bbox[3] - bbox[1]) / 2.;
				}


				/**
				 * @brief This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				const string getSymbolRepresentation() const override {

					string shape_json = getSymbolAttributeRepresentation();
					string shape = getShapeType();

					// add point list to polygons
					shape_json += QUOTE + "points" + QUOTE + COLON + OPEN_BOX;
					vector<float>::iterator it;
					for (int k = 0; k < points.size(); k++) {
						shape_json += to_string(points[k]) + COMMA;
					}

					// remove last comma
					if (points.size())
						shape_json.erase(shape_json.size() - 1);
					shape_json += CLOSE_BOX + CLOSE_CURLY;

					return shape_json;
				}
		};
	}
} // namespace bridges

#endif
