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
#include "Time.hpp"
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
		bool operator()(const saintNecPhysics::PhysicObject &o1, const saintNecPhysics::PhysicObject &o2) const
		{
			return o1.getPosition()[0] < o2.getPosition()[0];
		}

		bool operator()(const saintNecPhysics::PhysicObject *o1, const saintNecPhysics::PhysicObject *o2) const
		{
			return o1->getPosition()[0] < o2->getPosition()[0];
		}
	};

	class PhysicManager
	{
	private:
		static std::unique_ptr<PhysicManager> _instance;
		// std::set<saintNecPhysics::PhysicObject, ObjectComparator> _objects; 
		// Why not set instead of sort each time during compute ? 
		// Object will move and position will be updated.
		// We will still need to sort at each compute however it's fast with std::sort and vector
		// (sort is for sweep & prune)
		std::vector<saintNecPhysics::PhysicObject*> _objects;
		Time* time = Time::getInstance();


	private:
		PhysicManager() {}
		PhysicManager(PhysicManager &) = delete;
		auto operator=(PhysicManager &) = delete;

		/**
		 * @brief sort _objects using above comparator
		 * 
		 */
		void sortObject();

	private:
		friend std::unique_ptr<PhysicManager> std::make_unique<PhysicManager>();

	public:
		~PhysicManager() = default;

		/**
		 * @brief Get the singleton object
		 * 
		 * @return std::unique_ptr<PhysicManager>& 
		 */
		static std::unique_ptr<PhysicManager> &getInstance()
		{
			return _instance;
		}

		/**
		 * @brief makes calcul and update considering the passed time
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
		void addObject(saintNecPhysics::PhysicObject *);

		const std::vector<saintNecPhysics::PhysicObject*>& getObjects() const;
	};

}