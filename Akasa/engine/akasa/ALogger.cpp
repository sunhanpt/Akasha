#include "ALogger.h"
#include "os.h"
namespace aka
{
	ALogger::ALogger(): m_logLevel(ELL_INFORMATION)
	{
#if _DEBUG
		setDebugName("ALogger");
#endif
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

	// print log. 总入口
	void ALogger::Log(const c8 * text, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{
		if (ll < m_logLevel) {
			return;
		}
		os::Printer::Print(text);
		// 添加其他操作（如，可以支持输出到指定的recieve）
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

