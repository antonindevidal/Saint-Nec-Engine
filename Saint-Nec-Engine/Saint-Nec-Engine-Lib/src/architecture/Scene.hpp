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
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

#include "Time.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

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
		 * Projection matrix of the scene.
		 */
		glm::mat4 projection;

		/**
		 * Result of projection * view matrices.
		 * Recalculated every update.
		 */
		glm::mat4 viewProjection;

		/**
		 * Camera object for the scene.
		 */
		Camera camera;

		glm::vec3 directionnalLight;

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

		/**
		 * Load the scene.
		 */
		virtual void load();

		/**
		 * Unload the scene.
		 */
		virtual void unload();

		/**
		 * Process GLFW inputs here.
		 *
		 * @param window GLFW window.
		 * @param mouseX Position of the mouse on horizontal axis.
		 * @param mouseY Position of the mouse on vertical axis.
		 */
		void processInput(GLFWwindow* window, int mouseX, int mouseY);

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
		 * Setter for the scene's name.
		 *
		 * @param newName Name for the scene.
		 */
		void setName(const std::string& newName);

		/**
		 * Getter for View matrix of the scene (from the camera).
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
		 * Getter for Camera of the scene.
		 *
		 * @return camera.
		 */
		const Camera& getCamera() const;

		const glm::vec3& getDirectionnalLight() const;

		/**
		* Return the vector of GameObject of the scene.
		*/
		const std::vector<GameObject*>& getGameObjects() const;

		/**
		 * Add a GameObject to the scene.
		 *
		 * @param gameobject Gameobject to add.
		 */
		void addGameObject(GameObject* gameObject);

		/**
		 * Calculate if a point is inside the camera view frustum.
		 *
		 * @param point Point to check.
		 */
		bool isPointInsideViewFrustum(const glm::vec4& point) const;

	private:

		/**
		 * Structure having all 6 view frustum planes.
		 */
		struct frustumClipPlanes
		{
			glm::vec4 leftClipPlane = {};
			glm::vec4 rightClipPlane = {};
			glm::vec4 topClipPlane = {};
			glm::vec4 bottomClipPlane = {};
			glm::vec4 nearClipPlane = {};
			glm::vec4 farClipPlane = {};
		};

		/**
		 * Camera frustum.
		 * recalculated every frame.
		 */
		frustumClipPlanes frustum;

		/**
		 * Updates the frustum values.
		 */
		void updateFrustumClipPlanes();


	};
}
