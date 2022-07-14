#ifndef OSM_EDGE_H

#define OSM_EDGE_H

#include <string>

using namespace std;

namespace bridges {
	/**
	 * @brief  Class that hold Open Street Map edges
	 *
	 * Class that holds Open Street Map edges from https://openstreetmap.org
	 *
	 * Kalpathi Subramanian, 2/14/19
	 *
	 */


	class OSMEdge {

		private:
							// edge vertices
	  int src_vertex=0;
	  int dest_vertex=0;	
							// edge length
			double length=0.0;

		public:

			OSMEdge(int src, int dest, double dist) : 
				src_vertex(src), dest_vertex(dest), length(dist) {
			}

			OSMEdge(const OSMEdge *edge) : src_vertex(edge->src_vertex), 
				dest_vertex(edge->dest_vertex), length(edge->length) {
			}

			/**
			 *	get source vertex  of edge
			 *
			 *	@return int
			 *
			 */
			int getSourceVertex() const {
				return src_vertex;
			}
			/**
			 *	set source vertex  of edge
			 *
			 *	@param int
			 *
			 */
			void setSourceVertex(int src) {
				src_vertex = src;
			}
			/**
			 *	get destination vertex of edge
			 *
			 *	@return int
			 *
			 */
			int getDestinationVertex() const {
				return dest_vertex;
			}
			/**
			 *	set destination vertex of edge
			 *
			 *	@param int
			 *
			 */
			void setDestinationVertex(int dest) {
				this->dest_vertex = dest;
			}
			/**
			 *	get edge length of edge
			 *
			 *	@return double
			 *
			 */
			double getEdgeLength() const {
				return length;
			}
			/**
			 *	set edge length
			 *
			 *	@param double
			 *
			 */
			void setEdgeLength(double l) {
				this->length = l;
			}
	};

} // namespace bridges

#endif
