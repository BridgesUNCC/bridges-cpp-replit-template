#ifndef BT_ELEMENT_H
#define BT_ELEMENT_H

#include "TreeElement.h" //string, using std

namespace bridges {
	namespace datastructure {
		/**
		 * @brief This class can be used to create binary tree elements, derived from TreeElement
		 *
		 * This class can be used to create binary tree elements, with left and right subtrees
		 *
		 * @param E the application data type
		 *
		 * @author Kalpathi Subramanian
		 * @date 6/12/15
		 */
		template <typename E>
		class BTElement : public TreeElement<E> {
			private:
				int leftPos = 0, rightPos = 1;
			public:
				/**
				 * @brief Constructs a BTElement with the provided value, label, left
				 * and right BTElements.
				 *
				 * The defaults will be used if not provided.
				 *
				 * @param l The left TreeElement
				 * @param r The right TreeElement
				 * @param e The data to hold
				 * @param lab The label to show
				 */
				BTElement(BTElement* l, BTElement* r, const E& e = E(),
					const string& lab = string()) :
					TreeElement<E>(e, lab) {
					this->addChild(l);
					this->addChild(r);
				}
				/**
				 * @brief Constructs a BTElement with the provided value and label,
				 *	setting the left and right BTElement to nullptr.
				 *
				 * The defaults will be used if not provided.
				 *
				 * @param e The data to hold
				 * @param lab The label to show
				 */
				BTElement(const E& e = E(), const string& lab = string())
					: BTElement(nullptr, nullptr, e, lab) {}

				/**
				 *	@return the data structure type
				 */

				virtual const string getDStype() const override {
					return "BinaryTree";
				}

				/**
				 *	@return The left BTElement
				*/
				virtual BTElement* getLeft() {
					return static_cast<BTElement*>(this->getChild(leftPos));
				}
				/** Constant version */
				virtual const BTElement* getLeft() const {
					return static_cast<const BTElement*>(this->getChild(leftPos));
				}
				/** Sets left to "l" @param l The left BTElement */
				void setLeft(BTElement* l) {
					this->setChild(leftPos, l);
				}

				/** @return The right BTElement */
				virtual BTElement* getRight() {
					return static_cast<BTElement*>(this->getChild(rightPos));
				}

				/** Constant version */
				virtual const BTElement* getRight() const {
					return static_cast<const BTElement*>(this->getChild(rightPos));
				}
				/** Sets right to "r" @param r The right BTElement */
				void setRight(BTElement* r) {
					this->setChild(rightPos, r);
				}
		}; //end of BTElement class
	}
}//end of bridges namespace
#endif
