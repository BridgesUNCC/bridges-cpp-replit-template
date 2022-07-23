#ifndef ARRAY_1D_H
#define ARRAY_1D_H

#include "Array.h"
#include "Element.h"

namespace bridges {
	namespace datastructure {
		/**
		 * @brief A BRIDGES 1D array type.
		 *
		 * This class can be used to create 1D arrays of any type.
		 *
		 *
		 * The class stores an array of E where each entry can
		 * be styled.
		 *
		 * The access to the values stored are done
		 * directly using bracket operators such as
		 *
		 * \code{.cpp}
		 * Array1D<std::string> arr(19);
		 * arr [12] = "hello!";
		 * \endcode
		 *
		 * Entries in the array can be styled by showing a
		 * label and changing the color of an entry. This is
		 * achieved by styling the underlying element to a
		 * particular entry of the array such as:
		 *
		 * \code{.cpp}
		 * Array1D<std::string> arr(19);
		 * arr.getElement(12).setColor("yellow");
		 * arr.getElement(12).setLabel("Hi there");
		 * \endcode
		 *
		 * The array support range for loop so you can get to all elements in the array using :
		 *
		 * \code{.cpp}
		 * Array1D<std::string> arr(19);
		 * for (auto mystring : arr) {
		 *   std::cout<<mystring<<"\n";
		 * }
		 * \endcode
		 *
		 * @sa See tutorial at: https://bridgesuncc.github.io/tutorials/Array.html
		 *
		 * @param E the application data type
		 * @author Kalpathi Subramanian, Erik Saule
		 * @date 7/16/19
		 */
		template <typename E>
		class Array1D : public Array<E> {

			private:
				int size;

				///preventing Array1D to be created without a size
				Array1D() {}

			public:
				virtual ~Array1D() {}

				/// @brief builds an array given size
				///
				///@param sz size of the array
				Array1D(int sz) {
					int dim[] = {sz, 1, 1};
					this->setSize(1, dim);
				}

				///@brief access Array[indx]
				E & operator[](int indx) {
					return  Array<E>::getElement(indx).getValue();
				}

				///@brief access Array[indx]
				E const & operator[](int indx) const {
					return  Array<E>::getElement(indx).getValue();
				}

				///@brief access the element that stores Array[indx]
				///
				///@param indx index of the Element<E> to access
				Element<E>& getElement(int indx) {
					return  Array<E>::getElement(indx);
				}

				///@brief access the element that stores Array[indx]
				///
				///@param indx index of the Element<E> to access
				Element<E> const & getElement(int indx) const {
					return  Array<E>::getElement(indx);
				}

				///@brief change the element that stores Array[indx]
				///
				///@param indx index of the Element<E> to change
				///@param e element to change it to
				void setElement(int indx, const Element<E>& e ) {
					return  Array<E>::setElement(indx, e);
				}


				///enabling range for loops
				class iterator {
						Array1D<E>& arr;
						int index;
					public:
						iterator (Array1D<E>& a, int ind) : arr(a), index(ind) {}
						E const & operator* () const {
							return arr[index];
						}
						E & operator* () {
							return arr[index];
						}
						iterator& operator++ () {
							++index;
							return *this;
						}
						iterator& operator-- () {
							--index;
							return *this;
						}
						iterator& operator++ (int) {
							++index;
							return *this;
						}
						iterator& operator-- (int) {
							--index;
							return *this;
						}
						bool operator == (const iterator& it) const {
							return (&arr) == &(it.arr)
								&& index == it.index;
						}
						bool operator != (const iterator& it) const {
							return !(operator==(it));
						}
				};

				///@brief enables range for loops
				iterator begin() {
					return iterator(*this, 0);
				}
				///@brief enables range for loops
				iterator end() {
					return iterator(*this, Array<E>::getDimensions()[0]);
				}

				///enabling iterator loops in const contexts
				class const_iterator {
						Array1D<E> const & arr;
						int index;
					public:
						const_iterator (Array1D<E> const& a, int ind) : arr(a), index(ind) {}
						E const & operator* () const {
							return arr[index];
						}
						const_iterator& operator++ () {
							++index;
							return *this;
						}
						const_iterator& operator-- () {
							--index;
							return *this;
						}
						const_iterator& operator++ (int) {
							++index;
							return *this;
						}
						const_iterator& operator-- (int) {
							--index;
							return *this;
						}
						bool operator == (const const_iterator& it) const {
							return (&arr) == &(it.arr)
								&& index == it.index;
						}
						bool operator != (const const_iterator& it) const {
							return !(operator==(it));
						}
				};

				///@brief enables range for loops
				const_iterator begin() const {
					return const_iterator(*this, 0);
				}
				///@brief enables range for loops
				const_iterator end() const {
					return iterator(*this, Array<E>::getDimensions()[0]);
				}

		}; // Array1D
		// use some aliases for accessing iterators
		template <class E>
		using Array1DIterator = typename Array1D<E>::iterator;
	}
}// end namespace bridges

#endif
