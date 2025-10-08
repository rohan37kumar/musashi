#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"

namespace musashi {
	class MSSHI_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}


//creating macros to make calling the loggin fns easier

//musashi engine logger definitions
#define MSSHI_CORE_TRACE(...)    ::musashi::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MSSHI_CORE_INFO(...)     ::musashi::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MSSHI_CORE_WARN(...)     ::musashi::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MSSHI_CORE_ERROR(...)    ::musashi::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MSSHI_CORE_FATAL(...)    ::musashi::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//client logger definitions
#define MSSHI_TRACE(...)         ::musashi::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MSSHI_INFO(...)          ::musashi::Log::GetClientLogger()->info(__VA_ARGS__)
#define MSSHI_WARN(...)          ::musashi::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MSSHI_ERROR(...)         ::musashi::Log::GetClientLogger()->error(__VA_ARGS__)
#define MSSHI_FATAL(...)         ::musashi::Log::GetClientLogger()->fatal(__VA_ARGS__)

//most probabaly when distributing this engine for actual use, we'll need to remove these console message logging macros, for future reference
//not removing but will make their values empty so that they don't spam the console
