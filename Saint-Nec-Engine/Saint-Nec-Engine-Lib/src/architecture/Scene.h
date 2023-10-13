#pragma once

#include <vector>
#include "GameObject.h"

namespace saintNecEngine
{
	class Scene
	{
	private:
		std::vector<GameObject*> gameObjects;

	public:
		Scene() = default;
		~Scene() = default;
		void update();
		void draw() const;
	};
}
