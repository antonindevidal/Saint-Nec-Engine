#pragma once
#include "Scene.h"
#include <string>

class SceneManager
{
	std::vector<Scene*> scenes;
public:
	SceneManager() = default;
	~SceneManager() = default;
	void addScene(Scene& scene);
	void changeScene(std::string &name);
	void update();
	void draw() const;
};

