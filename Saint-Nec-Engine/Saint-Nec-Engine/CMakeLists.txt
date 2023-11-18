# CMakeList.txt : projet CMake pour Saint-Nec-Engine, incluez la source et définissez
# la logique spécifique au projet ici.

add_executable (Saint-Nec-Engine)
set(_SAINT_NEC_ENGINE_SRC 
	"src/Saint-Nec-Engine.cpp"
	"src/Game.cpp"
	"src/ui_helper/UiHelper.cpp"
	"src/scenes/FirstScene.cpp"
	"src/terrain/TerrainScene.cpp"
)

set(_SAINT_NEC_ENGINE_HDR
	"src/Saint-Nec-Engine.h"
	"src/Game.hpp"
	"src/ui_helper/UiHelper.hpp"
	"src/scenes/FirstScene.hpp"
	"src/terrain/TerrainScene.hpp"
)

# Make the copy of the resource fil every time
add_custom_target(copy_resources ALL 
					COMMAND ${CMAKE_COMMAND} -E copy_directory
						${CMAKE_SOURCE_DIR}/Saint-Nec-Engine/resources/ 
						${CMAKE_BINARY_DIR}/Saint-Nec-Engine/resources/
)
add_dependencies(Saint-Nec-Engine copy_resources)

target_sources(Saint-Nec-Engine PRIVATE ${_SAINT_NEC_ENGINE_SRC})
target_sources(Saint-Nec-Engine PUBLIC ${_SAINT_NEC_ENGINE_HDR})


# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_libraries(Saint-Nec-Engine Saint-Nec-Engine-Lib glfw glad imgui glm stb_image TracyClient)



add_subdirectory(Dependencies)
