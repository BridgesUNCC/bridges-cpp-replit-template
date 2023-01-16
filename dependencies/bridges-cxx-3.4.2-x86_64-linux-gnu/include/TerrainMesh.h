#ifndef TERRAIN_MESH

#define TERRAIN_MESH

#include <string>
#include <vector>
using namespace std;

namespace bridges {
	class TerrainMesh {

		private:
			string name;
  			string type;
  			vector<float> vertices;
  			vector<float> colors;
  			int rows;
  			int cols;

		public:
			TerrainMesh() {}
  			TerrainMesh(string id, int r, int c, vector<float> elevation_data) {
            	name = id;
            	type = "terrain";
				rows = r; cols = c; 
				vertices = elevation_data;
				// set color for each vertex
				for (int i = 0; i < rows; i++)
				for (int j = 0; j < cols; j++) 
				for (int k = 0; k < 4; k++) 
					colors.push_back(1.);
  			}
		
			void setName (string n) {
				name = n;
			}
	
			string getName () {
				return name;
			}
	
			void setType (string t) {
				type = t;
			}
	
			string getType () {
				return type;
			}
	
	  		int getRows() {
	    		return rows;
	  		}
	
	  		void setRows(int r) {
	    		rows = r;
	  		}
	
	  		int getCols() {
	    		return cols;
	  		}
	
	  		void setCols(int c) {
	    		cols = c;
	  		}

			
	  		vector<float>  getColors() {
	    		return colors;
	  		}
	
	  		void setColors(vector<float> cols) {
	    		colors = cols;
	  		}


	  		vector<float> getVertices() {
	    		return vertices;
	  		}
	
	  		void setVertices(vector<float>& v) {
	    		vertices = v;
	  		}
		};
} //namespace bridges

#endif
