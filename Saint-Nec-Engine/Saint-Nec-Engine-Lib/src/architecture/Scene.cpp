#include "Scene.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>

namespace sne
{

	Scene::Scene() : Scene("test") // TODO: Change this to a unique name
	{

	}
	Scene::Scene(std::string name) : name(name), view(1.0f), projection(1.0f) 
	{
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);// TODO change this to accept different aspect ratio

	}

	void Scene::update()
	{
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

	const glm::mat4& Scene::getView() const
	{
		return view;
	}

	const glm::mat4& Scene::getProjection() const
	{
		return projection;
	}

	void Scene::addGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
	}
}