#ifndef __AKA_IATTRIBUTEEXCHANGINGOBJECT_H_INCLUDED__
#define __AKA_IATTRIBUTEEXCHANGINGOBJECT_H_INCLUDED__

#include "IReferenceCounted.h"

namespace aka
{
namespace io
{

class IAttributeExchangingObject: public IReferenceCounted
{
public:

	//! Writes attributes of the object.
	virtual void serializeAttributes(/*io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0*/) const {}

	//! Reads attributes of the object.
	virtual void deserializeAttributes(/*io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0*/) {}
};
	
}
} // aka

#endif // __AKA_IATTRIBUTEEXCHANGINGOBJECT_H_INCLUDED__
