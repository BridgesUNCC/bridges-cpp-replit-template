#ifndef INPUTSTATEMACHINE_GAME_H
#define INPUTSTATEMACHINE_GAME_H

#include <functional>

namespace bridges {
  namespace game {

    class InputStateMachine {
      enum CycleState {
	JUST_PRESSED,
	STILL_PRESSED,
	JUST_NOT_PRESSED,
	STILL_NOT_PRESSED
      };
      
      enum FireState {
	FIRE,
	COOLDOWN,
	NOT_PRESSED
      };

      CycleState s;
      FireState f;
      int cooldown;
      int cooldownCounter;

      std::function<bool()> rawState;
      
    public:
    InputStateMachine(std::function<bool()> rawStateFunc)
	:s(STILL_NOT_PRESSED), f(NOT_PRESSED),
	cooldown(30), cooldownCounter(0),
	rawState(rawStateFunc) {
	
      }
      
      void update() {
	bool currentState = rawState();

       //update cycle state
	 switch(s) {
	 case JUST_PRESSED:
	     if (currentState) {
		 s = STILL_PRESSED;
	     } else {
		 s = JUST_NOT_PRESSED;
	     }	     
	     break;
	 case STILL_PRESSED:
	     if (currentState) {
		 s = STILL_PRESSED;
	     } else {
		 s = JUST_NOT_PRESSED;
	     }	     
	     break;
	 case JUST_NOT_PRESSED:
	     if (currentState) {
		 s = JUST_PRESSED;
	     } else {
		 s = STILL_NOT_PRESSED;
	     }	     
	     break;
	 case STILL_NOT_PRESSED:
	     if (currentState) {
		 s = JUST_PRESSED;
	     } else {
		 s = STILL_NOT_PRESSED;
	     }	     
	     break;
	 }

	 //update firestate
	 switch (f) {
	 case FIRE:
	     if (currentState) {
		 f = COOLDOWN;
		 cooldownCounter = cooldown;
	     } else {
		 f = NOT_PRESSED;
	     }	     
	     break;
	 case COOLDOWN:
	     if (currentState) {
		 cooldownCounter --;
		 if (cooldownCounter == 0)
		     f = FIRE;
	     } else {
		 f = NOT_PRESSED;
	     }	     
	     break;
	 case NOT_PRESSED:
	     if (currentState) {
		 f = FIRE;
	     } else {
		 f = NOT_PRESSED;
	     }	     
	     break;
	 }
	 
     }


      bool justPressed() const {
	 return s == JUST_PRESSED;
     }
      bool stillPressed() const {
	 return s == STILL_PRESSED;
     }
      bool justNotPressed() const {
	 return s == JUST_NOT_PRESSED;
     }
     bool stillNotPressed() const {
	 return s == STILL_NOT_PRESSED;
     }


     void setFireCooldown(int c) {
	 if (c <= 0) {
	     throw "cooldown must be positive";
	 }
	 cooldown = c;
     }
     
      bool fire() const {
	 return f == FIRE;
     }

      
    };
      
  }
}

#endif
