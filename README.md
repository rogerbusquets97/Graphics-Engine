# Graphics-Engine - Roger Busquets Duran and Josep Huguet Giron
Graphics Engine developed with Qt Creator for University class.

## Features:
* Unity like UI (Hierarchy, inspector, scene, ...).
* Create and delete Game Objects.
* Add Components to Game Objects (Light and Mesh.)
* Load Meshes to scene. 

To do so: Create a game object, select it and a Component Mesh to it. Click load mesh a select it from browser (".obj" or ".fbx").

NOTE: YOU WILL NEED TO ADD A LIGHT TO SEE IT.

To delete a mesh from the scene, just delete the game object.

* Multiple lighting.

To add lights: Create a game object, select it and a Component Light to it. There are several settings in the UI you can play with.

NOTE: Lights are needed to see the meshes in the scene. For example, create a Directional Map with Rotation (-90, 0, 0).

To delete the light from the scene, just delete the game object.

* Deferred Shading

Instead of direct rendering, we postpone the heavy processing to a later state. We do that by creating a gbuffer where we store all the geometry information of the scene and then we send make lightning pass to a quad that renders the scene fragment per fragment using the gbuffer info previously stored.

* Diffuse texturing

To add diffuse texturing to a mesh, go to the Diffuse section of your Component Mesh and click on Load. Select the image on your browser. You can set the tiling, mirror it, and enable it and disable it as you please.

* Normal mapping

To add a normal map to a mesh, go to the Normal section of your Component Mesh and click on Load Normal. Select the image on your browser. You can mirror it and enable it and disable it as you please.

## Qt features used:
* Slots and Signals: all signals triggered by UI widgets are connected to custom Slots that implement a certain functionallity. For example 
de Create and Delete button for managing objects triggers the Clicked() Signal that is connected to the Slot that creates or deletes the object.
The same applies for creating components or changing their variables. 
* Widget Promotion: some widgets has been promoted to use a custom behaviour coded from scratch. The rendering window (where shapes are rendered)
and the inspector has been promoted to run an specific behaviour. 
* QPainter: The QPainter feature provided by Qt has been used to render shapes for all the objects with a Shape component attached to them.
* Dialogs: In order to warn the user we have used dialogs from Qt to make sure some "dangerous actions" (like exting) are safe to compute. 
*

