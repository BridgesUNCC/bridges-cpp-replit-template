#ifndef SHAKESPEARE_H

#define SHAKESPEARE_H

#include <string>

using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Shakespeare Data source object containing sonnets, poems and
		 *      plays
		 *
		 * This is a convenience class provided for  users who wish to use this
		 * data source as part of their application. It provides an API that makes
		 * it easy to access the attributes of this data set.
		 *
		 * One would not normally create an object of this type but 
		 * rather get one by calling 
		 * bridges::DataSource::getShakespeareData()
		 *
		 * @sa Refer to the tutorial on how to use this dataset: 
		 * 	https://bridgesuncc.github.io/tutorials/Data_Shakespeare.html

		 * @author Kalpathi Subramanian
		 * @date   1/16/17, 12/28/20
		 *
		 */


		class Shakespeare {
			private:
				string 	title,			// title of work
						type, 			// play, sonnet, ...
						text;			// content?

			public:
				/**
				 * Constructor
				 */

				Shakespeare()
					: title(""), type(""), text("") {
				}
				/**
				  * Constructor
				  *
				  * @param title title of sonnet, play or poem
				  * @param type (sonnet, play or poem)
				  * @param text full text of entity
				  */

				Shakespeare(const string& title, const string& type,
					const string& text)
					: title(title), type(type), text(text) {
				}
				/**
				  *  Get title of sonnet, play or poem
				  *  @return title  (string)
				  */

				string getTitle() const {
					return title;
				}
				/**
				 *  set title of sonnet, play or poem
				 *  @param title  (string) to be set
				 */

				void setTitle (const string& title) {
					this->title = title;
				}
				/**
				 *  Get type of sonnet, play or poem
				 *  @return type  (string)
				 */

				string getType() const {
					return type;
				}
				/**
				 *  set type to sonnet, play or poem
				 *  @param type  (string) to be set
				 */

				void setType (const string& type) {
					this->type = type;
				}
				/**
				 *  Get full text of  sonnet, play or poem
				 *  @return full text  (string)
				 */

				string getText() const {
					return text;
				}
				/**
				 *  set full text of  sonnet, play or poem
				 *  @param text  full text (string) to be set
				 */

				void setText (const string& text) {
					this->text = text;
				}
		};
	}
} //namespace bridges

#endif
