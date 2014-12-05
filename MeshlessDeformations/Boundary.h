#if !defined(Boundary_h)
#define Boundary_h

#include <irrlicht.h>
#include "Globals.h"
#include "ModelObject.h"


using namespace irr;
using namespace core;


namespace Model
{

	class Boundary : public ModelObject
	{
		
		public:


			//CONSTRUCTOR
			Boundary(core::aabbox3d<f32> Box);

			//METHODS

			// Draws this node to the screen
			virtual void render();

			// Gets the box that has been resized by the given amount
			core::aabbox3d<f32> getResizedBoundary(f32 resizeAmount);

			// gets the normal of the wall that the given position is close to
			core::vector3df getNormal (core::vector3df position, f32 distance = 1.0f);
			
			vector3df min;
			vector3df max;


	private:
		void CreateBox( f32 width, f32 height, f32 depth );

	};
}


#endif // end if!defined for this header
