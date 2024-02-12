#include <architecture/SceneManager.hpp>
#include <architecture/GameObject.hpp>
#include <graphics/Cube.hpp>
#include "scenes/WaterGenerationScene.hpp"


class Game
{
public:

	Game();
	~Game();

	void update();
	void draw() const;

private:
	sne::SceneManager* sceneManager;

};