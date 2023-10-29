#include "SceneManager.h"

namespace sne
{
	SceneManager::SceneManager(): scenes(), currentScene(nullptr)
	{

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

}
