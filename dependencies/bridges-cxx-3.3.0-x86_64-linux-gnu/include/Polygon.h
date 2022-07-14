#include "DataStructure.h"
#include "Polyline.h"
#include <vector>

using namespace std;


#ifndef  POLYGON_H

#define POLYGON_H

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class defines a polygon and is part of the symbol collection.
		 *      A polygon has a set of vertices, with vertices connected by line
		 *		segments. It differs from the polyline in the sense that the last
		 *		and first vertex are connect to close the shape.
		 *
		 * @author David Burlinson, Kalpathi Subramanian
		 * @date 12/23/18, 7/12/19, 12/28/20
		 *
		 */
		class Polygon : public Polyline {

			public:
				/**
				 * @brief default constructor
				 */
				Polygon () : Polyline() {
				}

				/**
				 * @brief constructor, given a set of points
				 * @param pts to construct polygon
				 */
				Polygon (vector<float> pts) : Polyline (pts) {
				}

				/**
				 *	@brief This method gets the type of the shape
				 *
				 *  @return the shape type
				 */
				virtual string getShapeType()  const override {
					return "polygon";
				}

				/**
				 * @brief constructs a polygon, given a set of points
				 * @param pts to construct polygon
				 */
				void setPolygon (vector<float> pts) {
					this->setPolyline(pts);
				}
		};
	}
} // namespace bridges

#endif
