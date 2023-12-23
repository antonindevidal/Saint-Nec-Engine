include(FetchContent)

find_package( OpenGL REQUIRED )


FetchContent_Declare(glfw SYSTEM
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 7482de6 # last commit 3.3.8

)
set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

FetchContent_MakeAvailable(
	glfw
)

FetchContent_Declare(glm SYSTEM
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e # last commit for 0.9.9.8

)

FetchContent_MakeAvailable(
	glm
)


add_library (imgui
				"imgui/imconfig.h"
				"imgui/imgui.cpp"
				"imgui/imgui.h"
				"imgui/imgui_demo.cpp"
				"imgui/imgui_draw.cpp"
				"imgui/imgui_impl_glfw.cpp"
				"imgui/imgui_impl_glfw.h"
				"imgui/imgui_impl_opengl3.cpp"
				"imgui/imgui_impl_opengl3.h"
				"imgui/imgui_impl_opengl3_loader.h"
				"imgui/imgui_internal.h"
				"imgui/imgui_tables.cpp"
				"imgui/imgui_widgets.cpp"
				"imgui/imstb_rectpack.h"
				"imgui/imstb_textedit.h"
				"imgui/imstb_truetype.h"
				 "stb_image/stb_image.h" "stb_image/stb_image.cpp")
target_include_directories(imgui INTERFACE imgui)
target_link_libraries( imgui glfw )

add_library(stb_image
				"stb_image/stb_image.h"
				"stb_image/stb_image.cpp"
)
target_include_directories(stb_image INTERFACE stb_image)


FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=" CACHE STRING "API type/version pairs, like \"gl=3.3,gles=\", no version means latest")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")


FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
endif()


FetchContent_MakeAvailable(
	glad
)


FetchContent_Declare (
	tracy
	GIT_REPOSITORY https://github.com/wolfpld/tracy.git
	GIT_TAG 37aff70dfa50cf6307b3fee6074d627dc2929143
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable (tracy)

