#ifndef LINE_CHART_H
#define LINE_CHART_H

#include <unordered_map>
#include <vector>
#include <string>
#include <DataStructure.h>
#include <JSONutil.h>

namespace bridges {
	namespace datastructure {
		/**
		 * @brief Show series of data or functions using a line chart.
		 *
		 * Line charts (https://en.wikipedia.org/wiki/Line_chart) are used to
		 * represent graphically functions such as f(x) = 3*x+1, or data such
		 * as temperature of a liquid on a stove as time passes. A individual
		 * function or a set of data is called "series".
		 *
		 * A series is represented by two arrays xdata and ydata such that
		 * there is a point at (xdata[0], ydata[0]), an other at (xdata[1],
		 * ydata[1]), ... One can add a series by passing the two arrays using
		 * setDataSeries() or add the arrays individually using setXData() and
		 * setYData().
		 *
		 * The different series have a label associated with them by default
		 * which can be disabled (see toggleSeriesLabel()).
		 *
		 * The data is typically shown with axes that use a linear
		 * scale. However, the scale can be changed to logarithmic for each
		 * axis individually (see toggleLogarithmicX() and
		 * toggleLogarithmic()).
		 *
		 * The LineChart can have a title (see getTitle() and setTitle()) and
		 * a subtitle (see setSubTitle() and getSubTitle()).
		 *
		 * @author Erik Saule, Kalpathi Subramanian
		 *
		 * @date 7/16/19
		 *
		 *
		 **/
		class LineChart : public DataStructure {

			private:
				string plotTitle;
				string plotSubtitle;
				string xLabel;
				string yLabel;
				bool mouseTrack;
				bool dataLabel;
				bool logarithmicx;
				bool logarithmicy;

				unordered_map<string, vector<double>> xaxisData;
				unordered_map<string, vector<double>> yaxisData;

			public:
				LineChart() {
					plotTitle = "";
					plotSubtitle = "";
					yLabel = "";
					xLabel = "";
					mouseTrack = false;
					dataLabel = true;
					logarithmicx = false;
					logarithmicy = false;
				}

				/**
				 * @brief Get the data type
				 * @return name of the data type (used internally)
				 */
				virtual const string getDStype() const override {
					return "LineChart";
				}

				/**
				 * @brief Enables or disables mouse tracking
				 *
				 * Mouse tracking show the value of a data point when the mouse
				 * hovers on a data point.
				 *
				 * @param val Should mouse tracking be activated or not.
				 **/
				void toggleMouseTrack(bool val) {
					mouseTrack = val;
				}

				/**
				 * @brief Enables or disables series labels.
				 *
				 * When enabled, the name of the series will be shown on the line
				 * chart.
				 *
				 * @param val Should series be labeled or not
				 **/
				void toggleSeriesLabel(bool val) {
					dataLabel = val;
				}

				/**
				 * @brief Change the X-axis scale to logarithmic.
				 *
				 * When enabled, the X-axis scale becomes logarithmic (as opposed to linear).
				 *
				 * @param val Should the X-axis use a logarithmic scale?
				 **/
				void toggleLogarithmicX(bool val) {
					logarithmicx = val;
				}

				/**
				 * @brief Change the Y-axis scale to logarithmic.
				 *
				 * When enabled, the Y-axis scale becomes logarithmic (as opposed to linear).
				 *
				 * @param val Should the Y-axis use a logarithmic scale?
				 **/
				void toggleLogarithmicY(bool val) {
					logarithmicy = val;
				}

				/**
				 * @brief Title of the plot
				 *
				 * @param t the title to be shown
				 **/
				void setTitle(string t) {
					plotTitle = t;
				}

				/**
				 * @brief Title of the plot
				 *
				 * @return the title to be shown
				 **/
				string getTitle() const {
					return plotTitle;
				}

				/**
				 * @brief Subtitle of the plot
				 *
				 * @param s the subtitle to be shown
				 **/
				void setSubTitle(string s) {
					plotSubtitle = s;
				}

				/**
				 * @brief Subtitle of the plot
				 *
				 * @return the subtitle to be shown
				 **/
				string getSubTitle() const {
					return plotSubtitle;
				}


