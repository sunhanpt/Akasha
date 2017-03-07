#ifndef __AKA_ISCENENODE_H_INCLUDED__
#define __AKA_ISCENENODE_H_INCLUDED__

#include <list>

#include "matrix4.h"
#include "AkaString.h"

#include "IAttributeExchangingObject.h"

namespace aka
{
namespace scene
{
class ISceneManager;
class ISceneNode;

typedef std::list<ISceneNode *> ISceneNodeList;
class ISceneNode : public io::IAttributeExchangingObject
{
public:
	ISceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id = -1,
		const core::vector3df& position = core::vector3df(0.0f, 0.0f, 0.0f),
		const core::vector3df& rotation = core::vector3df(0.0f, 0.0f, 0.0f),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f))
		: m_relativeTranslation(position), m_relativeRotation(rotation), m_relativeScale(scale),
		m_parent(0), m_sceneManager(mgr), m_ID(id)/*,
		m_automaticCullingState(EAC_BOX), m_debugDataVisible(EDS_OFF),
		m_isVisible(true), m_isDebugObject(false)*/
	{

	}

	ISceneNode() {}
	virtual	~ISceneNode() = default;

	virtual void OnRegisterSceneNode() { /*TODO: 注册node到场景，需要遍历子节点，注册到相应的render管线中*/ }
	virtual void OnAnimate(u32 timeMs) {/*TODO: animate，需要遍历子节点*/ } 
	virtual void render() = 0;// render the node


private:
	//! node parent
	ISceneNode*					m_parent;

	//! scene manager
	ISceneManager*				m_sceneManager;

	//! sub nodes
	ISceneNodeList				m_childrenNodeList;
	
	//! Name of the scene node.
	core::stringc				m_name;

	//! Absolute transformation of the node.
	core::matrix4f				m_absoluteTransformation;

	//! Relative translation of the scene node.
	core::vector3df				m_relativeTranslation;

	//! Relative rotation of the scene node.
	core::vector3df				m_relativeRotation;

	//! Relative scale of the scene node.
	core::vector3df				m_relativeScale;

	//! ID
	s32							m_ID;

	//! Automatic culling state
	u32							m_automaticCullingState;

	//! Flag if debug data should be drawn, such as Bounding Boxes.
	u32							m_debugDataVisible;

	//! Is the node visible?
	bool						m_isVisible;

	//! Is debug object?
	bool						m_isDebugObject;
};
	
}
} // aka

#endif // __AKA_ISCENENODE_H_INCLUDED__
