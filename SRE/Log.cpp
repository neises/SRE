#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace SRE {

	using namespace SRE;
	Logger* Logger::m_pLoggerInstance = 0;

	void Logger::L_INFO(std::string _message)
	{
		m_pConsole->info(_message);
	}

	void Logger::L_INFO(float _fValue1, float _fValue2)
	{
		m_pConsole->info("X-Value {0}; Y-Value {1}",_fValue1,_fValue2);
	}

	void Logger::L_WARNING(std::string _message)
	{
		m_pConsole->warn(_message);
	}

	void Logger::L_ERROR(std::string _message)
	{
		m_pConsole->error(_message);
	}

	void Logger::L_CRITIC(std::string _message)
	{
		m_pConsole->critical(_message);
	}

	Logger::Logger()
	{
		m_pConsole = spdlog::stdout_color_mt("console");
	}

	SRE::Logger* Logger::GetLoggerInstance()
	{
		if (m_pLoggerInstance == nullptr)
		{
			m_pLoggerInstance = new Logger();

		}
		return m_pLoggerInstance;
	}


}