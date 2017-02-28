#ifndef __AKA_ISCENENODE_H_INCLUDED__
#define __AKA_ISCENENODE_H_INCLUDED__

#include "IAttributeExchangingObject.h"

namespace aka
{
namespace scene
{

class ISceneNode : public io::IAttributeExchangingObject
{
	ISceneNode() = default;
	virtual	~ISceneNode() = default;


};
	
}
} // aka

#endif // __AKA_ISCENENODE_H_INCLUDED__
