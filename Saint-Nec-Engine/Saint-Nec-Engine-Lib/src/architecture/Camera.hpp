#pragma once
/**
 * @file Camera.hpp
 * @brief Camera class definition.
 * @author Antonin DEVIDAL.
 * @date november 8 2023.
 *
 */
#include <glad/glad.h>
#include <architecture/Input.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace sne
{
	/**
	 * @class Camera
	 * @brief Camera object with keyboard input movement.
	 */
	class Camera
	{
		/**
		 * View matrix of the scene.
		 * Represent the camera.
		 */
		glm::mat4 view;

		/*
		* Position of the camera
		*/
		glm::vec3 cameraPos;

		/**
		 * Defines the direction where the camera is looking at.
		 */
		glm::vec3 cameraFront;

		/**
		 * Defines the upward vector for the camera.
		 */
		glm::vec3 cameraUp;

		/**
		 * Speed movement.
		 */
		float cameraSpeed;

		/**
		 * Last position of the mouse in the screen.
		 */
		int lastMouseX;

		/**
		 * Last position of the mouse in the screen.
		 */
		int lastMouseY;

		/**
		 * Yaw angle of the camera.
		 */
		float yaw;

		/**
		 * Pitch angle of the camera.
		 */
		float pitch;

		/**
		 * Is it the first time we record mouse pos.
		 * This avoid big camera rotations on the first frame.
		 */
		bool firstMouse;

	public:
		Camera();

		/**
		 * Update function.
		 * All the logic happens here.
		 */
		virtual void update();

		/**
		 * Getter for View matrix of the scene.
		 *
		 * @return View matrix.
		 */
		const glm::mat4& getView() const;

		/**
		 * Getter for the position of the camera.
		 */
		const glm::vec3& getPosition() const;

		/**
		 * .Getter for front vector of the camera.
		 */
		const glm::vec3& getFront() const;
	};
}
