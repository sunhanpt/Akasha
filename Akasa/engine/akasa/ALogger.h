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

		// ��ȡ��־����
		virtual ELOG_LEVEL GetLogLevel() const _AKA_OVERRIDE_;

		// ������־����
		virtual void SetLogLevel(ELOG_LEVEL logLevel) _AKA_OVERRIDE_;

		// ��text�İ��������־
		virtual void Log(const c8 * text, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// ��text�İ��������־
		virtual void Log(const wchar_t * text, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// ��text�İ��������־��hint�Ǹ�����Ϣ�����İ���ʽΪ(text:hint)
		virtual void Log(const c8 * text, const c8 * hint, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// ��text�İ��������־��hint�Ǹ�����Ϣ�����İ���ʽΪ(text:hint)
		virtual void Log(const wchar_t * text, const wchar_t * hint, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// ����־д�뵽�ĸ��ļ���������־��level
		virtual void OpenLogFile(const c8 * strFile, ELOG_LEVEL ll = ELL_INFORMATION) _AKA_OVERRIDE_;

		// ����־�ر�
		virtual void CloseLogFile() _AKA_OVERRIDE_;

	private:
		ELOG_LEVEL m_logLevel;
		io::IWriteFile * m_writeFile;
	};
}

#endif