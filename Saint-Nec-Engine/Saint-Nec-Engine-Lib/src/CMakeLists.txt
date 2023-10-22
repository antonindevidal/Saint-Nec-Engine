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
				)

target_include_directories(Saint-Nec-Engine-Lib  PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  ... other required includes
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Saint-Nec-Engine PROPERTY CXX_STANDARD 20)
endif()

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
