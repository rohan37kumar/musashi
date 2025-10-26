#include "msshi_pch.h"
#include "Application.h"

#include "musashi/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace musashi
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) //std::bind(...) binds function + arguments into callable

	Application* Application::s_Instance = nullptr; //for passing application instance reference

	Application::Application()
	{
		MSSHI_CORE_ASSERT(!s_Instance, "Application already exists!"); //check if instance already exists
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); //todo understand the event callback stack, how events are passed from window to application

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		//core dispatcher functionality
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); //so if the event e is WindowCloseEvent -> call OnWindowClose fn

		//MSSHI_CORE_TRACE("{0}", e.ToString()); //logging every event

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) //reverse iteration
		{
			(*--it)->OnEvent(e); //decrementing iterator first, then dereferencing to get Layer*, then calling OnEvent fn of that layer
			if (e.Handled)
				break; 
		}
	}

	void Application::Run()
	{
		while (m_Running) //our main loop
		{
			//clear the screen -> set GLFW window color
			glClearColor(0.157f, 0.157f, 0.157f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT);

			//update all layers
			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//imgui rendering implementation
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(); //swap buffers and poll events
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false; //stopping the main Run() loop
		return true;
	}
}