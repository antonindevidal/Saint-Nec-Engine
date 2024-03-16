#include "UIBuilder.hpp"

sne::GameObject *createCube(sne::PhysicManager &_physicManager, const glm::vec3 &center, const glm::vec3 &color, bool fix, float size)
{
	auto *cube = new sne::GameObject{};
	cube->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", color, size, size, size));
	cube->translate(center);

	auto *po = new sne::physics::PhysicObject{center, 10};
	po->setCollider(new sne::physics::BoxCollider{center, size, size, size});
	cube->addComponent(po);
	po->setAcceleration({0, 0, 0});
	po->setVelocity({0, 0, 0});
	_physicManager.addObject(po);

	if (fix)
		po->fix();

	return cube;
}

sne::GameObject *createBox(sne::PhysicManager &_physicManager, const glm::vec3 &center, const glm::vec3 &color,
						   float w, float h, float d, bool fix)
{
	auto *box = new sne::GameObject{};
	box->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", color, w, h, d));
	box->translate(center);

	auto *po = new sne::physics::PhysicObject{center, 10};
	po->setCollider(new sne::physics::BoxCollider{center, w, h, d});
	box->addComponent(po);
	po->setAcceleration({0, 0, 0});
	po->setVelocity({0, 0, 0});
	_physicManager.addObject(po);

	if (fix)
		po->fix();

	return box;
}