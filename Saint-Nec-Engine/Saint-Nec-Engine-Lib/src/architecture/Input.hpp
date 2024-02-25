#pragma once 
/**
 * @file Input.hpp
 * @brief Abstract GLFW calls for input.
 * @author Antonin DEVIDAL.
 * @date november 8 2023.
 *
 */
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
		/**
		 * @brief Check if key is currently pressed.
		 * 
		 * @param keycode Keycode to check.
		 * @return true if keycode is currently pressed.
		 */
		static bool isKeyPressed(const unsigned int& keycode);

		/**
		 * @brief Check if key has just been pressed. A key is considered just pressed for one frame.
		 *
		 * @param keycode Keycode to check.
		 * @return true if keycode has just been pressed.
		 */
		static bool isKeyJustPressed(const unsigned int& keycode);

		/**
		 * @brief Bind input callback. Need to be called in order to make the Input system working.
		 */
		static void bindInputCallbacks();

		/**
		 * @brief Bind mouse callback. Need to be called in order to make the Input system working.
		 */
		static void bindMouseCallbacks();

		/**
		 * @brief Reset value for key pressed during the frame. Must be called at the end of each frame.
		 */
		static void endFrame();

		/**
		 * @brief Return X position of the mouse.
		 */
		static const int& getMouseX();

		/**
		 * @brief Return Y position of the mouse.
		 */
		static const int& getMouseY();

	private:
		/**
		 * @brief Map of which key as been pressed this frame.
		 */
		static std::map<int, bool> keyJustPressed;

		/**
		 * @brief X Position of the mouse in the screen.
		 */
		static int mouseX;

		/**
		 * @brief Y Position of the mouse in the screen.
		 */
		static int mouseY;
		
		/**
		 * Callback function for keyboard.
		 */
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/**
		 * Callback function for mous.
		 */
		static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	};
}
