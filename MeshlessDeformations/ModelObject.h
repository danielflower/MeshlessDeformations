#if !defined(ModelObject_h)
#define ModelObject_h

#include <irrlicht.h>
#include "Globals.h"

using namespace irr;
using namespace core;

namespace ObjectType {
	enum ObjectType {
		ModelObjectType = 1, ParticleType = 2, DeformableObject = 4, BoundaryType = 8, DeformableObjectMesh = 16,
		SelectableObject = 32
	};
}

namespace Model
{



	class ModelObject : public scene::ISceneNode
	{
		
	protected:

		ObjectType::ObjectType type;

		core::aabbox3d<f32> Box;


		public:


			// PROPERTIES

			// specifies that the user is currently holding this object with their mouse
			bool isSelected;


			//CONSTRUCTOR
			ModelObject(ObjectType::ObjectType type);

			//METHODS

			// checks to see whether this object is of the given type
			bool is(ObjectType::ObjectType type);

			virtual const core::aabbox3d<f32>& getBoundingBox() const;

			// Determine whether we should draw this node, and the children nodes
			virtual void OnPreRender();

			// Draws this node to the screen
			virtual void render();




	};
}


#endif // end if!defined for this header
