# CMakeList.txt : projet CMake pour Saint-Nec-Engine, incluez la source et définissez
# la logique spécifique au projet ici.

add_executable (Saint-Nec-Engine 
	"src/Saint-Nec-Engine.cpp"
	"src/Saint-Nec-Engine.h"
)


# Saint Nec lib ---------------------------------------------------------------------------------------
target_link_directories(Saint-Nec-Engine PUBLIC ../Saint-nec-Engine-lib/src)
target_link_libraries(Saint-Nec-Engine Saint-Nec-Engine-Lib)


# GLFW ------------------------------------------------------------------------------------------------
find_package( OpenGL REQUIRED )

add_subdirectory("Dependencies/glfw")

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
target_link_libraries( Saint-Nec-Engine glfw )

# GLAD ------------------------------------------------------------------------------------------------
add_subdirectory ("Dependencies/GLAD/include")
target_link_directories(Saint-Nec-Engine PUBLIC Dependencies/GLAD)
target_link_libraries(Saint-Nec-Engine GLAD-Lib)


# imgui -----------------------------------------------------------------------------------------------
add_subdirectory ("Dependencies/imgui")
target_link_directories(Saint-Nec-Engine PUBLIC Dependencies/imgui)
target_link_libraries(Saint-Nec-Engine imgui)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Saint-Nec-Engine PROPERTY CXX_STANDARD 20)
endif()

