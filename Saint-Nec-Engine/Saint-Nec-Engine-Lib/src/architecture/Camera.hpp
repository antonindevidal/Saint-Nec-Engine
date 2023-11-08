#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Time.hpp"
namespace sne
{
	class Camera
	{
		/**
		 * View matrix of the scene.
		 * Represent the camera.
		 */
		glm::mat4 view;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		float cameraSpeed;
		int lastMouseX;
		int lastMouseY;
		float yaw;
		float pitch;
		bool firstMouse;

	public:
		Camera();


		void processInput(GLFWwindow* window, int mouseX, int mouseY);

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
	};
}
