#pragma once
/**
 * @file PhysicManager.hpp
 * @brief Physic Manager.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date december 14th 2023.
 *
 */

#include <string>
#include <memory>
#include <iostream>
#include <set>
#include <algorithm>
#include "../physics/PhysicObject.hpp"
#include "../physics/algorithms.hpp"

namespace sne
{
	/**
	 * @class PhysicManager.
	 * @brief Manage physic object, this class is a Singleton!
	 */

	class ObjectComparator
	{
	public:
		bool operator()(const physics::PhysicObject &o1, const physics::PhysicObject &o2) const
		{
			return o1.getPosition()[0] < o2.getPosition()[0];
		}

		bool operator()(const physics::PhysicObject *o1, const physics::PhysicObject *o2) const
		{
			return o1->getPosition()[0] < o2->getPosition()[0];
		}
	};

	class PhysicManager
	{
	private:
		// std::set<physics::PhysicObject, ObjectComparator> _objects;
		// Why not set instead of sort each time during compute ?
		// Object will move and position will be updated.
		// We will still need to sort at each compute however it's fast with std::sort and vector
		// (sort is for sweep & prune)
		std::vector<physics::PhysicObject *> _objects;

	private:
		/**
		 * @brief sort _objects using above comparator
		 *
		 */
		void sortObject();

	public:
		PhysicManager() = default;
		PhysicManager(PhysicManager &) = delete;
		auto operator=(PhysicManager &) = delete;
		~PhysicManager() = default;

		/**
		 * @brief call the update of each objects
		 *
		 */
		void update();

		/**
		 * @brief compute collision of each object
		 *
		 */
		void computeCollision();

		/**
		 * @brief taking PhysicObject
		 *
		 */
		void addObject(physics::PhysicObject *);

		/**
		 * @brief Get the PhysicObjects* object
		 *
		 * @return const std::vector<physics::PhysicObject*>&
		 */
		const std::vector<physics::PhysicObject *> &getObjects() const;

		/**
		 * @brief clear the instance (test purpose)
		 *
		 */
		void clear();

		physics::PhysicObject *getLast()
		{
			if (_objects.size() == 0)
				return nullptr;

			return _objects[_objects.size() - 1];
		}
	};

}