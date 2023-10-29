
#include <architecture/SceneManager.h>
#include <architecture/Scene.h>
#include <architecture/GameObject.h>
#include <graphics/Cube.hpp>

class Game
{
public:

	Game();
	~Game();

	void update();
	void draw() const;

private:
	sne::SceneManager sceneManager;

};