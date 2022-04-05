#ifndef ELEMENT_H

#define ELEMENT_H

#include <unordered_set>
#include <unordered_map>
#include <cmath>

using namespace std;

#include "DataStructure.h"
#include "ElementVisualizer.h"
#include "LinkVisualizer.h"
#include <JSONutil.h>

namespace bridges {
	namespace datastructure {
		// forward Declarations
		template <typename K, typename E1, typename E2> class GraphAdjList;
		template <typename K, typename E1, typename E2> class GraphAdjMatrix;

		/**
		 *	@brief This is the fundamental building block for all data structures
		 *	in BRIDGES.
		 *
		 *	This is the Superclass Element for  SLelement, DLelement, MLElement,
		 *	CircSlElement, CircDlElement, TreeElement, BinTreeElement, BSTElement,
		 *	AVLTreeElement, and KdTreeElement subclasses.
		 *
		 * 	The label field(string type) is used to label the visualization of the
		 * 	element.
		 *
		 * 	Element holds a LinkVisualizer for each of its links and
		 * 	an ElementVisualizer for itself; these are use for styling the
		 * 	nodes and edges (emanating from the link, if there is a destination
		 * 	element), respectively.

		 * All the tutorials under
		 *
		 * https://bridgesuncc.github.io/tutorials/Overview.html
		 *
		 * show how to use different types of elements
		 *
		 * 	@param E the application data type
		 *
		 * 	@author Kalpathi Subramanian
		 *
		 * 	@date 6/11/15, 11/27/16, 7/12/19, 12/28/20
		 */


