#ifndef __I_ILOGGER_H_INCLUDED__
#define __I_ILOGGER_H_INCLUDED__

#include "akaTypes.h"
#include "IReferenceCounted.h"

namespace aka
{
	// log's Level
	enum ELOG_LEVEL
	{
		ELL_DEBUG,
		ELL_INFORMATION,
		ELL_WARNING,
		ELL_ERROR,
		ELL_NONE // 这个级别的log不会有，仅仅作为log级别的个数上限，用于循环
	};

	class ILogger : public IReferenceCounted
	{
	public:

		//! Destructor.
		virtual ~ILogger(){}

		// 获取日志级别
		virtual ELOG_LEVEL GetLogLevel() const = 0;

		// 设置日志级别
		virtual void SetLogLevel(ELOG_LEVEL logLevel) = 0;

		// 将text文案，打进日志
		virtual void Log(const c8 * text, ELOG_LEVEL ll = ELL_INFORMATION ) = 0;

		// 将text文案，打进日志
		virtual void Log(const wchar_t * text, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// 将text文案，打进日志，hint是附加信息最终文案格式为(text:hint)
		virtual void Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// 将text文案，打进日志，hint是附加信息最终文案格式为(text:hint)
		virtual void Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// 将日志写到哪个文件
		virtual void OpenLogFile(const c8 * strFile, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// 将日志关闭
		virtual void CloseLogFile() = 0;
	};

} // end namespace aka

#endif

