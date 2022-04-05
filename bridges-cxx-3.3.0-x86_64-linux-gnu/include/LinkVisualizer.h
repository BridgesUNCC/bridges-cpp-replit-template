#ifndef LINK_VISUALIZER_H
#define LINK_VISUALIZER_H

#include "Color.h" //string, using std

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class maintains the visual properties of links within data structures.
		 *
		 * This class is used to keep the visual properties of links that are part of
		 * data structures such as linked lists, pointer based trees, link based
		 * graph representations, etc.  Relevant attributes include color and thickness
		 *
		 * Objects of this class are stored as properties of Elements.
		 * A user may manipulate the LinkVisualizer returned from the Element's getLinkVisualizer() method.
		 *
		 * BRIDGES supports color of any legal named CSS or (R,G,B) triplets
		 * 	value. Check the Color class for details. Default: "steelblue".
		 *
		 * Thickness values must range from ]0.0,10.0]. Default: 1.0
		 *
		 * @author Kalpathi Subramanian, Dakota Carmer, Erik Saule
		 * @date 6/29/15, 6/10/16, 7/12/19, 12/28/20
		 */
		class LinkVisualizer {
			public:

				/**
				 * @brief get default thickness of link (1.0)
				 */
				static constexpr double DEFAULT_THICKNESS() {
					return 1.0;
				}
				/**
				 * @brief get default color of link ("steelblue")
				 */
				static Color DEFAULT_COLOR() {
					return Color("steelblue");
				}; //SteelBlue

			private:

				Color color = DEFAULT_COLOR();
				string label = "";
				double thickness = DEFAULT_THICKNESS();

			public:
				/**
				 * @brief Constructs a LinkVisualizer with the specified
				 *	color and thickness.
				 8
				 * The defaults will be used if not provided (black,1)
				 *
				 * @param col Link color
				 * @param th Link thickness
				 *
				 */
				LinkVisualizer(Color col = DEFAULT_COLOR(),
					double th = DEFAULT_THICKNESS()):
					color(col) {
					setThickness(th);
				}

				/**
				 *  @brief Return the link label
				 *  @return The label of the link
				 */
				string getLabel() const {
					return label;
				}

				/**
				 * @brief Sets label of the link
				 *
				 * @param lab The label of the link
				 */
				void setLabel(const string& lab) {
					label = lab;
				}

				/**
				 * Set the link thickness
				 * Valid Range:]0.0,10.0] Default: 1
				 *
				 * @param th The size in pixels of the link's line weight
				 * @throw string If invalid thickness
				 */
				void setThickness(const double& th) {
					if (th < 0.0 || 10 < th)
						throw "Invalid Thickness Value.. " + to_string(th) +
						" Must be in the ]0.0,10.0] range";
					else
						thickness = th;
				}
				/**
				 *  @brief Get the link thickness
				 *	@return Size in pixels of the link's line thickness
				 */
				double getThickness() const {
					return thickness;
				}

				/**
				 * @brief Set the link color.
				 *
				 * @param col The color of the element
				 */
				void setColor(const Color& col) {
					color = col;
				}
				/**
				 *  @brief Set the color by name.
				 *  @param col The color name. See Color for supported names.
				 */
				void setColor(const string& col) {
					color = Color(col);
				}

				/**
				 *  @brief Return the link color
				 *	@return The color of the link
				 */
				Color getColor() const {
					return color;
				}
		}; //end of LinkVisualizer class
	}
}//end of bridges namespace
#endif
