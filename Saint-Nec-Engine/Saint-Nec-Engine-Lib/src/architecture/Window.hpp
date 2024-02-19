#pragma once 

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace sne
{
	class Window
	{
	public:

		/**
		 * @brief Create a GLFW window.
		 * 
		 * @param name Name of the window.
		 * @param width Width in pixel of the window.
		 * @param height Height in pixel of the window.
		 */
		static int createWindow(const std::string& name, const int& width, const int& height);

		/**
		 * @brief Getter for the window.
		 * 
		 * @return window	
		 */
		static GLFWwindow* getWindow();

		/**
		 * @brief Bind buffer callback.
		 */
		static void setBufferCallBack(GLFWframebuffersizefun fun);

		/**
		 * @brief How many frames to wait until swapping the buffers.
		 * 
		 * @param value 0 to not set fps restriction, 1 to VSync
		 */
		static void swapIntervals(const int& value);

		/**
		 * @brief Destroy window and cursor.
		 */
		static void terminate()
		{
			glfwTerminate();
		}

		/**
		 * @brief Should the current window be closed.
		 * 
		 * @return true if the window should close
		 */
		static bool windowShouldClose()
		{
			return glfwWindowShouldClose(getWindow());
		}

		/**
		 * @brief Swaps the front and back buffers.
		 */
		static void swapBuffers()
		{
			glfwSwapBuffers(getWindow());
		}

		/**
		 * Processes events.
		 */
		static void pollEvents()
		{
			glfwPollEvents();
		}

		/**
		 * @brief Get GLSL version.
		 * 
		 * @return GLSL version.
		 */
		static const std::string& getGLSLVersion()
		{
			return glslVersion;
		}

		/**
		 * Get major version of OpenGL.
		 * 
		 * @return Major version
		 */
		static const int& getMajorVersion()
		{
			return glfwMajorVersion;
		}

		/**
		 * Get minor version of OpenGL.
		 *
		 * @return Minor version
		 */
		static const int& getMinorVersion()
		{
			return glfwMinorVersion;
		}

	private:
		/**
		 * @brief Window of the application (only one window per app).
		 */
		static GLFWwindow* window;

		/**
		 * @brief GLSL version.
		 */
		static const std::string glslVersion;

		/**
		 * @brief GLFW Major version.
		 */
		static const int glfwMajorVersion;
		
		/**
		 * @brief GLFW Minor version.
		 */
		static const int glfwMinorVersion;

	};
}
