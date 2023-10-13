#pragma once
#include <vector>
#include "Component.h"

namespace saintNecEngine
{

	class GameObject
	{
		std::vector<int> position;
		std::vector<int> rotation;
		std::vector<Component*> components;

	public:
		GameObject() = default;
		~GameObject() = default;
		void update();
		void draw() const;
	};
}