#include "msshi_pch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_opengl_renderer.h"

#include "GLFW/glfw3.h" //temporary

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

		//Now imgui can no longer set keymap directly,"Added io.AddKeyEvent() function. Obsoleted writing directly to io.KeyMap[], io.KeysDown[] arrays."
		//it can be used like this：io.AddKeyEvent(ImGuiKey_Tab, key == GLFW_KEY_TAB && is_pressed);
		//io.AddKeyEvent(ImGuiKey_Tab, false);
		//TODO: set key map - high priority

		ImGui_ImplOpenGL3_Init("#version 410");
	}
	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}
