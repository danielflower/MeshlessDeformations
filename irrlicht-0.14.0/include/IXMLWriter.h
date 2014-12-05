// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_XML_WRITER_H_INCLUDED__
#define __I_XML_WRITER_H_INCLUDED__

#include "IUnknown.h"

namespace irr
{
namespace io
{

	//! Interface providing methods for making it easier to write XML files.
	/** This XML Writer only writes UTF-16 xml files, because these are parsed 
	faster than all other formats by IXMLReader.
	*/
	class IXMLWriter : public IUnknown
	{
	public:

		//! Destructor
		virtual ~IXMLWriter() {};

		//! Writes a xml 1.0 header like <?xml version="1.0"?>. This should
		//! always be called before writing anything other, because also the
		//! text file header for unicode texts is written out with this method.
		virtual void writeXMLHeader() = 0;

		//! Writes an xml element with maximal 5 attributes like <foo /> or
		//! <foo optAttr="value" />. The element can be empty or not.
		//! \param name: Name of the element
		//! \param empty: Specifies if the element should be empty. Like <foo />. If
		//! You set this to false, something like this is written instead: <foo>.
        virtual void writeElement(const wchar_t* name, bool empty=false,
			const wchar_t* attr1Name = 0, const wchar_t* attr1Value = 0,
			const wchar_t* attr2Name = 0, const wchar_t* attr2Value = 0,
			const wchar_t* attr3Name = 0, const wchar_t* attr3Value = 0,
			const wchar_t* attr4Name = 0, const wchar_t* attr4Value = 0,
			const wchar_t* attr5Name = 0, const wchar_t* attr5Value = 0) = 0;

		//! Writes a comment into the xml file
		virtual void writeComment(const wchar_t* comment) = 0;

		//! Writes the closing tag for an element. Like </foo>
		virtual void writeClosingTag(const wchar_t* name) = 0;

		//! Writes a text into the file. All occurrences of special characters like
		//! & (&amp;), < (&lt;), > (&gt;), and " (&quot;) are automaticly replaced.
		virtual void writeText(const wchar_t* text) = 0;

		//! Writes a line break
		virtual void writeLineBreak() = 0;
	};

} // end namespace irr
} // end namespace io

#endif

