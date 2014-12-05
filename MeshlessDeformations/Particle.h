#if !defined(Particle_h)
#define Particle_h

#include <irrlicht.h>
#include "Globals.h"
#include "ModelObject.h"
#include "Boundary.h"



using namespace irr;
using namespace core;
using namespace scene;


namespace Model
{

	class DeformableObject;

	class Particle : public ModelObject
	{

	private:
		static video::SMaterial boundingBoxMaterial;
		static video::SMaterial boundingBoxMaterialSelected;



	public:

		//PROPERTIES
		vector3df position;
		vector3df originalPosition;
		vector3df goalPosition;

		vector3df roofPosition;
		vector3df velocityRoof;

		vector3df velocity;
		vector3df acceleration;

		f32 radius;
		f32 weight;

		int nr;

		DeformableObject *owner;

		//CONSTRUCTOR
		Particle(DeformableObject *owner, f32 radius, f32 weight);
		Particle(DeformableObject *owner, f32 weight);

		// Sets the Original Position and initializes the rest of the Particle 
		// position properties to the same value
		void setOriginalPosition(vector3df orgPosition) {
			originalPosition = orgPosition;
			setPosition(orgPosition);
			position = orgPosition;
			goalPosition = position;
		}


		vector3df getForces();
		// updates the position of this particle
		void update(f32 timeElapsed);

		// checks to see whether the new position is possible to move to
		bool canMoveTo ( const vector3df &newPosition );

		// gets the object that this particle would collide with at the newPosition, or returns NULL if no collision occurred
		ModelObject* getCollidedObject ( const vector3df &newPosition );

		// Determine whether we should draw this node, and the children nodes
		virtual void OnPreRender();

		// Draws this node to the screen
		virtual void render();

	};
}


#endif // end if!defined for this header
