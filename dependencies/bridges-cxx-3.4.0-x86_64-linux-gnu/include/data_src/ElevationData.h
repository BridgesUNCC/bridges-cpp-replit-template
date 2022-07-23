
#ifndef ELEVATION_DATA

#define ELEVATION_DATA

#include <vector>

namespace bridges {

	namespace dataset {

		/**
		 * @brief  Class that hold elevation data
		 *
		 * Class that holds Elevation data. 
		 *
		 * A user would not normally create an ElevationData object but 
		 * rather obtain one from calling bridges::DataSource::getElevationData()
		 *
		 * A tutorial on how to use the Elevation dataset is available at: 
		 *	https://bridgesuncc.github.io/tutorials/Data_Elevation.html
		 *
		 * @author Kalpathi Subramanian
		 *
		 * @date 3/28/20
		 */
		class ElevationData {
			private:

				// elevation data - sequence of integers
				std::vector<int> data;

				// data dimensions
				int rows, cols;

				// origin
				int xll, yll;
				int cellSize;

				// maximum value in the data set
				int maxVal;
		  		int minVal;

			public:

				/**
				 *
				 * default constructor
				 *
				 *assumes all values will be set 
				 */
				ElevationData() {

					cols = rows = 0;
					xll = yll = 0.;
					cellSize = 0;
					maxVal = std::numeric_limits<int>::min();
					minVal = std::numeric_limits<int>::max();
				}

				/**
				 *
				 * constructor
				 *
				 * assumes all values will be explicit set
				 *
				 * @param r number of rows (height) of elevation map
				 * @param c number of columns (width) of elevation map
				 */
				ElevationData(int r, int c) {
					rows = r;
					cols = c;
					data.resize(cols * rows);
					xll = yll = 0.;
					cellSize = 0;
					maxVal = std::numeric_limits<int>::min();
					minVal = std::numeric_limits<int>::max();
				}
				/**
				 *
				 * constructor
				 * @param rows number of rows (height) of elevation map
				 * @param cols number of columns (width) of elevation map
				 * @param xll  lower left of map - x coordinate
				 * @param yll  lower left of map - y coordinate
				 * @param cellsize size of each cell
				 * @param maxVal  max elevation value in map
				 * @param maxVal  min elevation value in map
				 */
				ElevationData (int cols, int rows, int xll,
					       int yll, int cellsize, int maxVal, int minVal) {
					//data = new int[cols * rows];
					data.resize(cols * rows);
					setCols(cols);
					setRows(rows);
					setxll(xll);
					setyll(yll);
					setCellSize (cellsize);
					setMaxVal(maxVal);
					setMinVal(minVal);
				}

				/**
				 * destructor
				 */
				~ElevationData() {
					//delete [] data;
				}

				/**
				 * get width of elevation map
				 * @return width of map
				 */

				int getCols() const {
					return cols;
				}

				/**
				 * set width of elevation map
				 * @param c  width of map
				 */
				void setCols(int c)  {
					cols = c;
				}

				/**
				 * get width of elevation map
				 *
				 * @param r row index
				 * @param c column index
				 */
				int getVal (int r, int c) const {
					return data[r * cols + c];
				}

				/**
				 *	set elevation value at row r and column c
				 *
				 * @param r row index
				 * @param c column index
				 * @param val  elevation value
				 */
				void setVal (int r, int c, int val) {
				  minVal = std::min(minVal, val);
				  maxVal = std::max(maxVal, val);
				    
					data[r * cols + c] = val;
				}
				/**
				 *	get num rows of data
				 *
				 *	@return width of elevation map
				 */
				int getRows() const {
					return rows;
				}

				/**
				 *	set num rows of data
				 *
				 *	@param r width of elevation map to set
				 */
				void setRows(int r) {
					rows = r;
				}

				/**
				 *	get lower left corner of data (X)
				 *  @return x coord of lower left of map
				 */
				int getxll() const {
					return xll;
				}

				/**
				 *
				 *	set lower left corner of data (X)
				 *
				 *	@param x_ll  lower left coord of X to set
				 */
				void setxll(int x_ll) {
					xll = x_ll;
				}

				/**
				 *	get lower left corner of data (Y)
				 *  @return y coord of lower left of map
				 */
				int getyll() const {
					return yll;
				}

				/**
				 *
				 *	set lower left corner of data (Y)
				 *	@param y_ll  lower left coord of Y to set
				 */
				void setyll(int y_ll) {
					yll = y_ll;
				}

				/**
				 *
				 *	get  data resolution
				 *  @return the cell size
				 */
				int getCellSize() const {
					return cellSize;
				}

				/**
				 *
				 *	set  data resolution
				 *  @param cell_size set the resolution of the map to cell_size
				 */
				void setCellSize(int cell_size) {
					cellSize = cell_size;
				}

				/**
				 *
				 *	get max elevation of data
				 *	@return the max elevation value in the map
				 */
				int getMaxVal() const {
					return maxVal;
				}

				/**
				 *
				 *	set max elevation of data
				 *	@param max_val the max value of elevation to set
				 */
				void setMaxVal(int max_val) {
					maxVal = max_val;
				}
		  /**
				 *
				 *	get min elevation of data
				 *	@return the min elevation value in the map
				 */
				int getMinVal() const {
					return minVal;
				}

				/**
				 *
				 *	set min elevation of data
				 *	@param min_val the max value of elevation to set
				 */
				void setMinVal(int min_val) {
					minVal = min_val;
				}

		};
	}
}
#endif
