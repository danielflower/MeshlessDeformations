// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_MATERIAL_RENDERER_H_INCLUDED__
#define __I_MATERIAL_RENDERER_H_INCLUDED__

#include "IUnknown.h"
#include "SMaterial.h"
#include "S3DVertex.h"

namespace irr
{
namespace video  
{

class IVideoDriver;
class IMaterialRendererServices;

//!	Interface for material rendering. Can be used to extend the engine with new materials.
/** Refer to IVideoDriver::addMaterialRenderer() for more informations on how to extend the engine
 with new materials.
*/
class IMaterialRenderer : public IUnknown
{
public:

	//! destructor
	virtual ~IMaterialRenderer() {};

	//! Called by the IVideoDriver implementation the let the renderer
	//! set its needed render states. This is called during the IVideoDriver::setMaterial() call.
	//! When overriding this, you can set some renderstates or for example a vertex or pixel shader
	//! if you like.
	//! \param material: The new material parameters to be set. The renderer may change the material
	//! flags in this material. For example if this material does not accept the zbuffer = true, it
	//! can set it to false. This is useful, because in the next lastMaterial will be just the material
	//! in this call.
	//! \param lastMaterial: The material parameters which have been set before this material.
	//! \param resetAllRenderstates: True if all renderstates should really be reset. This is usually
	//! true if the last rendering mode was not a usual 3d rendering mode, but for example 
	//! a 2d rendering mode.
	//! You should reset really all renderstates if this is true, no matter if the lastMaterial had
	//! some similar settings. This is used because in most cases, some common renderstates are not
	//! changed if they are already there, for example bilinear filtering, wireframe, gouraudshading, 
	//! lighting, zbuffer, zwriteenable, backfaceculling and fogenable.
	//! \param services: Interface providing some methods for changing advanced, internal
	//! states of a IVideoDriver.
	virtual void OnSetMaterial(SMaterial& material, const SMaterial& lastMaterial,
		bool resetAllRenderstates, IMaterialRendererServices* service) {};

	//! Called every time before a new bunch of geometry is being drawn using this material with
	//! for example drawIndexedTriangleList() call. OnSetMaterial should normally only be called
	//! if the renderer decides that the renderstates should be changed, it won't be called if for
	//! example two drawIndexedTriangleList() will be called with the same material set. This 
	//! method will be called every time. This is useful for example for materials with shaders,
	//! which don't only set new renderstates but also shader constants.
	//! \param service: Pointer to interface providing methos for setting constants and other things.
	//! \param vtxtype: Vertex type with which the next rendering will be done. This can be used
	//! by the material renderer to set some specific optimized shaders or if this is an incompatible
	//! vertex type for this renderer, to refuse rendering for example.
	//! \return Returns true if everything is ok, and false if nothing should be rendered. 
	//! The material renderer can choose to return false for example if he doesn't support the
	//! specified vertex type. This is actually done in D3D8 and D3D9 when using a 
	//! normal mapped material with a vertex type other than EVT_TANGENTS. 
	virtual bool OnRender(IMaterialRendererServices* service, E_VERTEX_TYPE vtxtype) { return true; };

	//! Called by the IVideoDriver to unset this material. Called during the 
	//! IVideoDriver::setMaterial() call before the new material will get the OnSetMaterial()
	//! call.
	virtual void OnUnsetMaterial() {};

	//! Returns if the material is transparent. The scene managment needs to know this
	//! for being able to sort the materials by opaque and transparent.
	virtual bool isTransparent() { return false; }

	//! Returns the render capability of the material. Because some more complex materials
	//! are implemented in multiple ways and need special hardware capabilities, it is possible
	//! to query how the current material renderer is performing on the current hardware with this
	//! function.
	//! \return Returns 0 if everything is running fine. Any other value is material renderer
	//! specific and means for example that the renderer switched back to a fall back material because 
	//! it cannot use the latest shaders. More specific examples: 
	//! Fixed function pipeline materials should return 0 in most cases, parallax mapped
	//! material will only return 0 when at least pixel shader 1.4 is available on that machine.
	virtual s32 getRenderCapability() { return 0; }
};

//! Interface providing some methods for changing advanced, internal states of a IVideoDriver.
class IMaterialRendererServices
{
public: 

	//! Can be called by an IMaterialRenderer to make its work easier.
	//! Sets all basic renderstates if needed.
	//! Basic render states are diffuse, ambient, specular, and emissive color, specular power,
	//! bilinear and trilinear filtering, wireframe mode,
	//! grouraudshading, lighting, zbuffer, zwriteenable, backfaceculling and fog enabling.
	virtual void setBasicRenderStates(const SMaterial& material, 
		const SMaterial& lastMaterial,
		bool resetAllRenderstates) = 0;

	//! Sets a constant for the vertex shader based on a name. This can be used if you used
	//! a high level shader language like GLSL or HLSL to create a shader. Example: If you
	//! created a shader which has variables named 'mWorldViewProj' (containing the 
	//! WorldViewProjection matrix) and another one named 'fTime' containing one float, 
	//! you can set them in your IShaderConstantSetCallBack derived class like this:
	//! \code
	//! virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
	//! {
	//! 	video::IVideoDriver* driver = services->getVideoDriver();
	//! 
	//! 	float time = (float)os::Timer::getTime()/100000.0f;
	//! 	services->setVertexShaderConstant("fTime", &time, 1);
	//! 
	//! 	core::matrix4 worldViewProj;
	//! 	worldViewProj = driver->getTransform(video::ETS_PROJECTION);			
	//! 	worldViewProj *= driver->getTransform(video::ETS_VIEW);
	//! 	worldViewProj *= driver->getTransform(video::ETS_WORLD);
	//! 	services->setVertexShaderConstant("mWorldViewProj", worldViewProj.M, 16);
	//! }
	//! \endcode
	//! \param name: Name of the variable
	//! \param floats: Pointer to array of floats
	//! \param count: Amount of floats in array.
	//! \return: Returns true if successful.
	virtual bool setVertexShaderConstant(const c8* name, const f32* floats, int count) = 0;

	//! Sets a vertex shader constant. Can be used if you created a shader using 
	//! pixel/vertex shader assembler or ARB_fragment_program or ARB_vertex_program.
	//! \param data: Data to be set in the constants
	//! \param startRegister: First register to be set
	//! \param constantAmount: Amount of registers to be set. One register consists of 4 floats.
	virtual void setVertexShaderConstant(f32* data, s32 startRegister, s32 constantAmount=1) = 0;

	//! Sets a constant for the pixel shader based on a name. This can be used if you used
	//! a high level shader language like GLSL or HLSL to create a shader. See 
	//! setVertexShaderConstant() for an example on how to use this.
	//! \param name: Name of the variable
	//! \param floats: Pointer to array of floats
	//! \param count: Amount of floats in array.
	//! \return: Returns true if successful.
	virtual bool setPixelShaderConstant(const c8* name, const f32* floats, int count) = 0;

	//! Sets a pixel shader constant. Can be used if you created a shader using 
	//! pixel/vertex shader assembler or ARB_fragment_program or ARB_vertex_program.
	//! \param data: Data to be set in the constants
	//! \param startRegister: First register to be set.
	//! \param constantAmount: Amount of registers to be set. One register consists of 4 floats.
	virtual void setPixelShaderConstant(f32* data, s32 startRegister, s32 constantAmount=1) = 0;

	//! Returns a pointer to the IVideoDriver interface
	virtual IVideoDriver* getVideoDriver() = 0;
};

} // end namespace video
} // end namespace irr

#endif

