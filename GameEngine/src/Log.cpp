#include "Log.h"

#include <iostream>


namespace ProjectAlpha {

std::map<std::string, bool> Log::m_alreadyPrinted;

Log::Log() {
}

const void Log::Print(std::string type, std::string msg, bool repeat = true) {
	std::string sMsg = std::string(type) + ": " + std::string(msg);

	if (repeat || !m_alreadyPrinted[sMsg]) {
		std::cout << sMsg << std::endl;
		m_alreadyPrinted[sMsg] = true;
	}
}

/*
void Log::Print(const char* type, const char* message, bool repeat) {

	std::string sMsg = std::string(type) + ": " + std::string(message);

	if (repeat || !m_alreadyPrinted[sMsg]) {
		std::cout << sMsg << std::endl;
		m_alreadyPrinted[sMsg] = true;
	}
	
}
*/


}//END namespace ProjectAlpha
