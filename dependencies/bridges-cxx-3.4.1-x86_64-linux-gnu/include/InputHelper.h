#ifndef INPUTHELPER_GAME_H
#define INPUTHELPER_GAME_H

#include <GameBase.h>

namespace bridges {
	namespace game {

		///@brief This is meant to be an internal class, not something
		/// that the library user will use
		///
		///  This class provide input device (mouse and keyboard)
		///	 handling for Bridges games
		///
		///  @sa See the Games Tutorials at
		///		https://bridgesuncc.github.io/tutorials/NonBlockingGame.html
		///		for more information on keys and mouse device usage.
		///
		/// @author Erik Saule, David Burlinson
		/// @date 2018, 2019, 12/28/20
		class InputHelper: public KeypressListener {
				bool debug = false;

				bool up = false;
				bool down = false;
				bool right = false;
				bool left = false;
				bool w = false;
				bool a = false;
				bool s = false;
				bool d = false;
				bool q = false;
				bool space = false;


			private:
				void handleKey(std::string JSONmessage) {
					using namespace rapidjson;
					// ...
					rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> alloc;
					Document msg(&alloc);
					msg.Parse(JSONmessage.c_str());

					std::string type = msg["type"].GetString();

					bool setto = (type.compare("keydown") == 0);

					std::string key = msg["key"].GetString();

					if (key.compare("ArrowUp") == 0)
						up = setto;
					else if (key.compare("ArrowDown") == 0)
						down = setto;
					else if (key.compare("ArrowLeft") == 0)
						left = setto;
					else if (key.compare("ArrowRight") == 0)
						right = setto;
					else if (key.compare("w") == 0)
						w = setto;
					else if (key.compare("a") == 0)
						a = setto;
					else if (key.compare("s") == 0)
						s = setto;
					else if (key.compare("d") == 0)
						d = setto;
					else if (key.compare("q") == 0)
						q = setto;
					else if (key.compare(" ") == 0)
						space = setto;
				}


			protected:
				virtual void keyup(std::string JSONmessage) override {
					if (debug)
						std::cerr << "InputHelper::keyup(\"" << JSONmessage << "\")\n";
					handleKey(JSONmessage);
				}

				virtual void keydown(std::string JSONmessage) override {
					if (debug)
						std::cerr << "InputHelper::keydown(\"" << JSONmessage << "\")\n";
					handleKey(JSONmessage);
				}


			public:

				bool keyUp() const {
					return up;
				}

				bool keyDown() const {
					return down;
				}

				bool keyLeft() const {
					return left;
				}

				bool keyRight() const {
					return right;
				}

				bool keyW() const {
					return w;
				}
				bool keyA() const {
					return a;
				}
				bool keyS() const {
					return s;
				}
				bool keyD() const {
					return d;
				}
				bool keyQ() const {
					return q;
				}
				bool keySpace() const {
					return space;
				}

		};

	}
}
#endif
