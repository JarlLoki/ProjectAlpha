#pragma once
#include <map>
#include <string>

namespace ProjectAlpha {

class Log {
public:
	Log();
	~Log() = default;

	//static void Print(const char* type, const char* message, bool repeat);
	static void Print(std::string type, std::string msg, bool repeat);


private:

	static std::map<std::string, bool> m_alreadyPrinted;

};

}
#ifdef _DEBUG

#define PA_LOG_ERROR(...) ::ProjectAlpha::Log::Print("Error", __VA_ARGS__, false)
#define PA_LOG_WARN(...)  ::ProjectAlpha::Log::Print("Warning", __VA_ARGS__, false)
#define PA_LOG_INFO(...)  ::ProjectAlpha::Log::Print("Info", __VA_ARGS__, false)

#else

#define PA_LOG_ERROR(...) 
#define PA_LOG_WARN(...)  
#define PA_LOG_INFO(...)  

#endif
