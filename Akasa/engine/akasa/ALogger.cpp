#include "ALogger.h"
#include "os.h"
#include"AWriterFile.h"

namespace aka
{
	ALogger::ALogger(): m_logLevel(ELL_INFORMATION)
	{
#if _DEBUG
		setDebugName("ALogger");
#endif
		m_logLevel = ELOG_LEVEL::ELL_INFORMATION;
		m_writeFile = nullptr;
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
		m_writeFile->Write(text); // 应该加上日志级别
	}

	void ALogger::Log(const wchar_t * text, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{
		if (ll < m_logLevel) {
			return;
		}
		core::stringc s = text;
		Log(s.c_str(), ll);
	}
	void ALogger::Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{
		if (ll < m_logLevel) {
			return;
		}
		core::stringc s = text;
		s += ": ";
		s += hint;
		Log(s.c_str(), ll);
	}
	void ALogger::Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll /* = ELL_INFORMATION */)
	{
		if (ll < m_logLevel) {
			return;
		}
		core::stringc s = text;
		s += ": ";
		s += hint;
		Log(s.c_str(), ll);
	}

	void ALogger::OpenLogFile(const c8 * strFile, ELOG_LEVEL ll)
	{
		CloseLogFile();
		m_writeFile = new io::AWriteFile(strFile, false);
		m_logLevel = ll;
	}

	void ALogger::CloseLogFile()
	{
		if (m_writeFile) {
			m_writeFile->Close();
			delete m_writeFile;
			m_writeFile = nullptr;
		}
		
	}


}

