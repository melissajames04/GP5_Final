#include "Timer.h"
#include "SDL.h"


//The timer is used to get the current time tick on the computer and compare it to the last tick grabbed by the program to be used in 
//calculating the amount of time that occurs between these ticks for the program to use as a way of keeping time
//
//The program starts by initializing the two time ticks before throwing in the computer's current time tick into both. Afterwards, update 
//can be called to check the current time tick and then get the new one, storing both to be used in GetDeltaTime to check how much time has 
//elapsed in the duration of the update. It can then use GetSleepTime to take a refresh rate wanted and having the program refresh the 
//update in the rate set, such as 60fps, telling it to refresh 60 times in a second.
//
//Altogether this will combine to create a timer to be used for various physics and rendering calculations or rates.


Timer::Timer() :prevTicks(0), currTicks(0) {

}

Timer::~Timer() {

}

void Timer::Start() {
	prevTicks = SDL_GetTicks();
	currTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks() {
	prevTicks = currTicks;
	currTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const { 
	return (currTicks - prevTicks) / 1000.0f;
}

unsigned int Timer::GetSleepTime(const unsigned int fps) const {
	unsigned int milliSecsPerFrame = 1000 / fps;
	
	if (milliSecsPerFrame == 0){
		return 0;
	}

	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currTicks);
	return sleepTime;
}

