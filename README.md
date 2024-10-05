
# My own graphics engine on C++ and OpenGL

My task was to create a game engine in C++ and OpenGL for the subject of graphics programming at CTU. I wanted to create the most universal program that would have the functionality to allow the user to load their own 3D models, manipulate them, customize the environment, create and save their own scenes. 


## Demo

![My Engine](https://github.com/user-attachments/assets/5df7211d-4ccc-479e-b9ba-c00dab36d78c)



## Usage/Examples

```
W, A, S, D  - camera movement. 
Ctrl - acceleration, 
SHIFT/Spase - down/up.

TAB - lock cursor.

     C key - copy the object.
     Backspace - delete.

     Key 1 - load standard model.
     2 - load the model to which the special shader will be applied.
     3 - add spot light (right mouse button to change the color of the light).
     4 - add spot light
     5 - adding the hardcode
     6 - add camera(L - freeze cameras)(right arrow - switch between cameras).
     7 - adding points to animate the object.
     H - disable visibility of points.

     0 - turn the sun on/off
     9 - turn on/off fog
     Each object in the scene can be selected. O key on the selected object - use shadows. P key - start animation(up arrow - toggle interpolation).

     Right at the beginning you will be offered to open the prepared scene. If no such scene exists, press the ESC key. A default one will be created.
     F1 to save the scene.
     F2 to load the scene.

```


## Installation

The project was developed on windows using MinGW. For a long time there was Linux support, but in the end it had to be abandoned.

To build and run the project you need to set the project working directory to the root directory of the project.

    