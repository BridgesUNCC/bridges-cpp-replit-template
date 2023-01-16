#ifndef SCENE_H

#define SCENE_H

#include <string> 
#include <list>
#include <unordered_map>

#include "Camera.h"
#include "TerrainMesh.h"
#include "DataStructure.h"

namespace bridges  {
    class Scene: public DataStructure {

    	private:
            std::unordered_map<string, TerrainMesh> terrains;
    		Camera  camera;

    	public:
			Scene() {
				float pos[] = {0., 0., 0.};
				Scene("fps", 90, pos);
			}

    		Scene(std::string type, int fov, float position[3]) {
                camera.setType(type);
                camera.setFov(fov);
                camera.setPosition(position);
    		}

			/** 
			 * @brief Get data structure type
			 */
			virtual const string getDStype() const override {
				return "Scene";
			}

            /**
             * @brief add function for Camera objects
             */
    		void setCamera (Camera& c) {
    			camera = c;
    		}

			/** 
			 * 	@brief get the current camera
			 */
			Camera getCamera () {
				return camera;
			}

            /**
             * @brief add function for TerrainMesh objects
             */
            void add(TerrainMesh terrain){
                terrains[terrain.getName()] = terrain;
            }

            /**
             * @brief add function for TerrainMesh objects
             */
            TerrainMesh& get(string mesh_name){
                return terrains[mesh_name];
            }

            /**
             * @brief remove function for TerrainMesh objects
             */
//			void remove(TerrainMesh scene_object) {
//				terrains.remove(scene_object);
// 			}

			virtual const string getDataStructureRepresentation() const 
											override {

    			std::string scene_json = OPEN_CURLY;
				float pos[3];
				// add camera
				camera.getPosition(pos);
    			scene_json += 
						QUOTE + "camera" + QUOTE + COLON + 
						OPEN_CURLY + 
							QUOTE + "name" + QUOTE  +  COLON + 
							QUOTE + camera.getType() + QUOTE  + COMMA +
							QUOTE + "fov" + QUOTE + COLON + 
							QUOTE + std::to_string(camera.getFov()) + QUOTE + COMMA +  
							QUOTE + "position" + QUOTE + COLON + 
							OPEN_BOX + 
								std::to_string(pos[0]) + COMMA +
								std::to_string(pos[1]) + COMMA +
								std::to_string(pos[2])  + 
							CLOSE_BOX + 
						CLOSE_CURLY + COMMA; 

				// add lights
				scene_json += QUOTE + "lights" + QUOTE + COLON + 
								OPEN_BOX + CLOSE_BOX + COMMA;

				// add terrain meshes
				scene_json += 
					QUOTE + "meshes" + QUOTE + COLON + OPEN_BOX;
				for(auto t : terrains) {
					// get vertices of this mesh
					TerrainMesh tr = t.second;
					vector<float> verts = tr.getVertices();
					vector<float> colors = tr.getColors();
					scene_json += OPEN_CURLY + 
						QUOTE + "name" + QUOTE + COLON + QUOTE + tr.getName() + QUOTE + COMMA +
						QUOTE + "type" + QUOTE + COLON + QUOTE + tr.getType()+ QUOTE + COMMA +
						QUOTE + "rows" + QUOTE + COLON + QUOTE + std::to_string(tr.getRows()) + QUOTE + COMMA +
						QUOTE + "cols" + QUOTE + COLON + QUOTE + std::to_string(tr.getCols())+ QUOTE + COMMA +

						// terrain vertices
						QUOTE + "vertices" + QUOTE + COLON; 

						scene_json += OPEN_BOX;			//vertices start
						// list vertices one row at a time
						int k = 0;
						for (int i = 0; i < tr.getRows(); i++) {
							scene_json += OPEN_BOX;	// row start
							for (int j = 0; j < tr.getCols(); j++) {
								scene_json += std::to_string(verts[k++])+COMMA;
							}
							// remove the last comma
							scene_json.erase(scene_json.size()-1);
							scene_json += CLOSE_BOX + COMMA; // row end
						}
						// remove the last comma
						scene_json.erase(scene_json.size()-1);
						scene_json += CLOSE_BOX + COMMA;	//end of vertices
						// terrain colors
						scene_json += QUOTE + "colors" + QUOTE + COLON; 
						scene_json += OPEN_BOX;				//colors start

						// list colors one row at a time
						k = 0;
						for (int i = 0; i < tr.getRows(); i++) {
							scene_json += OPEN_BOX;	// row start
							for (int j = 0; j < tr.getCols(); j++) {
								string col_str = std::to_string(colors[k])
									+ COMMA + std::to_string(colors[k+1])
									+ COMMA + std::to_string(colors[k+2])
									+ COMMA + std::to_string(colors[k+3]);
								scene_json += OPEN_BOX + col_str + CLOSE_BOX +
										COMMA;
								k += 4;
							}
							// remove the last comma
							scene_json.erase(scene_json.size()-1);
							scene_json += CLOSE_BOX + COMMA; // row (colors) end
						}
						// remove the last comma
						scene_json.erase(scene_json.size()-1);
						scene_json += CLOSE_BOX + CLOSE_CURLY + CLOSE_BOX + CLOSE_CURLY; 
				}
				return scene_json;
    		}
    };
}
#endif
