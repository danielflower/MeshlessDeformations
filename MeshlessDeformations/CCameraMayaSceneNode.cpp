// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CCameraMayaSceneNode.h"
#include <IVideoDriver.h>
#include <ISceneManager.h>

namespace irr
{
namespace d2
{








//! constructor
CCameraSceneNode::CCameraSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id, 
	const core::vector3df& position, const core::vector3df& lookat)
	: ICameraSceneNode(parent, mgr, id, position, core::vector3df(0.0f, 0.0f, 0.0f),
			core::vector3df(1.0f, 1.0f, 1.0f)), InputReceiverEnabled(true)
{
	#ifdef _DEBUG
	setDebugName("CCameraSceneNode");
	#endif

	BBox.reset(0,0,0);

	// set default view

	UpVector.set(0.0f, 1.0f, 0.0f);
	Target.set(lookat);

	// set default projection

	fovy = core::PI / 2.5f;	// Field of view, in radians. 
	aspect = 4.0f / 3.0f;	// Aspect ratio. 
	zn = 1.0f;				// value of the near view-plane. 
	zf = 3000.0f;			// Z-value of the far view-plane. 

	video::IVideoDriver* d = mgr->getVideoDriver();
	if (d)
	{
		screenDim.Width = (f32)d->getScreenSize().Width;
		screenDim.Height = (f32)d->getScreenSize().Height;
		aspect = screenDim.Height / screenDim.Width;
	}

	recalculateProjectionMatrix();
}



//! destructor
CCameraSceneNode::~CCameraSceneNode()
{
}


//! Disables or enables the camera to get key or mouse inputs.
void CCameraSceneNode::setInputReceiverEnabled(bool enabled)
{
	InputReceiverEnabled = enabled;
}


//! Returns if the input receiver of the camera is currently enabled.
bool CCameraSceneNode::isInputReceiverEnabled()
{
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return InputReceiverEnabled;
}


//! Sets the projection matrix of the camera. The core::matrix4 class has some methods
//! to build a projection matrix. e.g: core::matrix4::buildProjectionMatrixPerspectiveFovLH
//! \param projection: The new projection matrix of the camera. 
void CCameraSceneNode::setProjectionMatrix(const core::matrix4& projection)
{
	Projection = projection;
}



//! Gets the current projection matrix of the camera
//! \return Returns the current projection matrix of the camera.
const core::matrix4& CCameraSceneNode::getProjectionMatrix()
{
	return Projection;
}



//! Gets the current view matrix of the camera
//! \return Returns the current view matrix of the camera.
const core::matrix4& CCameraSceneNode::getViewMatrix()
{
	return View;
}



//! It is possible to send mouse and key events to the camera. Most cameras
//! may ignore this input, but camera scene nodes which are created for 
//! example with scene::ISceneManager::addMayaCameraSceneNode or
//! scene::ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
//! for changing their position, look at target or whatever. 
bool CCameraSceneNode::OnEvent(SEvent event)
{
	return false;
}



//! sets the look at target of the camera
//! \param pos: Look at target of the camera.
void CCameraSceneNode::setTarget(const core::vector3df& pos)
{
	Target = pos;
}



//! Gets the current look at target of the camera
//! \return Returns the current look at target of the camera
core::vector3df CCameraSceneNode::getTarget() const
{
	return Target;
}



//! sets the up vector of the camera
//! \param pos: New upvector of the camera.
void CCameraSceneNode::setUpVector(const core::vector3df& pos)
{
	UpVector = pos;
}



//! Gets the up vector of the camera.
//! \return Returns the up vector of the camera.
core::vector3df CCameraSceneNode::getUpVector() const
{
	return UpVector;
}


f32 CCameraSceneNode::getNearValue()
{
	return zn;
}

f32 CCameraSceneNode::getFarValue()
{
	return zf;
}

f32 CCameraSceneNode::getAspectRatio()
{
	return aspect;
}

f32 CCameraSceneNode::getFOV()
{
	return fovy;
}

void CCameraSceneNode::setNearValue(f32 f)
{
	zn = f;
	recalculateProjectionMatrix();
}

void CCameraSceneNode::setFarValue(f32 f)
{
	zf = f;
	recalculateProjectionMatrix();
}

void CCameraSceneNode::setAspectRatio(f32 f)
{
	aspect = f;
	recalculateProjectionMatrix();
}

void CCameraSceneNode::setFOV(f32 f)
{
	fovy = f;
	recalculateProjectionMatrix();
}

void CCameraSceneNode::recalculateProjectionMatrix()
{
	Projection.buildProjectionMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
	//recalculateViewArea();
}


//! prerender
void CCameraSceneNode::OnPreRender()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	if (!driver)
		return;

