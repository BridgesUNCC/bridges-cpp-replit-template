#ifndef DLelement_H
#define DLelement_H

#include "SLelement.h" //string, using std

namespace bridges {
	namespace datastructure {
		/**
		 * @brief The doubly linked list element, derived from SLelement
		 *
		 * This class extends the SLelelement class by adding a previous DLelement
		 * pointer
		 *
		 * There is a tutorial about Doubly Linked Lists :
		 * https://bridgesuncc.github.io/tutorials/DoublyLinkedList.html
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 6/11/15, 7/12/19
		 *
		 */
		template<typename E>
		class DLelement: public SLelement<E> {
			private:

				DLelement* prev = nullptr;// The pointer to the previous DLelement

			public:
				/**
				 *  Constructs a dlelement with the provided value, label, next and
				 *  previous elements.
				 *  The defaults will be used if not provided.
				 *
				 * @param n The next DLelement
				 * @param p The previous DLelement
				 * @param val The data to hold
				 * @param lab The label to show
				 */
				DLelement(DLelement* n, DLelement* p = nullptr, const E& val = E(),
					const string& lab = string()) : SLelement<E>(n, val, lab) {
					setPrev(p);
				}

				/**
				 * Constructs a dlelement with the provided value and label,
				 *  setting the next and previous dlelements to NULL.
				 * The defaults will be used if not provided.
				 *
				 * @param val The data to hold
				 * @param lab The label to show
				 */
				DLelement (const E& val = E(), const string& lab = string()) :
					DLelement(nullptr, nullptr, val, lab) {
				}

				/**
				 *  Return the data structure type
				 *
				 * @return The name of this data structure type
				 *
				 */
				virtual const string getDStype() const override {
					return "DoublyLinkedList";
				}
				/**
				 * 	Return the next DL element.
				 *
				 *	@return The next DLelement
				 */
				virtual DLelement* getNext() override {
					return static_cast<DLelement*>(SLelement<E>::getNext());
				}

				/**
				 * Constant version
				 *
				 * @return The next DLelement
				 */
				virtual const DLelement* getNext() const override {
					return static_cast<const DLelement*>(SLelement<E>::getNext());
				}
				/**
				 * Sets next element to "n"
				 *
				 * @param n The next DLelement
				 *
				 */
				void setNext(DLelement* n) {
					if (this->next != n && this->next != prev) {
						//if different, remove old link data
						this->links.erase(this->next);
					}
					if ((this->next = n)) {
						this->links[this->next];
					}
				}
				/**
				 * Returns the previous element in the list
				 * @return The previous DLelement
				 */
				virtual DLelement* getPrev() {
					return prev;
				}
				/**
				 * Returns the previous element - Constant version
				 *
				 * @return The previous DLelement
				 */
				virtual const DLelement* getPrev() const {
					return prev;
				}
				/**
				 * Sets prev element to "p"
				 *
				 * @param p The previous element
				 */
				virtual void setPrev(DLelement* p) {
					if (prev != p && this->next != prev) {
						this->links.erase(prev);   //if different, remove old link data
					}
					//	set prev to p and if not null, create
					//	default link data if none already present
					if ((prev = p)) {
						this->links[prev];
					}
				}

			private:

				virtual const string  getDataStructureRepresentation() const override {

					vector<const DLelement<E>*> nodes;

					// get the list of nodes

					getListElements(nodes);

					// generate the JSON string

					if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
						// cant exceed max number of elements
						throw "Max allowed elements(for visualization) exceeded.. " +
						to_string(nodes.size()) + " Must be less than " +
						to_string(MAX_ELEMENTS_ALLOWED);
					}

					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs
					unordered_map<const DLelement*, int> node_map { {nullptr, -1} };

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

