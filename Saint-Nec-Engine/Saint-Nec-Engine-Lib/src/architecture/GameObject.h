#pragma once
#include <vector>
#include "Component.h"
#include "Vector3.hpp"

namespace sne
{

	class GameObject
	{
		Vector3 position;
		Vector3 rotation;
		std::vector<Component*> components;

	public:
		GameObject();
		~GameObject() = default;
		void update();
		void draw() const;

		void addComponent(Component* component);

	};
}