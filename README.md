# Saint-Nec Engine

Saint-Nec Engine is 3rd year engineering school project created by Abdeljalil Zoghlami and Antonin Devidal starting on october 8th and ending on march 17th.

This 240h project aim to create a physic and graphic engine using C++ and OpenGL on Visual Studio.

## Technologies

- C++ 17
- OpenGL 4.1
- CMake (tested on Windows and Linux)
- Tracy profiler (v0.10.0)

In this project, we are reinventing the wheel because we can’t create better things without understanding the base of what we are working on.

## [Documentation](https://antonindevidal.github.io/Saint-Nec-Engine-Documentation)

You can find Doxygen documentation enhanced with [Doxygen Theme - Flat Design](https://github.com/kcwongjoe/doxygen_theme_flat_design).

## Objectives

### Physics

- [X]  Basic objects collisions ( spheres, cubes)
- [ ]  Complex objects collisions ( terrain)

### Graphics

- [X]  Terrain generation
- [X]  Grass simulation
- [X]  Water simulation

This tasks will use various implementation techniques such as particles, complex shaders, lighting, level of detail and multi-threading.

## Videos

### Grass Generation with wind 

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Ft2P-KOoZWY
" target="_blank"><img src="http://img.youtube.com/vi/Ft2P-KOoZWY/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="1280" height="720" border="10" /></a>

### Terrain Generation with tesselation

<a href="http://www.youtube.com/watch?feature=player_embedded&v=4_0hg54vT2w
" target="_blank"><img src="http://img.youtube.com/vi/4_0hg54vT2w/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="1280" height="720" border="10" /></a>


## Sprints reviews
- [Sprint 1](Doc/SprintReviews/Sprint_1.md)
- [Sprint 2](Doc/SprintReviews/Sprint_2.md)
- [Sprint 3](Doc/SprintReviews/Sprint_3.md)
- [Sprint 4](Doc/SprintReviews/Sprint_4.md)
- [Sprint 5](Doc/SprintReviews/Sprint_5.md)
- [Sprint 6](Doc/SprintReviews/Sprint_6.md)
- [Sprint 7](Doc/SprintReviews/Sprint_7.md)
- [Sprint 8](Doc/SprintReviews/Sprint_8.md)
- [Sprint 9](Doc/SprintReviews/Sprint_9.md)


## Run the demo

### On Linux

- create the folder build: <span style="color:orange">Saint-Nec-Engine/Saint-Nec-Engine/build</span>
- move in the build folder
- type cmake ..
- The game executable is in <span style="color:orange">build/Saint-Nec-Engine</span>

### Commandes

You can move the camera with the touch:
- Z : above
- S : behind
- Q : left
- D : right
- Shift : up
- Space : down
- F1 : unlock mouse selector
- F2 : Wireframe mode