					// generate the links using the node map ids
					for (int k = 0; k < nodes.size(); k++) {
						if (nodes[k]->next != nullptr) { // link exists
							links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->next),
									to_string(node_map[nodes[k]]),
									to_string(node_map[nodes[k]->getNext()]) ) + COMMA;
						}
						if (nodes[k]->prev != nullptr) { // link exists
							links_JSON += this->getLinkRepresentation(nodes[k]->links.at(nodes[k]->prev),
									to_string(node_map[nodes[k]]),
									to_string(node_map[nodes[k]->prev]) ) + COMMA;
						}
					}

					//Remove trailing comma
					if (links_JSON.size()) {
						links_JSON = links_JSON.erase(links_JSON.size() - 1);
					}

					string dl_list_json =
						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX + nodes_JSON + CLOSE_BOX + COMMA +
						QUOTE + "links" + QUOTE + COLON +
						OPEN_BOX + links_JSON + CLOSE_BOX +
						CLOSE_CURLY;


					return dl_list_json;
				}

				/**
				*  Get the list of nodes
				*
				*  @param nodes The list of nodes
				*/
				virtual void getListElements(vector<const DLelement<E>*>&
					nodes) const  {

					//prevents potential infinite loop
					unordered_set<const DLelement<E>*> visited;
					auto it = this;

					// using the visited array handles both regular and
					// circular lists
					while (it != nullptr && visited.emplace(it).second) {
						nodes.push_back(it);
						it = it->getNext();
					}
				}
			public:

				/// @brief these are helper classes for DLelement for easy iteration in a
				/// range for loop.  It is not meant to be created by the bridges user.
				/// But it may be returned by Bridges to provide an STL compliant list API.
				class DLelement_listhelper {
						typename bridges::datastructure::DLelement<E> *start, *last;

					public:
						DLelement_listhelper (typename bridges::datastructure::DLelement< E > * s)
							: start(s) {

							// determine the last element
							auto el = s;
							if (el) {
								for (el = s; el->getNext() != nullptr; el = el->getNext());
								last = el;
							}
						}

						class iterator {

								typename bridges::datastructure::DLelement<E> *current;

							public:

								iterator(typename bridges::datastructure::DLelement<E> * c )
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
								iterator& operator-- () {
									current = current->getPrev();
									return *this;
								}
								iterator operator-- (int) {
									iterator clone(*this);
									current = current->getPrev();
									return clone;
								}
						};

						// forward iteration
						iterator begin() {
							return iterator(start);
						}

						iterator end() {
							return iterator(nullptr);
						}

						// reverse iteration
						iterator rbegin() {
							return iterator(last);
						}
						iterator rend() {
							return iterator(nullptr);
						}

				};

				///@brief these are helper classes for DLelement for easy iteration in a range for loop.
				///It is not meant to be created by the bridges user. But it may be returned by Bridges to provide an STL compliant list API.
				class DLelement_constlisthelper {
						typename bridges::datastructure::DLelement<E> const *start, *last;

					public:
						DLelement_constlisthelper (typename bridges::datastructure::DLelement< E > const * s) : start(s) {
							// determine the last element
							auto el = s;
							if (el) {
								for (el = s; el->getNext() != nullptr; el = el->getNext());
								last = el;
							}
						}
						class iterator {

								typename bridges::datastructure::DLelement< E > const  * current;
							public:
								iterator(    typename bridges::datastructure::DLelement< E > const   * c )
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
								iterator& operator-- () {
									current = current->getPrev();
									return *this;
								}
								iterator operator-- (int) {
									iterator clone(*this);
									current = current->getPrev();
									return clone;
								}
						};

						// forward iteration
						iterator begin() {
							return iterator(start);
						}
						iterator end() {
							return iterator(nullptr);
						}
						// reverse iteration
						iterator rbegin() {
							return iterator(last);
						}
						iterator rend() {
							return iterator(nullptr);
						}
				};
		}; //end of DLelement class
		// use some aliases for accessing iterators
		template <class E>
		using DLelement_List = typename DLelement<E>::DLelement_listhelper;
		template <class E>
		using DLelement_ConstList = typename DLelement<E>::DLelement_constlisthelper;


	}
}//end of bridges namespace
#endif
