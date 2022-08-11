#ifndef REDDIT_H
#define REDDIT_H

#include <string>

using std::string;

namespace bridges {
	namespace dataset {

/**
 * @brief  An object to represent a Reddit post, used along with the Reddit data source
 *
 * This is a convenience class provided for  users who wish to use this
 * data source as part of their application. It provides an API that makes
 * it easy to access the attributes of this data set.
 *
 * The Reddit object is typically not created by a student but rather
 * obtained from calling bridges::DataSource::getRedditData().
 *
 * Refer to tutorial for example of using this feature: https://bridgesuncc.github.io/tutorials/Data_Reddit.html
 *
 *
 * @author Erik Saule
 * @date   7/12/22
 *
 */
	  class Reddit {

			private:
		  std::string id, title, author, subreddit, url, text;
		  int score, comment_count, post_time;
		  float vote_ratio;

			public:
		  Reddit() = default;

    	/**
	 *           @brief return id of the reddit post
	 *
	 *   @return id
	 */
		  std::string getID() const {
		    return id;
		  }

		  void setID(std::string i) {
		    id = i;
		  }

    	/**
	 *           @brief return the title of the reddit post
	 *
	 *   @return title
	 */
		  std::string  getTitle() const {
		    return title;
		  }
		  
		  void  setTitle(std::string titl) {
					title = titl;
				}

    	/**
	 *           @brief return the author of the reddit post
	 *
	 *   @return author's username
	 */
		  std::string getAuthor() const {
		    return author;
		  }

		  void setAuthor(string auth) {
					author = auth;
				}

    	/**
	 *           @brief return the score (upvotes - downvotes) of the reddit post
	 *
	 *   @return score (upvotes - downvotes)
	 */
		  int getScore() const {
					return score;
				}

				void setScore(int sc){
					score = sc;
				}

    /**
     *   @brief ratio of upvotes to downvotes of the reddit post
     *
     *   @return vote ratio
     */
				float  getVoteRatio() const {
					return vote_ratio;
				}

				void setVoteRatio(float vr) {
					vote_ratio = vr;
				}

    /**
     *   @brief number of comments of the reddit post
     *
     *   @return number of comments
     */
				int  getCommentCount()  const {
					return comment_count;
				}

				void setCommentCount(int cnt) {
					comment_count = cnt;
				}

    /**
     *   @brief name of the subreddit the post appeared in
     *
     *   @return subreddit name
     */
		  std::string  getSubreddit() const {
					return subreddit;
				}

		  void setSubreddit(std::string sr) {
					subreddit = sr;
				}

    /**
     *   @brief time the post was made (UNIX time)
     *
     *   @return unix time
     */
				int  getPostTime() const {
					return post_time;
				}

				void  setPostTime(int pt) {
					post_time = pt;
				}

    /**
     *   @brief  URL associated with the post. 
     *
     *   This could be the url of the reddit post itself or the URL of an associated article/video
     *
     *
     *   @return URL
     */
		  std::string  getURL() const {
					return url;
				}

				void  setURL(std::string u) {
					url = u;
				}
		  
    /**
     *   @brief   returns the text of the reddit post.
     *
     *   The text of the reddit post. Often in markdown format.
     *
     *  The text could be empty if the reddit post is just a link to a video or an article
     *
     *
     *   @return full text of the reddit post
     */
		  std::string  getText() const {
					return text;
				}

				void setText(std::string txt) {
					text = txt;
				}
		};
	};
};
#endif
