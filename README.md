Meshless Deformations Based on Shape Matching
=============================================

This C++ project was created for a graduate level computer science course at the [University of Auckland](https://www.cs.auckland.ac.nz/) back in 2005 (COMPSCI 715 S2 C - Advanced Computer Graphics). This was created by Daniel Weisser, Heiko Voigt, and myself. 

The source code contains bits of the [Irrlicht](http://irrlicht.sourceforge.net/) game engine, and some other maths libraries with attributions in the source code.

[Read the project report](MeshlessDeformationsReport.pdf) to get more details about how this works.

How to run
----------

You need Windows. This has been tested on Windows 8.1 only. Just run `MeshlessDeformations.exe` located in the `Debug` folder.

How to build
------------

This has only been tested on Windows 8.1 64bit using Visual Studio 2013. You should be able to just build the solution from Visual Studio and then go to the Debug folder and run the exe.

Note that this project has been constructed by someone who doesn't understand C++ well, nor how to build C++ projects, so it is not exactly production quality. 

Usage Instructions
------------------

This demo allows you to throw around and collide a number of deformable objects.

To pick up an object, simply click and drag a particle with the left mouse button.  When you click on an object, you can alter its alpha and beta values, which affect the way that object deforms.  You can also change the elasticity, which affects how much energy is lost when that particle collides with other objects.  Finally, you can turn the object on and off.

When you start the program, there is only one object visible.  To add more, click on an object name in the objects list, and tick the "show this object" checkbox.  Most objects are meshless, but try showing the duck to see a meshed model.

You can also alter global parameters, such as the force of gravity and the speed of time.  If you slow time down to zero, you can move the particles around and see how the goal positions are affected by changing the parameters. You can also turn the goal positions on and off.

Finally, you can select either basic, linear, or quadratic shape matching.

Camera Controls
---------------

Rotation: hold down the right mouse button and move the mouse.
Zoom: hold down the left and right mouse buttons together and move the mouse up or down.
Moving: hold down the middle button and move the mouse.

