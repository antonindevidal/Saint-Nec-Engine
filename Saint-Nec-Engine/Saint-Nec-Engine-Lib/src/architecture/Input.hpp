#pragma once 

#include <GLFW/glfw3.h>
#include <map>
#include "Window.hpp"
namespace sne
{
	class Input
	{
	public:
		static bool isKeyPressed(const unsigned int& keycode)
		{
			auto state = glfwGetKey(Window::getWindow(), keycode);
			return state == GLFW_REPEAT || state == GLFW_PRESS;
		}

		static bool isKeyJustPressed(const unsigned int& keycode)
		{
			auto state = glfwGetKey(Window::getWindow(), keycode);
			return (state == GLFW_PRESS || state == GLFW_REPEAT) && keyStates[keycode] == GLFW_RELEASE;
		}

	private:
		std::map<int, int> keyStates;
		

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			keyStates[key] = action;
		}

		friend class Window;
	};
}
