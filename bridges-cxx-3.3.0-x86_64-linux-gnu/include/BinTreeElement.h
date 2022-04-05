#ifndef BT_ELEMENT_H
#define BT_ELEMENT_H

#include "TreeElement.h" //string, using std

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class can be used to create binary tree elements, derived from TreeElement
		 *
		 * This class can be used to create binary tree elements, with left and right
		 *	 children.
		 *
		 * @sa There is a tutorial about Binary Trees :
		 * https://bridgesuncc.github.io/tutorials/BinTree.html
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 6/12/15, 7/12/19
		 */

		template <typename E>
		class BinTreeElement : public TreeElement<E> {
			private:
				int leftPos = 0, rightPos = 1;
			public:
				/**
				 * Constructs a BinTreeElement with the provided value, label, left
				 * and right BinTreeElements.
				 * The defaults will be used if not provided.
				 *
				 * @param e The data to hold
				 * @param lab The label to show
				 * @param l The left TreeElement
				 * @param r The right TreeElement
				 */
				BinTreeElement(BinTreeElement* l, BinTreeElement* r, const E& e = E(),
					const string& lab = string()) : TreeElement<E>(e, lab) {
					this->addChild(l);
					this->addChild(r);
				}

				/**
				 * Constructs a BinTreeElement with the provided value and label,
				 *  setting the left and right BinTreeElement to NULL.
				 * The defaults will be used if not provided.
				 *
				 * @param e The data to hold
				 * @param lab The label to show
				 */
				BinTreeElement(const E& e = E(), const string& lab = string())
					: BinTreeElement(nullptr, nullptr, e, lab) {
				}

				/**
				 *	@return the data structure type
				 */
				virtual const string getDStype() const override {
					return "BinaryTree";
				}

				/**
				 *  Returns the left child
				 *	@return The left BinTreeElement
				 */
				virtual BinTreeElement* getLeft() {
					return static_cast<BinTreeElement*>(this->getChild(leftPos));
				}

				/**
				 *  Returns the left child - Constant version
				 *	@return The left BinTreeElement
				 */
				virtual const BinTreeElement* getLeft() const {
					return static_cast<const BinTreeElement*>(this->getChild(leftPos));
				}

				/**
				 *	Sets left child to "l"
				 *
				 *	@param l  left child pointer
				 */
				void setLeft(BinTreeElement* l) {
					this->setChild(leftPos, l);
				}

				/**
				 *  Returns the right child
				 *	@return The right BinTreeElement
				 */
				virtual BinTreeElement* getRight() {
					return static_cast<BinTreeElement*>(this->getChild(rightPos));
				}

				/**
				 *  Returns the right child - Constant version
				 *	@return The right BinTreeElement
				 */
				virtual const BinTreeElement* getRight() const {
					return static_cast<const BinTreeElement*>(this->getChild(rightPos));
				}

				/**
				 *	Sets right to "r"
				 *
				 *	@param r  right child pointer
				 */
				void setRight(BinTreeElement* r) {
					this->setChild(rightPos, r);
				}
		}; //end of BinTreeElement class
	}
}//end of bridges namespace
#endif
