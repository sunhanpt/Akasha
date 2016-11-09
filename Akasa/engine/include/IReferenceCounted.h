#ifndef __I_IREFERENCE_COUNTED_H_INCLUDED__
#define __I_IREFERENCE_COUNTED_H_INCLUDED__

#include "akaTypes.h"


namespace irr
{
	class IReferenceCounted
	{
	public:

		//! Constructor.
		IReferenceCounted()
			: DebugName(0), ReferenceCounter(1)
		{

		//! Destructor.
		virtual ~IReferenceCounted()
		{
		}

		void grab() const { ++ReferenceCounter; }

		bool drop() const
		{
			// someone is doing bad reference counting.
			_AKA_DEBUG_BREAK_IF(ReferenceCounter <= 0)

				--ReferenceCounter;
			if (!ReferenceCounter)
			{
				delete this;
				return true;
			}

			return false;
		}

		//! Get the reference count.
		/** \return Current value of the reference counter. */
		s32 getReferenceCount() const
		{
			return ReferenceCounter;
		}

		//! Returns the debug name of the object.
		const c8* getDebugName() const
		{
			return DebugName;
		}

	protected:

		//! Sets the debug name of the object.
		void setDebugName(const c8* newName)
		{
			DebugName = newName;
		}

	private:

		//! The debug name.
		const c8* DebugName;

		//! The reference counter. Mutable to do reference counting on const objects.
		mutable s32 ReferenceCounter;
	};

} // end namespace aka

#endif

