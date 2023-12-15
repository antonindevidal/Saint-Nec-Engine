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
// #include <physics/PhysicObject.hpp>
#include "../physics/PhysicObject.hpp"

namespace sne
{
	/**
	 * @class PhysicManager.
	 * @brief Manage physic object, this class is a Singleton!
	 */
	class PhysicManager
	{
	private:
		static std::unique_ptr<PhysicManager> _instance;
		PhysicManager() {}
		PhysicManager(PhysicManager &) = delete;
		auto operator=(PhysicManager &) = delete;

	private:
		friend std::unique_ptr<PhysicManager> std::make_unique<PhysicManager>();

	public:
		~PhysicManager() = default;
		static std::unique_ptr<PhysicManager>& getInstance()
		{
			return _instance;
		}

		void update();

		void computeCollision();

		void addObject(saintNecPhysics::PhysicObject &);
	};

}