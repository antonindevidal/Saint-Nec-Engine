# CMakeList.txt : projet CMake pour Saint-Nec-Engine, incluez la source et définissez
# la logique spécifique au projet ici.

add_executable (Saint-Nec-Engine)
set(_SAINT_NEC_ENGINE_SRC 
	"src/Saint-Nec-Engine.cpp"
)

set(_SAINT_NEC_ENGINE_HDR
	"src/Saint-Nec-Engine.h"
)
target_sources(Saint-Nec-Engine PRIVATE ${_SAINT_NEC_ENGINE_SRC})
target_sources(Saint-Nec-Engine PUBLIC ${_SAINT_NEC_ENGINE_HDR})


# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_libraries(Saint-Nec-Engine Saint-Nec-Engine-Lib glfw glad imgui)


add_subdirectory(Dependencies)
