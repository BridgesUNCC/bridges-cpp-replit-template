#ifndef OSM_DATA

#define OSM_DATA

#include <math.h>
#include <cmath>


#include <algorithm>

//should be defined in math.h but VS2017 has a weird behavior here.
#ifndef M_PI
#define M_PI 3.1415926535897
#endif


#include <GraphAdjList.h>

#include "OSMVertex.h"
#include "OSMEdge.h"

namespace bridges {
	namespace dataset {
		using namespace bridges::datastructure;
		/**
		 * @brief  Class that hold Open Street Map Data
		 *
		 * Class that holds Open Street Map data, from https://openstreetmap.org

	     * Objects from this class are typically not created by the user 
		 *  but retruned by bridges::DataSource::getOSMData()

		 * @sa Check out how to use OSM data at: 
		 *	https://bridgesuncc.github.io/tutorials/Data_OSM.html
		 *
		 * @author Erik Saule, Kalpathi Subramanian
		 * @date 2/16/19, 12/28/20
		 */

		class OSMData {
			private:

				bool debug() const {
					return false;
				}

				string name = "";
				// data range
				double latitude_range[2] = {0.0, 0.0},
					longitude_range[2] = {0.0, 0.0};
				double cartesian_range_x[2] = {0.0, 0.0},
					cartesian_range_y[2] = {0.0, 0.0};
				// vertices
				vector<OSMVertex> vertices;
				// edges
				vector<OSMEdge> edges;

				static double degreeToRadians(double deg) {
					return deg * M_PI / 180.;
				}


				void recomputeCartesianRange() {
					cartesian_range_x[0] = 1000000.;
					cartesian_range_x[1] = -1000000.;
					cartesian_range_y[0] = 1000000.;
					cartesian_range_y[1] = -1000000.;

					OSMVertex v1 (0, latitude_range[0], longitude_range[0]);
					OSMVertex v2 (1, latitude_range[1], longitude_range[1]);
					OSMVertex v3 (2, latitude_range[0], longitude_range[1]);
					OSMVertex v4 (3, latitude_range[1], longitude_range[0]);

					//the cartesian range will always come from one of the extremities
					double coords[2];
					v1.getCartesianCoords(coords);

					cartesian_range_x[0] = (std::min)(cartesian_range_x[0], coords[0]);
					cartesian_range_x[1] = (std::max)(cartesian_range_x[1], coords[0]);
					cartesian_range_y[0] = (std::min)(cartesian_range_y[0], coords[1]);
					cartesian_range_y[1] = (std::max)(cartesian_range_y[1], coords[1]);

					v2.getCartesianCoords(coords);

					cartesian_range_x[0] = (std::min)(cartesian_range_x[0], coords[0]);
					cartesian_range_x[1] = (std::max)(cartesian_range_x[1], coords[0]);
					cartesian_range_y[0] = (std::min)(cartesian_range_y[0], coords[1]);
					cartesian_range_y[1] = (std::max)(cartesian_range_y[1], coords[1]);

					v3.getCartesianCoords(coords);

					cartesian_range_x[0] = (std::min)(cartesian_range_x[0], coords[0]);
					cartesian_range_x[1] = (std::max)(cartesian_range_x[1], coords[0]);
					cartesian_range_y[0] = (std::min)(cartesian_range_y[0], coords[1]);
					cartesian_range_y[1] = (std::max)(cartesian_range_y[1], coords[1]);

					v4.getCartesianCoords(coords);

					cartesian_range_x[0] = (std::min)(cartesian_range_x[0], coords[0]);
					cartesian_range_x[1] = (std::max)(cartesian_range_x[1], coords[0]);
					cartesian_range_y[0] = (std::min)(cartesian_range_y[0], coords[1]);
					cartesian_range_y[1] = (std::max)(cartesian_range_y[1], coords[1]);

				}

			public:

				/**
				 *   @brief set the latitude and longitude range of the dataset
				 *
				 *   @param[in]  lat_range (array of 2 for min and max)
				 *   @param[in]  longit_range (array of 2 for min and max)
				 */
				void setLatLongRange (double *lat_range, double *longit_range) {
					latitude_range[0] = lat_range[0];
					latitude_range[1] = lat_range[1];
					longitude_range[0] = longit_range[0];
					longitude_range[1] = longit_range[1];
					recomputeCartesianRange();
				}
				/**
				 *   @brief set the range of the dataset
				 *
				 *   @param  lat_min, long_min lower left corner
				 *   @param  lat_max, long_max upper right corner
				 */
				void setLatLongRange (double lat_min, double lat_max,
					double long_min, double long_max) {
					latitude_range[0] = lat_min;
					latitude_range[1] = lat_max;
					longitude_range[0] = long_min;
					longitude_range[1] = long_max;
					recomputeCartesianRange();
				}

