#include "SceneManager.hpp"

namespace sne
{
	SceneManager* SceneManager::instance = nullptr;

	SceneManager::SceneManager(): scenes(), currentScene(nullptr)
	{

	}

	SceneManager::~SceneManager()
	{
		for (Scene *s : instance->scenes)
		{
			delete s;
		}
		delete instance;
	}

	SceneManager* SceneManager::getInstance()
	{
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}
		return instance;
	}


	void SceneManager::addScene(Scene* scene)
	{
		scenes.push_back(scene);
		if (scenes.size() == 1)
		{
			changeScene(scene->getName());
		}
	}

	void SceneManager::changeScene(const std::string& name)
	{
		for (Scene* s : scenes)
		{
			if (s->getName() == name)
			{
				if (currentScene != nullptr)
				{
					currentScene->unload();
				}
				currentScene = s;
				currentScene->load();

				break;
			}
		}
	}

	void SceneManager::processInput(GLFWwindow* window, int mouseX, int mouseY)
	{
		if (currentScene != nullptr)
		{
			currentScene->processInput(window,mouseX,mouseY);
		}
	}


	void SceneManager::update()
	{
		if (currentScene != nullptr)
		{
			currentScene->update();
		}
	}

	void SceneManager::draw() const
	{
		if (currentScene != nullptr)
		{
			currentScene->draw();
		}
	}

	const Scene* SceneManager::getCurrentScene() const
	{
		return currentScene;
	}


}
