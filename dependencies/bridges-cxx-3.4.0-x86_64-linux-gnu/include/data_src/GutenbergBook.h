#ifndef GUTENBERG_BOOK_H

#define GUTENBERG_BOOK_H
#include <string>
using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Gutenberg Book object (meta data and book's full text)
		 *
		 * This is a convenience class provided for  users who wish to use this
		 * data source as part of their application. It provides an API that makes
		 * it easy to access the attributes of this data set.
		 *
		 * Objects of this type are typically not constructed by the user 
		 * but returned by a call to our Gutenberg API such as 
		 * bridges::DataSource::getGutenbergBookMetaData(), with
		 * an optional book id (integer) as a parameter.

		 * The object does not contain the text of the book itself. Though it 
		 * can be obtained using bridges::DataSource::getGutenbergBookText()

		 * @sa A tutorial of how to use the Gutenberg data in BRIDGES is 
		 * available: https://bridgesuncc.github.io/tutorials/Data_Gutenberg.html
		 *
		 * @author Kalpathi Subramanian
		 * @date   2/1/17, 12/28/20, 6/9/21
		 *
		 */

		class GutenbergBook {
				string title;
				int id;
				string loc_class;
				vector<string> authors;
				string lang, date_added;
				vector<string> genres;

			public:
				/**
				 * Default Constructor
				 */
				GutenbergBook() 
					  : title(""), lang(""), date_added(""), id(0), loc_class ("") {
				}

				/**
				 * Constructor
				 *
				 * @param titl 	   	book title
				 * @param id        book id
				 * @param loc       book's library of congress class
				 * @param auth   	book authors
				 * @param lng       language
				 * @param genr		genres of book
				 * @param da        date added
				 */
				GutenbergBook(const string& titl, const int& book_id, const vector<string>& auth, 
					const string& lng, const vector<string>& genr, const string& da) 
					: title(titl), id(book_id), authors(auth), lang(lng), genres(genr), date_added(da) {
				}

				/**
				 * get name of author
				 * @return authorName
				 */
				vector<string> getAuthors() const {
					return authors;
				}
				/**
				 * set names of authors
				 * @param auth   	name of author
				 */
				void setAuthors(const vector<string>& auth) {
					this->authors = auth;
				}

				/**
				 * get  book id
				 * @return   book's id
				 */
				int getId() const {
					return id;
				}
				/**
				 * set book id
				 * @param id  id of book to set
				 */
				void setId(const int& id) {
					this->id = id;
				}

				/**
				 * get  book title
				 * @return   book's title
				 */
				string getTitle() const {
					return title;
				}
				/**
				 * set book title
				 * @param title  title of book to set
				 */
				void setTitle(const string& titl) {
					this->title = titl;
				}

				/**
				 * get  Library of Congress class
				 * @return   book's LOC class
				 */
				string getLoc() const {
					return loc_class;
				}
				/**
				 * set book's LOC class
				 * @param loc class of book to set
				 */
				void setLoc(const string& loc) {
					this->loc_class = loc;
				}

				/**
				 * get book's language
				 * @return language of book
				 */
				string  getLang() const {
					return lang;
				}
				/**
				 * set book's language
				 * @param lang   	book's language to be set
				 */
				void setLang(const string& lang)  {
					this->lang = lang;
				}

				/**
				 * get book's genres
				 * @return genres of book
				 */
				vector<string>  getGenres() const {
					return genres;
				}
				/**
				 * set book's genres
				 * @param genre genres of book to be set
				 */
				void setGenres(const vector<string>& genre)  {
					this->genres = genre;
				}

				/**
				 * set book's subjects
				 * @return subjects covered by the book
				 */
				string  getDateAdded() const {
					return date_added;
				}
				/**
				 * set book added date
				 * @param da   date added to collection
				 */
				void setDateAdded(const string& da)  {
					this->date_added = da;
				}
		};

	}
}// namespace bridges

#endif

