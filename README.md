This is the documentation for the Build a Box Game Engine

## What is the Build a Box Game Engine?

The Build a Box Engine helps to create 3D games using C++ and OpenGL. It handles all the basic things needed like opening a window, having dedicated update steps and asset importing.

To get started, you just have to create a child class from the Game class that can be found in the Game.h file in the engine folder.
Create a main.cpp file, make an object of your game in main method and call the run function on the object.
Make sure to set up a CMake file that has the engine as a linked library. The DocumentationExample folder has an example for this setup.
That is all you need to start your game window.

### Prerequisites
- CMake version 25
- Visual Studio 2022 compiler
- In CLion under Preferences -> Build, Execution, Deployment -> CMake -> Use Ninja as the default generator

### Folder structure

Before starting on your own project, there are a few folders that need to be explained. The hierarchy of these should not be changed since the engine is depending on those.
First the asset folder. The asset loader will load assets only from this folder. This goes for 3d assets (.glb), textures, and sounds files.
Second, there is the engine folder. It contains all the includes you need to access engine features.
Then there is the extern folder, it contains external libraries like glf, glm or soloud. You can add your own libraries, but take a look at the CMake files if you do so.
Then there are two example projects, the basic one is a minimal setup that provides you with an empty template, the other one is a full game build with the engine and can be used as a reference.
### How to build a game with the engine

As already said, it is recommended that take a look at the 2 provided examples. If you start with the basic on in the DocumentationExample folder, you need to know the following:

The game class provides you with a few functions that can be overridden. Those are:

```
start()     // gets called when the game starts
update()    // gets called every frame
draw()      // gets called every frame during the draw step
drawUI()    // draws UI
```

These are very useful for initializing game data and so on.
However, the engine also provides you with an event system. You can subscribe to events in objects, which means you don't have to store objects in the game object and then call functions on them from there.
Instead, the following events are already provided:

        event_t onStartup
        event_t onAfterStartup
        event_t onBeforeUpdate
        event_t onUpdate
        event_t onAfterUpdate
        event_t onDraw
        event_t onBeforeShutdown
        event_t onShutdown


The names are self-explanatory and get called in the order displayed above however, it is worth mentioning that the before and after events do not have any special purpose other than providing an easy way to introduce an order to specific steps if data needs to be set, for example before another object access it.

### The entity component system (ECS)

Use of the ECS is recommended as it lets use the provided system and components and lets you create your own ones.
In this engine it is mainly used for architecture and usability reasons, not for data optimization.
In short, an ECS divides the common game object into:
- Entities (normally just a global unique ID or GUID for short)
- Components (mainly data containers)
- and Systems (Hold logic that gets called on components)

One of the advantages there is that the components of a given type are not stored on the entity. They are stored together in an array in the ECS, which has the advantage that a system like the renderer system can iterate over the components easily,
just by accessing the container of said component type. Events can be registered in systems,  which means the only thing your game class really has to do is create the necessary / wanted systems on startup. New entity GUIDs and components can get created inside system or its own Prefab class/manager/factory.
Components on and entity can also accessed via the entities GUID and vice versa.

### Engine components and systems that you will or should use

- #### The Transform component:
  - Holds the local transform data (position, rotation, scale)
  - Has a reference (GUID) to its parent and possible children
  - Can calculate world transform data
  - Is Required in general for every entity

- #### The Draw mesh system and components:
  - Needs to be initialized inside the derived game class
  - Will iterate over every entity with a mesh component and tries to render them
  - Entities that should be rendered require: A transform component, a mesh component and a shader component,
  - Additionally, optionally the material component can be used to render textures onto objects

- #### The camera component
  - The camera component has its own transform and entity and is by default a child of the origin. The game stores a reference to its entity ad it can be accessed like this.
  - ``game.camera->getComponent<CameraComponent>()``
  - You can set its data to follow a specific entity, for example.

### Now build your own game

This should already cover everything you need to know to build a game with this engine.
Make sure to initialize the mesh renderer and make sure that the camera looks at the object. After that, try to make your own system that moves the object on a button press.
Have fun!






