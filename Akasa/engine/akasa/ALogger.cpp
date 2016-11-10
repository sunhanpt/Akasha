#include "ALogger.h"

namespace aka
{
	ALogger::ALogger()
	{

	}

	ALogger::~ALogger()
	{

	}

	ELOG_LEVEL ALogger::GetLogLevel() const
	{
		return m_logLevel;
	}

	void ALogger::SetLogLevel(ELOG_LEVEL ll)
	{
		m_logLevel = ll;
	}

	void ALogger::Log(const c8 * text, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{

	}

	void ALogger::Log(const wchar_t * text, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{

	}
	void ALogger::Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{

	}
	void ALogger::Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{

	}
}

