#ifndef  CIRC_SL_ELEMENT_H

#define CIRC_SL_ELEMENT_H
#include "SLelement.h"

namespace bridges {
	namespace datastructure {
		/**
		 *  @brief This class can be used to instantiate Singly Linked
		 *  Circular List Elements.

		 * 	This class can be used to instantiate Circular (Singly) Linked
		 *	List Elements, derived from Singly Linked Element. The main difference
		 *	from the SLelement is that they create circularly linked elements and
		 *  their traversals are slightly different.
		 *
		 * 	Elements have labels (string) that are displayed on the visualization
		 *  Elements take an generic object as a user defined parameter, any native
		 *	type or object.
		 *
		 * 	Element contains a visualizer object for setting visual attributes (color,
		 *	shape, opacity, size), necessary for displaying them in a web browser
		 *
		 * @sa There is a tutorial about Circular Singly Linked Lists :
		 * https://bridgesuncc.github.io/tutorials/CircularSinglyLinkedList.html
		 *
		 *	@author Kalpathi Subramanian
		 *	@date 10/5/2016, 7/12/19
		 *
		 *	@param E User type stored in the list
		 *
		 */

		template <typename E>
		class CircSLelement : public SLelement<E> {

			public:
				/**
				* 	This constructor creates an CircSLelement object
				* 	and sets its next pointer to itself
				*
				*/
				CircSLelement() : SLelement<E> (this) {
				}
				/**
				 * 	This constructor creates an CircSLelement object of value "e" and
				 *	label "label"
				 * 	and sets the next pointer to null
				 *
				 * 	@param label the label of CircSLelement that shows up on
				 *		the Bridges visualization
				 * 	@param val the generic object that this CircSLelement will hold
				 */
				CircSLelement (E val = E(), string label = string())
					: SLelement<E> (this, val, label) {
				}

				/**
				 * Creates a new element with value "e" and sets the next pointer
				 * to the CircSLelement referenced by the "next" argument
				 *
				 * @param e the generic object that this CircSLelement will hold
				 * @param next the CircSLelement that should be assigned to the next
				 * 		pointer
				 */
				CircSLelement (E e = E(), CircSLelement *next = nullptr)
					: SLelement<E> (next, e) {
				}

				/**
				 * Creates a new element and sets the next pointer
				 * to the CircSLelement "next"
				 * @param next the CircSLelement that should be assigned to the
				 *	next pointer
				 */
				CircSLelement (CircSLelement *next) : SLelement<E> (next) {
				}

				/**
				 *	This method gets the data structure type
				 *
				 *	@return  The date structure name
				 */
				virtual const string getDStype() const override {
					return "CircularSinglyLinkedList";
				}

				/**
				 * Retrieves the next CircSLelement
				 * @return the next element in the list
				 */
				virtual CircSLelement<E> *getNext() override {
					return static_cast<CircSLelement*> (SLelement<E>::getNext());
				}

				/**
				 * Sets the pointer to the next CircSLelement
				 * @param next CircSLelement<E> that should be assigned to the next
				 *	pointer
				 */
				void setNext(CircSLelement<E> *next) {
					SLelement<E>::setNext(next);
				}

			public:
				/**
				 * @brief This is a helper class to facilitate using iterators
				 *  to traverse circular list
				 */
				class CircSLelement_listhelper {
						typename bridges::datastructure::CircSLelement<E> *start,
								 *last;

					public:
						CircSLelement_listhelper (typename bridges::datastructure::CircSLelement< E > * s) : start(s), last (s) {}

						class iterator {
								typename bridges::datastructure::CircSLelement<E> *current;
							public:
								iterator(typename bridges::datastructure::CircSLelement<E> * c )
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
							return iterator(last);
						}
				};

				/**
				 * @brief these are helper classes for CircSLelement for
				 *	easy iteration in a range for loop.
				 *	It is not meant to be created by the bridges user. But
				 *	it may be returned by Bridges to provide an STL
				 * 	compliant list API.
				 */
				class CircSLelement_constlisthelper {
						typename bridges::datastructure::CircSLelement<E> const * start, *last;

					public:
						CircSLelement_constlisthelper (typename bridges::datastructure::CircSLelement< E > const * s)
							: start(s), last(s)
						{}

						class iterator {

								typename bridges::datastructure::CircSLelement< E > const  * current;
							public:
								iterator(    typename bridges::datastructure::CircSLelement< E > const   * c )
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
							return iterator(last);
						}
				};

		}; // end CircSLelement
		template <class E>
		using CircSLelement_List = typename CircSLelement<E>::CircSLelement_listhelper;
		template <class E>
		using CircSLelement_ConstList = typename CircSLelement<E>::CircSLelement_constlisthelper;

	}
} // namespace bridges
#endif
