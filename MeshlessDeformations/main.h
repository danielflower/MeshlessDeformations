#if !defined(main_h)
#define main_h

#include <iostream>
#include <irrlicht.h>
#include "Globals.h"
#include "EventHandler.h"
#include "Boundary.h"
#include "Particle.h"
#include "DeformableObject.h"
#include "GUIManager.h"
#include "ObjectFactory.h"

#pragma comment(lib, "Irrlicht.lib")

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


//Screen Details
const int WINDOWWIDTH = 1024;
const int WINDOWHEIGHT = 768;
const int FULLSCREEN = false;
const SColor CLEARCOLOR = SColor(0,255, 255,255);


#endif // end if!defined for this header
