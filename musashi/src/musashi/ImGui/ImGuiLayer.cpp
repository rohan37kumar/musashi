//used many references form the imgui backend codes of implementing opengl and glfw

#include "msshi_pch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_opengl_renderer.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

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

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		 
		// fixed: //TODO: set key map correctly - high priority
		//New method, used official imgui backend
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()); // implemented - //TODO: get the window pointer from application

		ImGui_ImplGlfw_InitForOpenGL(window, true); // true = install callbacks, this will handle all key events automatically
		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame(); //this automatically handles the deltaTime and DisplaySize setup
		//damn, maybe this also implements mouse and keyboard events handling
		ImGui::NewFrame();
		//! will have to study ImGui GLFW and OpenGL backend more better, this hack works for now

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::OnEvent(Event& event)
	{
	}

}

//in previous versions of ImGUI, instead of ImGui_ImplGlfw_NewFrame()
//we had to manually set up the frame like this:
// 		ImGuiIO& io = ImGui::GetIO();
//		float time = (float)glfwGetTime();
//		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
// 		m_Time = time;
//		