#pragma once
#include <string>
#include "spdlog/spdlog.h"

namespace SRE
{
	class Logger
	{
	public:
		Logger();
		static Logger* GetLoggerInstance();

		void L_INFO(std::string _message);
		void L_INFO(float _fValue1, float _fValue2);
		void L_WARNING(std::string _message);
		void L_ERROR(std::string _message);
		void L_CRITIC(std::string _message);


		static Logger* m_pLoggerInstance;
		std::shared_ptr<spdlog::logger> m_pConsole;
	};
}