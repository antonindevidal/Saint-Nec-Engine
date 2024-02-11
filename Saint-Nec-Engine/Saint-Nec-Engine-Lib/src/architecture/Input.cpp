#include "Input.hpp"

namespace sne
{
	std::map<int, bool> Input::keyJustPressed{};

	bool Input::isKeyPressed(const unsigned int& keycode)
	{
		auto state = glfwGetKey(Window::getWindow(), keycode);
		return state == GLFW_REPEAT || state == GLFW_PRESS;
	}

	bool Input::isKeyJustPressed(const unsigned int& keycode)
	{
		std::cout << "justPressed " << keyJustPressed[keycode] << std::endl;
		bool res = keyJustPressed[keycode];
		
		return res;
	}

	void Input::bindInputCallbacks()
	{
		glfwSetKeyCallback(Window::getWindow(), keyCallback);
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		std::cout << "callback " << (key == GLFW_KEY_F1) << std::endl;
		keyJustPressed[key] = keyJustPressed[key] == false && action == GLFW_PRESS;
	}
}
