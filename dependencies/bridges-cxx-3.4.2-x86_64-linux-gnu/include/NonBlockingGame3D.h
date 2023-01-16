#ifndef NONBLOCKING_GAME_3D_H
#define NONBLOCKING_GAME_3D_H

#include <GameBase3D.h>
#include <InputHelper.h>

namespace bridges {
	namespace game {

		/**
		 * @brief This class is an extension of the NonBlockingGame class to 3D game
         *    environments
		 *
		 * The games that can be created out of NonBlockingGame3D are
		 * currently based on terrain models and simple interactions with them
		 *
		 * @author Kalpathi Subramanian, Matthew Mcquaigue
		 * @date 9/22/22
		 *
		 **/
		class NonBlockingGame3D : public GameBase3D {
			private:
				using GameBase3D::render;
				using GameBase3D::registerKeyListener;

				typedef std::chrono::steady_clock localclock;

				InputHelper ih;

				double fps = 30.;

				localclock::time_point timeOfLastFrame;

				void handleFrameRate() {
					using std::chrono::seconds;
					using std::chrono::microseconds;
					using std::chrono::duration_cast;

					microseconds frametime = duration_cast<microseconds>(seconds(1l)) / (int)fps;

					localclock::time_point theoretical_next_frame = timeOfLastFrame + frametime;

					auto wait_time = theoretical_next_frame - localclock::now();

					if (wait_time.count() > 0) {
						microseconds wait_time_in_us = duration_cast<microseconds>(wait_time);
						usleep(wait_time_in_us.count());
					}

					timeOfLastFrame = localclock::now();
				}


			public:
				/// constructor
				/// @param assignmentID  Bridges assignment id
				/// @param username      Bridges user name
				/// @param apikey        Bridges API authentication key
				/// @param nbRow         GameGrid height
				/// @param nbCol         GameGrid width
				NonBlockingGame3D(int assignmentID, std::string username, 
											std::string apikey)
							: GameBase3D(assignmentID, username, apikey) {

					registerKeyListener(&ih);
				}

		  virtual ~NonBlockingGame3D() =default;
		  
				/// @brief Call this function from main to start the game. Runs
				/// exactly once.
				void start() {
					timeOfLastFrame = localclock::now();
					initialize();

					render();

exit(0);
					long framelimit = -1; //negative means no limit
					{
						char* str_limit = getenv("FORCE_BRIDGES_FRAMELIMIT");
						if (str_limit != nullptr) {
							std::stringstream ss;
							ss << str_limit;
							ss >> framelimit;
							std::cerr << "Setting framelimit to " << framelimit << std::endl;
						}
					}
					long frame = 0;
					while (!gameover()) {
						gameLoop();
						render();
						handleFrameRate();
						frame++;
						if (framelimit > 0 && frame > framelimit)
							quit();
					}
				}


			protected:
				/// @brief What frame rate is the game running at?
				///
				/// @return the target framerate. The game could be somewhat
				/// slower depending on how computationally expensive the
				/// gameloop is and on the speed of the network.
				double getFrameRate() const {
					return fps;
				}

				///@brief Is Left currently pressed?
				///
				///@return true if Left is currently pressed
				bool keyLeft() {
					return ih.keyLeft();
				}

				///@brief Is Right currently pressed?
				///
				///@return true if Right is currently pressed
				bool keyRight() {
					return ih.keyRight();
				}

				///@brief Is Up currently pressed?
				///
				///@return true if Up is currently pressed
				bool keyUp() {
					return ih.keyUp();
				}

				///@brief Is Down currently pressed?
				///
				///@return true if Down is currently pressed
				bool keyDown() {
					return ih.keyDown();
				}

				///@brief Is W currently pressed?
				///
				///@return true if W is currently pressed
				bool keyW() {
					return ih.keyW();
				}

				///@brief Is A currently pressed?
				///
				///@return true if A is currently pressed
				bool keyA() {
					return ih.keyA();
				}

				///@brief Is S currently pressed?
				///
				///@return true if S is currently pressed
				bool keyS() {
					return ih.keyS();
				}

				///@brief Is D currently pressed?
				///
				///@return true if D is currently pressed
				bool keyD() {
					return ih.keyD();
				}

				///@brief Is Q currently pressed?
				///
				///@return true if S is currently pressed
				bool keyQ() {
					return ih.keyQ();
				}

				///@brief Is Space currently pressed?
				///
				///@return true if Space is currently pressed
				bool keySpace() {
					return ih.keySpace();
				}

		};
	}
}

#endif
