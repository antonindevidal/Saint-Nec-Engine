#pragma once
/**
 * @file Component.hpp
 * @brief Component abstract class.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 3rd 2023.
 *
 */

namespace sne
{
	// Forward declaration of GameObject to reference parent.
	class GameObject;
	
	/**
	* @class Component.
	* @brief Class to add features and behaviour to a GameObject.
	* 
	* To create your own feature for a GameObject (scripting), you must extend the Component class.
	* 
	*/
	class Component
	{
	public:
		/**
		 * Reference to the parent GameObject.
		 * This value might be NULL.
		 */
		GameObject* parent;

	public:
		/**
		 * Default constructor for a Component.
		 */
		Component();

		/**
		 * Destructor for a Component instance.
		 */
		virtual ~Component() = 0;

		/**
		 * Update function of a Component instance.
		 * All the logic happens here.
		 */
		virtual void update() {};

		/**
		 * Draw function of a GameObject instance.
		 * No logic should happen there.
		 */
		virtual void draw() const {};
	};
	
}