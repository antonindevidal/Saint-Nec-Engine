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
	private:
		Vector3 position;
		Vector3 rotation;
		std::vector<Component*> components;
 		glm::mat4 model;

	public:
		GameObject();
		~GameObject();
		void update();
		void draw() const;

		void addComponent(Component* component);

		const glm::mat4& getModel();
		void setModel(const glm::mat4& newModel);
		void translate(const glm::vec3& translation);
		void rotate(const float angle, const glm::vec3& axis);
	};
}