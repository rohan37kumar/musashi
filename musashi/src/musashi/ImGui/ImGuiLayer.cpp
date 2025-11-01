//used many references form the imgui backend codes of implementing opengl and glfw
//DONE - add documentation comments

#include "msshi_pch.h"
#include "ImGuiLayer.h"
#include "imgui.h"

#include <GLFW/glfw3.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

//#include "Platform/OpenGL/imgui_opengl_renderer.h"
//#include "Platform/OpenGL/imgui_impl_glfw.h"

#include "musashi/Application.h"

namespace musashi
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach() //this fn lot copied from imgui opengl3 and glfw backend
	{
		//setup ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		//ImGui style
		ImGui::StyleColorsDark();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true); //true = install callbacks, this will handle all events automatically
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//generated new frame -> took input etc from GLFW -> then starts ImGui frame
	}
	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		//matched display size to application window size

		//Rendering - more like give draw commands to opengl backend
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) //handles updating and rendering of all viewports
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
			//temporarily switching contexts to each window -> render them -> then switching back to main context
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		//only sample Example window for now

	}

}

//in previous versions of ImGUI, instead of ImGui_ImplGlfw_NewFrame()
//we had to manually set up the frame like this:
// 		ImGuiIO& io = ImGui::GetIO();
//		float time = (float)glfwGetTime();
//		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
// 		m_Time = time;

	/*
	void ImGuiLayer::OnAttach() //older hacking method
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;


		// fixed: //DONE: set key map correctly - high priority
		//New method, used official imgui backend
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); // implemented - //DONE: get the window pointer from application

		ImGui_ImplGlfw_InitForOpenGL(window, true); // true = install callbacks, this will handle all key events automatically
		//damn, maybe this also implements mouse and keyboard events handling

		ImGui_ImplOpenGL3_Init("#version 410");
	}


	void ImGuiLayer::OnUpdate()
	{
		//should be in Begin()
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		//this automatically handles the deltaTime and DisplaySize setup
		//! will have to study ImGui GLFW and OpenGL backend more better, this hack works for now
		ImGui::NewFrame();

		//imGui rendering code goes here, need new fn like OnImGuiRender()
		static bool show = true;
		ImGui::ShowDemoWindow(&show);


		//should be in End()
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	*/
