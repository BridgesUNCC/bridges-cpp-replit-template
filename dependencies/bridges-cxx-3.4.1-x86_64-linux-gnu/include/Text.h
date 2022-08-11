
#ifndef  LABEL_H

#define LABEL_H

#include "DataStructure.h"
#include "Symbol.h"
#include <vector>
#include <cmath>

using namespace std;

/**
 */



namespace bridges {
	namespace datastructure {
		/**
		 * @brief This is a label object and used for defining text labels
		 *   as part of the symbol collection.
		 *
		 * @author Kalpathi Subramanian
		 * @date 12/23/18, 12/28/20
		 *
		 */
		class Text : public Symbol {
			private:
				// label anchor location
		  double origin[2];

				// label attributes
		  double 	fontSize = 12;
				string 	*anchorType = nullptr,
						*anchorAlignmentLR = nullptr, 
						*anchorAlignmentTB = nullptr;

				string label_text = string();

			public:

				/**
				 * 	constructors
				 */
				Text() :  
						anchorType(nullptr),
						anchorAlignmentLR(nullptr),
						anchorAlignmentTB(nullptr) {

					origin[0] = origin[1] = 0.0f;
				}

		  Text(const Text& t):
		    Symbol(t) {
		    this->label_text = t.label_text;
		    this->origin[0] = t.origin[0];
		    this->origin[1] = t.origin[1];
		    this->fontSize = t.fontSize;
		    
		    if (t.anchorType)
		      this->anchorType = new string(*(t.anchorType));
		    if (t.anchorAlignmentTB)
		      this->anchorAlignmentTB = new string(*(t.anchorAlignmentTB));
		    if (t.anchorAlignmentLR)
		      this->anchorAlignmentLR = new string(*(t.anchorAlignmentLR));
		  }

		  Text& operator= (const Text& t) {
		    Symbol::operator=(t);
		    
		    this->label_text = t.label_text;
		    this->origin[0] = t.origin[0];
		    this->origin[1] = t.origin[1];

		    if (anchorType) {
		      delete anchorType;
		      anchorType = nullptr;
		    }
		    if (anchorAlignmentLR) {
		      delete anchorAlignmentLR;
		      anchorAlignmentLR = nullptr;
		    }
		    if (anchorAlignmentTB) {
		      delete anchorAlignmentTB;
		      anchorAlignmentTB = nullptr;
		    }

		    this->fontSize = t.fontSize;
		    if (t.anchorType)
		      this->anchorType = new string(*(t.anchorType));
		    if (t.anchorAlignmentTB)
		      this->anchorAlignmentTB = new string(*(t.anchorAlignmentTB));
		    if (t.anchorAlignmentLR)
		      this->anchorAlignmentLR = new string(*(t.anchorAlignmentLR));

		    return *this;
		  }
		  
		  /**
				 * Create a label object with label l
				 *
				 * @param l  label
				 */
				Text (string l): Text() {
					label_text = l;
				}

				~Text() {
					if (anchorType)
						delete anchorType;
					if (anchorAlignmentLR)
						delete anchorAlignmentLR;
					if (anchorAlignmentTB)
						delete anchorAlignmentTB;
				}

				/*
				 * @brief Get Data Structure name
				 * @return name of data type
				 */
				virtual string getShapeType() const override {
					return "text";
				}
				/**
				 * @brief Set the label text
				 *
				 * @param lbl the text to set
				 */
				Text& setText(string lbl) {
					label_text = lbl;

					return *this;
				}

				/**
				 * @brief Get the symbol label
				 *
				 * @return  the text label
				 */
				string getText() const {
					return label_text;
				}

				/**
				 * @brief This method sets the label origin; 
				 *
				 * @param  loc coordinates of label location
				 *
				 */
				Text& setAnchorLocation(float *loc) {
					origin[0] = loc[0];
					origin[1] = loc[1];

					return *this;
				}

				/**
				 * @brief This method sets the label origin; 
				 *
				 * @param  locx  x coordinate of label location
				 * @param  locy  y coordinate of label location
				 *
				 */
				Text& setAnchorLocation(float locx, float locy) {
					origin[0] = locx;
					origin[1] = locy;

					return *this;
				}

				/**
				 * Sets the alignment parameters for the text label
				 *
				 * @param typeLR valid parameters are "left", "middle", and "right"
				 * @param typeTB valid parameters are "top", "bottom", 
				 *	"embottom", "emtop", "middle"
				 *
				 * @return  symbol
				 **/
				Text& setAnchorAlignment(string typeLR, string typeTB) {
					if (!anchorAlignmentLR)
						anchorAlignmentLR = new string;
					if (!anchorAlignmentTB)
						anchorAlignmentTB = new string;


					*anchorAlignmentLR = typeLR;
					*anchorAlignmentTB = typeTB;

					return *this;
				}
	
				/**
				 * @brief This method gets the label anchor location 
				 *
				 * @return anchor location x
				 *
				 */
				double getAnchorLocationX() {
					return origin[0];
				}

				/**
				 * @brief This method gets the label anchor location 
				 *
				 * @return anchor location y
				 *
				 */
				double getAnchorLocationY() {
					return origin[1];
				}
		  
				/**
				 * @brief This method sets the label's anchor type
				 *
				 * @param  type  string
				 *
				 * @return  symbol
				 */
				Symbol& setAnchorType(string type) {
					if (!anchorType)
						anchorType = new string;

					*anchorType = type;

					return *this;
				}

				/**
				 * @brief This method gets the label's anchor type
				 *
				 * @return  type  
				 *
				 */
				string  getAnchorType() {
					if (!anchorType)
						throw "Anchor type not set!";

					return *anchorType;
				}
				
				/**
				 * @brief This method sets the font size
				 *
				 * @param sz  font size
				 *
				 * @return  symbol
				 */
				Symbol& setFontSize(double sz) {
				  fontSize = sz;

					return *this;
				}

				/**
				 * @brief This method gets the font size
				 *
				 * @return   font size
				 *
				 */
				double getFontSize() {
					return fontSize;
				}


				/**
				 * @brief This method returns the JSON representation of the shape
				 *
				 * @return string  JSON string
				 */
				const string getSymbolRepresentation() const override {

					string shape_json = getSymbolAttributeRepresentation();
					if (anchorType)  
						shape_json += QUOTE + "anchorType" + QUOTE + COLON + 
								QUOTE + *anchorType + QUOTE + COMMA;

					if (anchorAlignmentLR)
						shape_json += QUOTE + "anchor-alignmentLR" + QUOTE + COLON +
								QUOTE + *anchorAlignmentLR + QUOTE + COMMA;

					if (anchorAlignmentTB)
						shape_json += QUOTE + "anchor-alignmentTB" + QUOTE + COLON +
								QUOTE + *anchorAlignmentTB + QUOTE + COMMA;

					shape_json += QUOTE + "font-size" + QUOTE + COLON +  
								to_string(fontSize)  + COMMA; 

					shape_json +=
						QUOTE + "anchor-location" + QUOTE + COLON +  
							OPEN_BOX + 
								to_string(origin[0]) + COMMA + to_string(origin[1]) +
							CLOSE_BOX + COMMA + 
						QUOTE + "text" + QUOTE + COLON +   QUOTE + label_text + QUOTE +
								CLOSE_CURLY;


					return shape_json;
				}
		};
	}
} // namespace bridges

#endif
