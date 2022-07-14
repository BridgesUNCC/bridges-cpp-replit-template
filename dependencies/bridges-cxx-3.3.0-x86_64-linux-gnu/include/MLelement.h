#ifndef ML_ELEMENT_H

#define ML_ELEMENT_H

#include "SLelement.h"

namespace bridges {
	namespace datastructure {
		/**
		 *
		 *	@brief This class can be used to instantiate Multi-list Elements.
		 *
		 *
		 *	This class extends SLelement (singly linked list element) to build multi-lists;
		 *	Multilist elements contain a tag (boolean) that indicates if the element
		 *	contains a sublist or not; if the tag is true, then there is a sublist beginning
		 *	at this node and the starting point is the `sublist' field in the element.
		 *	If the tag is false, then the list continues as a normal singly linked list.
		 *	The sublists are re recursive: any sublist can have its own sublists and so on.
		 *	As in singly linked elements, the next pointer points to the following list element and
		 *	each element contains a generic application specific object.
		 *
		 * 	Multi-list elements contain a visualizer (ElementVisualizer) object for setting
		 *	visual attributes (color, shape, opacity, size), necessary for displaying
		 *	them in a web browser.
		 *
		 *	Elements also have a LinkVisualizer object, that is used when they are linked to
		 *	another element, appropriate for setting link attributes, for instance, between
		 *	the current element and its next element. In this case, the link in question is that
		 *  which connects the element to the following elements; a similar logic follows for
		 *	sublists.
		 *
		 * @sa There is a tutorial about Multi Lists :
		 *	https://bridgesuncc.github.io/tutorials/MultiList.html
		 *
		 * @author Kalpathi Subramanian
		 *
		 * @date 5/24/17, 7/12/19, 12/28/20
		 *
		 * @param E The generic parameter object that is part of this element, representing
		 *			either application specific data, or a pointer to a sublist.
		 *
		 */


		template <typename E>
		class MLelement : public SLelement<E> {

			protected:
				MLelement<E> *sub_list = nullptr; // link to a sublist
				bool tag = false;

			public:

				/**
				 * @brief constructor
				 *
				 * This constructor creates an MLelement object
				 * and sets the next pointer to null
				 *
				 * @param val generic object
				 * @param lab label
				 *
				 */

				MLelement(const E& val = E(), const string& lab = string())
					: SLelement<E> (nullptr, val, lab) {
					sub_list = nullptr;
					tag = false;
				}

				/**
				 * @brief Creates an MLelement object
				 *
				 * This constructor creates an MLelement object of generic
				 *	parameter object E,
				 *	and label "label" and sets the next pointer to null
				 *
				 * @param label the label of MLelement that shows up on the
				 *	Bridges visualization
				 *
				 */
				MLelement (string label) : SLelement<E> (nullptr, E(), label) {
					sub_list = nullptr;
					tag = false;
				}

				/**
				 * @brief Creates an MLelement object
				 *
				 * Creates a new element with value "e" and sets the next pointer
				 * to the MLelement referenced by the "next" argument
				 *
				 * @param e the generic object that this element will hold
				 * @param next the element that should be assigned to the next pointer
				 *
				 */
				MLelement (E e, MLelement<E> *next) : SLelement<E> (next, e, string()) {
					sub_list = nullptr;
					tag = false;
				}

				/**
				 * @brief Sets the start of a new sublist
				 * to the MLelement "next"
				 *
				 * @param sl the MLelement that is the beginning of a sublist
				 */
				void setSubList(MLelement<E> *sl) {
					// Hmmm, need to think about removing link data from
					// an existing sublist
					this->sub_list = sl;
					tag = true;

					// create link data from node to head of sublist
					if (sl)
						this->links[sl];

					// by default, color and shape sublist nodes to distinguish them
					this->getVisualizer()->setColor(Color("red"));
					this->getVisualizer()->setShape(SQUARE);
				}

				/**
				 * @brief Gets the sublist at this node, if it exists
				 *
				 * @return  the sublist head element, if it exists
				 */
				MLelement *getSubList() {
					return sub_list;
				}

				/**
				 * @brief Retrieves the element following this element
				 *
				 * @return MLelement<E> assigned to next
				 *
				 */
				MLelement<E> *getNext() override {
					return (MLelement<E>*) this->next;
				}

				/**
				 * @brief Retrieves the element following this element - const version
				 *
				 * @return MLelement<E> assigned to next
				 *
				 */
				MLelement<E> *getNext() const override {
					return (MLelement<E>*) this->next;
				}

				/**
				 * @brief Sets the element to point to the next MLelement
				 *
				 * @param n MLelement<E> that should be assigned to the next pointer
				 */
				void setNext(MLelement<E> *n) {
					if (n) {
						if (this->next != n)	// remove old link data, possibly
							this->links.erase(this->next);

						this->next = n;
						this->links[this->next];
					}
				}

				/**
				 *	@brief Sets the tag of the element.
				 *
				 *	@param t tag to set
				 */
				void setTag(bool t) {
					tag = t;
				}

				/**
				 *  @brief Gets the tag of the element.
				 *
				 *  @return tag of the element
				 */
				bool getTag() {
					return tag;
				}
				/**
				 *  @brief Return the string representaion of element
				 *
				 *	@return The string representation of this data structure type
				 */
				virtual const string getDStype() const override {
					return "Multilist";
				}
			private:
				/**
				 * Gets the JSON representation of this multilist and its links
				 *
				 * @return JSON string of the data structure representation
				 */
				virtual const string getDataStructureRepresentation() const override final {
					vector<const MLelement<E>*> nodes;

					// get the list of nodes
					this->getListElements(this, nodes);

					// generate the JSON string

					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs
					unordered_map<const MLelement*, int> node_map { {nullptr, -1} };

					string nodes_JSON, links_JSON;

					int i = 0; 		// get the JSON string for nodes
					for (const auto* e : nodes) {
						if (node_map.emplace(e, i).second)  {
							// successful emplacement
							i++;
							nodes_JSON += e->getElementRepresentation() + COMMA;
						}
					}
					//Remove trailing comma and nullptr entry
					node_map.erase(nullptr);
					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					// generate the links representation
					for (int k = 0; k < nodes.size(); k++) {
						if (nodes[k]->next != nullptr) { // link exists
							links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->next),
									to_string(node_map[nodes[k]]),
									to_string(node_map[nodes[k]->getNext()])) + COMMA;
						}
						if (nodes[k]->tag) {	// sublist link

							if (nodes[k]->sub_list != nullptr) { // link exists
								links_JSON += this->getLinkRepresentation(
										nodes[k]->links.at(nodes[k]->sub_list),
										to_string(node_map[nodes[k]]),
										to_string(node_map[nodes[k]->sub_list])) + COMMA;
							}
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					string ml_list_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON + OPEN_BOX +
						links_JSON + CLOSE_BOX +
						CLOSE_CURLY;

					return ml_list_json;
				}
				/**
				 *  Get the list of nodes into a vector
				 *
				 *  @param list MLelement list
				 *  @param nodes [output] The list of nodes (in a vector)
				 */
				void getListElements(const MLelement<E> *list,
					vector<const MLelement<E>*>& nodes) const {

					auto it = list;
					while (it != nullptr) {
						nodes.push_back(it);
						// if this node has a sublist, recurse
						if (it->tag) {
							getListElements(it->sub_list, nodes);
						}
						// iterate
						it = (MLelement<E>*) it->next;
					}
				}
		};
	}
} // end namespace bridges

#endif
