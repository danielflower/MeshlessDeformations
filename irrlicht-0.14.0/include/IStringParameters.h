// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_STRING_PARAMETERS_H_INCLUDED__
#define __I_STRING_PARAMETERS_H_INCLUDED__

#include "IUnknown.h"

namespace irr
{

//! Provides a generic interface for parameters and their values as strings.
class IStringParameters : public IUnknown
{
public:

	//! Sets a string parameter. 
	//! \param parameterName: Name for the parameter
	//! \param value: Value for the parameter. Set this to 0 to delete the parameter
	virtual void setParameter(const c8* parameterName, const c8* value) = 0;

	//! Gets a string parameter.
	//! \param parameterName: Name of the parameter to get.
	//! \return Returns value of the parameter previously set by setParameter() as string
	//! or 0 if parameter is not set.
	virtual const c8* getParameter(const c8* parameterName) = 0;

	//! Sets a parameter as boolean value
	virtual void setParameter(const c8* parameterName, bool value) = 0;

	//! Gets a parameter as boolean value
	//! \param parameterName: Name of the parameter to get.
	//! \return Returns value of the parameter previously set by setParameter() as bool
	//! or 0 if parameter is not set.
	virtual bool getParameterAsBool(const c8* parameterName) = 0;

	//! Sets a parameter as integer value
	virtual void setParameter(const c8* parameterName, s32 value) = 0;

	//! Gets a parameter as integer value
	//! \param parameterName: Name of the parameter to get.
	//! \return Returns value of the parameter previously set by setParameter() as integer
	//! or 0 if parameter is not set.
	virtual s32 getParameterAsInt(const c8* parameterName) = 0;

	//! Sets a parameter as float value
	virtual void setParameter(const c8* parameterName, f32 value) = 0;

	//! Gets a parameter as integer value
	//! \param parameterName: Name of the parameter to get.
	//! \return Returns value of the parameter previously set by setParameter() as float value
	//! or 0 if parameter is not set.
	virtual f32 getParameterAsFloat(const c8* parameterName) = 0;

	//! Returns amount of string parameters set in this scene manager.
	virtual s32 getParameterCount() = 0;

	//! Returns string parameter name by index. 
	//! \param index: Index value, must be between 0 and getParameterCount()-1.
	virtual const c8* getParameterName(s32 index) = 0;

	//! Returns string parameter value by index. 
	//! \param index: Index value, must be between 0 and getParameterCount()-1.
	virtual const c8* getParameterValue(s32 index) = 0;	
};

} // end namespace 

#endif

