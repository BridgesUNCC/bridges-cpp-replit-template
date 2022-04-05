#ifndef NONBLOCKING_GAME_H
#define NONBLOCKING_GAME_H

#include <GameBase.h>
#include <InputHelper.h>

namespace bridges {
	namespace game {

		/**
		 * @brief This class provides the features necessary to implement  simple non blocking games.
		 *
		 * The games that can be created out of NonBlockingGame are
		 * based on a simple board grid of at most 1024 cells (e.g.,
		 * 32x32, or any combinations less than 1024 cells). Each
		 * cell has a background color, and a colored symbol.
		 *
		 * This class is used by having another class derive
		 * from it and implement the two functions: initialize()
		 * and GameLoop(). initialize() is called exactly
		 * once, on the first frame of the game. It is used to
		 * make first time initializations of the game state
		 * (such as setting the board in its initial position,
		 * for instance in chess). However, GameLoop() is called
		 * at every frame of the game. The game starts when the
		 * function start() is called on the object you
		 * created.
		 *
		 * For this reason the simplest game that can run is created
		 * by:
		 *
		 * \code{.cpp}
		 * #include <NonBlockingGame.h>
		 * using namespace bridges::game;
		 * struct my_game : public NonBlockingGame {
		 *   my_game() : NonBlockingGame (1, "myuserid",  "myapikey") {}
		 *   virtual void initialize() override { }
		 *   virtual void GameLoop() override { }
		 * };
		 *
		 * int main () {
		 *   my_game g;
		 *   g.start();
		 * }
		 * \endcode
		 *
		 * This game does not do anything, but it is the
		 * minimal code that will run a game. Note that the
		 * constructor of my_game passes 3 parameters to the
		 * constructor of NonBlockingGame(). These three
		 * parameters are the classic parameters that the
		 * constructor of bridges::Bridges takes (e.g.,
		 * assignmentID, username, apikey).
		 *
		 * To change the board, two functions are
		 * used. setBGColor() change the background color of a
		 * particular cell. It takes three parameters, the
		 * first two identify the cell of the board to change,
		 * and the last one is a color from a color palette
		 * provided by NamedColor. drawSymbol() takes four
		 * parameters, the first two identify the cell of the
		 * board to change, the third is a symbol from a
		 * symbol palette provided by NamedSymbol, the fourth
		 * is the color that symbol shold be drawn in and
		 * provided by NamedColor.
		 *
		 * For instance, a very simple initialize() could look like:
		 * \code{.cpp}
		 * virtual void initialize() override {
		 *   setBGColor(0, 0, NamedColor.lightsalmon);
		 *   drawSymbol(0, 0, NamedSymbol.sword, NamedColor.blue);
		 * }
		 * \endcode
		 *
		 * Note that the size of the board is set by default
		 * at 10x10 and that drawing on a cell that does not
		 * exist will lead to an error. One can specify a
		 * gameboard of a different size by passing additional
		 * parameters to the NonBlockingGame
		 * constructor. However, the game can not be more than
		 * 1024 cells in total, so a 15x15 board is possible,
		 * a 32x32 board is the largest square board possible,
		 * and a rectangular 64x16 rectangular board is also
		 * possible. But a 100x20 board would be 2000 cells
		 * and is not possible. For instance a board of 16
		 * rows and 64 columns can be created defining the
		 * my_game constructor as:
		 *
		 * \code{.cpp}
		 *   my_game() : NonBlockingGame (1, "myuserid",  "myapikey", 16, 64) {}
		 * \endcode
		 *
		 * The bridges game engine will call the GameLoop()
		 * function at each frame of the game. You can write
		 * this function to modify the state of the game board
		 * using setBGColor() and drawSymbol(). For instance,
		 * the following GameLoop() will color the board
		 * randomly one cell at a time.
		 *
		 * \code{.cpp}
		 * virtual void gameLoop() override {
		 *   setBGColor(rand()%10, rand()%10, NamedColor.lightsalmon);
		 * }
		 * \endcode
		 *
		 * The gameLoop can also probe the state of some keys
		 * of the keyboard using functions keyUp(), keyLeft(),
		 * keyDown(), keyRight(), keyW(), keyA(), keyS(),
		 * keyD(), keySpace(), and keyQ(). These functions
		 * return a boolean that indicate whether the key is
		 * pressed at that frame or not. For instance, the
		 * following code will only color the board randomly
		 * when the up arrow is pressed.
		 *
		 * \code{.cpp}
		 * virtual void gameLoop() override {
		 *   if (keyUp())
		 *     setBGColor(rand()%10, rand()%10, NamedColor.lightsalmon);
		 * }
		 * \endcode
		 *
		 * @sa There is a tutorial at: https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		 *
		 * @author Erik Saule
		 * @date 7/21/19, 12/28/20
		 *
		 **/
		class NonBlockingGame : public GameBase {
			private:
				using GameBase::render;
				using GameBase::registerKeyListener;

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
				NonBlockingGame(int assignmentID, std::string username,
					std::string apikey, int nbRow = 10, int nbCol = 10)
					: GameBase(assignmentID, username, apikey, nbRow, nbCol) {
					if (debug)
						std::cerr << "nbRow: " << nbRow << " nbCol: " <<
							nbCol << std::endl;

					if (nbRow * nbCol > 32 * 32) {
						throw "NonBlockingGame can not have a grid of more than 32x32 (or a combination(so 16x64 is ok; 16x128 is not)";
					}

					registerKeyListener(&ih);

				}

				/// @brief Call this function from main to start the game. Runs
				/// exactly once.
				void start() {
					timeOfLastFrame = localclock::now();
					initialize();

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
