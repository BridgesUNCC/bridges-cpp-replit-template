#ifndef NONBLOCKING_GAME_H
#define NONBLOCKING_GAME_H

#include <GameBase.h>
#include <InputHelper.h>
#include <InputStateMachine.h>

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
		 * There are three ways for your game to take input.
		 *
		 * The gameLoop can probe the state of some keys
		 * of the keyboard using functions keyUp(), keyLeft(),
		 * keyDown(), keyRight(), keyW(), keyA(), keyS(),
		 * keyD(), keySpace(), and keyQ(). These functions
		 * return a boolean that indicates whether the key is
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
		 * The previous way will have an action executed at each
		 * frame of the game if the key stays pressed. This
		 * could be cumbersome for some games and you may want
		 * a key press to be triggered with a cooldown (so
		 * that it activates only every so many frames). You can
		 * configure how many frames will pass between two
		 * activations of the key with keyUpSetupFire() and
		 * you can tell whether it is a fire frame with
		 * keyUpFire(). There are similar functions for all
		 * keys that are recognized by Bridges. See the
		 * following code for a simple usage:
		 *
		 * \code{.cpp}
		 * virtual void initialize() override {
		 *   keyUpSetupFire(20); 
		 * }
		 * virtual void gameLoop() override {
		 *   if (keyUpFire()) //will only be true once every 20 frames
		 *     setBGColor(rand()%10, rand()%10, NamedColor.lightsalmon);
		 * }
		 * \endcode		 
		 *
		 * Bridges supports a third way to use inputs that
		 * enables you to know the first frame a key is
		 * pressed and the first frame a key is no longer
		 * pressed. You can also know whether a key is still
		 * being pressed (after the first frame it is being
		 * pressed) and whether it is still not pressed (after
		 * the first frame it is no longer pressed). The four
		 * functions are keyUpJustPressed(),
		 * keyUpStillPressed(), keyUpJustNotPressed(),
		 * keyUpStillNotPressed(). The following code
		 * examplifies the usage of these functions.
		 *
		 * \code{.cpp}
		 * virtual void gameLoop() override {
		 *   if (keyUpJustPressed())
		 *     setBGColor(0, 0, NamedColor.lightsalmon);
		 *   if (keyUpStillPressed())
		 *     setBGColor(0, 1, NamedColor.lightsalmon);
		 *   if (keyUpJustNotPressed())
		 *     setBGColor(0, 2, NamedColor.lightsalmon);
		 *   if (keyUpStillNotPressed())
		 *     setBGColor(0, 3, NamedColor.lightsalmon);
		 * }
		 * \endcode		 
		 *
		 *
		 * @sa There is a tutorial at: https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		 *
		 * @author Erik Saule
		 * @date 7/21/2019, 12/28/2020, 1/11/2023
		 *
		 **/
		class NonBlockingGame : public GameBase {
			private:
				using GameBase::render;
				using GameBase::registerKeyListener;

				typedef std::chrono::steady_clock localclock;

				InputHelper ih;
				InputStateMachine upSM;
				InputStateMachine downSM;
				InputStateMachine leftSM;
				InputStateMachine rightSM;

				InputStateMachine qSM;
				InputStateMachine spaceSM;

				InputStateMachine wSM;
				InputStateMachine aSM;
				InputStateMachine sSM;
				InputStateMachine dSM;

		  
		  
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

		  void updateInputState() {
		    upSM.update();
		    downSM.update();
		    leftSM.update();
		    rightSM.update();

		    qSM.update();
		    spaceSM.update();

		    wSM.update();
		    aSM.update();
		    sSM.update();
		    dSM.update();
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
				  : GameBase(assignmentID, username, apikey, nbRow, nbCol),
				    ih(),
				    upSM([this]() ->bool {return this->ih.keyUp();}),
				    downSM([this]() ->bool {return this->ih.keyDown();}),
				    leftSM([this]() ->bool {return this->ih.keyLeft();}),
				    rightSM([this]() ->bool {return this->ih.keyRight();}),

				    qSM([this]() ->bool {return this->ih.keyQ();}),
				    spaceSM([this]() ->bool {return this->ih.keySpace();}),

				    wSM([this]() ->bool {return this->ih.keyW();}),
				    aSM([this]() ->bool {return this->ih.keyA();}),
				    sSM([this]() ->bool {return this->ih.keyS();}),
				    dSM([this]() ->bool {return this->ih.keyD();})
		  {
					if (debug)
						std::cerr << "nbRow: " << nbRow << " nbCol: " <<
							nbCol << std::endl;

					if (nbRow * nbCol > 32 * 32) {
						throw "NonBlockingGame can not have a grid of more than 32x32 (or a combination(so 16x64 is ok; 16x128 is not)";
					}

					registerKeyListener(&ih);

				}

		  virtual ~NonBlockingGame() =default;
		  
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
					  updateInputState();
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

		  ///@brief indicates whether the Left key has just been pressed this current frame.
    bool keyLeftJustPressed() {
        return leftSM.justPressed();
    }

		  ///@brief indicates whether the Left key is still being pressed this current frame.
    bool keyLeftStillPressed() {
        return leftSM.stillPressed();
    }
		  ///@brief indicates whether the Left key has just been released this current frame.
    bool keyLeftJustNotPressed() {
        return leftSM.justNotPressed();
    }
		  ///@brief indicates whether the Left key is not pressed and has not been pressed for more than a frame.
    bool keyLeftStillNotPressed() {
        return leftSM.stillNotPressed();
    }

		  ///@brief indicates whether the current frame is a fire frame for the Left key.
    bool keyLeftFire() {
        return leftSM.fire();
    }

		  ///@brief configures how many frames between two fire events for the Left key.
		  ///
		  ///@param f how many frames between two fire events
    void keyLeftSetupFire(int f) {
        leftSM.setFireCooldown(f);
    }
				///@brief Is Right currently pressed?
				///
				///@return true if Right is currently pressed
				bool keyRight() {
					return ih.keyRight();
				}
		  		  ///@brief indicates whether the right key has just been pressed this current frame.
    bool keyRightJustPressed() {
        return rightSM.justPressed();
    }
		  ///@brief indicates whether the Right key is still being pressed this current frame.
    bool keyRightStillPressed() {
        return rightSM.stillPressed();
    }
		  ///@brief indicates whether the Right key has just been released this current frame.
    bool keyRightJustNotPressed() {
        return rightSM.justNotPressed();
    }
		  ///@brief indicates whether the Right key is not pressed and has not been pressed for more than a frame.
    bool keyRightStillNotPressed() {
        return rightSM.stillNotPressed();
    }
		  ///@brief indicates whether the current frame is a fire frame for the Right key.
    bool keyRightFire() {
        return rightSM.fire();
    }
		  ///@brief configures how many frames between two fire events for the Right key.
		  ///
		  ///@param f how many frames between two fire events
    void keyRightSetupFire(int f) {
        rightSM.setFireCooldown(f);
    }
				///@brief Is Up currently pressed?
				///
				///@return true if Up is currently pressed
				bool keyUp() {
					return ih.keyUp();
				}

		  ///@brief indicates whether the Up key has just been pressed this current frame.
    bool keyUpJustPressed() {
        return upSM.justPressed();
    }
		  ///@brief indicates whether the Up key is still being pressed this current frame.

    bool keyUpStillPressed() {
        return upSM.stillPressed();
    }
		  ///@brief indicates whether the Up key has just been released this current frame.
		  
    bool keyUpJustNotPressed() {
        return upSM.justNotPressed();
    }
		  		  ///@brief indicates whether the Up key is not pressed and has not been pressed for more than a frame.

    bool keyUpStillNotPressed() {
        return upSM.stillNotPressed();
    }
		  		  ///@brief indicates whether the current frame is a fire frame for the Up key.

    bool keyUpFire() {
        return upSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the Up key.
		  ///
		  ///@param f how many frames between two fire events

    void keyUpSetupFire(int f) {
        upSM.setFireCooldown(f);
    }


				///@brief Is Down currently pressed?
				///
				///@return true if Down is currently pressed
				bool keyDown() {
					return ih.keyDown();
				}

		  		  ///@brief indicates whether the Down key has just been pressed this current frame.
    bool keyDownJustPressed() {
        return downSM.justPressed();
    }
		  		  ///@brief indicates whether the Down key is still being pressed this current frame.

    bool keyDownStillPressed() {
        return downSM.stillPressed();
    }
		  		  ///@brief indicates whether the Down key has just been released this current frame.
		  
    bool keyDownJustNotPressed() {
        return downSM.justNotPressed();
    }
		  ///@brief indicates whether the Down key is not pressed and has not been pressed for more than a frame.
    bool keyDownStillNotPressed() {
        return downSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the Down key.
    bool keyDownFire() {
        return downSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the Down key.
		  ///
		  ///@param f how many frames between two fire events

    void keyDownSetupFire(int f) {
        downSM.setFireCooldown(f);
    }

		  
				///@brief Is W currently pressed?
				///
				///@return true if W is currently pressed
				bool keyW() {
					return ih.keyW();
				}

		  		  ///@brief indicates whether the W key has just been pressed this current frame.
    bool keyWJustPressed() {
        return wSM.justPressed();
    }
		  		  ///@brief indicates whether the W key is still being pressed this current frame.

    bool keyWStillPressed() {
        return wSM.stillPressed();
    }
		  ///@brief indicates whether the W key has just been released this current frame.
		  
    bool keyWJustNotPressed() {
        return wSM.justNotPressed();
    }
		  		  ///@brief indicates whether the W key is not pressed and has not been pressed for more than a frame.

    bool keyWStillNotPressed() {
        return wSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the W key.
    bool keyWFire() {
        return wSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the W key.
		  ///
		  ///@param f how many frames between two fire events

    void keyWSetupFire(int f) {
        wSM.setFireCooldown(f);
    }
		  
				///@brief Is A currently pressed?
				///
				///@return true if A is currently pressed
				bool keyA() {
					return ih.keyA();
				}

		  ///@brief indicates whether the A key has just been pressed this current frame.
    bool keyAJustPressed() {
        return aSM.justPressed();
    }
		  		  ///@brief indicates whether the A key is still being pressed this current frame.

    bool keyAStillPressed() {
        return aSM.stillPressed();
    }
		  		  ///@brief indicates whether the A key has just been released this current frame.
		  
    bool keyAJustNotPressed() {
        return aSM.justNotPressed();
    }
		  		  ///@brief indicates whether the A key is not pressed and has not been pressed for more than a frame.

    bool keyAStillNotPressed() {
        return aSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the A key.
    bool keyAFire() {
        return aSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the A key.
		  ///
		  ///@param f how many frames between two fire events

    void keyASetupFire(int f) {
        aSM.setFireCooldown(f);
    }
		  
				///@brief Is S currently pressed?
				///
				///@return true if S is currently pressed
				bool keyS() {
					return ih.keyS();
				}

		  ///@brief indicates whether the S key has just been pressed this current frame.
    bool keySJustPressed() {
        return sSM.justPressed();
    }

		  ///@brief indicates whether the S key is still being pressed this current frame.

    bool keySStillPressed() {
        return sSM.stillPressed();
    }
		  ///@brief indicates whether the S key has just been released this current frame.

    bool keySJustNotPressed() {
        return sSM.justNotPressed();
    }
		  		  ///@brief indicates whether the S key is not pressed and has not been pressed for more than a frame.

    bool keySStillNotPressed() {
        return sSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the S key.
    bool keySFire() {
        return sSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the S key.
		  ///
		  ///@param f how many frames between two fire events

    void keySSetupFire(int f) {
        sSM.setFireCooldown(f);
    }
		  
				///@brief Is D currently pressed?
				///
				///@return true if D is currently pressed
				bool keyD() {
					return ih.keyD();
				}
		  ///@brief indicates whether the D key has just been pressed this current frame.
    bool keyDJustPressed() {
        return dSM.justPressed();
    }
		  ///@brief indicates whether the D key is still being pressed this current frame.
		  
    bool keyDStillPressed() {
        return dSM.stillPressed();
    }
		  ///@brief indicates whether the D key has just been released this current frame.
		  
    bool keyDJustNotPressed() {
        return dSM.justNotPressed();
    }
		  ///@brief indicates whether the D key is not pressed and has not been pressed for more than a frame.

    bool keyDStillNotPressed() {
        return dSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the D key.
    bool keyDFire() {
        return dSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the D key.
		  ///
		  ///@param f how many frames between two fire events

    void keyDSetupFire(int f) {
        dSM.setFireCooldown(f);
    }
				///@brief Is Q currently pressed?
				///
				///@return true if S is currently pressed
				bool keyQ() {
					return ih.keyQ();
				}
		  		  ///@brief indicates whether the Q key has just been pressed this current frame.
    bool keyQJustPressed() {
        return qSM.justPressed();
    }
		  ///@brief indicates whether the Q key is still being pressed this current frame.

    bool keyQStillPressed() {
        return qSM.stillPressed();
    }
		  ///@brief indicates whether the Q key has just been released this current frame.
		  
    bool keyQJustNotPressed() {
        return qSM.justNotPressed();
    }
		  		  ///@brief indicates whether the Q key is not pressed and has not been pressed for more than a frame.

    bool keyQStillNotPressed() {
        return qSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the Q key.
    bool keyQFire() {
        return qSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the Q key.
		  ///
		  ///@param f how many frames between two fire events

    void keyQSetupFire(int f) {
        qSM.setFireCooldown(f);
    }
				///@brief Is Space currently pressed?
				///
				///@return true if Space is currently pressed
				bool keySpace() {
					return ih.keySpace();
				}
		  		  ///@brief indicates whether the Space key has just been pressed this current frame.
    bool keySpaceJustPressed() {
        return spaceSM.justPressed();
    }
		  		  ///@brief indicates whether the Space key is still being pressed this current frame.

    bool keySpaceStillPressed() {
        return spaceSM.stillPressed();
    }
		  		  ///@brief indicates whether the Space key has just been released this current frame.

    bool keySpaceJustNotPressed() {
        return spaceSM.justNotPressed();
    }
		  ///@brief indicates whether the Space key is not pressed and has not been pressed for more than a frame.

    bool keySpaceStillNotPressed() {
        return spaceSM.stillNotPressed();
    }
		  		  		  ///@brief indicates whether the current frame is a fire frame for the Space key.
    bool keySpaceFire() {
        return spaceSM.fire();
    }
		  		  ///@brief configures how many frames between two fire events for the Space key.
		  ///
		  ///@param f how many frames between two fire events

    void keySpaceSetupFire(int f) {
        spaceSM.setFireCooldown(f);
    }
		};
	}
}

#endif
