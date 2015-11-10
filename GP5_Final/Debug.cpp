#include "Debug.h"
#include <string>
#include <fstream>


//ofstream is used to create a log.txt file to store the error messages of the run, later taking in the error message as well as the file
//name and line it was triggered on
//
//After creating it in initalize, the log method uses a switch to filter the error message into a readable format when checked later
//
//Once finished, it saves and closes the file it wrote to


void Debug::Initialize() {
	ofstream out;
	out.open("log.txt", ios::out);
	out.close();
}

void Debug::Log(const EMessageType MsgType, const string& message, const string& filename, const int line) {
	ofstream out;
	out.open("log.txt", ios::app | ios::out);
	
	switch (MsgType) {
		case EMessageType::INFO:
			out << "INFO:" << message << " (" << filename << ":" << line << "(" << endl;
			break;
		case EMessageType::WARNING:
			out << "WARNING:" << message << " (" << filename << ":" << line << "(" << endl;
			break;
		case EMessageType::ERROR:
			out << "ERROR:" << message << " (" << filename << ":" << line << "(" << endl;
			break;
		case EMessageType::FATAL_ERROR:
			out << "FATAL_ERROR:" << message << " (" << filename << ":" << line << "(" << endl;
			break;
	}

	out.close();

}