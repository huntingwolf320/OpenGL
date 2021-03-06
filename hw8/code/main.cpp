#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include "hw.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG_HW", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//setup imGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsLight();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGuiWindowFlags window_flags = 0;

	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoBackground;

	unsigned int nowProgram = 0;
	unsigned int hw2_Program = load_hw2();
	unsigned int hw3_Program = load_hw3();
	unsigned int hw4_Program = load_hw4();
	unsigned int hw5_Program = load_hw5();
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);
		
		//imGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		{
			/*
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(SCR_WIDTH, 0));

			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0;
			*/
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("H W 2", "triangle"))
					{
						nowProgram = 2;
					}
					if (ImGui::MenuItem("H W 3", "line"))
					{
						nowProgram = 3;
					}
					if (ImGui::MenuItem("H W 4", "Cube"))
					{
						nowProgram = 4;
					}
					if (ImGui::MenuItem("H W 5", "Camera"))
					{
						nowProgram = 5;
					}
					if (ImGui::MenuItem("H W 6", "Light"))
					{
						nowProgram = 6;
					}
					if (ImGui::MenuItem("H W 7", "Shadow"))
					{
						nowProgram = 7;
					}
					if (ImGui::MenuItem("H W 8", "Bezier Curve"))
					{
						nowProgram = 8;
						glfwSetMouseButtonCallback(window, mousebutton_callback);
					}
					ImGui::MenuItem("...", "...");
					
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
		}

		switch (nowProgram)
		{
		case 2:
			render_hw2(hw2_Program);
			break;
		case 3:
			render_hw3(hw3_Program);
			break;
		case 4:
			render_hw4(hw4_Program);
			break;
		case 5:
			render_hw5(hw5_Program, window);
			break;
		case 6:
			render_hw6();
			break;
		case 7:
			render_hw7();
			break;
		case 8:
			render_hw8();
			break;
		default:
			ImGui::ShowDemoWindow();
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			break;
		}
		
		//render imGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}