				/**
				 * Construct a graph out of the vertex and edge
				 * data of the OSM object.  The graph will
				 * associate the length of the edge to the
				 * graph edge. No data is bound to the
				 * vertices.
				 *
				 * The vertices of the graph will be located at
				 * the location given in the data set
				 * converted to cartesian coordinate.
				 *
				 * @param[out] gr  constructed graph from the OSM data
				 **/
				void getGraph (GraphAdjList<int, OSMVertex, double>* gr) const {
					//	vector<OSMVertex> vertices = osm_data->getVertices();
					//	vector<OSMEdge> edges = osm_data->getEdges();

					int k = 0;
					double coords[2];

					double xrange[2], yrange[2];
					this->getCartesianCoordsRange(xrange, yrange);
					if (debug()) {
						cout << "Range(Cartesian):" << xrange[0] << "," << xrange[1] <<
							yrange[0] << "," << yrange[1] << endl;
					}


					double ll[2], ur[2];
					// translation
					double tx  = xrange[0];
					double ty  = yrange[0];

					// scale factor -- assume  a display of 1000 pixels wide
					double sx = 1000. / (xrange[1] - xrange[0]);
					double sy = 1000. / (yrange[1] - yrange[0]);

					if (debug()) {
						cout << "Translate:" << tx << "," << ty << endl;
						cout << "Scale:" << sx << "," << sy << endl;
					}

					std::unordered_map<OSMVertex::OSMVertexID, int> vert_map;


					k = 0;
					for (int k = 0; k < vertices.size(); k++) {
						// Preventing multiple vertex inclusion.
						// Not sure why that would happen, but being safe.
						if (vert_map.find(vertices[k].getVertexID()) == vert_map.end()) {

							vert_map[vertices[k].getVertexID()] = k;
							gr->addVertex(k, vertices[k]);

							vertices[k].getCartesianCoords(coords);
							//coords[1] = yrange[1] - (coords[1] - yrange[0]);
							//double x = (coords[0]-tx)*sx, y = (coords[1]-ty)*sy;
							double x = coords[0];
							double y = coords[1];
							gr->getVertex(k)->getVisualizer()->setLocation( x, y);
							gr->getVertex(k)->getVisualizer()->setColor(Color("green"));
						}
					}
					for (int k = 0; k < edges.size(); k++) {
						//	  std::cout<<edges[k].getEdgeLength()<<std::endl;

						gr->addEdge(vert_map[edges[k].getSourceVertex()], vert_map[edges[k].getDestinationVertex()],
							edges[k].getEdgeLength() );
					}

					if (debug()) {
						cout << "Num vertices, Edges: " << vertices.size() << "," << edges.size() << endl;
					}

				}


				OSMData() {
				}

				/**
				 *   @brief get the name of the dataset
				 *
				 *   @return name of the dataset
				 */
				const string& getName() const {
					return name;
				}
				/**
				 *   @brief change the name of the dataset
				 *
				 *   @param n name of the data set
				 *
				 */
				void setName(const string& n) {
					name = n;
				}

				/**
				 *   get the Latitude and Longitude range of the dataset
				 *
				 *   @param[out]  lat_range latitude range
				 *   @param[out]  longit_range longitude range
				 */
				void getLatLongRange (double *lat_range, double *longit_range) const {
					lat_range[0] = latitude_range[0];
					lat_range[1] = latitude_range[1];
					longit_range[0] = longitude_range[0];
					longit_range[1] = longitude_range[1];
				}
				/**
				 *   @brief get the range of dataset in Cartesian coords
				 *
				 *   @param[out] xrange (array of 2 for min and max)
				 *   @param[out] yrange (array of 2 for min and max)
				 */
				void getCartesianCoordsRange (double *xrange, double *yrange) const {
					xrange[0] = cartesian_range_x[0];
					xrange[1] = cartesian_range_x[1];
					yrange[0] = cartesian_range_y[0];
					yrange[1] = cartesian_range_y[1];
				}

				/**
				 *   get vertices
				 *
				 *   @return  vertices (std::vector)
				 *
				 */
				const vector<OSMVertex>& getVertices () const {
					return vertices;
				}
				/**
				 *   @brief replace the vertices stored by this new set.
				 *
				 * This will adjust the lat/long range to the tightest box around the vertices
				 *
				 *   @param  verts a vector of OSMVertex to set.
				 */
				void setVertices (const vector<OSMVertex>& verts) {
					vertices = verts;
					// update the ranges for lat/long and cartesian equivalent
					latitude_range[0] = 1000000.;
					latitude_range[1] = -1000000.;
					longitude_range[0] = 1000000.;
					longitude_range[1] = -1000000.;
					double lat, longit, cart_coords[2];
					for (auto& v : vertices) {
						lat = v.getLatitude();
						longit = v.getLongitude();
						latitude_range[0] = (std::min)(latitude_range[0], lat); //The parenthesis around std::min are needed to workaround a VS2017 bug

						latitude_range[1] = (std::max)(latitude_range[0], lat);
						longitude_range[0] = (std::min)(longitude_range[1], longit);
						longitude_range[1] = (std::max)(longitude_range[1], longit);
					}
					recomputeCartesianRange();
				}

				/**
				 *   @brief get edges.
				 *
				 * Typically the roads
				 *
				 *   @return  edges (std::vector)
				 */
				const vector<OSMEdge>& getEdges () const {
					return edges;
				}

				/**
				 *   @brief set edges
				 *
				 * There is an assumption that the edges set have corresponding vertices.
				 *
				 *   @param  e a vector of OSMEdge to set
				 */
				void setEdges (const vector<OSMEdge>& e) {
					edges = e;
				}
				/**
				 * 	convert lat/long coords to Cartesian
				 *
				 *	@param[in] lat latitude
				 *	@param[in] longit longitude
				 *	@param[out] coords computed cartesian coords
				 */
				static void toCartesianCoords(double lat, double longit, double *coords) {
					const double R = 6378.; // Radius of the earth in km
					double lat_rad  = degreeToRadians(lat);
					double longit_rad  = degreeToRadians(longit);
					coords[0] = R * cos(lat_rad) * cos (longit_rad);
					coords[1] = R * cos(lat_rad) * sin (longit_rad);
				}
		};
	}
} // end namespace bridges

#endif
