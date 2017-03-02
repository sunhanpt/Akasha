/************************************************************************/
/* 
	所有object类的基类，管理一些通用的属性
	created by sunhanpt 2017/3/2
*/
/************************************************************************/
#ifndef __I_OBJECT_H_INCLUDED__
#define __I_OBJECT_H_INCLUDED__
#include <string.h>

#include "AkaUtils.h"
#include "IReferenceCounted.h"

namespace aka
{
	class IObject : IReferenceCounted
	{
	public:

		//! Constructor.
		IObject()
			: m_objectName(0)
		{
		}

		//! Destructor.
		virtual ~IObject()
		{
			A_SAFE_DELETE(m_objectName);
		}

		void setName(const c8* name) 
		{ 
			A_SAFE_DELETE_ARRAY(m_objectName);

			m_objectName = new c8[sizeof(name)];
			strcpy(m_objectName, name);
		}

		const c8* getName() const
		{
			return m_objectName;
		}

	private:

		//! The object name.
		c8* m_objectName;

		// TODO: 添加其他object属性
	};

} // end namespace aka

#endif

