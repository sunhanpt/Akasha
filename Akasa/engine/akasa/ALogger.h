#ifndef __I_ALOGGER_H_INCLUDED__
#define __I_ALOGGER_H_INCLUDED__

#include "ILogger.h"
#include "os.h"
#include "AkaString.h"
#include "IWriteFile.h"


using namespace std;


namespace aka
{
	class ALogger :public ILogger
	{
	public:
		ALogger();
		virtual ~ALogger();

		// 获取日志级别
		virtual ELOG_LEVEL GetLogLevel() const _AKA_OVERRIDE_;

		// 设置日志级别
		virtual void SetLogLevel(ELOG_LEVEL logLevel) _AKA_OVERRIDE_;

		// 将text文案，打进日志
		virtual void Log(const c8 * text, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// 将text文案，打进日志
		virtual void Log(const wchar_t * text, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// 将text文案，打进日志，hint是附加信息最终文案格式为(text:hint)
		virtual void Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// 将text文案，打进日志，hint是附加信息最终文案格式为(text:hint)
		virtual void Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// 将日志写入到哪个文件，包含日志的level
		virtual void OpenLogFile(const c8 * strFile, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// 将日志关闭
		virtual void CloseLogFile() _AKA_OVERRIDE_;

	private:
		ELOG_LEVEL m_logLevel;
		io::IWriteFile * m_writeFile;
	};
}

#endif