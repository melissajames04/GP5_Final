#ifndef TIMER_H
#define TIMER_H


//Timer acts like the debug, in that we always want to be able to access the same one from multiple classes without having to create a new
//object each time. To do this, we define it at compile and have it essentially always there to be called on by any class that defines it and
//then calls it.
//
//For these timer files, we'll keep the ticks private for it's own use while the outside world can use the number returned by GetDeltaTime
//and GetSleepTime, which will give a time tick to anything that calls it
//
//For public use, we have a basic constructor and destructor, as well as the familiar deleting of all preset constructors that VS makes for 
//you
//
//Below that we have the methods that will be used for the timer, a start, an update, a float that is the difference between the two ticks,
//and an unsigned int that will be the frequency of refresh rate per second of the screen


class Timer {
	private:
		unsigned int prevTicks;
		unsigned int currTicks;

	public:
		Timer();
		~Timer();

		Timer(const Timer&) = delete;
		Timer(Timer&&) = delete;
		Timer& operator =(const Timer&) = delete;
		Timer& operator= (Timer&&) = delete;

		void Start();
		void UpdateFrameTicks();
		float GetDeltaTime() const;
		unsigned int GetSleepTime(const unsigned int fps) const;
};
#endif

