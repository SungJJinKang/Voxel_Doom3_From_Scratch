#include "Core.h"
#include "Logger.h"

#ifdef DEBUG_MODE

#include <cstdarg>
#include <string>
#include <intrin.h>
#include <iostream>
#include <type_traits>

#include "../Graphics/DebugGraphics.h"
#include "../Math/LightMath_Cpp/Vector2.h"
#include "../Math/LightMath_Cpp/Vector3.h"
#include "../Game/ConfigData.h"

#include <portable-snippets/debug-trap/debug-trap.h>



using namespace doom::logger;

namespace doom
{
	namespace logger
	{
		const char* LogTypeStr(eLogType logType) noexcept;

		class StdStreamLogger
		{
		private:


		public:
			constexpr StdStreamLogger() noexcept
			{

			}


			void Log(const char* log, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(const std::string log, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept;
			void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) const noexcept;



		};

		class EmptyLogger
		{
		private:
			EmptyLogger()
			{

			}

		public:
			friend class Logger;

			inline void Log(const char* log, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(const std::string log, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(std::initializer_list<const char*> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
			inline void Log(std::initializer_list<const std::string> logs, eLogType logType = eLogType::D_LOG) const noexcept {}
		};

		constexpr inline StdStreamLogger mLogger{};
		eLogType MIN_DEBUG_LEVEL{ eLogType::D_LOG };
		eLogType MAX_DEBUG_LEVEL{ eLogType::D_LOG };
		void Logger::InitLogger()
		{
			MIN_DEBUG_LEVEL = static_cast<eLogType>(::doom::ConfigData::GetSingleton()->GetConfigData().GetValue<int>("SYSTEM", "MIN_DEBUG_LEVEL"));
			MAX_DEBUG_LEVEL = static_cast<eLogType>(::doom::ConfigData::GetSingleton()->GetConfigData().GetValue<int>("SYSTEM", "MAX_DEBUG_LEVEL"));
		}

		void Logger::StopIfError(eLogType logType)
		{
			if (logType == eLogType::D_ERROR)
			{
				std::cout.flush();
				psnip_trap();
			}
		}
		void Logger::Log(const char* log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(log, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(const std::string log, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(log, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(std::initializer_list<const char*> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(logs, logType);
				StopIfError(logType);
			}
		}
		void Logger::Log(std::initializer_list<const std::string> logs, eLogType logType) noexcept
		{
			if (logType == eLogType::D_ALWAYS || (logType >= MIN_DEBUG_LEVEL && logType <= MAX_DEBUG_LEVEL))
			{
				mLogger.Log(logs, logType);
				StopIfError(logType);
			}
		}

		/*
		template <typename Last>
		void Logger::Log(Last arg, eLogType logType) noexcept
		{
			if constexpr (std::is_same_v<char, std::remove_cv<Last>> || std::is_same_v< wchar_t, std::remove_cv<Last>> || std::is_same_v<std::string, std::remove_cv<Last>> || std::is_same_v<std::wstring, std::remove_cv<Last>>)
			{
				Logger.Log(firstArg);
			}
			else
			{
				Logger.Log(std::to_string(firstArg));
			}
		}
		template <typename First, typename... Args>
		void Logger::Log(First firstArg, Args... args, eLogType logType) noexcept
		{
			Logger::Log(firstArg, logType);

			Logger::Log(args..., logType);
		}
		*/

		void Logger::Draw2DLine(const math::Vector2& startPosition, const math::Vector2& endPosition, eColor color) noexcept
		{
			doom::graphics::DebugGraphics::GetSingleton()->DebugDraw2DLine(startPosition, endPosition, color);
		}
		void Logger::Draw3DLine(const math::Vector3& startPosition, const math::Vector3& endPosition, eColor color) noexcept
		{
			doom::graphics::DebugGraphics::GetSingleton()->DebugDraw3DLine(startPosition, endPosition, color);
		}
		void Logger::Draw2DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color) noexcept
		{
			doom::graphics::DebugGraphics::GetSingleton()->DebugDraw2DTriangle(pointA, pointB, pointC, color);
		}
		void Logger::Draw3DTriangle(const math::Vector3& pointA, const math::Vector3& pointB, const math::Vector3& pointC, eColor color) noexcept
		{
			doom::graphics::DebugGraphics::GetSingleton()->DebugDraw3DTriangle(pointA, pointB, pointC, color);
		}


	}
}







const char* doom::logger::LogTypeStr(eLogType logType) noexcept
{
	switch (logType)
	{
	case eLogType::D_LOG:
		return "LOG : ";
		break;

	case eLogType::D_WARNING:
		return "WARNING : ";
		break;

	case eLogType::D_ERROR:
		return "ERROR : ";
		break;

	default:
		__assume(0);
	}

	return "ERROR : ";
}

void StdStreamLogger::Log(const char* log, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType) << log;
	std::cout.put('\n');
}


void StdStreamLogger::Log(std::string log, eLogType logType /*= Doom::LogType::D_LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType) << log;
	std::cout.put('\n');
}


void StdStreamLogger::Log(std::initializer_list<const char*> logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType);
	for (auto c : logs)
		std::cerr << c;
	std::cout.put('\n');
}

void StdStreamLogger::Log(std::initializer_list<const std::string> logs, eLogType logType /*= Doom::LogType::LOG*/) const noexcept
{
	std::cerr << LogTypeStr(logType);
	for (auto c : logs)
		std::cerr << c;
	std::cout.put('\n');
}

#endif