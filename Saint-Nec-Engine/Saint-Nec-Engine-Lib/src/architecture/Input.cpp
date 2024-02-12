#include "Input.hpp"

namespace sne
{
	std::map<int, bool> Input::keyJustPressed{};

	int Input::mouseX = 0;
	int Input::mouseY = 0;

	bool Input::isKeyPressed(const unsigned int& keycode)
	{
		auto state = glfwGetKey(Window::getWindow(), keycode);
		return state == GLFW_REPEAT || state == GLFW_PRESS;
	}

	bool Input::isKeyJustPressed(const unsigned int& keycode)
	{
		return keyJustPressed[keycode];
	}

	void Input::bindInputCallbacks()
	{
		glfwSetKeyCallback(Window::getWindow(), keyCallback);
	}

	void Input::bindMouseCallbacks()
	{
		glfwSetCursorPosCallback(Window::getWindow(), mouseCallback);
	}

	void Input::endFrame()
	{
		for (auto & [key, val] : keyJustPressed)
		{
			val = false;
		}
	}

	const int& Input::getMouseX()
	{
		return mouseX;
	}

	const int& Input::getMouseY()
	{
		return mouseY;
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyJustPressed[key] = keyJustPressed[key] == false && action == GLFW_PRESS;
	}

	void Input::mouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseX = static_cast<int>(xpos);
		mouseY = static_cast<int>(ypos);
	}
}
