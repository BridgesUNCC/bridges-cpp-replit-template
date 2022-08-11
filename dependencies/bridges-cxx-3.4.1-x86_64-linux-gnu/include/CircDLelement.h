#ifndef  CIRC_DL_ELEMENT_H

#define CIRC_DL_ELEMENT_H
#include "DLelement.h"

namespace bridges {
	namespace datastructure {
		/**
		 *
		 *  @brief This class can be used to instantiate Circular Doubly Linked
		 *  List Elements.

		 *  Structurally they are the same as doubly linked elements
		 *  except that each node constructed with the next and the previous pointers
		 *  pointing to itself.

		 *  User's implementation of the circularly linked list needs to ensure that
		 *  the last node's next pointer points to the first node and the first node's
		 *  previous pointer points to the last node, as the visualization generation
		 *  is dependent on this.

		 *  Elements have labels (string) that are displayed on the visualization.
		 *  Elements take an generic object E as a user defined parameter, which can
		 *  any native type or object.
		 *  Elements contain a visualizer object for setting visual attributes (color,
		 *  shape, opacity, size), necessary for displaying them in a web browser
		 *
		 *
		 * @sa There is a tutorial about Circular Doubly Linked Lists :
		 * https://bridgesuncc.github.io/tutorials/CircularDoublyLinkedList.html
		 *
		 * @author Kalpathi Subramanian
		 * @date  10/5/16, 7/12/19
		 */
		template <typename E>
		class CircDLelement : public  DLelement<E> {
			public:
				/**
				 *	Constructs an empty CircDLelement with next and prev pointers set
				 *	to itself
				*/
				CircDLelement() : DLelement<E> (this, this, E()) {
				}

				/** Constructs a CircDLelement labeled "label", holding an object "e",
				 *	with next and prev pointers set to itself
				 * 	@param e the genereic object that this CircDLelement is holding
				 * 	@param label the label for this CircDLelement that shows up on the
				 *		Bridges visualization
				 */
				CircDLelement (E e, string label)
					: DLelement<E>(this, this, e, label) {
				}

				/**
				 *	Constructs an empty DLelement with the next pointer set to the
				 *	CircDLelement "next" and the prev pointer set to CircDLelement
				 *	"prev".
				 *
				 * 	@param next the DLelement that should be assigned to the next
				 *		pointer
				 *	@param prev the DLelement that should be assigned to the prev
				 *		pointer
				 *
				 */
				CircDLelement(CircDLelement<E> next, CircDLelement<E> prev)
					: DLelement<E>(this, this) {
				}

				/**
				 *	Constructs a DLelement holding an object "e", with the next pointer
				 *	set to the DLelement "next" and the prev pointer set to DLelement
				 *	"prev".
				 *
				 *	@param e the genereic object that this CircDLelement is holding
				 *	@param next the CircDLelement that should be assigned to the next
				 *		pointer
				 *	@param prev the CircDLelement that should be assigned to the prev
				 *	pointer
				 *
				 */
				CircDLelement(E e, CircDLelement<E> next, CircDLelement<E> prev)
					: DLelement<E>(this, this, e) {
				}

				/**
				 *	This method gets the data structure type
				 *
				 *	@return  The date structure type as a string
				 */
				virtual const string getDStype() const override {
					return "CircularDoublyLinkedList";
				}

				/**
				 * This method returns the pointer to the next DLelement - const version
				 * @return the DLelement assigned to the next pointer
				 */
				const CircDLelement<E> *getNext() const override {
					return static_cast<const CircDLelement*>(SLelement<E>::getNext());
				}

				/**
				 * Retrieves the next CircSLelement
				 * @return CircSLelement<E> assigned to next
				 */
				virtual CircDLelement<E> *getNext() override {
					return static_cast<CircDLelement*> (SLelement<E>::getNext());
				}

				/**
				 * This method sets the pointer to the next DLelement
				 *
				 * @param next the DLelement that should be assigned to the next pointer
				 *
				 */
				void setNext(CircDLelement<E> *next) {
					DLelement<E>::setNext(next);
				}

				/**
				 * This method returns the pointer to the previous DLelement
				 * @return the DLelement assigned to the prev pointer
				 */
				CircDLelement<E> *getPrev() override {
					return static_cast<CircDLelement*>(DLelement<E>::getPrev());
				}

				/**
				 * This method returns the pointer to the previous DLelement
				 * @return the DLelement assigned to the prev pointer
				 */
				const CircDLelement<E> *getPrev() const override {
					return static_cast<const CircDLelement*>(DLelement<E>::getPrev());
				}

				/**
				 * This method sets the pointer to the previous DLelement
				 * @param prev the DLelement that should be assigned to the prev pointer
				 */
				void setPrev(CircDLelement<E> *prev) {
					DLelement<E>::setPrev(prev);
				}
			public:

				/// @brief these are helper classes for CircDLelement for easy iteration in a
				/// range for loop.  It is not meant to be created by the bridges user.
				/// But it may be returned by Bridges to provide an STL compliant list API.
				class CircDLelement_listhelper {
						typename bridges::datastructure::CircDLelement<E> *start, *last;

					public:
						CircDLelement_listhelper (typename bridges::datastructure::CircDLelement< E > * s)
							: start(s), last(s) {

						}

						class iterator {

								typename bridges::datastructure::CircDLelement<E> *current;

							public:

								iterator(typename bridges::datastructure::CircDLelement<E> * c )
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
							return iterator(last);
						}

						// reverse iteration
						iterator rbegin() {
							return iterator(last);
						}
						iterator rend() {
							return iterator(start);
						}
				};

				///@brief these are helper classes for CircDLelement for easy iteration in a range for loop.
				///It is not meant to be created by the bridges user. But it may be returned by Bridges to provide an STL compliant list API.
				class CircDLelement_constlisthelper {
						typename bridges::datastructure::CircDLelement<E> const *start;

					public:
						CircDLelement_constlisthelper (typename bridges::datastructure::CircDLelement< E > const * s) : start(s) {
						}
						class iterator {

								typename bridges::datastructure::CircDLelement< E > const  * current;
							public:
								iterator(    typename bridges::datastructure::CircDLelement< E > const   * c )
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
							return iterator(start);
						}
						// reverse iteration
						iterator rbegin() {
							return iterator(start->getPrev());
						}
						iterator rend() {
							return iterator(start->getPrev());
						}
				};
		}; // end CircDLelement
		template <class E>
		using CircDLelement_List = typename CircDLelement<E>::CircDLelement_listhelper;
		template <class E>
		using CircDLelement_ConstList = typename CircDLelement<E>::CircDLelement_constlisthelper;

	}
} //namespace bridges
#endif
