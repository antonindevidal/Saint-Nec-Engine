# CMakeList.txt : projet CMake pour Saint-Nec-Engine-Lib, incluez la source et définissez
# la logique spécifique au projet ici.
#

# Ajoutez une source à l'exécutable de ce projet.
add_library (Saint-Nec-Engine-Lib 
				"architecture/Component.cpp"
				"architecture/Scene.cpp" 
				"architecture/GameObject.cpp"
				"architecture/SceneManager.cpp"
				"Physics/BoxCollider.cpp"
				"Physics/SphereCollider.cpp"
				"graphics/Cube.cpp"
				 "graphics/Shader.cpp")

target_include_directories(Saint-Nec-Engine-Lib  PUBLIC .)

target_link_libraries(Saint-Nec-Engine-Lib glfw glad glm)
