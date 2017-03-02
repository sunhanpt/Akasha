#ifndef __AKA_ISCENENODE_H_INCLUDED__
#define __AKA_ISCENENODE_H_INCLUDED__

#include "IAttributeExchangingObject.h"

namespace aka
{
namespace scene
{
class ISceneManager;
class ISceneNode : public io::IAttributeExchangingObject
{
public:
	ISceneNode(ISceneNode * parent, ISceneManager * mgr) {}
	virtual	~ISceneNode() = default;

	virtual void OnRegisterSceneNode() { /*TODO: 注册node到场景，需要遍历子节点，注册到相应的render管线中*/ }
	virtual void OnAnimate(u32 timeMs) {/*TODO: animate，需要遍历子节点*/ } /
	virtual void render() = 0;// render the node

};
	
}
} // aka

#endif // __AKA_ISCENENODE_H_INCLUDED__
