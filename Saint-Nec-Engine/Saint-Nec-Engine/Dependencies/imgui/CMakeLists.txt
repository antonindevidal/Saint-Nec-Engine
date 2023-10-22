# CMakeList.txt : projet CMake pour Saint-Nec-Engine, incluez la source et définissez
# la logique spécifique au projet ici.
#

add_library (imgui
				"imconfig.h"
				"imgui.cpp"
				"imgui.h"
				"imgui_demo.cpp"
				"imgui_draw.cpp"
				"imgui_impl_glfw.cpp"
				"imgui_impl_glfw.h"
				"imgui_impl_opengl3.cpp"
				"imgui_impl_opengl3.h"
				"imgui_impl_opengl3_loader.h"
				"imgui_internal.h"
				"imgui_tables.cpp"
				"imgui_widgets.cpp"
				"imstb_rectpack.h"
				"imstb_textedit.h"
				"imstb_truetype.h"
				)

#GLFW ------------------------------------------------------------------------------------------------
find_package( OpenGL REQUIRED )
target_link_libraries( imgui glfw )




target_include_directories(imgui PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
  ... other required includes
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Saint-Nec-Engine PROPERTY CXX_STANDARD 20)
endif()

