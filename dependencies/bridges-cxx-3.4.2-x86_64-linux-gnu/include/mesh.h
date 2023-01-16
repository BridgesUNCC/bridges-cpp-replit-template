#include <vector>
#include <string>
using namespace std;

namespace bridges {
	class Mesh {

		struct objectJson {
  			string type;
  			vector<float> vertices;
		};

		public: 
  			vector<float> vertices;
  			Mesh(vector<float> vertices) : setVertices(vertices){
    				float color[4] = {1.0, 1.0, 0.5, 1.0};
    				float transform[0] = {};
    				objectJson obJ1;
    				obJ1.type = "custom mesh";
    				obJ1.vertices = vertices;
  			}

			setVertices(vector<float> v){
				vertices = v;
			}
	};
} //namespace bridges

