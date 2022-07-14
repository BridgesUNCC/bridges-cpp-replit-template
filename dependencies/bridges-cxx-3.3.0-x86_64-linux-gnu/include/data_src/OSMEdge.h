#ifndef OSM_EDGE_H

#define OSM_EDGE_H

#include <string>
#include "./data_src/OSMVertex.h"


using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  Class that hold Open Street Map edges
		 *
		 * Class that holds Open Street Map edges from https://openstreetmap.org
		 *
		 * Objects from this class are typically not created by the user but 
		 * contained in the OsmData object returned by 
		 * bridges::DataSource::getOSMData()

		 * @sa Check out how to use OSM data at: 
		 *	https://bridgesuncc.github.io/tutorials/Data_OSM.html
		 *
		 * @author Erik Saule, Kalpathi Subramanian
		 * @date 2/14/19, 12/28/20
		 */
		class OSMEdge {

			private:
				// edge vertices
				OSMVertex::OSMVertexID src_vertex = 0;
				OSMVertex::OSMVertexID dest_vertex = 0;
				// edge length
				double length = 0.0;

			public:
				/**
				 * Constructor
				 * @param src  source vertex of  edge
				 * @param dest  destination vertex of  edge
				 * @param dist length of edge
				 */
				OSMEdge(OSMVertex::OSMVertexID src, OSMVertex::OSMVertexID dest,
					double dist) : src_vertex(src), dest_vertex(dest),
					length(dist) {
				}

				/**
				 * Constructor
				 * @param edge  edge data to be used for this edge
				 */
				OSMEdge(const OSMEdge *edge) : src_vertex(edge->src_vertex),
					dest_vertex(edge->dest_vertex), length(edge->length) {
				}

				/**
				 *	get source vertex  of edge
				 *
				 *	@return source vertexID
				 */
				OSMVertex::OSMVertexID getSourceVertex() const {
					return src_vertex;
				}
				/**
				 *	set source vertex  of edge
				 *
				 *	@param src source vertexID
				 */
				void setSourceVertex(OSMVertex::OSMVertexID src) {
					src_vertex = src;
				}
				/**
				 *	get destination vertex of edge
				 *
				 *	@return destination vertexID
				 */
				OSMVertex::OSMVertexID getDestinationVertex() const {
					return dest_vertex;
				}
				/**
				 *	set destination vertex of edge
				 *
				 *	@param dest destination vertexID
				 */
				void setDestinationVertex(OSMVertex::OSMVertexID dest) {
					this->dest_vertex = dest;
				}
				/**
				 *	get edge length of edge
				 *
				 *	@return edge length
				 */
				double getEdgeLength() const {
					return length;
				}
				/**
				 *	set edge length
				 *
				 *	@param l edge length
				 */
				void setEdgeLength(double l) {
					this->length = l;
				}
		};
	}
} // namespace bridges

#endif
