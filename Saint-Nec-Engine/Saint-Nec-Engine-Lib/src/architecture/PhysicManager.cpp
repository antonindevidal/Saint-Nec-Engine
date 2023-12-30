#include "PhysicManager.hpp"

namespace sne
{

	std::unique_ptr<PhysicManager> PhysicManager::_instance = std::make_unique<PhysicManager>();

	void PhysicManager::update()
	{
		computeCollision();
		for (auto &elt : _objects)
			elt->compute(time->getDeltaTime());
	}

	void PhysicManager::computeCollision()
	{
		// If effect makes others collision we take
		// for (int i = 0; i < _objects.size(); i++)
		// {
		// 	for (int j = i + 1; j < _objects.size(); j++)
		// 	{
		// 		_objects[i]->computeCollide(*_objects[j]);
		// 	}
		// }

		// With sweep and prune
		auto pairs = sweepAndPrune(_objects);
		for(auto &elt : pairs)
		{
			elt.first->computeCollide(*(elt.second));
		}
	}

	void PhysicManager::addObject(saintNecPhysics::PhysicObject *o)
	{
		_objects.push_back(o);
	}

	void PhysicManager::sortObject()
	{
		std::sort(_objects.begin(), _objects.end(), ObjectComparator());
	}

	const std::vector<saintNecPhysics::PhysicObject*> &PhysicManager::getObjects() const
	{
		return _objects;
	}

	void PhysicManager::clear()
	{
		for(saintNecPhysics::PhysicObject* elt: _objects)
		{
			if(elt->getCollider() == nullptr)
				std::cout << "destruction de null\n";
			delete elt;
		}
		_objects.clear();
	}
}