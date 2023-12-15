#include "PhysicManager.hpp"

namespace sne
{

	std::unique_ptr<PhysicManager> PhysicManager::instance = std::make_unique<PhysicManager>();
	void PhysicManager::update()
	{
	}

	void PhysicManager::computeCollision()
	{
	}

	void PhysicManager::addObject(saintNecPhysics::PhysicObject &o)
	{
	}
}