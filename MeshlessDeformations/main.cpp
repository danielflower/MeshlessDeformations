#include "main.h"
#include "CCameraMayaSceneNode.h"

//! Adds a camera scene node which is able to be controlle with the mouse similar
//! like in the 3D Software Maya by Alias Wavefront.
//! The returned pointer must not be dropped.
ICameraSceneNode* addCameraSceneNode(ISceneNode* parent, 
	f32 rotateSpeed, f32 zoomSpeed, f32 translationSpeed, s32 id)
{
	if (!parent)
		parent = Globals::sceneManager->getRootSceneNode();

	ICameraSceneNode* node = new d2::CCameraMayaSceneNode(parent, Globals::sceneManager, id, rotateSpeed,
		zoomSpeed, translationSpeed);
	node->drop();

	Globals::sceneManager->setActiveCamera(node);

	return node;
}

int main()
{

	// create the EventHandler
	EventHandler eventHandler;

	//Setup the Irrlicht Engine
	IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<s32>(WINDOWWIDTH, WINDOWHEIGHT), 16, FULLSCREEN, Globals::useShadows, false, &eventHandler);

	//Handles to Managers etc.
	ISceneManager* smgr = device->getSceneManager();
	IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();
	Globals::sceneManager = smgr;

	//Window Title
	device->setWindowCaption(L"Meshless Deformations");

	//Setup the Camera
	//ICameraSceneNode *camera = smgr->addCameraSceneNode(0, core::vector3df(0,0,-200), core::vector3df(0,0,0), 0);
	//ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0, 50, 50, 0);
	Globals::camera = addCameraSceneNode(0,-1500,  600, 1500, 0);
	Globals::camera->setPosition( core::vector3df( 0.0f, -80.0f, -190.0f ) );
	Globals::camera->setTarget( core::vector3df( 0.0f, -80.0f, 0.0f ) );

	
	//ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS(0,100,500,0);




	Globals::init(device);

	// set up the lighting
	smgr->addLightSceneNode(0, core::vector3df(0.0f, 350.0f, 0.0f), video::SColorf(1.0f,1.0f,0.9f), 500.0f, 0);
	driver->setAmbientLight(SColorf( 0.6f, 0.6f, 0.6f, 0.0f ));
	

	ObjectFactory::createObjects();

	// create gui
	GUIManager::createGUIElements( env );


	// set up the boundary
	f32 halfSize = 200.0f;
	Globals::boundary = new Model::Boundary( core::aabbox3df( -halfSize, -halfSize, -halfSize, halfSize, halfSize, halfSize));
	//object->setParent( Globals::boundary );
	//Globals::boundary->setPosition( core::vector3df( 30.0f, 0.0f, 0.0f ) );



	u32 lastTime = device->getTimer()->getTime();
	int lastFPS = -1;

	// run the main loop
	while(device->run())
	{

		// find out how much time has elapsed since the last run of the loop
		u32 currentTime = device->getTimer()->getTime();
		Globals::timeElapsed = (currentTime - lastTime) / 1000.0f /2.0f;
		lastTime = currentTime;

    

		for (u16 index = 0; index < Globals::objects.size(); index ++) {
			Model::DeformableObject* object = Globals::objects[index];
			if (object->isVisible()) {
				object->update( Globals::timeElapsed );
			}
		}

		// start drawing the scene
		driver->beginScene(true, true, CLEARCOLOR);

		// draw all the graphical objects
		smgr->drawAll();
		
		// draw gui
		env->drawAll();

		// finish drawing
		driver->endScene();

		// if not in full-screen display frames per second in window title
		if (!FULLSCREEN) {
			int fps = driver->getFPS();
			if (lastFPS != fps)		{			
				core::stringw str = L"Meshless Deformations [";			
				str += driver->getName();			
				str += "] FPS:";			
				str += fps;			
				device->setWindowCaption(str.c_str());			
				lastFPS = fps;		
			}
		}

	}

	// clean up and exit
	device->drop();

	return 0;
}
