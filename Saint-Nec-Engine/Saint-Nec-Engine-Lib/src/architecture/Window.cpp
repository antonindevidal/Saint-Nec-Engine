#include "Window.hpp"


namespace sne
{
	GLFWwindow* Window::window = nullptr;

    const std::string Window::glslVersion = "#version 130";
    const int Window::glfwMajorVersion = 4;
    const int Window::glfwMinorVersion = 1;


	int Window::createWindow(const std::string& name, const int& width, const int& height)
	{
        /* Initialize the library */
        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwMinorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

	}

	GLFWwindow* Window::getWindow()
	{
		return window;
	}

    void Window::setBufferCallBack(GLFWframebuffersizefun fun)
    {
        glfwSetFramebufferSizeCallback(window, fun);
    }
    void Window::swapIntervals(const int& value)
    {
        glfwSwapInterval(value);
    }
}