	if (SceneManager->getActiveCamera() == this)
	{
		screenDim.Width = (f32)driver->getScreenSize().Width;
		screenDim.Height = (f32)driver->getScreenSize().Height;

		driver->setTransform(video::ETS_PROJECTION, Projection);

		// if upvector and vector to the target are the same, we have a
		// problem. so solve this problem:

		core::vector3df pos = getAbsolutePosition();
		core::vector3df tgtv = Target - pos;
		tgtv.normalize();

		core::vector3df up = UpVector;
		up.normalize();

		f32 dp = tgtv.dotProduct(up);
		if ((dp > -1.0001f && dp < -0.9999f) ||
			(dp < 1.0001f && dp > 0.9999f))
			up.X += 1.0f;

		View.buildCameraLookAtMatrixLH(pos, Target, up);
		recalculateViewArea();

		SceneManager->registerNodeForRendering(this, ESNRP_LIGHT_AND_CAMERA);
	}

	ISceneNode::OnPreRender();
}


//! render
void CCameraSceneNode::render()
{	
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	if (!driver)
		return;

	driver->setTransform(video::ETS_VIEW, View);
}


//! returns the axis aligned bounding box of this node
const core::aabbox3d<f32>& CCameraSceneNode::getBoundingBox() const
{
	return BBox;
}



//! returns the view frustrum. needed sometimes by bsp or lod render nodes.
const SViewFrustrum* CCameraSceneNode::getViewFrustrum()
{
	return &ViewArea;
}


void CCameraSceneNode::recalculateViewArea()
{
	core::matrix4 mat = Projection * View;
	ViewArea = SViewFrustrum(mat);

	ViewArea.cameraPosition = getAbsolutePosition();
	ViewArea.recalculateBoundingBox();
}













//! constructor
CCameraMayaSceneNode::CCameraMayaSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
	 f32 rs, f32 zs, f32 ts)
: CCameraSceneNode(parent, mgr, id)
{
	#ifdef _DEBUG
	setDebugName("CCameraMayaSceneNode");
	#endif

	zooming = false;
	rotating = false;
	moving = false;
	translating = false;
	zoomSpeed = zs;
	rotateSpeed = rs;
	translateSpeed = ts;
	currentZoom = 70.0f;
	//Pos.set(0.0f, 70.0f, 0.0f);
	Target.set(0.0f, 0.0f, 0.0f);
	rotX = 0;
	rotY = 0;
	oldTarget = Target;

	allKeysUp();
	recalculateViewArea();
}


//! destructor
CCameraMayaSceneNode::~CCameraMayaSceneNode()
{
}


//! It is possible to send mouse and key events to the camera. Most cameras
//! may ignore this input, but camera scene nodes which are created for 
//! example with scene::ISceneManager::addMayaCameraSceneNode or
//! scene::ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
//! for changing their position, look at target or whatever.
bool CCameraMayaSceneNode::OnEvent(SEvent event)
{
	if (event.EventType != EET_MOUSE_INPUT_EVENT ||
		!InputReceiverEnabled)
		return false;

	switch(event.MouseInput.Event)
	{
	case EMIE_LMOUSE_PRESSED_DOWN:
		MouseKeys[0] = true;
		break;
	case EMIE_RMOUSE_PRESSED_DOWN:
		MouseKeys[2] = true;
		break;
	case EMIE_MMOUSE_PRESSED_DOWN:
		MouseKeys[1] = true;
		break;
	case EMIE_LMOUSE_LEFT_UP:
		MouseKeys[0] = false;
		break;
	case EMIE_RMOUSE_LEFT_UP:
		MouseKeys[2] = false;
		break;
	case EMIE_MMOUSE_LEFT_UP:
		MouseKeys[1] = false;
		break;
	case EMIE_MOUSE_MOVED:
		{
			video::IVideoDriver* driver = SceneManager->getVideoDriver();
			if (driver)
			{
				core::dimension2d<s32> ssize = SceneManager->getVideoDriver()->getScreenSize();
				MousePos.X = event.MouseInput.X / (f32)ssize.Width;
				MousePos.Y = event.MouseInput.Y / (f32)ssize.Height;
			}
		}
		break;
	}
	return true;
}

//! onPostRender is called just after rendering the whole scene.
//! nodes may calculate or store animations here, and may do other useful things,
//! dependent on what they are.
void CCameraMayaSceneNode::OnPostRender(u32 timeMs)
{
	animate();

	ISceneNode::setPosition(Pos);
	updateAbsolutePosition();

	// This scene node cannot be animated by scene node animators, so
	// don't invoke them.
}


bool CCameraMayaSceneNode::isMouseKeyDown(s32 key)
{
	return MouseKeys[key];
}



