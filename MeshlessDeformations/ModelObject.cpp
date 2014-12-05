#include "ModelObject.h"

using namespace Model;



//CONSTRUCTORS
ModelObject::ModelObject(ObjectType::ObjectType type) : scene::ISceneNode(Globals::sceneManager->getRootSceneNode(), Globals::sceneManager, (type | ObjectType::ModelObjectType))
{
	this->type = (ObjectType::ObjectType) getID();
	this->isSelected = false;
	
}

bool ModelObject::is(ObjectType::ObjectType type) {
	return (type & this->type) > 0;
}


// Determine whether we should draw this node, and the children nodes
void ModelObject::OnPreRender()
{
	if (IsVisible) {
		// Draw this node
		SceneManager->registerNodeForRendering(this);


		// Draw the children nodes
		ISceneNode::OnPreRender();

	}

}

// Draws this node to the screen
void ModelObject::render()
{


}


const core::aabbox3d<f32>& ModelObject::getBoundingBox() const
{
	return Box;
}


