#include "Camera.hpp"
#include "Time.hpp"

namespace sne
{
	Camera::Camera(): view(glm::mat4(1.0f)), cameraPos(0.0f, 5.0f, -3.0f), cameraFront(0.0f, 0.0f, -1.0f), cameraUp(0.0f, 1.0f, 0.0f),
		cameraSpeed(5.0f), lastMouseX(0), lastMouseY(0), yaw(45.0f), pitch(0.0f), firstMouse(false)
	{
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void Camera::update()
	{
		if (firstMouse)
		{
			lastMouseX = Input::getMouseX();
			lastMouseY = Input::getMouseY();
		}
		float speed = cameraSpeed * Time::getDeltaTime();
		if (Input::isKeyPressed(GLFW_KEY_W))
			cameraPos += speed * cameraFront;
		if (Input::isKeyPressed(GLFW_KEY_S))
			cameraPos -= speed * cameraFront;
		if (Input::isKeyPressed(GLFW_KEY_A))
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		if (Input::isKeyPressed(GLFW_KEY_D))
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
		if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
			cameraPos.y -= speed;
		if (Input::isKeyPressed(GLFW_KEY_SPACE))
			cameraPos.y += speed;


		float xoffset = Input::getMouseX() - lastMouseX;
		float yoffset = lastMouseY - Input::getMouseY(); // reversed since y-coordinates range from bottom to top
		lastMouseX = Input::getMouseX();
		lastMouseY = Input::getMouseY();

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);

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

	const glm::vec3& Camera::getFront() const
	{
		return cameraFront;
	}
}
