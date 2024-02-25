
add_library (Saint-Nec-Engine-Lib)

set(_SAINT_NEC_ENGINE_LIB_SRC
	"architecture/Component.cpp"
	"architecture/Scene.cpp" 
	"architecture/GameObject.cpp"
	"architecture/SceneManager.cpp"
	"architecture/util.cpp"
	"architecture/Window.cpp"
	"architecture/Input.cpp"
	"physics/BoxCollider.cpp"
	"physics/SphereCollider.cpp"
	"physics/SAT.cpp"
	"graphics/Cube.cpp"
	"graphics/GraphicComponent.cpp"
	"graphics/Plane.cpp"
	"graphics/Shader.cpp"
	"architecture/Time.cpp"
	"architecture/Camera.cpp"
	"physics/PhysicObject.cpp"
	"physics/util.cpp"
	"graphics/TessellatedPlane.cpp"
	"architecture/PhysicManager.cpp"
	"physics/algorithms.cpp"
	"graphics/Skybox.cpp"
)

set(_SAINT_NEC_ENGINE_LIB_HDR
	"architecture/Component.hpp"
	"architecture/Scene.hpp" 
	"architecture/GameObject.hpp"
	"architecture/SceneManager.hpp"
	"architecture/util.hpp"
	"architecture/Window.hpp"
	"architecture/Input.hpp"
	"physics/BoxCollider.hpp"
	"physics/SphereCollider.hpp"
	"physics/SAT.hpp"
	"graphics/Cube.hpp"
	"graphics/GraphicComponent.hpp"
	"graphics/Plane.hpp"
	"graphics/Shader.hpp"
	"architecture/Time.hpp"
	"architecture/Camera.hpp"
	"physics/PhysicObject.hpp"
	"physics/util.hpp"
	"physics/Collider.hpp"
	"graphics/TessellatedPlane.hpp"
	"architecture/PhysicManager.hpp"
	"physics/algorithms.hpp"
	"graphics/Skybox.hpp"
)
target_sources(Saint-Nec-Engine-Lib INTERFACE ${_SAINT_NEC_ENGINE_LIB_HDR})
target_sources(Saint-Nec-Engine-Lib PRIVATE ${_SAINT_NEC_ENGINE_LIB_SRC})


target_include_directories(Saint-Nec-Engine-Lib  PUBLIC .)

target_link_libraries(Saint-Nec-Engine-Lib glfw glad glm stb_image TracyClient)
