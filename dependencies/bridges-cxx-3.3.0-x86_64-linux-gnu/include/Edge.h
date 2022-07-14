
#include <string>
using namespace std;

#include "LinkVisualizer.h"

#ifndef EDGE_H

#define EDGE_H

namespace bridges {

	namespace datastructure {
		/**
		 * @brief This helper class is used by the graph
		 *  classes - GraphAdjList , GraphAdjMatrix -  to keep track of edge
		 *  information
		 *
		 * This class is used to assign a visual connection between two Elements in the
		 * Bridges Visualization.
		 *
		 * Bridges will represent these as arrows between two
		 * Elements. The starting Element of the arrow will be referred to as the source
		 * Element and the ending Element of the arrow will be referred to as the
		 * terminating Element.
		 *
		 * @author Kalpathi Subramanian, Erik Saule
		 *
		 * @date 12/28/20
		 *
		 * @param E
		 */


		template <typename K, typename E2 = K>
		class Edge {
			private:
				// The source vertex of this edge */
				K fromv = K();

				// The destination vertex of this edge */
				K tov = K();

				// The application specific data of this edge */
				E2 edge_data = E2();

				// The link visualizer for this edge
				LinkVisualizer  *lvis;

			public:

				/**
				 * @brief Constructs an edge with the given destination vertex,
				 *	and edge data.
				 *
				 * This constructor is not meant to be used by the Bridges user.
				 * If an argument is not given its default is used.
				 *
				 * @param from source  vertex
				 * @param to destination  vertex
				 * @param lv LinkVisualizer storing the styling information for the edge
				 * @param data edge data
				 */
				Edge(const K& from, const K& to, LinkVisualizer* lv, const E2& data = E2()) :
					fromv(from), tov (to), edge_data(data), lvis(lv) {

				}
				~Edge() {
					//lvis lifetime is managed by the graph itself
				}

				/**
				 *  @brief Source vertex accessor
				 *
				 *	@return The source vertex
				 */
				const K& from() const {
					return fromv;
				}


				/**
				 *  @brief Destination vertex accessor
				 *	@return The terminating vertex
				 */
				const K& to() const {
					return tov;
				}

				/**
				 * 	@brief Sets edge data to "data".
				 *	@param data Application data to be set
				 */
				void setEdgeData(const E2& data) {
					edge_data = data;
				}

				/**
				 *  @brief Return the edge data.
				 *	@return The edge data
				 */
				const E2& getEdgeData() const {
					return edge_data;
				}
				/**
				 *  @brief Return the edge data.
				 *	@return The edge data
				 */
				E2& getEdgeData() {
					return edge_data;
				}
				/**
				 *  @brief Return the edge label.
				 *  @return The label of the element
				 */
				string getLabel() const {
					return lvis->getLabel();
				}

				/**
				 *  @brief Sets edge label to "lab".
				 *
				 * @param lab The label of the element
				 */
				void setLabel(const string& lab) {
					lvis->setLabel(lab);
				}

				/**
				 * @brief Change the thickness of the edge when displayed.
				 *
				 * Valid Range:[1,10] Default: 1
				 *
				 * @param th The size in pixels of the link's line weight
				 * @throw string If invalid thickness
				 */
				void setThickness(const double& th) {
					lvis->setThickness(th);
				}
				/**
				 *  @brief Get the thickness of the edge.
				 *	@return Size in pixels of the link's line thickness
				 */
				double getThickness() const {
					return lvis->getThickness();
				}

				/**
				 * @brief Set the color of the edge.
				 *
				 * @param col The color of the edge
				 */
				void setColor(const Color& col) {
					lvis->setColor(col);
				}
				/**
				 * @brief Set the color to a named color. Check the Color class
				 *  for a list of named colors.
				 *
				 * @param col The name of the color.
				 */
				void setColor(const string  col) {
					lvis->setColor(col);
				}
				/**
				 *  @brief return the current color of the edge
				 *	@return The color of the edge
				 */
				Color getColor() const {
					return lvis->getColor();
				}
				/**
				 * @brief Get the link visualizer of this edge
				 * @return return the link visualizer of this edge
				 */
				LinkVisualizer *getLinkVisualizer() {
					return lvis;
				}
		}; //end of Edge class
	}
} // end of bridges namespace
#endif
