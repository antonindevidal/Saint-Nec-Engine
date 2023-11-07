#pragma once
/**
 * @file Scene.hpp
 * @brief Scene.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 3rd 2023.
 *
 */

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.hpp"

namespace sne
{
	/**
	* @class Scene.
	* @brief Scene containing GameObjects.
	*/
	class Scene
	{
	protected:
		/**
		 * Name of the scene.
		 * Must be unique.
		 */
		std::string name;

		/**
		 * Vector of the GameObjects present in the scene.
		 */
		std::vector<GameObject*> gameObjects;

		/**
		 * View matrix of the scene.
		 * Represent the camera.
		 */
		glm::mat4 view;

		/**
		 * Projection matrix of the scene.
		 */
		glm::mat4 projection;

	public:

		/**
		 * Default constructor of Scene.
		 * (might get removed)
		 */
		Scene();

		/**
		 * Scene constructor.
		 */
		Scene(std::string name);

		/**
		 * Destructor of a scene.
		 */
		~Scene();

		virtual void load();

		virtual void unload();

		/**
		 * Update function.
		 * All the logic happens here.
		 */
		virtual void update();

		/**
		 * Draw function.
		 * No logic should happen there.
		 */
		virtual void draw() const;

		/**
		 * Getter for the scene's name.
		 * 
		 * @return Name of the scene.
		 */
		const std::string& getName()const;

		/**
		 * Getter for View matrix of the scene.
		 * 
		 * @return View matrix.
		 */
		const glm::mat4& getView() const;

		/**
		 * Getter for Projection matrix of the scene.
		 *
		 * @return Projection matrix.
		 */
		const glm::mat4& getProjection() const;

		/**
		* Return the vector of GameObject of the scene.
		*/
		const std::vector<GameObject*> getGameObjects() const;

		/**
		 * Add a GameObject to the scene.
		 * 
		 * @param gameobject Gameobject to add.
		 */
		void addGameObject(GameObject* gameObject);
	};
}
