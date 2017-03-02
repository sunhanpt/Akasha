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

	virtual void OnRegisterSceneNode() { /*TODO: ע��node����������Ҫ�����ӽڵ㣬ע�ᵽ��Ӧ��render������*/ }
	virtual void OnAnimate(u32 timeMs) {/*TODO: animate����Ҫ�����ӽڵ�*/ } /
	virtual void render() = 0;// render the node

};
	
}
} // aka

#endif // __AKA_ISCENENODE_H_INCLUDED__
