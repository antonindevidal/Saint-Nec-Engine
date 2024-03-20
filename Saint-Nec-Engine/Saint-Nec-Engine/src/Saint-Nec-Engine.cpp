#include "Saint-Nec-Engine.h"


int mouseX = 640;
int mouseY = 360;

bool mouseMode = true;
bool polygonMode = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = ypos;
}

void processInput(Game& g)
{
	if (sne::Input::isKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(sne::Window::getWindow(), true);

	// Press F1 to change from mouse used for camera to mouse used for UI
	if (sne::Input::isKeyJustPressed(GLFW_KEY_F1))
	{
		if (mouseMode)
		{
			glfwSetInputMode(sne::Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else
		{
			glfwSetInputMode(sne::Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		mouseMode = !mouseMode;
	}
	if (sne::Input::isKeyJustPressed(GLFW_KEY_F2))
	{
		if (polygonMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		polygonMode = !polygonMode;
	}


}


void draw_imgui(bool& show_demo_window, bool& show_another_window, ImVec4& clear_color, ImGuiIO& io)
{
	//Demo window (can be commented if needed)
	//if (show_demo_window)
	ImGui::ShowDemoWindow(&show_demo_window);

	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
	}

}

int main(void)
{
    #ifdef __APPLE__
        std::cerr << "Ecosystem is closed for Apple users." << std::endl;
        return 1;
    #endif



#ifdef NDEBUG
	std::cout << "RELEASE MODE" << std::endl;
#else
	std::cout << "DEBUG MODE" << std::endl;
#endif // DEBUG



	if (sne::Window::createWindow("Saint-Nec-Engine", 1280, 720) == -1)
	{
		std::cout << "Error creating window, terminating program" <<std::endl;
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	sne::Window::setBufferCallBack(framebuffer_size_callback);
	sne::Input::bindInputCallbacks();
	sne::Input::bindMouseCallbacks();

	glEnable(GL_DEPTH_TEST);
	sne::Window::swapIntervals(0);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	//Init ImGUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(sne::Window::getWindow(), true);
	ImGui_ImplOpenGL3_Init(sne::Window::getGLSLVersion().c_str());
	bool show_demo_window = true;
	bool show_another_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	Game g{};
	//TracyGpuContext

	/* Loop until the user closes the window */
	while (!sne::Window::windowShouldClose())
	{
		sne::Window::pollEvents();
		Time::getInstance()->calculateDeltaTime(); // TODO: Move this call to the scene manager for it to be abstract for the user
		//std::cout << Time::getDeltaTime() << std::endl;
		processInput(g);
		g.update();
		/* Render here */
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();




		//draw_imgui(show_demo_window, show_another_window, clear_color, io);
		g.draw();

		//Render ImGUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		sne::Window::swapBuffers();
		
		sne::Input::endFrame();
	}

	// Cleanup ImGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	sne::Window::terminate();
	return 0;
}
