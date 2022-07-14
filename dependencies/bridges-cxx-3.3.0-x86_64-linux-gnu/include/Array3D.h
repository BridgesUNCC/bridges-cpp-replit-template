#ifndef ARRAY_3D_H
#define ARRAY_3D_H

#include "Element.h"
#include "Array.h"


namespace bridges {
	namespace datastructure {
		/**
		 * @brief A BRIDGES array type
		 *
		 * This class can be used to create 3D arrays of any type.
		 *
		 * The access to the values stored are done
		 * directly using bracket operators such as
		 *
		 * \code{.cpp}
		 * Array3D<std::string> arr(19, 30, 30);
		 * arr [12][25][12] = "hello!";
		 * \endcode
		 *
		 * Entries in the array can be styled by showing a
		 * label and changing the color of an entry. This is
		 * achieved by styling the underlying element to a
		 * particular entry of the array such as:
		 *
		 * \code{.cpp}
		 * Array3D<std::string> arr(19, 30, 3);
		 * arr.getElement(12, 25, 0).setColor("yellow");
		 * arr.getElement(12, 25, 2).setLabel("Hi there");
		 * \endcode
		 *
		 *
		 * @sa See tutorial at: https://bridgesuncc.github.io/tutorials/Array.html
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 7/16/19
		 */
		template <typename E>
		class Array3D : public Array<E> {
			private:
				int num_slices, num_rows, num_cols;

				//preventing the creation of blank array3d
				Array3D() {
					num_slices = num_rows = num_cols = 0;
				}
			public:


				virtual ~Array3D() {
				}

				/**
				 * builds a 3D array.
				 * param slices number of slices (depth)
				 * param rows number of rows (height)
				 * param columns number of columns (width)
				 */
				Array3D(int slices, int rows, int columns)
					: num_slices(slices), num_rows(rows), num_cols(columns) {
					int dim[] = {slices, rows, columns};
					this->setSize(3, dim);
				}
				/**
				 *	Gets the number of rows of the 3D array
				 *  @return number of rows
				 */
				int getNumRows () {
					return num_rows;
				}
				/**
				 *	Gets the number of columns of the 3D array
				 *  @return number of columns
				 */
				int getNumColumns () {
					return num_cols;
				}
				/**
				 *	Gets the number of slices of the 3D array
				 *  @return number of slices
				 */
				int getNumSlices () {
					return num_slices;
				}

				/**
				 *
				 *  Get the object at (slice, row, col) for 3D arrays
				 *
				 *  @param slice  - slice index
				 *  @param row  - row index
				 *  @param col  - column index
				 *
				 *  @return Element<E>  object at slice, row, col
				 */
				Element<E>& getElement(int slice, int row, int col) {
					return Array<E>::getElement(slice * num_cols * num_rows + row * num_cols + col);
				}

				/**
				 *
				 *  Get the object at (slice, rows, col) for 3D arrays
				 *
				 *  @param col column index
				 *  @param row row index
				 *  @param slice slice index
				 *
				 *  @return the Element at (slice, rows, col)
				 */
				Element<E> const & getElement(int slice, int row, int col) const {
					return Array<E>::getElement(slice * num_cols * num_rows + row * num_rows + col);
				}

				/**
				 *
				 *  Set the object at index slice, row, col  - 3D array
				 *
				 *  @param slice slice index into the array
				 *  @param col column index into the array
				 *  @param row row index into the array
				 *  @param el - Element object
				 */
				void setElement(int slice, int row, int col, Element<E> el) {
					setElement(slice * num_rows * num_cols + row * num_cols + col, el);
				}


				/**
				 *  @brief Bracker_helper class to make [][] operators work on
				 *	array 2d. You should never use it directly
				 */
				struct Bracket_helper2 {
					Array3D<E>& arr;
					int x;
					int y;
					Bracket_helper2(Array3D<E>& a, int x, int y) : arr(a), x(x), y(y) {}

					E& operator[] (int z) {
						return arr.getElement(x, y, z).getValue();
					}
				};


				/**
				 *  @brief Bracker_helper class to make [] operators work on
				 *	array 2d. You should never use it directly
				 */
				struct Bracket_helper {
					Array3D<E>& arr;
					int x;
					Bracket_helper(Array3D<E>& a, int x) : arr(a), x(x) {}

					Bracket_helper2 operator[] (int y) {
						return Bracket_helper2(arr, x, y);
					}
				};

				///@brief enables using the bracket [] operator
				Bracket_helper operator[] (int index) {
					return Bracket_helper(*this, index);
				}

				/**
				 *  @brief helper2 const class is to make [][] operators
				 *	work on array 2d. You should never use it directly
				 */
				struct Bracket_helper2_const {
					Array3D<E> const & arr;
					int x;
					int y;
					Bracket_helper2_const(Array3D<E>& a, int x, int y) : arr(a), x(x), y(y) {}

					E const & operator[] (int z) const {
						return arr.getElement(x, y, z).getValue();
					}
				};


				/**
				 *  @brief helper const class is to make [][] operators
				 *	work on array 2d. You should never use it directly
				 */
				/// @brief helper class to make [][] operators work on array 2d. You should never use it directly
				struct Bracket_helper_const {
					Array3D<E> const& arr;
					int x;
					Bracket_helper_const(Array3D<E>& a, int x) : arr(a), x(x) {}

					Bracket_helper2_const operator[] (int y) const {
						return Bracket_helper2(arr, x, y);
					}
				};

				/**
				 *  @brief helper const class is to make [] operators
				 *	work on array 2d. You should never use it directly
				 */
				Bracket_helper_const operator[] (int index) const {
					return Bracket_helper_const(*this, index);
				}

		}; // Array3D
	}
}// end namespace bridges

#endif
