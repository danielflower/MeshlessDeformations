// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_PARTICLE_AFFECTOR_H_INCLUDED__
#define __I_PARTICLE_AFFECTOR_H_INCLUDED__

#include "IUnknown.h"
#include "SParticle.h"

namespace irr
{
namespace scene
{

//! A particle affector modifies particles.
class IParticleAffector : public IUnknown
{
public:

	//! Affects an array of particles.
	//! \param now: Current time. (Same as ITimer::getTime() would return)
	//! \param particlearray: Array of particles.
	//! \param count: Amount of particles in array.
	virtual void affect(u32 now, SParticle* particlearray, u32 count) = 0;

};

} // end namespace scene
} // end namespace irr


#endif

