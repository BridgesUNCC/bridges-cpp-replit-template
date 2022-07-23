#ifndef BOOK_H

#define BOOK_H
#include <string>
using namespace std;

namespace bridges {
	namespace dataset {
		/**
		 * @brief  A Book object, used along with the books data source.
		 *
		 * This is a convenience class provided for  users who wish to use this
		 *	data source as part of their application. It provides an API that makes
		 *  it easy to access the attributes of this data set.
		 *
		 * Refer to tutorial examples to using this data source in data structure
		 *  assignments.
		 *
		 * @author Kalpathi Subramanian
		 * @date   1/16/17
		 *
		 */

		class Book {
				string authorName;
				int authorBirth,
					authorDeath;
				string title;
				vector<string> lang, genre, subject;
				int numChars, numWords, numSentences, numDifficultWords;
				string url;
				int downloads;

			public:
				Book ()
					: authorName(""), authorBirth(0), authorDeath(0),
					  title(""), lang(), genre(), subject(),
					  numChars(0), numWords(0), numSentences(0), numDifficultWords(0),
					  url(""), downloads(0) {
				}

				Book(const string& authorName, int authorBirth, int authorDeath,
					const string& title, const vector<string>& lang, const vector<string>& genre,
					const vector<string>& subject, int numChars, int numWords,
					int numSentences, int numDifficultWords, const string& url,
					int downloads)
					: authorName(authorName), authorBirth(authorBirth), authorDeath(authorDeath),
					  title(title), lang(lang), genre(genre), subject(subject),
					  numChars(numChars), numWords(numWords), numSentences(numSentences), numDifficultWords(numDifficultWords),
					  url(url), downloads(downloads) {
				}

				string getAuthorName() const {
					return authorName;
				}
				void setAuthorName(const string& authorName) {
					this->authorName = authorName;
				}

				int getAuthorBirth() const {
					return authorBirth;
				}
				void setAuthorBirth(int authorBirth) {
					this->authorBirth = authorBirth;
				}

				int getAuthorDeath() const {
					return authorDeath;
				}
				void setAuthorDeath(int authorDeath) {
					this->authorDeath = authorDeath;
				}

				string getTitle() const {
					return title;
				}
				void setTitle(const string& title) {
					this->title = title;
				}

				vector<string>  getLang() const {
					return lang;
				}
				void setLang(const vector<string>& lang)  {
					this->lang = lang;
				}

				vector<string>  getGenre() const {
					return genre;
				}
				void setGenre(const vector<string>& genre)  {
					this->genre = genre;
				}

				vector<string>  getSubject() const {
					return subject;
				}
				void setSubject(const vector<string>& subject)  {
					this->subject = subject;
				}

				string getURL() const {
					return url;
				}
				void setURL(const string& url) {
					this->url = url;
				}

				int getNumChars() const {
					return numChars;
				}
				void setNumChars(int numChars) {
					this->numChars = numChars;;
				}

				int getNumWords() const {
					return numWords;
				}
				void setNumWords(int numWords) {
					this->numWords = numWords;
				}

				int getNumSentences() const {
					return numSentences;
				}
				void setNumSentences(int numSentences) {
					this->numSentences = numSentences;
				}

				int getNumDifficultWords() const {
					return numDifficultWords;
				}
				void setNumDifficultWords(int numDifficultWords) {
					this->numDifficultWords = numDifficultWords;
				}

				int getDownloads() const {
					return downloads;
				}

				void setDownloads(int downloads) {
					this->downloads = downloads;
				}
		};

	}
}// namespace bridges

#endif

