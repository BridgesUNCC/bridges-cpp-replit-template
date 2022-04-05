#ifndef ELE_ARRAY_H
#define ELE_ARRAY_H

#include "Element.h"
namespace bridges {
	namespace datastructure {
		/**
		 *  @brief  Currently unused class, ignore
		 *
		 */

		template <typename E, size_t X, size_t Y = 1, size_t Z = 1>
		class ElementArray : public DataStructure {
			private:
				array<array<array<Element<E>*, Z>, Y>, X> data;
			public:
				ElementArray() {
					for (const auto& x : data) { // each Array<Array> in data
						for (const auto& y : x) { // each Array in Array<Array>
							y.fill(nullptr); //initializes to nullptr
						}
					}
				}
				Element<E>* getValue(size_t x, size_t y = 0, size_t z = 0) {
					return data[x][y][z];
				}
				const Element<E>* getValue(size_t x, size_t y = 0, size_t z = 0) const {
					return data[x][y][z];
				}
				void setValue(Element<E>* el, size_t x, size_t y = 0, size_t z = 0) {
					data[x][y][z] = el;
				}

				virtual const string getDStype() const override {
					return "Array";
				}
			private:
				virtual const pair<string, string> getDataStructureRepresentation() const override final {
					unordered_set<const Element<E>*> nodes;
					for (const auto& x : data) { // each Array<Array> in data
						for (const auto& y : x) { // each Array in Array<Array>
							for (const auto& z : y) { // each Element* in Array
								if (z) {
									nodes.emplace(z);
								}
							}
						}
					}
					return Element<E>::generateJSON(nodes); // generate the JSON
				}
		};
	}
}
#endif
