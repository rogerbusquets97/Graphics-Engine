# Graphics-Engine - Roger Busquets Duran and Josep Huguet Giron
Graphics Engine developed with Qt Creator for University class.

## Features:
* Unity like UI (Hierarchy, inspector, scene, ...).
* Create and delete Game Objects.
* Add Components to Game Objects (Light and Mesh.)
* Load Meshes to scene. 

To do so: Create a game object, select it and add a Component Mesh to it. Click load mesh and select it from browser (".obj" or ".fbx").

NOTE: YOU WILL NEED TO ADD A LIGHT TO SEE IT.

To delete a mesh from the scene, just delete the game object.

* Multiple lighting.

To add lights: Create a game object, select it and add a  Component Light to it. There are several settings in the UI you can play with.

NOTE: Lights are needed to see the meshes in the scene. For example, create a Directional Map with Rotation (-90, 0, 0).

To delete the light from the scene, just delete the game object.

You can add multiple lights of both types, directional and point lights. You can change their colors and set their diffuse, ambient and specular attributes.

To move them around the space, it is highly recommended to use the mousewheel hovering the transform values on the inspector.

A directional light example:

![Image](http://i66.tinypic.com/28hct9v.png)

Multiple Point Lights example:

![Image](http://i63.tinypic.com/15551lk.png)

Directional + Point Lights example:

![Image](http://i68.tinypic.com/ighq2u.png)


* Deferred Shading

Instead of direct rendering, we postpone the heavy processing to a later state. We do that by creating a gbuffer where we store all the geometry information of the scene and then we make a lightning pass to a quad that renders the scene fragment per fragment using the gbuffer info previously stored.

Init picture:

![Image](http://i65.tinypic.com/1xz868.png)

Sending info to Geometry Pass and Lightning Pass:

![Image](http://i66.tinypic.com/2ykau5h.png)


* Diffuse texturing

To add diffuse texturing to a mesh, go to the Diffuse section of your Component Mesh and click on Load. Select the image on your browser. You can set the tiling, mirror it, and enable it and disable it as you please.

![Image](http://i64.tinypic.com/20fcoea.png)

* Normal mapping

To add a normal map to a mesh, go to the Normal section of your Component Mesh and click on Load. Select the image on your browser. You can mirror it and enable it and disable it as you please.

![Image](http://i64.tinypic.com/1et5qw.png)

![Image](http://i66.tinypic.com/2lcb3vk.png)

* Parallax Mapping

To add a height map to a mesh, go to the Height Map section of your component mesh and click on Load. Select the image on your browser. You can mirror it and disable it as your please.

NOTE: Normal map needs to be enabled for Parallax Mapping to work.

![Image](http://i68.tinypic.com/mwb49x.png)

![Image](http://i63.tinypic.com/fc8f3k.png)


## Qt features used:
* Slots and Signals: all signals triggered by UI widgets are connected to custom Slots that implement a certain functionallity. For example 
de Create and Delete button for managing objects triggers the Clicked() Signal that is connected to the Slot that creates or deletes the object.
The same applies for creating components or changing their variables. 
* Widget Promotion: some widgets has been promoted to use a custom behaviour coded from scratch. The rendering window (where shapes are rendered)
and the inspector has been promoted to run an specific behaviour. 
* QPainter: The QPainter feature provided by Qt has been used to render shapes for all the objects with a Shape component attached to them.
* Dialogs: In order to warn the user we have used dialogs from Qt to make sure some "dangerous actions" (like exting) are safe to compute. 

