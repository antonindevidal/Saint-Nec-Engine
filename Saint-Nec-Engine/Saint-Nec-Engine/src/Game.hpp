#include <architecture/SceneManager.hpp>
#include <architecture/GameObject.hpp>
#include <graphics/Cube.hpp>


class Game
{
public:

	Game();
	~Game();

	void processInput(GLFWwindow* window, int mouseX, int mouseY);
	void update();
	void draw() const;

private:
	sne::SceneManager* sceneManager;

};