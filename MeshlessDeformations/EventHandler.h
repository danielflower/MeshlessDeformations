#if !defined(EventHandler_h)
#define EventHandler_h
#include <irrlicht.h>
#include "Globals.h"
#include "ModelObject.h"
#include "DeformableObjectMesh.h"
#include "Particle.h"
#include "GUIManager.h"



using namespace irr;


class EventHandler : public IEventReceiver{ 
  public: 
	  
	  EventHandler() { selectedSceneNode = 0; currentSelected = 0;  }
	  
	virtual bool OnEvent(SEvent event);




private:
	Model::ModelObject *selectedSceneNode;
	bool keyboardEvent( SEvent event );
	
	Model::ModelObject* currentSelected;
	core::vector3df lastObjectPosition;
	core::vector3df oneBeforeLastObjectPosition;

	core::vector3df startPosition;
	core::plane3d<f32> movePlane;

	// used only for deformable mesh objects
	core::array<Model::Particle*> selectedParticles;


}; 


#endif // end if!defined for this header
