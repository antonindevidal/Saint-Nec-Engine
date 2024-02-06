#include "UIBuilder.hpp"


sne::GameObject* createCube(sne::PhysicManager &_physicManager, const glm::vec3 &center, const glm::vec3 &color, bool fix)
{
    auto *cube = new sne::GameObject{};
	cube->addComponent(new sne::graphics::Cube("resources/shaders/color.vert", "resources/shaders/color.frag", color));
	cube->translate(center);

	auto *po = new sne::physics::PhysicObject{center, 10};
	po->setCollider(new sne::physics::BoxCollider{center, 1, 1, 1});
	cube->addComponent(po);
	po->setAcceleration({0,0,0});
	po->setVelocity({0,0,0});
	_physicManager.addObject(po);

	if(fix)
		po->fix();

    return cube;
}