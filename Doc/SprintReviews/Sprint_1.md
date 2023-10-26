## What happened during this sprint?

- Created the project for Visual Studio
- Added  needed dependencies for the project:
    - GLFW
    - Glad
    - imgui
- Moved the entire project to CMake for portability (tested on Linux and Windows)
- Created the base architecture of the project

The project is separated into 3 projects:

- Saint-Nec-Engine: executable (graphic application)
- Saint-Nec-Engine-Lib: library of the engine (containing physics and base architecture)
- Saint-Nec-Engine-Test: Project for unit testing of Saint-Nec-Engine-Lib

- Researched how to detect collision
    - AABB Algorithm
        
        Won’t be implemented
        
    - Separate Axis Theorem
        
        First algorithm to implement and optimize further
        
        - Sweep and Prune (optimization)
    - Continuous Collision Detection
        
        If we have time enough, would be great to implement
        

- Associated Pull Request
    - https://github.com/antonindevidal/Saint-Nec-Engine/pull/2
    - https://github.com/antonindevidal/Saint-Nec-Engine/pull/3
    - https://github.com/antonindevidal/Saint-Nec-Engine/pull/5
    - https://github.com/antonindevidal/Saint-Nec-Engine/pull/6