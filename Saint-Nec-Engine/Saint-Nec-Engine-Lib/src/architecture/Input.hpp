#pragma once 

#include <GLFW/glfw3.h>
#include <map>
#include "Window.hpp"

namespace sne
{

	class Input
	{
	public:
		static bool isKeyPressed(const unsigned int& keycode);

		static bool isKeyJustPressed(const unsigned int& keycode);

		static void bindInputCallbacks();

	private:
		static std::map<int, bool> keyJustPressed;
		
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
