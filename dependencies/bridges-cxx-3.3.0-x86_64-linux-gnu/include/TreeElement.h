#ifndef TREE_ELEMENT_H
#define TREE_ELEMENT_H

#include <vector>

#include "Element.h" //string, using std

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class can be used to create tree elements, derived from Element
		 *
		 * This class can be used to create tree elements, with subtrees
		 *
		 * Generic Parameters: E the application data type
		 *
		 * @author Kalpathi Subramanian, Dakota Carmer
		 * @date 6/12/15, 7/12/19, 12/28/20
		 *
		 * There is a tutorial about Trees :
		 * https://bridgesuncc.github.io/tutorials/Tree.html
		 **/
		template <typename E>
		class TreeElement : public Element<E>, public DataStructure {
			private:
				vector<TreeElement*> children;
			public:
				/**
				 * @brief Construct a TreeElement from given values
				 *
				 * Constructs a TreeElement with the provided value and label,
				 * setting the left and right TreeElements to NULL.
				 * The defaults will be used if not provided.
				 *
				 * @param e The data to hold
				 * @param lab The label to show
				 */
				TreeElement(const E& e = E(), const string& lab = string())
					: Element<E>(e, lab) {
				}
				/**
				 *  @brief Get the data structure name
				 *	@return The name of  this data structure
				 */
				virtual const string getDStype() const override {
					return "Tree";
				}
				/**
				 *  @brief Get the children of this node
				 *	@return The children TreeElements
				 */
				vector<TreeElement*>& getChildren() {
					return children;
				}
				/**
				 * Constant version
				 *
				 * @brief Get the children of this node
				 * @return The children TreeElements
				 */
				const vector<TreeElement*>& getChildren() const {
					return children;
				}
				/**
				 *  @brief Gets the nth child of this node
				 *
				 *	Gets the nth child of this TreeElement, returns null
				 *	if non-existent
				 *
				 * @param n The index of the child
				 * @return The child TreeElement
				 */
				TreeElement* getChild(const int& n) {
					return (n >= children.size() || n < 0 ) ? nullptr : children.at(n);
				}
				/**
				 *
				 *  @brief Gets the nth child of this node - constant version
				 *
				 * Gets the nth child of this TreeElement, returns null if
				 *	non-existent
				 *
				 * @param n The index of the child
				 * @return The child TreeElement
				 */
				const TreeElement* getChild(const int& n) const {
					return (n >= children.size() || n < 0) ? nullptr : children.at(n);
				}
				/**
				 * @brief Adds a child to children
				 *
				 * @param child The child TreeElement
				 */
				void addChild(TreeElement* child) {
					children.push_back(child);
					if (child) {
						this->links[child];
					}
				}
				/**
				 * @brief Sets child at index to "kid".
				 *
				 * Will do nothing given invalid index.
				 *
				 * @param index of child to replace
				 * @param kid The child TreeElement
				 */
				void setChild(const size_t& index, TreeElement* kid) {
					/**
					 *  This simply replaces the element at position index and the old element
					 *  is lost(actually can create memory leak if it came from dynamic memory
					 *  Since we cannot distinguish from allocated or static memory
					 *	from pointers, it is the user's responsibility to keep track of
					 *	allocated memory its linkage. For new elements, if not null,
					 *	create linkage
					 */
					if ((index < children.size()) && index >= 0) {
						children[index] = kid;
						this->links.erase(children[index]); // remove any existing links
						this->links[kid];			// initialize this element in the map
					}
				}
			private:
				/**
				 * Gets the JSON representation of this TreeElement and its links
				 *
				 * @return A string holding a hierarchical JSON representation of the
				 *		tree
				 *
				 * The JSON creation for a tree structure is different from other
				 * data structures; we will use a preorder traversal to build a
				 * hierarchical JSON; it is assumed that children are in order
				 * from left to right.
				 * Also each child that is NULL is explicitly specified as NULL for
				 * visualization convenience
				 */
				virtual const string getDataStructureRepresentation() const override final {
					//TODO: Check for exceeding max node
					string tree_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						(OPEN_CURLY +
							this->preOrder((TreeElement<E>*)this)
							+ CLOSE_CURLY + CLOSE_CURLY);

					return tree_json;
				}

				/**
				 * Does a preorder traversal to build a hierarchical JSON of the tree
				 * rooted at this node
				 *
				 * @return the JSON string
				 */
				string  preOrder(TreeElement<E>* root) const {
					using bridges::JSONUtil::JSONencode;
					string json_str = "", children = "", link_props = "", elem_rep = "";
					string t_str;
					if (root != NULL) {
						// first get the node representation
						elem_rep = root->getElementRepresentation();
						// remove surrounding curly braces
						t_str = elem_rep.substr(1, elem_rep.size() - 2);
						json_str += t_str + COMMA;
						// now get the children
						if (root->children.size())
							json_str += QUOTE + "children" + QUOTE + COLON + OPEN_BOX ;
						for (int k = 0; k < root->children.size(); k++) {
							if (root->children[k] == NULL) {
								json_str += OPEN_CURLY + QUOTE + "name" + QUOTE + COLON +
									QUOTE + "NULL" + QUOTE + CLOSE_CURLY + COMMA;
							}
							else {
								LinkVisualizer *lv =
									root->getLinkVisualizer(root->children[k]);
								json_str += OPEN_CURLY;
								if (lv) {
									Color c = lv->getColor();
									json_str += QUOTE + "linkProperties" + QUOTE + COLON + OPEN_CURLY +
										QUOTE + "color" + QUOTE + COLON +
										c.getCSSRepresentation() + COMMA +
										QUOTE + "thickness" + QUOTE + COLON +
										JSONencode(lv->getThickness()) +
										//									QUOTE + "weight" + QUOTE + COLON +
										//									JSONencode(lv->getWeight()) +
										CLOSE_CURLY + COMMA;
								}
								else
									json_str += "linkProperties" + COLON + "{}" + COMMA;
								// process its children
								json_str +=	preOrder(root->children[k]);
								json_str += CLOSE_CURLY + COMMA;
							}
						}
						// remove last comma
						json_str = json_str.substr(0, json_str.size() - 1);
						// end of children
						if (root->children.size())
							json_str += CLOSE_BOX;
					}

					return json_str;
				}
		}; //end of TreeElement class

	}
}//end of bridges namespace
#endif
