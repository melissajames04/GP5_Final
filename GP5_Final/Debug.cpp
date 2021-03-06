#include "Debug.h"
#include <string>
#include <fstream>


void Debug::Initialize(){
	std::ofstream out;
	out.open("log.txt", std::ios::out);
	out.close();
}

void Debug::Log(const EMessageType MsgType, const std::string& message, const std::string& filename, const int line){
	std::ofstream out;
	out.open("log.txt", std::ios::app | std::ios::out);
	switch (MsgType){
	case EMessageType::INFO:
		out << "INFO:" << message << " (" << filename << ":" << line << "(" << std::endl;
		break;
	case EMessageType::WARNING:
		out << "WARNING:" << message << " (" << filename << ":" << line << "(" << std::endl;
		break;
	case EMessageType::ERROR:
		out << "ERROR:" << message << " (" << filename << ":" << line << "(" << std::endl;
		break;
	case EMessageType::FATAL_ERROR:
		out << "FATAL_ERROR:" << message << " (" << filename << ":" << line << "(" << std::endl;
		break;
	}
	out.close();

}