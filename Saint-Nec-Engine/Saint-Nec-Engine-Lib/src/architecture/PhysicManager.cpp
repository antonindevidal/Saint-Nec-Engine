#include "PhysicManager.hpp"

namespace sne
{
	void PhysicManager::update()
	{
		computeCollision();
		for (auto &elt : _objects)
			elt->update();
	}

	void PhysicManager::computeCollision()
	{
		// sortObject(); TO USE LATER (sweep & prune)

		// // If effect makes others collision we take
		 /*for (int i = 0; i < _objects.size(); i++)
		 {
			for (int j = i + 1; j < _objects.size(); j++)
		 	{
		 		_objects[i]->computeCollide(*_objects[j]);
			}
		 }*/

		// With sweep and prune
		auto pairs = sweepAndPrune(_objects);
		for(auto &elt : pairs)
		{
			elt.first->computeCollide(*(elt.second));
		}
	}

	void PhysicManager::addObject(physics::PhysicObject *o)
	{
		_objects.push_back(o);
	}

	void PhysicManager::sortObject()
	{
		std::sort(_objects.begin(), _objects.end(), ObjectComparator());
	}

	const std::vector<physics::PhysicObject*> &PhysicManager::getObjects() const
	{
		return _objects;
	}

	void PhysicManager::clear()
	{
		for(physics::PhysicObject* elt: _objects)
		{
			if(elt->getCollider() == nullptr)
				std::cout << "destruction de null\n";
			delete elt;
		}
		_objects.clear();
	}
}