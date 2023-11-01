#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"
#include "Vector3.hpp"

namespace sne
{

	class GameObject
	{
		Vector3 position;
		Vector3 rotation;
		std::vector<Component*> components;
		//graphics::Shader* shader;
		glm::mat4 model;

	public:
		GameObject();
		~GameObject();
		void update();
		void draw() const;

		void addComponent(Component* component);
		//void addComponent(graphics::Shader* shader);

	};
}