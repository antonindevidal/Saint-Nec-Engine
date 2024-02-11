#pragma once 

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

namespace sne
{
	class Window
	{
	public:

		static int createWindow(const std::string& name, const int& width, const int& height);

		static GLFWwindow* getWindow();


		static void setBufferCallBack(GLFWframebuffersizefun fun);

		static void swapIntervals(const int& value);

		static void terminate()
		{
			glfwTerminate();
		}

		static bool windowShouldClose()
		{
			return glfwWindowShouldClose(getWindow());
		}

		static void swapBuffers()
		{
			glfwSwapBuffers(getWindow());
		}

		static void pollEvents()
		{
			glfwPollEvents();
		}

		static const std::string& getGLSLVersion()
		{
			return glslVersion;
		}

		static const int& getMajorVersion()
		{
			return glfwMajorVersion;
		}

		static const int& getMinorVersion()
		{
			return glfwMinorVersion;
		}

	private:
		static GLFWwindow* window;
		static const std::string glslVersion;
		static const int glfwMajorVersion;
		static const int glfwMinorVersion;

	};
}
