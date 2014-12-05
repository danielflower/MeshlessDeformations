#if !defined(Globals_h)
#define Globals_h

#include <iostream>
#include <irrlicht.h>

#include "matrix/newmat.h"
#include "matrix/newmatap.h"


// wrapper for sqrt of matrix4 
irr::core::matrix4 sqrt(irr::core::matrix4 A);

irr::core::matrix4 volumeNormalize(irr::core::matrix4 A_input);

irr::core::vector3df getReflected( irr::core::vector3df vector, irr::core::vector3df normal );

using namespace irr;
using namespace scene;


namespace Model {
	class Boundary;
	class DeformableObject;
}

namespace DeformationMode {
	enum DeformationMode { Basic=0, Linear=1, Quadratic=2 };
}


class Globals {
public:


	static IrrlichtDevice *device;
	static scene::ISceneManager* sceneManager;
	static scene::ICameraSceneNode* camera;
	static video::IVideoDriver* driver;
  	static f32 gravity;	static f32 drag;	static f32 timeElapsed;

	static bool stopMode;
	static bool useShadows;
	static DeformationMode::DeformationMode mode;

	static Model::DeformableObject* selectedObject;
	static core::array<Model::DeformableObject*> objects;


	static bool drawGoalPositions;

	static void init(IrrlichtDevice *device);


	static Model::Boundary* boundary;


private:
	Globals();


};


#endif // end if!defined for this header
