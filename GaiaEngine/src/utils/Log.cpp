#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::Init()
{
	spdlog::set_pattern("%^[%T] [%l] %n: %v%$");
	spdlog::set_level(LEVEL_TRACE);

	s_CoreLogger = spdlog::stderr_color_mt("Core");
	s_ClientLogger = spdlog::stderr_color_mt("Client");
}