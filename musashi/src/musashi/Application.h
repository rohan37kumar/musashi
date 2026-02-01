//this is the main application header file

#pragma once

#include "Core.h"

#include "Window.h"
#include "musashi/LayerStack.h"
#include "musashi/Events/Event.h"
#include "musashi/Events/ApplicationEvent.h"

#include "musashi/ImGui/ImGuiLayer.h"

#include "musashi/Renderer/Shader.h"
#include "musashi/Renderer/Buffer.h"
#include "musashi/Renderer/VertexArray.h"
#include "musashi/Renderer/Renderer.h"
#include "musashi/Renderer/Camera.h"

namespace musashi{

	class MSSHI_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; //unique ptr represents exclusive ownership of a dynamically allocated object, here Window
		//std::unique_ptr<ImGuiLayer> m_ImGuiLayer; 
		//now musashi intrinsically provides ImGui Layer as it's UI solution
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		OrthographicCamera m_Camera;	// default testing camera

	private:
		static Application* s_Instance;
	};

	//will be defined in the CLIENT code
	Application* CreateApplication();
}
