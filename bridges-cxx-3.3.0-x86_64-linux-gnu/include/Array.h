#ifndef ARRAY_H
#define ARRAY_H

#include "Element.h"

#include "Bridges.h"

namespace bridges {
	namespace datastructure {
		/**
		 * @brief The foundation of  BRIDGES array types. It is not meant to be used directly by students.
		 *
		 * This class can be used to create 1D, 2D, and 3D arrays of any type.
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 1/14/17, 7/12/19
		 */
		template <typename E>
		class Array : public DataStructure {

				friend class Element<E>;
			private:
				Element<E> *array_data;
				int num_dims;
				int dims[3];
				int size;

			protected:
				Array()
					: array_data(nullptr), num_dims(0), dims{0, 0, 0}, size(0) {
				}

				virtual ~Array() {
					if (array_data != nullptr)
						delete [] array_data;
				}

				/**
				 * @brief builds an array given the size
				 *
				 * @param sz  size of array
				 */
				Array(int sz)
					: array_data(nullptr) {
					int dim[] = {1, 1, sz};
					setSize(sz, dim);
				}

				/**
				 *  @brief Set the size of the array
				 *
				 *  @param[in] nd number of dimension
				 *  @param[in] dim the size of the dimensions
				 */
				void setSize(int nd, int *dim) {
					if (dim[0] <= 0 || dim[1] <= 0 || dim[2] <= 0) {
						cout << "Dimensions of array must be positive!" << endl
							<< "\tProvided dimensions: " << dim[0]
							<< "," << dim[1] << "," << dim[2] << endl;
						throw;
					}
					dims[0] = dim[0];
					dims[1] = dim[1];
					dims[2] = dim[2];
					num_dims = nd;
					size = dim[0] * dim[1] * dim[2];

					// allocate space for the array
					if (array_data != nullptr)
						delete[] array_data;
					array_data = new Element<E>[size];
				}
				/**
				 * @brief Get the dimensions of the array
				 *
				 * @param[out] dim  an array to return the dimensions
				 */
				void getDimensions(int *dim) {
					switch (num_dims) {
						case 1:
							dim[0] = dims[0];
							break;
						case 2:
							dim[0] = dims[0];
							dim[1] = dims[1];
							break;
						case 3:
							dim[0] = dims[0];
							dim[1] = dims[1];
							dim[2] = dims[2];
							break;
					}
				}

				int const * getDimensions() const {
					return dims;
				}
				/**
				 *
				 *  Get the object at index index  - 1D array
				 *
				 *  @param index index into the array
				 *
				 *  @return the Element at 'index'
				 */
				Element<E>& getElement(int index) {
					return array_data[index];
				}

				/**
				 *  @brief Get the object at index index  - 1D array
				 *
				 *  @param index - index into the array
				 *
				 *  @return the Element at 'index'
				 */
				Element<E> const & getElement(int index) const {
					return array_data[index];
				}

				/**
				 *  @brief Set the Element at index ind  - 1D array
				 *
				 *  @param ind index into the array
				 *  @param el Element object
				 */
				void setElement(int ind, Element<E> el) {
					array_data[ind] = el;
				}
			public:
				/**
				 *	Get the data structure type
				 *	@return data structure name
				 *
				 */
				virtual const string getDStype() const override {
					return "Array";
				}

				virtual const string getDataStructureRepresentation() const override final {
					using bridges::JSONUtil::JSONencode;

					vector<const Element<E>*> nodes;

					for (int k = 0; k < size; k++) {
						nodes.push_back(&array_data[k]);
					}
					//  first write out dimensions
					string array_json =
						QUOTE + "dims" + QUOTE + COLON +
						OPEN_BOX +
						JSONencode(dims[0]) + COMMA +
						JSONencode(dims[1]) + COMMA +
						JSONencode(dims[2]) +
						CLOSE_BOX + COMMA +

						QUOTE + "nodes"  + QUOTE + COLON +
						OPEN_BOX +
						generateJSON(nodes) +
						CLOSE_BOX + CLOSE_CURLY;

					return array_json;
				}

				Array(const Array&) = delete; //would be incorrect, so disabled.
				Array& operator=(const Array&) = delete; //would be incorrect, so disabled.


			private:
				const string generateJSON( const vector<const Element<E>*>& nodes) const {
					if (MAX_ELEMENTS_ALLOWED <= nodes.size()) {
						// cant exceed max number of elements
						throw "Max allowed elements(for visualization) exceeded.. " +
						to_string(nodes.size()) + " Must be less than " +
						to_string(MAX_ELEMENTS_ALLOWED);
					}
					// map the nodes to a sequence of ids, 0...N-1
					// then get the JSON string for nodes placeholder
					// nullptr prevents insertion of other nullptrs
					unordered_map<const Element<E>*, int> map{{nullptr, -1}};

					string nodes_JSON;

					int i = 0; // get the JSON string for nodes
					for (const auto* e : nodes) {
						if (map.emplace(e, i).second && ++i)  {
							// short circut only incriments i and gets rep
							// upon successful emplacement
							nodes_JSON += e->getElementRepresentation() + COMMA;
						}
					}
					map.erase(nullptr); //Remove trailing comma and nullptr entry
					if (nodes_JSON.size()) {
						nodes_JSON = nodes_JSON.erase(nodes_JSON.size() - 1);
					}

					return nodes_JSON;
				};


		}; // Array
	}
}// end namespace bridges

#endif
