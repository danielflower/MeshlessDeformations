==========================================================================
The Irrlicht Engine SDK version 0.14.0
==========================================================================

  Welcome the Irrlicht Engine SDK.

  Content of this file:

  1. Directory structure overview
  2. How to start
  3. Requirements
  4. Release Notes
  5. License
  6. Contact



==========================================================================
1. Directory structure overview
==========================================================================

  You will find some directories after decompressing the archive in which
  came the SDK. These are:
  
  \bin         The compiled library Irrlicht.DLL and some compiled demo 
               and example applications, just start them to see the 
               Irrlicht Engine in action.
  \doc         Documentation of the Irrlicht Engine.
  \examples    Examples and tutorials showing how to use the native engine
               engine using C++.
  \example.net Examples and tutorials showing how to use the engine with
               a .net languages.
  \exporters   Exporters and tools for varous 3D modelling packages. There
               is a readme file with more details in the directory.
  \include     Header files to include when using the engine.
  \lib         Lib to link with your programs when using the engine.
  \media       Graphics and sound data for the demo applications and
               examples.
  \source      The source code of the Irrlicht Engine. This code is
               not needed to develop applications with the engine,
               but it is included to let you be able to recompile and
               debug it, if necessary.     
  \tools       Useful tools and their sourcecode for the engine.



==========================================================================
2. How to start
==========================================================================

  To see the engine in action in Windows, just go to the \bin\Win32-VisualStudio
  directory, and start some applications. There should also be an
  application named Demo.exe, this should show the most
  interesting things.
  
  To start developing own applications and games with the engine take 
  a look at the 01.HelloWorld example in the \examples directory.
  There will also be a .html file with a tutorial which should be
  easy to understand.

  The Irrlicht Engine is a static lib under linux. A precomipled version can be
  found in \lib\Linux. 
  
  If you wish to compile the engine in linux yourself, unzip the file source.zip
  file in the \source directory. Run a 'make' in the now existing new subfolder
  'Irrlicht'. After this, you should be able to make all example applications in 
  \examples. Then just start an X Server and run them, from the directory where 
  they are.
  
  It is also possible to use Irrlicht as shared object (libIrrlicht.so.versionNumber),
  use the makefile target for this, running 'make sharedlib' in the source folder.
  See Makefile for details.


==========================================================================
3. Requirements
==========================================================================

  You can use one of the following compilers/IDEs to develop applications
  with Irrlicht or recompile the engine. However, other compilers/IDEs make work 
  as well, we simply didn't test them. 
  
  * gcc 3.2
  * gcc 3.3
  * gcc 3.4
  * Visual Studio 6.0
  * Visual Studio.NET (7.0)
  * Visual Studio.NET 2003 (7.1)
  * Visual Studio 2005 (8.0)
  * DevC++ 4.9 & gcc (project files included)
     
  If you ever want to (re)compile the engine yourself (which means you don't
  want to use the precompiled version) you need the following:
  
  * Windows:
  	* Needed: PlatformSDK (which usually comes with all IDEs)
  	* Optional: DirectX 9 SDK, for D3D9 support
  	* Optional: DirectX 8 SDK, for D3D8 support
  	
  * Linux:
  	* Needed: XServer with GLX + XF86VidMode extension (should be there by default)
  	* Optional: OpenGL headers and libraries (libGL and libGLU), for OpenGL support
  	
  	
==========================================================================
4. Release Notes
==========================================================================

  This is an alpha version of the SDK. Therefore please note that there are
  features missing in the engine and maybe also some bugs. 

  Informations about changes in this new version of the engine can be 
  found in changes.txt.

  Please also note that the textures, 3D models and levels are copyright
  by their authors and not included in the Irrlicht engine license. 

==========================================================================
5. License
==========================================================================

  The license of the Irrlicht Engine is based on the zlib/libpng license.
  Even though this license does not require you to mention that you are
  using the Irrlicht Engine in your product, an acknowledgement
  would be highly appreciated.

  Please note that the Irrlicht Engine is based in part on the work of 
  the Independent JPEG Group and the zlib. This means that if you use
  the Irrlicht Engine in your product, you must acknowledge somewhere 
  in your documentation that you've used the IJG code. It would also be
  nice to mention that you use the Irrlicht Engine and the zlib.
  See the README files in the jpeglib and the zlib for
  further informations.


  The Irrlicht Engine License
  ===========================

  Copyright (C) 2002-2005 Nikolaus Gebhardt

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  

  
==========================================================================
6. Contact
==========================================================================

  If you have problems, questions or suggestions, please visit the 
  official homepage of the Irrlicht Engine:
  
  http://irrlicht.sourceforge.net
  
  You will find forums, bugtrackers, patches, tutorials, and other stuff
  which will help you out.
  
  If want to contact the author of the engine, please send an email to
  Nikolaus Gebhardt:
  
  irrlicht@users.sourceforge.net


  
    