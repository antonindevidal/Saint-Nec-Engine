#include "Camera.hpp"


namespace sne
{
	Camera::Camera(): view(glm::mat4(1.0f)), cameraPos(0.0f, 0.0f, -3.0f), cameraFront(0.0f, 0.0f, -1.0f), cameraUp(0.0f, 1.0f, 0.0f),
		cameraSpeed(5.0f), lastMouseX(0), lastMouseY(0), yaw(45.0f), pitch(0.0f), firstMouse(false)
	{
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void Camera::processInput(GLFWwindow* window, int mouseX, int mouseY)
	{

		if (firstMouse)
		{
			lastMouseX = mouseX;
			lastMouseY = mouseY;
		}
		float speed = cameraSpeed * Time::getDeltaTime();
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += speed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= speed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraPos.y -= speed;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			cameraPos.y += speed;


		float xoffset = mouseX - lastMouseX;
		float yoffset = lastMouseY - mouseY; // reversed since y-coordinates range from bottom to top
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		lastMouseX = mouseX;
		lastMouseY = mouseY;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);


	}

	void Camera::update()
	{
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	const glm::mat4& Camera::getView() const
	{
		return view;
	}
	const glm::vec3& Camera::getPosition() const
	{
		return cameraPos;
	}
}
