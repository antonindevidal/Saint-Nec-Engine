#include "Scene.hpp"

namespace sne
{

	Scene::Scene() : Scene("test") // TODO: Change this to a unique name
	{

	}
	Scene::Scene(std::string name) : gameObjects(), name(name), projection(glm::mat4(1.0f)), camera(), viewProjection(), frustum()
	{
		projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);// TODO change this to accept different aspect ratio
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
		camera.update();
		viewProjection = projection * camera.getView();
		updateFrustumClipPlanes();
		for (GameObject* g : gameObjects)
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

	void Scene::updateFrustumClipPlanes()
	{
		//Planes are calculated using Gribb/Hartmann method
		glm::vec4 row1 = glm::row(viewProjection, 0);
		glm::vec4 row2 = glm::row(viewProjection, 1);
		glm::vec4 row3 = glm::row(viewProjection, 2);
		glm::vec4 row4 = glm::row(viewProjection, 3);

		frustum.leftClipPlane = row1 + row4;
		frustum.rightClipPlane = row1 - row4;
		frustum.bottomClipPlane = row2 + row4;
		frustum.topClipPlane = row2 - row4;
		frustum.nearClipPlane = row3 + row4;
		frustum.farClipPlane = row3 - row4;
	}

	bool Scene::isPointInsideViewFrustum(const glm::vec4& point) const
	{
		//World space culling
		return (glm::dot(frustum.leftClipPlane, point) >= 0 &&
			glm::dot(frustum.rightClipPlane, point) <= 0 &&
			glm::dot(frustum.bottomClipPlane, point) >= 0 &&
			glm::dot(frustum.topClipPlane, point) <= 0 &&
			glm::dot(frustum.farClipPlane, point) <= 0 &&
			glm::dot(frustum.nearClipPlane, point) >= 0);

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

	const glm::vec3& Scene::getDirectionnalLight() const
	{
		return directionnalLight;
	}

	void Scene::addGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
	}
}