				/**
				 * @brief Change the label for the Y-axis
				 *
				 * @param yaxisName label to show for the Y-axis
				 **/
				void setYLabel(string yaxisName) {
					yLabel = yaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				string getYLabel() const {
					return yLabel;
				}

				/**
				 * @brief Change the label for the X-axis
				 *
				 * @param xaxisName label to use for the X-axis
				 **/
				void setXLabel(string xaxisName) {
					xLabel = xaxisName;
				}

				/**
				 * @brief Returns the label for the Y-axis
				 *
				 * @return label shown for the Y-axis
				 **/
				string getXLabel() const {
					return xLabel;
				}


				/**
				 * @brief Add a series (or update it)
				 *
				 * @param seriesName indicates the series to add (or change)
				 * @param xdata the X data in the series
				 * @param ydata the Y data in the series
				 **/
				void setDataSeries(string seriesName, vector<double> xdata, vector<double> ydata) {
					setXData(seriesName, xdata);
					setYData(seriesName, ydata);
				}


				/**
				 * @brief Changes the X data for a series
				 *
				 * @param series indicates the series to get
				 * @param xdata the X data in the series
				 **/
				void setXData(string series, vector<double> xdata) {
					xaxisData[series] =  xdata;
				}

				/**
				 * @brief Returns the X data for a series
				 *
				 * @param series indicate the series to get
				 * @return the X data of series or null if the series is not in there
				 **/
				vector<double> getXData(string series) {
					return  xaxisData[series];
				}

				/**
				 * @brief Changes the Y data for a series
				 *
				 * @param series indicates the series to get
				 * @param ydata the Y data in the series
				 **/
				void setYData(string series, vector<double> ydata) {
					yaxisData[series]  = ydata;
				}

				/**
				 * @brief Returns the Y data for a series
				 *
				 * @param series indicate the series to get
				 * @return the Y data of series or null if the data is not in there
				 **/
				vector<double> getYData(string series) {
					return yaxisData[series];
				}

			private:
				/**
				 * @brief check if the LineChart is in a valid state.
				 *
				 * Checks whether the xdata and ydata are present for each series.
				 * Checks whether the xdata and ydata are the same length for each series.
				 * Checks whether the data are positive if logarithmic scales are used.
				 *
				 * Print an error message to System.err if the data structure is in an invalid state.
				 *
				 * @return whether it is in a valid state
				 */
				bool check() const {
					bool correct = true;
					for (auto& entry : xaxisData) {
						string series = entry.first;
						vector<double> xdata = entry.second;
						vector<double> ydata = yaxisData.at(series);
						if (!ydata.size()) {
							cout << "Series \"" + series + "\" has xdata but no ydata";
							correct = false;
						}
						if (xdata.size() != ydata.size()) {
							cout << "Series \"" + series + "\" has xdata and ydata of different sizes";
							correct = false;
						}
						if (logarithmicx) {
							for (int i = 0; i < xdata.size(); ++i) {
								if (xdata[i] == 0) {
									cout << "Xaxis scale is logarithmic but series \"" + series
										+ "\" has xdata[" << i << "] = " <<  xdata[i]  <<
										" (should be stricly positive)";
								}
							}
						}
						if (logarithmicy) {
							for (int i = 0; i <  ydata.size(); ++i) {
								if (ydata[i] == 0) {
									cout << "Yaxis scale is logarithmic but series \"" +
										series + "\" has ydata[" <<  i <<  "] = "  <<  ydata[i] <<
										" (should be stricly positive)";
								}
							}
						}
					}
					for (auto& entry : yaxisData) {
						string series = entry.first;
						vector<double> ydata = entry.second;
						vector<double> xdata = xaxisData.at(series);
						if (!xdata.size()) {
							cout << "Series: " + series + " has ydata but no xdata";
							correct = false;
						}
						//Everything else already checked.
					}
					return correct;
				}

			public:
				virtual const string getDataStructureRepresentation() const override {
					using bridges::JSONUtil::JSONencode;
					check();
					string xaxis_json = "";
					for (auto& entry : xaxisData) {
						string key = entry.first;
						vector<double> value = entry.second;

						xaxis_json += OPEN_CURLY + JSONencode("Plot_Name")
							+ COLON + JSONencode( key ) + COMMA +
							JSONencode("xaxis_data") + COLON + OPEN_BOX;
						for ( int i = 0; i < value.size() ; i++) {
							xaxis_json += JSONencode(value[i]) + COMMA;
						}
						xaxis_json = xaxis_json.erase(xaxis_json.size() - 1);
						xaxis_json += CLOSE_BOX + CLOSE_CURLY + COMMA;
					}
					xaxis_json = xaxis_json.erase(xaxis_json.length() - 1);

					string yaxis_json = "";
					for (auto& entry : yaxisData) {
						string key = entry.first;
						vector<double> value = entry.second;
						yaxis_json += OPEN_CURLY + JSONencode("Plot_Name")
							+ COLON + JSONencode( key) + COMMA +
							JSONencode("yaxis_data") + COLON + OPEN_BOX;
						for ( int i = 0; i <  value.size() ; i++) {
							yaxis_json +=  JSONencode(value[i])  + COMMA;
						}
						yaxis_json = yaxis_json.erase(yaxis_json.length() - 1);
						yaxis_json += CLOSE_BOX + CLOSE_CURLY + COMMA;
					}
					yaxis_json = yaxis_json.erase(yaxis_json.length() - 1);


					string json_str = JSONencode("plot_title") + COLON +  JSONencode(getTitle()) + COMMA +
						JSONencode("subtitle") + COLON + JSONencode(getSubTitle())  + COMMA +
						JSONencode("xLabel") + COLON + JSONencode(getXLabel()) +  COMMA +
						JSONencode("yLabel") + COLON + JSONencode(getYLabel()) + COMMA +
						JSONencode("xaxisType") + COLON + JSONencode(logarithmicx) + COMMA +
						JSONencode("yaxisType") + COLON + JSONencode(logarithmicy) + COMMA +
						JSONencode("options") + COLON + OPEN_CURLY + JSONencode("mouseTracking") + COLON +
						JSONencode(mouseTrack) + COMMA + JSONencode("dataLabels") + COLON + JSONencode(dataLabel) + CLOSE_CURLY + COMMA +
						JSONencode("xaxis_data") + COLON + OPEN_BOX + xaxis_json + CLOSE_BOX + COMMA +
						JSONencode("yaxis_data") + COLON + OPEN_BOX + yaxis_json + CLOSE_BOX +
						CLOSE_CURLY;

					return json_str;
				}

		};
	}
}
#endif
