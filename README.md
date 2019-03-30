# Graphics-Engine - Josep Huguet Giron and Roger Busquets Duran
Graphics Engine developed with Qt Creator for University class.
## Fetures:
* Unity like UI (Hierarchy, inspector, scene, ...).
* Create and delete Game Objects.
* Add Components to Game Objects (just a few for now).
* Shape Render component (component that allow a game object to render an specific shape).
* Save and Load scenes.



## Qt features used:
* Slots and Signals: all signals triggered by UI widgets are connected to custom Slots that implement a certain functionallity. For example 
de Create and Delete button for managing objects triggers the Clicked() Signal that is connected to the Slot that creates or deletes the object.
The same applies for creating components or changing their variables. 
* Widget Promotion: some widgets has been promoted to use a custom behaviour coded from scratch. The rendering window (where shapes are rendered)
and the inspector has been promoted to run an specific behaviour. 
* QPainter: The QPainter feature provided by Qt has been used to render shapes for all the objects with a Shape component attached to them.
* Dialogs: In order to warn the user we have used dialogs from Qt to make sure some "dangerous actions" (like exting) are safe to compute. 
*

