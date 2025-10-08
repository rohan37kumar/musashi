#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace musashi {

	//the static logger variables, two of them
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger; //engine side logger
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger; //client side logger

	void Log::Init()
	{
		// https://github.com/gabime/spdlog/wiki/Custom-formatting for reference

		spdlog::set_pattern("%^[%T] %n: %@ %v%s");
		// %^ --- %s mark the color boundaries
		//%T - Time, %n - Logger name, %@ - source file name and line number, %v - the actual message

		s_CoreLogger = spdlog::stdout_color_mt("musashi");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}


//sample code usage from the spdlog github page: (for reference)
/*

-------------------------------------------------------------------------------------------------------------------------------------

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
void stdout_example()
{
	// create a color multi-threaded logger
	auto console = spdlog::stdout_color_mt("console");
	auto err_logger = spdlog::stderr_color_mt("stderr");
	spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");
}

-------------------------------------------------------------------------------------------------------------------------------------

#include "spdlog/spdlog.h"

int main()
{
	spdlog::info("Welcome to spdlog!");
	spdlog::error("Some error message with arg: {}", 1);

	spdlog::warn("Easy padding in numbers like {:08d}", 12);
	spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
	spdlog::info("Support for floats {:03.2f}", 1.23456);
	spdlog::info("Positional args are {1} {0}..", "too", "supported");
	spdlog::info("{:<30}", "left aligned");

	spdlog::set_level(spdlog::level::debug); // Set *global* log level to debug
	spdlog::debug("This message should be displayed..");

	// change log pattern
	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

	// Compile time log levels
	// Note that this does not change the current log level, it will only
	// remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
	SPDLOG_TRACE("Some trace message with param {}", 42);
	SPDLOG_DEBUG("Some debug message");
}

-------------------------------------------------------------------------------------------------------------------------------------

*/