void CCameraMayaSceneNode::animate()
{
	//Alt + LM = Rotieren um KameraDrehpunkt
	//Alt + LM + MM = Dolly vor/zurück in Kamerablickrichtung (Geschwindigkeit % von Abstand Kamera zu Drehpunkt - Maximalweg zum Kameradrehpunkt)
	//Alt + MM = Verschieben in Kameraebene (Bildmitte hängt vom Tempo ungefähr am Mauszeiger)

	const SViewFrustrum* va = getViewFrustrum();

	f32 nRotX = rotX;
	f32 nRotY = rotY;
	f32 nZoom = currentZoom;

	if (isMouseKeyDown(0) && isMouseKeyDown(2))
	{
		if (!zooming)
		{
			zoomStartX = MousePos.X;
			zoomStartY = MousePos.Y;
			zooming = true;
			nZoom = currentZoom;
		}
		else
		{
			f32 old = nZoom;
			nZoom += (zoomStartY - MousePos.Y) * zoomSpeed;

			f32 targetMinDistance = 0.1f;
			if (nZoom < targetMinDistance) // jox: fixed bug: bounce back when zooming to close
				nZoom = targetMinDistance;

			if (nZoom < 0)
				nZoom = old;
		}
	}
	else
	{
		if (zooming)
		{
			f32 old = currentZoom;
			currentZoom = currentZoom + (zoomStartY - MousePos.Y ) * zoomSpeed;
			nZoom = currentZoom;

			if (nZoom < 0)
				nZoom = currentZoom = old;
		}

		zooming = false;
	}

	// Translation ---------------------------------

	core::vector3df translate(oldTarget);

	core::vector3df tvectX = Pos - Target;
	tvectX = tvectX.crossProduct(UpVector);
	tvectX.normalize();

	core::vector3df tvectY = (va->getFarLeftDown() - va->getFarRightDown());
	tvectY = tvectY.crossProduct(UpVector.Y > 0 ? Pos - Target : Target - Pos);
	tvectY.normalize();
	

	if (isMouseKeyDown(1) && !zooming)
	{
		if (!translating)
		{
			translateStartX = MousePos.X;
			translateStartY = MousePos.Y;
			translating = true;
		}
		else
		{
			translate +=	tvectX * (translateStartX - MousePos.X)*translateSpeed + 
								tvectY * (translateStartY - MousePos.Y)*translateSpeed;
		}
	}
	else
	{
		if (translating)
		{
			translate +=	tvectX * (translateStartX - MousePos.X)*translateSpeed + 
								tvectY * (translateStartY - MousePos.Y)*translateSpeed;
			oldTarget = translate;
		}

		translating = false;
	}

	// Rotation ------------------------------------

	if (isMouseKeyDown(2) && !zooming)
	{
		if (!rotating)
		{
			rotateStartX = MousePos.X;
			rotateStartY = MousePos.Y;
			rotating = true;
			nRotX = rotX;
			nRotY = rotY;
		}
		else
		{
			nRotX += (rotateStartX - MousePos.X) * rotateSpeed;
			nRotY += (rotateStartY - MousePos.Y) * rotateSpeed;
		}
	}
	else
	{
		if (rotating)
		{
			rotX = rotX + (rotateStartX - MousePos.X) * rotateSpeed;
			rotY = rotY + (rotateStartY - MousePos.Y) * rotateSpeed;
			nRotX = rotX;
			nRotY = rotY;
		}

		rotating = false;
	}

	// Set Pos ------------------------------------

	Target = translate;

	Pos.X = nZoom + Target.X;
	Pos.Y = Target.Y;
	Pos.Z = Target.Z;

	Pos.rotateXYBy(nRotY, Target);
	Pos.rotateXZBy(-nRotX, Target);

	// Rotation Error ----------------------------

	// jox: fixed bug: jitter when rotating to the top and bottom of y
	UpVector.set(0,1,0);
	UpVector.rotateXYBy(-nRotY, core::vector3df(0,0,0));
	UpVector.rotateXZBy(-nRotX+180.f, core::vector3df(0,0,0));

	/*if (nRotY < 0.0f)
		nRotY *= -1.0f;
	
	nRotY = (f32)fmod(nRotY, 360.0f);
	
	
	if (nRotY >= 90.0f && nRotY <= 270.0f)
		UpVector.set(0, -1, 0);
	else
		UpVector.set(0, 1, 0);*/
}


void CCameraMayaSceneNode::allKeysUp()
{
	for (s32 i=0; i<3; ++i)
		MouseKeys[i] = false;
}

// function added by jox: fix setPosition()
void CCameraMayaSceneNode::setPosition(const core::vector3df& pos) 
{
	Pos = pos;
	updateAnimationState();
}

// function added by jox: fix setTarget()
void CCameraMayaSceneNode::setTarget(const core::vector3df& pos) 
{
	Target = oldTarget = pos;
	updateAnimationState();
}


// function added by jox
void CCameraMayaSceneNode::updateAnimationState() 
{
	core::vector3df pos(Pos - Target);

	// X rotation
	core::vector2df vec2d(pos.X, pos.Z);
	rotX = (f32)vec2d.getAngle();

	// Y rotation
	pos.rotateXZBy(rotX, core::vector3df());
	vec2d.set(pos.X, pos.Y);
	rotY = -(f32)vec2d.getAngle();

	// Zoom
	currentZoom = (f32)Pos.getDistanceFrom(Target);
}

} // end namespace
} // end namespace

