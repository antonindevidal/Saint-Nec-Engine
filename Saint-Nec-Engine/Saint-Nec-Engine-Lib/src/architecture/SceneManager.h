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
		static SceneManager* instance;

	public:
		SceneManager();
		~SceneManager() = default;

		static SceneManager* getInstance();

		void addScene(Scene* scene);
		void changeScene(const std::string& name);

		void update();
		void draw() const;
	};
}