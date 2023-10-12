#pragma once
#include <vector>
#include "GameObject.h"
class Scene
{
	std::vector<GameObject*> gameObjects;
public:
	Scene() = default;
	~Scene() = default;
	void update();
	void draw() const;
};

