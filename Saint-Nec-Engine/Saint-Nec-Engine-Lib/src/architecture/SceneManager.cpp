#include "SceneManager.h"

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
	}

	void SceneManager::changeScene(const std::string& name)
	{
		for (Scene* s : scenes)
		{
			if (s->getName() == name)
			{
				currentScene = s;
				break;
			}
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
	const Scene& SceneManager::getCurrentScene() const
	{
		return *currentScene;
	}


}
