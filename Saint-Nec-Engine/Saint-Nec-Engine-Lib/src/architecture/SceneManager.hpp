#pragma once
/**
 * @file SceneManager.hpp
 * @brief Scene Manager.
 * @author Abdeljalil ZOGHLAMI, Antonin DEVIDAL.
 * @date november 3rd 2023.
 *
 */

#include <string>
#include "Scene.hpp"


namespace sne
{
	/**
	* @class SceneManager.
	* @brief Manage scenes, this class is a Singleton!
	*/
	class SceneManager
	{
	private:
		/**
		 * Vector of all the scenes of the game.
		 */
		std::vector<Scene*> scenes;

		/**
		 * Current scene to update and draw.
		 */
		Scene *currentScene;

		/**
		 * Instance of the SceneManager.
		 */
		static SceneManager* instance;

	public:

		/**
		 * Default constructor for a SceneManager.
		 */
		SceneManager();

		/**
		 * Destructor for the SceneManager instance.
		 */
		~SceneManager();

		/**
		 * Getter for the instance of the SceneManager.
		 * 
		 * @return Instance of the SceneManager.
		 */
		static SceneManager* getInstance();

		/**
		 * Add a scene to the scenes.
		 * 
		 * @param scene Scene to add.
		 */
		void addScene(Scene* scene);

		/**
		 * Change current scene to update and draw.
		 * 
		 * @param name Name of the scene to use.
		 */
		void changeScene(const std::string& name);

		/**
		 * Process GLFW inputs here.
		 *
		 * @param window GLFW window.
		 * @param mouseX Position of the mouse on horizontal axis.
		 * @param mouseY Position of the mouse on vertical axis.
		 */
		void SceneManager::processInput(GLFWwindow* window, int mouseX, int mouseY);

		/**
		 * Update function for the current scene.
		 * All the logic happens here.
		 */
		void update();

		/**
		 * Draw function for the current scene instance.
		 * No logic should happen there.
		 */
		void draw() const;

		/**
		 * Getter for the current Scene.
		 * 
		 * @param Current scene
		 */
		const Scene& getCurrentScene() const;
	};
}