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
		ELL_NONE // ��������log�����У�������Ϊlog����ĸ������ޣ�����ѭ��
	};

	class ILogger : public IReferenceCounted
	{
	public:

		//! Destructor.
		virtual ~ILogger(){}

		// ��ȡ��־����
		virtual ELOG_LEVEL GetLogLevel() const = 0;

		// ������־����
		virtual void SetLogLevel(ELOG_LEVEL logLevel) = 0;

		// ��text�İ��������־
		virtual void Log(const c8 * text, ELOG_LEVEL ll = ELL_INFORMATION ) = 0;

		// ��text�İ��������־
		virtual void Log(const wchar_t * text, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// ��text�İ��������־��hint�Ǹ�����Ϣ�����İ���ʽΪ(text:hint)
		virtual void Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// ��text�İ��������־��hint�Ǹ�����Ϣ�����İ���ʽΪ(text:hint)
		virtual void Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// ����־д���ĸ��ļ�
		virtual void OpenLogFile(const c8 * strFile, ELOG_LEVEL ll = ELL_INFORMATION) = 0;

		// ����־�ر�
		virtual void CloseLogFile() = 0;
	};

} // end namespace aka

#endif

