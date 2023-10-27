
add_library (Saint-Nec-Engine-Lib)

set(_SAINT_NEC_ENGINE_LIB_SRC 
	"architecture/Vector3.cpp"
	"architecture/Component.cpp"
	"architecture/Scene.cpp" 
	"architecture/GameObject.cpp"
	"architecture/SceneManager.cpp"
	"physics/BoxCollider.cpp"
	"physics/SphereCollider.cpp"
)

set(_SAINT_NEC_ENGINE_LIB_HDR
	"architecture/Vector3.hpp"
	"architecture/Component.hpp"
	"architecture/Scene.hpp" 
	"architecture/GameObject.hpp"
	"architecture/SceneManager.hpp"
	"physics/BoxCollider.hpp"
	"physics/SphereCollider.hpp"
	"physics/SAT.hpp"
)
target_sources(Saint-Nec-Engine-Lib PRIVATE ${_SAINT_NEC_ENGINE_LIB_SRC})
target_sources(Saint-Nec-Engine-Lib PUBLIC ${_SAINT_NEC_ENGINE_LIB_HDR})


target_include_directories(Saint-Nec-Engine-Lib  PUBLIC .)

