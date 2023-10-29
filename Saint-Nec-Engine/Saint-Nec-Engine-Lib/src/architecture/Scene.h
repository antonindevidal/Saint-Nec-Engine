#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"

namespace sne
{
	class Scene
	{
	private:
		std::string name;
		std::vector<GameObject*> gameObjects;
		glm::mat4 view;
		glm::mat4 projection;

	public:
		Scene::Scene();
		Scene(std::string name);
		~Scene() = default;
		void update();
		void draw() const;

		const std::string& getName()const;
		const glm::mat4& getView() const;
		const glm::mat4& getProjection() const;
		void addGameObject(GameObject* gameObject);
	};
}
