// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_CAMERA_MAYA_SCENE_NODE_H_INCLUDED_D2__
#define __C_CAMERA_MAYA_SCENE_NODE_H_INCLUDED_D2__

#include <irrlicht.h>
// # include <CCameraSceneNode.h>
// # include <vector2d.h>

using namespace irr;
using namespace scene;

namespace irr
{
namespace d2
{


	class CCameraSceneNode : public ICameraSceneNode
	{
	public:

		//! constructor
		CCameraSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id, 
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& lookat = core::vector3df(0,0,100));

		//! destructor
		virtual ~CCameraSceneNode();

		//! Sets the projection matrix of the camera. The core::matrix4 class has some methods
		//! to build a projection matrix. e.g: core::matrix4::buildProjectionMatrixPerspectiveFovLH
		//! \param projection: The new projection matrix of the camera. 
		virtual void setProjectionMatrix(const core::matrix4& projection);

		//! Gets the current projection matrix of the camera
		//! \return Returns the current projection matrix of the camera.
		virtual const core::matrix4& getProjectionMatrix();

		//! Gets the current view matrix of the camera
		//! \return Returns the current view matrix of the camera.
		virtual const core::matrix4& getViewMatrix();

		//! It is possible to send mouse and key events to the camera. Most cameras
		//! may ignore this input, but camera scene nodes which are created for 
		//! example with scene::ISceneManager::addMayaCameraSceneNode or
		//! scene::ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
		//! for changing their position, look at target or whatever. 
		virtual bool OnEvent(SEvent event);

		//! sets the look at target of the camera
		//! \param pos: Look at target of the camera.
		virtual void setTarget(const core::vector3df& pos);

		//! Gets the current look at target of the camera
		//! \return Returns the current look at target of the camera
		virtual core::vector3df getTarget() const;

		//! sets the up vector of the camera
		//! \param pos: New upvector of the camera.
		virtual void setUpVector(const core::vector3df& pos);

		//! Gets the up vector of the camera.
		//! \return Returns the up vector of the camera.
		virtual core::vector3df getUpVector() const;

		//! \return returns value of the near plane of the camera
		virtual f32 getNearValue();

		//! \return returns value of the far plane of the camera
		virtual f32 getFarValue();

		//! \return returns aspect ration of the camera
		virtual f32 getAspectRatio();

		//! \return returns field of view of the camera
		virtual f32 getFOV();

		//! sets the value of the near clipping plane. (default: 1.0f)
		virtual void setNearValue(f32 zn);

		//! sets the value of the far clipping plane (default: 2000.0f)
		virtual void setFarValue(f32 zf);

		//! sets the aspect ratio (default: 4.0f / 3.0f)
		virtual void setAspectRatio(f32 aspect);

		//! sets the field of view (Default: PI / 3.5f)
		virtual void setFOV(f32 fovy);

		//! pre render event
		virtual void OnPreRender();

		//! render
		virtual void render();

		//! returns the axis aligned bounding box of this node
		virtual const core::aabbox3d<f32>& getBoundingBox() const;

		//! returns the view area. needed sometimes by bsp or lod render nodes.
		virtual const SViewFrustrum* getViewFrustrum();

		//! Disables or enables the camera to get key or mouse inputs.
		//! If this is set to true, the camera will respond to key inputs
		//! otherwise not.
		virtual void setInputReceiverEnabled(bool enabled);

		//! Returns if the input receiver of the camera is currently enabled.
		virtual bool isInputReceiverEnabled();

	protected:

		void recalculateProjectionMatrix();
		void recalculateViewArea();

		//core::vector3df Pos;
		core::vector3df Target;
		core::vector3df UpVector;

		core::matrix4 Projection;
		core::matrix4 View;

		core::aabbox3d<f32> BBox;

		f32 fovy;		// Field of view, in radians. 
		f32 aspect;	// Aspect ratio. 
		f32 zn;		// value of the near view-plane. 
		f32 zf;		// Z-value of the far view-plane.

		core::dimension2d<f32> screenDim;

		SViewFrustrum ViewArea;

		bool InputReceiverEnabled;
	};







	class CCameraMayaSceneNode : public CCameraSceneNode
	{
	public:

		//! constructor
		CCameraMayaSceneNode(ISceneNode* parent, ISceneManager* mgr, s32 id,
			f32 rotateSpeed = -1500.0f, f32 zoomSpeed = 200.0f, f32 translationSpeed = 100.0f);

		//! destructor
		virtual ~CCameraMayaSceneNode();

		//! It is possible to send mouse and key events to the camera. Most cameras
		//! may ignore this input, but camera scene nodes which are created for 
		//! example with scene::ISceneManager::addMayaCameraSceneNode or
		//! scene::ISceneManager::addMeshViewerCameraSceneNode, may want to get this input
		//! for changing their position, look at target or whatever. 
		virtual bool OnEvent(SEvent event);

		//! onPostRender is called just after rendering the whole scene.
		//! nodes may calculate or store animations here, and may do other useful things,
		//! dependent on what they are.
		virtual void OnPostRender(u32 timeMs);

		//! Sets the position of the node. Note that the position is
		//! relative to the parent.
		virtual void setPosition(const core::vector3df& newpos);

		//! Sets the position of the node. Note that the position is
		//! relative to the parent.
		virtual void setTarget(const core::vector3df& newpos);

	private:

		void allKeysUp();
		void animate();
		bool isMouseKeyDown(s32 key);
		void updateAnimationState();

		bool MouseKeys[3];

		core::vector3df Pos;
		bool zooming, rotating, moving, translating;
		f32 zoomSpeed;
		f32 translateSpeed;
		f32 rotateSpeed;
		f32 rotateStartX, rotateStartY;
		f32 zoomStartX, zoomStartY;
		f32 translateStartX, translateStartY;
		f32 currentZoom;
		f32 rotX, rotY;
		core::vector3df oldTarget;

		core::vector2df MousePos;
	};

} // end namespace
} // end namespace

#endif

