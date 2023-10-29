#pragma once
#include <string>
#include "Scene.h"


namespace sne
{
	class SceneManager
	{
	private:
		std::vector<Scene*> scenes;
		Scene *currentScene;

	public:
		SceneManager();
		~SceneManager() = default;
		void addScene(Scene* scene);
		void changeScene(const std::string& name);

		void update();
		void draw() const;
	};
}