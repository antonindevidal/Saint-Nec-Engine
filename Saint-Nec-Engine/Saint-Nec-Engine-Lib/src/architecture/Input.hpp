#pragma once 

#include <GLFW/glfw3.h>
#include <map>
#include <algorithm>
#include <ranges>
#include "Window.hpp"

namespace sne
{

	class Input
	{
	public:
		static bool isKeyPressed(const unsigned int& keycode);

		static bool isKeyJustPressed(const unsigned int& keycode);

		static void bindInputCallbacks();

		static void bindMouseCallbacks();

		static void endFrame();

		static const int& getMouseX();

		static const int& getMouseY();

	private:
		static std::map<int, bool> keyJustPressed;

		static int mouseX;
		static int mouseY;
		
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	};
}
