#ifndef CAMERA_H

#define CAMERA_H

#include <string>
using namespace std;

namespace bridges {
    class Camera {
        struct objectJson {
            string type;
            int fov;
            float position[3];
        };

        public:
            string type;
            int fov;
            float position[3];
            objectJson obJ1;

			Camera () {
				type = "default_camera";
				fov = 90;
				position[0] = position[1] = position[2] = 0.;
			}
            Camera(string t, int f, float p[3]) {
                type = t;
                fov = f;
                memcpy(position, p, sizeof(position));
                obJ1.type = type;
                obJ1.fov = fov;
                memcpy(obJ1.position, p, sizeof(obJ1.position));
            }

            string getType() const{
                return type;
            }

            void setType(string t) {
                type = t;
            }

            int getFov() const{
                return fov;
            }

            void setFov(int f){
                fov = f;
            }

            void setPosition(float p[3]){
                memcpy(position, p, sizeof(position));
            }
			void getPosition (float *p) const {
				p[0] = position[0]; p[1] = position[0]; p[2] = position[0];
			}

    };
} //namespace bridges
#endif
