#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>

enum class EMessageType : unsigned short {
	INFO = 0,
	WARNING,
	ERROR,
	FATAL_ERROR
};
class Debug
{
private:
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
