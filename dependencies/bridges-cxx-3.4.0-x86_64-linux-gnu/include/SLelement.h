#ifndef SLELEMENT_H
#define SLELEMENT_H

#include "DataStructure.h"
#include "Element.h" //string, using std


namespace bridges {
	namespace datastructure {
		/**
		 * @brief The singly linked list element, derived from Element
		 *
		 * This class can be used to create singly linked elements, with a next
		 *	SLelement pointer
		 *
		 * @sa There is a tutorial about Singly Linked Lists :
		 * https://bridgesuncc.github.io/tutorials/SinglyLinkedList.html
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 6/11/15, 7/12/19
		 *
		 */

		template <typename E>
		class SLelement : public Element<E>, public DataStructure {

			protected:
				SLelement* next = nullptr;

			public:
				/**
				 *	@brief Constructs an slelement with the provided value.
				 *
				 * 	Constructs an SLelement with the provided value,
				 *	label, and next  SLelement.
				 * 	The defaults will be used if not provided.
				 *
				 * 	@param val The data to hold
				 * 	@param lab The label to show
				 * 	@param next The next SLelement
				 */
				SLelement(SLelement* next, const E& val = E(), const string& lab =
						string()) : Element<E>(val, lab) {
					setNext(next);
				}
				/**
				 *	@brief Constructs an slelement with the provided value.
				 *
				 *	Constructs an slelement with the provided value
				 *	and label,
				 *  setting the next slelement to NULL.
				 * 	The defaults will be used if not provided.
				 *
				 * 	@param val The data to hold
				 * 	@param lab The label to show
				 */
				SLelement(const E& val = E(), const string& lab = string())
					: SLelement(nullptr, val, lab) {
				}
				/**
				 *  @brief Returns the data structure name
				 *
				 *	@return The string representation of this data structure type
				 */
				virtual const string getDStype() const override {
					return "SinglyLinkedList";
				}

				/**
				 *  @brief Returns the next element in the list
				 *	@return The next SLelement
				 */
				virtual SLelement* getNext() {
					return next;
				}

				/**
				 *  @brief Returns the next element in the list -
				 *	Constant version
				 *	@return The next SLelement
				 */
				virtual const SLelement* getNext() const {
					return next;
				}

				/**
				 * Sets next link  to "n"
				 *
				 * @param n The next SLelement
				 */
				void setNext(SLelement* n) {
					//if different, remove old link data
					if (next != n) {
						this->links.erase(next);
					}

					next = n;
					this->links[next]; //this creates an entry in links if it does not exist
				}

			private:
				/**
				 * Gets the JSON representation of this slelement and its links
				 *
				 * @return JSON string of the singly linked list representation
				 */
				virtual const string getDataStructureRepresentation() const override {

					vector<const SLelement<E>*> nodes;
					// get the list of nodes
					getListElements(nodes);
					// generate the JSON string

					if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
						// cant exceed max number of elements
						throw "Max allowed elements(for visualization) exceeded.. " +
						to_string(nodes.size()) + " Must be less than " +
						to_string(MAX_ELEMENTS_ALLOWED);
					}

					pair<string, string> json_nodes_links = generateJSON(nodes);

					string sl_list_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + json_nodes_links.first + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON + OPEN_BOX +
						json_nodes_links.second + CLOSE_BOX +
						CLOSE_CURLY;


					return sl_list_json;
				}
			protected:
				/**
				 *  @brief Generates the JSON representation of the element
				 *
				 *	Generates  the JSON representation of the nodes and links
				 *	@return JSON string pair containing the nodes and links
				 */

				virtual const pair<string, string> generateJSON(
					vector<const SLelement<E>*> nodes) const {
					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs
					unordered_map<const SLelement*, int> node_map { {nullptr, -1} };

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
					// for each pair<SLelement*,int> in map
					for (unsigned int k = 0; k < nodes.size(); k++) {
						if (nodes[k]->next != nullptr) { // link exists
							links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->next),
									to_string(node_map[nodes[k]]),
									to_string(node_map[nodes[k]->next]) ) + COMMA;
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					return pair<string, string> (nodes_JSON, links_JSON);
				}
			protected:
				/**
				 * 	@brief Get the list of nodes
				 *
				 * 	@param nodes The list of nodes
				 */
				virtual void getListElements(vector<const SLelement<E>*>& nodes) const  {

					//prevents potential infinite loop
					unordered_set<const SLelement<E>*> visited;
					auto it = this;

					// using the visited array handles both regular and
					// circular lists
					while (it != nullptr && visited.emplace(it).second) {
						nodes.push_back(it);
						it = it->next;
					}
				}

			public:

				/**
				 *	@brief These are helper classes for SLelement for easy
				 *	 iteration.
				 *
				 *	These are helper classes for SLelement for easy
				 *	iteration  in a range for loop.  It is not meant to be
				 * 	created by the bridges user.  But it may be returned
				 *	by Bridges to provide an STL compliant list API.
				 */

				class SLelement_listhelper {
						typename bridges::datastructure::SLelement<E> * start;

					public:
						SLelement_listhelper (typename bridges::datastructure::SLelement< E > * s)
							: start(s)
						{}

						class iterator {
								typename bridges::datastructure::SLelement<E> *current;
							public:
								iterator(typename bridges::datastructure::SLelement<E> * c )
									: current(c)
								{}

								bool operator!= (const iterator& it) const {
									return this->current != it.current;
								}

								E const &  operator* () const {
									return current->getValue();
								}

								E &  operator* ()  {
									return current->getValue();
								}

								iterator& operator++ () {
									current = current->getNext();
									return *this;
								}
								iterator operator++ (int) {
									iterator clone(*this);
									current = current->getNext();
									return clone;
								}
						};

						iterator begin() {
							return iterator(start);
						}

						iterator end() {
							return iterator(nullptr);
						}
				};


				/**
				 *	@brief These are helper classes for SLelement for easy
				 *	 iteration.
				 *
				 * 	These are helper classes for SLelement for easy iteration
				 *	in a range for loop. It is not meant to be created by the
				 *	bridges user. But it may be returned by Bridges to
				 *	provide an STL compliant list API.
				 */
				class SLelement_constlisthelper {
						typename bridges::datastructure::SLelement<E> const * start;

					public:
						SLelement_constlisthelper (typename bridges::datastructure::SLelement< E > const * s)
							: start(s)
						{}

						class iterator {

								typename bridges::datastructure::SLelement< E > const  * current;
							public:
								iterator(    typename bridges::datastructure::SLelement< E > const   * c )
									: current(c)
								{}

								bool operator!=(const iterator& it) const {
									return this->current != it.current;
								}

								E const &  operator*() const {
									return current->getValue();
								}

								iterator& operator++() {
									current = current->getNext();
									return *this;
								}
						};

						iterator begin() {
							return iterator(start);
						}

						iterator end() {
							return iterator(nullptr);
						}
				};


		}; //end of SLelement class
		// use some aliases for accessing iterators
		template <class E>
		using SLelement_List = typename SLelement<E>::SLelement_listhelper;
		template <class E>
		using SLelement_ConstList = typename SLelement<E>::SLelement_constlisthelper;
	}
}//end of bridges namespace
#endif
