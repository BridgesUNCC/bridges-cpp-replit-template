#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

#include <JSONutil.h>
#include "DataStructure.h"
#include "Symbol.h"


/**
 * @brief The SymbolGroup object is a container object to hold a collection
 *	of primitive symbol objects  such as rectangles, polygons, circles, labels.
 *
 *	In this version, all symbols are individual primitives; future versions
 *	 will support groups within groups, thereby facilitating a hierarchical
 * 	 model of symbols
 *
 * @sa

 * @author Kalpathi Subramanian
 *
 */

#ifndef SYMBOL_GROUP_H

#define SYMBOL_GROUP_H

namespace bridges {
	namespace datastructure {
		/**
		 * 	@brief the SymbolGroup represents a collection of symbols (shapes,
		 *		polygons, and text) to visualize in Bridges
		 *
		 * 	@author Kalpathi Subramanian
		 *	@date 3/31/21
		 *
		 */
		class SymbolGroup : public  Symbol {
			private:

				// symbols in this group
		  std::vector<std::shared_ptr<Symbol>> symbols;
		  
			public:
				/**
				 *	Constructors
				 */
				SymbolGroup() {
					symbols.clear();
				}

				/**
				 *   @brief This method adds a symbol to the collection
				 *
				 *   @param s  symbol being added
				 */

		  void addSymbolPtr(std::shared_ptr<Symbol> s) {
		    symbols.push_back(s);
		  }

		  template <typename T>
		  void addSymbol(T s) {
		    std::shared_ptr<T> pt = std::make_shared<T>(s);
		    addSymbolPtr ((std::shared_ptr<Symbol>)pt);
		  }

		  std::vector<std::shared_ptr<Symbol>> getAllSymbols() const{
		    return symbols;
		  }
		  
		  /**
				 * @brief This method returns the JSON representation of the
				 *		symbol group
				 *
				 * @return string  JSON string
				 */

				/**
				 *  @brief This method gets the shape type name
				 *
				 *  @return shape type
				 */
                virtual string getShapeType() const override {
                    return "group";
                }

				virtual const string getSymbolRepresentation() const override {

					using bridges::JSONUtil::JSONencode;

					
					// first get the group's representation
					string symbol_json = getSymbolAttributeRepresentation() + COMMA;

					// process the symbols in the group
					for (auto& entry : symbols) {
						symbol_json +=
							entry->getSymbolRepresentation();

						// remove the close curly brace 
						if (symbol_json.size())
							symbol_json.erase(symbol_json.size() - 1);

						// add parent id
						symbol_json += COMMA + QUOTE + "parentID" + QUOTE + COLON +
								to_string(getIdentifier()) + CLOSE_CURLY + COMMA;
					}
					// remove last comma
					if (symbols.size()) {
						symbol_json.erase(symbol_json.size() - 1);
					}

					return symbol_json;
				}
		};
	}
} // namespace bridges

#endif
