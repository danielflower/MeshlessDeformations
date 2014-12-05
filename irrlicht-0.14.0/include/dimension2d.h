// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_DIMENSION2D_H_INCLUDED__
#define __IRR_DIMENSION2D_H_INCLUDED__

#include "irrTypes.h"

namespace irr
{
namespace core
{

	//! Specifies a 2 dimensional size.
	template <class T>
	class dimension2d
	{
		public:

			dimension2d()
				: Width(0), Height(0) {};

			dimension2d(T width, T height)
				: Width(width), Height(height) {};

			dimension2d(const dimension2d<T>& other)
				: Width(other.Width), Height(other.Height) {};


			bool operator == (const dimension2d<T>& other) const
			{
				return Width == other.Width && Height == other.Height;
			}


			bool operator != (const dimension2d<T>& other) const
			{
				return Width != other.Width || Height != other.Height;
			}

			const dimension2d<T>& operator=(const dimension2d<T>& other) 
			{
				Width = other.Width;
				Height = other.Height;
				return *this;
			}

			T Width, Height;
	};

} // end namespace core
} // end namespace irr

#endif

