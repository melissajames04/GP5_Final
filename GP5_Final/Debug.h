#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>


//The debug is more of a side function that is accessable by any class that calls it
//Used to store error messages into a log file when called
//
//Using an Enumerator, it sets up a series of variables that will hold the values of the error messages
//
//After the initialize, the series of deletes are put there to delete any constructors that VS might try to make for the program
//on compile
//
//The void log() is the method that will be called to write the error message out to a log.txt file
//
//The static keywords infront of initialize and log, as well as the ifndef and define, are all in place to make the debug be created at 
//compile and used whenever called freely by any other class. This means we won't need to create a thousand debugs to call for each class,
//but just one that will be created and sit in wait until called upon at any point in any class that has defined it at the top

using namespace std;

enum class EMessageType : unsigned short {
	INFO = 0,
	WARNING,
	ERROR,
	FATAL_ERROR
};

class Debug {
	public:
		static void Initialize();
		
		Debug() = delete;
		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator = (const Debug&) = delete;
		Debug& operator = (Debug&&) = delete;
	
		static void Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line);
};

#endif
