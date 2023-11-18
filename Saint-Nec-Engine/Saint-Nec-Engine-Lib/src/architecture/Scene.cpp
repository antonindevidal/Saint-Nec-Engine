#include "Scene.hpp"

namespace sne
{

	Scene::Scene() : Scene("test") // TODO: Change this to a unique name
	{

	}
	Scene::Scene(std::string name) : gameObjects(), name(name), projection(glm::mat4(1.0f)), camera()
	{
		projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);// TODO change this to accept different aspect ratio
	}

	Scene::~Scene()
	{
		for (GameObject* o : gameObjects)
		{
			delete o;
		}
	}

	void Scene::load()
	{
	}

	void Scene::unload()
	{
	}

	void Scene::processInput(GLFWwindow* window, int mouseX, int mouseY)
	{
		
		camera.processInput(window, mouseX, mouseY);
	}

	void Scene::update()
	{
		ZoneScopedN("SceneUpdate");
		camera.update();
		for (GameObject *g : gameObjects)
		{
			g->update();
		}
	}
	
	void Scene::draw() const
	{
		for (GameObject* g : gameObjects)
		{
			g->draw();
		}
	}

	const std::string& Scene::getName() const
	{
		return name;
	}

	void Scene::setName(const std::string& newName)
	{
		name = newName;
	}

	const glm::mat4& Scene::getView() const
	{
		return camera.getView();
	}

	const glm::mat4& Scene::getProjection() const
	{
		return projection;
	}

	const Camera& Scene::getCamera() const
	{
		return camera;
	}


	const std::vector<GameObject*>& Scene::getGameObjects() const
	{
		return gameObjects;
	}

	void Scene::addGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
	}
}