		template <typename E> class Element {
				//Used for access to generateJSON() and for links manipulation
				template <typename K, typename E1, typename E2> friend class GraphAdjList;
				template <typename K, typename E1, typename E2> friend class GraphAdjMatrix;
				template <typename K> friend class Array;
				template <typename K> friend class Array1D;
				template <typename K> friend class Array2D;
				template <typename K> friend class Array3D;

			private:
				bool debug() const {
					return false;
				}
				/**
				 * List of shapes supported by BRIDGES : CIRCLE, SQUARE, DIAMOND,
				 *	CROSS, TRIANGLE, WYE, STAR
				 */
				static const unordered_map<const Shape, const string, hash<int>>& ShapeNames() {

					static std::unordered_map<const Shape, const string, hash<int>> sn = {
						{CIRCLE, "circle"},
						{SQUARE, "square"},
						{DIAMOND, "diamond"},
						{CROSS, "cross"},
						{TRIANGLE, "triangle"},
						{WYE, "wye"},
						{STAR, "star"}
					};
					return sn;
				}



				//this element's label
				string label;
				// appl. specific data stored with element
				E value = E();
				// this element's visualizer
				ElementVisualizer* elvis;

			protected:

				// this element's collection of links
				unordered_map<Element*, LinkVisualizer> links;

			public:
				/**
				 * Constructs an element with the provided value and label.
				 * The defaults will be used if not provided.
				 *
				 * @param val The data to hold
				 * @param lab The label to show
				 */
				explicit Element(const E& val = E(), const string& lab = string()) :
					label(lab), value(val) {
					elvis = new ElementVisualizer;
				}

				/**
				 *
				 * Constructs an element with the provided element as input
				 * @param e element
				 *
				 */
				Element(const Element& e)
					: label(e.label), value(e.value), elvis(new ElementVisualizer(*(e.elvis))), links(e.links) {
				}

				Element& operator= (const Element& e) {
					this->label = e.label;
					this->value = e.value;
					*(this->elvis) = *(e.elvis);
					this->links = e.links;
					return *this;
				}

				E& operator= (E const& e) {
					this->value = e;
					return this->value;
				}

				/**
				 * Element destructor
				 */
				virtual ~Element() {
					delete elvis; // removes the visualizer
				}

				/**
				 *	@brief Get the element visualizer object
				 *	@return The ElementVisualizer of this element
				 */
				ElementVisualizer* getVisualizer() {
					return elvis;
				}
				/**
				 *	@brief Get the element visualizer object - constant version
				 *
				 * @return The ElementVisualizer of this element
				 */
				const ElementVisualizer* getVisualizer() const {
					return elvis;
				}
				/**
				 * @brief Returns the LinkVisualizer of element
				 *
				 *	Returns the LinkVisualizer of element "el" or NULL
				 *	if no link exists
				 *
				 * @param el The terminating element of the link
				 *
				 * @return The LinkVisualizer
				 */
				LinkVisualizer* getLinkVisualizer(const Element* el) {
					if (links.find(const_cast<Element*>(el)) != links.end()) {
						return &(links.at(const_cast<Element*>(el)));
					}
					if (debug())
						cerr << "Element " << label << " not linked to Element "
							<< el->getLabel() << ", returning NULL" << endl;
					return nullptr;
				}

				/**
				 * @brief Returns the LinkVisualizer of element
				 *
				 * Returns the LinkVisualizer of element "el" - Constant version
				 *
				 * @param el The terminating element of the link
				 * @return The LinkVisualizer
				 */
				LinkVisualizer* getLinkVisualizer(const Element* el) const {
					return const_cast<Element*> (this)->getLinkVisualizer(el);
				}

				/**
				 *  @brief Gets the label of this element
				 *	@return The label of the element
				 */
				string const & getLabel() const {
					return label;
				}

				/**
				 * @brief Sets label  of this element
				 *
				 * @param lab The label of the element
				 */
				void setLabel(const string& lab) {
					label = lab;
				}

				/**
				 *  @brief Gets the object held in the generic object E
				 *
				 *  Gets the object (generic) held in the element  - const version
				 *	@return The value of the element
				 */
				E const & getValue() const {
					return value;
				}

				/**
				 *  @brief Gets the object held in the generic object E
				 *
				 *  Gets the object (generic) held in the element
				 *	@return The value of the element
				 */
				E & getValue() {
					return value;
				}

				/**
				 * @brief Sets generic object to "val"
				 *
				 * @param val The value of the element to be set
				 */
				void setValue(const E& val) {
					value = val;
				}

			protected:
				/**
				 *  @brief Gets the JSON string of the element representation
				 *	@return The JSON string of this element's properties
				 */
				virtual const string getElementRepresentation() const {
					using bridges::JSONUtil::JSONencode;
					//write out ElementVisualizer properties

					// first check if location is set and needs to be included
					string loc_str = "";
					if ( (elvis->getLocationX() != INFINITY) &&
						(elvis->getLocationY() != INFINITY) ) {
						loc_str =  QUOTE + "location" + QUOTE + COLON +
							OPEN_BOX +
							JSONencode(elvis->getLocationX())  + COMMA +
							JSONencode(elvis->getLocationY()) +
							CLOSE_BOX + COMMA;
					}
					return  OPEN_CURLY +
						QUOTE + "color" + QUOTE + COLON + elvis->getColor().getCSSRepresentation()
						+ COMMA +
						loc_str +
						QUOTE + "shape" + QUOTE + COLON + QUOTE +
						ShapeNames().at(elvis->getShape()) + QUOTE + COMMA +
						QUOTE + "size" + QUOTE + COLON +
						JSONencode(elvis->getSize()) + COMMA +
						QUOTE + "name" + QUOTE + COLON + JSONencode( label) +
						CLOSE_CURLY;
				}
				/**
				 * Gets the JSON representation of this link visualizer using
				 * the supplied source and destination strings
				 *
				 * @param lv The LinkVisualizer
				 * @param src The source vertex
				 * @param dest The destination vertex
				 * @return The JSON of this link visualizer
				 *
				 */
				static const string getLinkRepresentation(const LinkVisualizer& lv,
					const string& src, const string& dest) {
					using bridges::JSONUtil::JSONencode;


					//write out LinkVisualizer properties
					return OPEN_CURLY +
						QUOTE + "color"     + QUOTE + COLON + lv.getColor().getCSSRepresentation()
						+ COMMA +
						(!lv.getLabel().empty() ?
							(QUOTE + "label" + QUOTE + COLON +
								JSONencode( lv.getLabel()) + COMMA) : "") +
						QUOTE + "thickness" + QUOTE + COLON +
						JSONencode(lv.getThickness()) + COMMA +
						QUOTE + "source"    + QUOTE + COLON + JSONencode(src)  + COMMA +
						QUOTE + "target"    + QUOTE + COLON + JSONencode(dest) +
						CLOSE_CURLY;
				}
			public:
				/**
				 * @brief Sets size of the element.
				 *
				 * @param sz The size in pixel weight of the element. Valid Range:[1;50]
				 */
				void setSize(const double& sz) {
					elvis->setSize(sz);
				}

				/**
				 *  @brief Get element size
				 *	@return the size (in pixels) of the element
				 *
				 */
				double getSize() const {
					return elvis->getSize();
				}
				/**
				 * @brief Set the color of the Element.
				 *
				 *  @param col The color of the element
				 */
				void setColor(const Color& col) {
					elvis->setColor(col);
				}
				/**
				 *  @brief Set the color by name.
				 *
				 *  @param col The color name. Refer to the Color class for
				 *		supported color names.
				 */
				void setColor(const string col) {
					elvis->setColor(col);
				}

				/**
				 *  @brief Get the current color of the element
				 *
				 *  @return The color of the element
				 */
				Color getColor() const {
					return elvis->getColor();
				}

				/**
				 *	@brief Set opacity of element - use the 4th color component
				 *
				 *  @param opacity
				 */
				void setOpacity(double opacity) {
					elvis->setOpacity(opacity);
				}

				/**
				 *	get opacity of element
				 *
				 *	@return opacity
				 */
				double getOpacity() {
					return elvis->getOpacity();
				}
				/**
				 * @brief Set the shape  of the element
				 *
				 * @param shp is one of Shape.CIRCLE, Shape.SQUARE, Shape.DIAMOND,
				 *  		Shape.CROSS, Shape.TRIANGLE, Shape.WYE, Shape.STAR
				 *
				 */
				void setShape(const Shape& shp) {
					elvis->setShape(shp);
				}
				/**
				 *  @brief Returns the shape of the element
				 *
				 *	@return The shape of the element(one of
				 *		Shape.CIRCLE, Shape.SQUARE, Shape.DIAMOND,
				 *  	Shape.CROSS, Shape.TRIANGLE, Shape.WYE, Shape.STAR)
				 */
				Shape getShape() const {
					return elvis->getShape();
				}
				/**
				 * 	@brief Sets the location attributes of an element.
				 *
				 * 	@param locX X coordinate of the element location
				 * 	@param locY Y coordinate of the element location
				 */
				void setLocation(const double& locX, const double& locY) {
					elvis->setLocation(locX, locY);
				}

				/**
				 *  @brief Gets the X coordinate of the location
				 *	@return the X coordinate of the  element's location attribute
				 */
				double getLocationX() const {
					return elvis->getLocationX();
				}
				/**
				 *  @brief Gets the Y coordinate of the location
				 *	@return the Y coordinate of the  element's location attribute
				 */
				double getLocationY() const {
					return elvis->getLocationY();
				}
		};	//end of Element class

	}
}//end of bridges namespace

#endif
