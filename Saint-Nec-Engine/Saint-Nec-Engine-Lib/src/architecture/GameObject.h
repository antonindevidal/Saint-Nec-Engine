#pragma once
#include <vector>
#include "Component.h"

namespace saintNecEngine
{

	class GameObject
	{
		float position[3];
		float rotation[3];
		std::vector<Component*> components;

	public:
		GameObject() = default;
		~GameObject() = default;
		void update();
		void draw() const;
	};
}