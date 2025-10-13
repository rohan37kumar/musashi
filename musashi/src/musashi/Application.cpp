#include "msshi_pch.h"
#include "Application.h"

#include "musashi/Log.h"

#include <GLFW/glfw3.h>

namespace musashi
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) //std::bind(...) binds function + arguments into callable

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		//core dispatcher functionality
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); //so if the event e is WindowCloseEvent -> call OnWindowClose fn

		MSSHI_CORE_TRACE("{0}", e.ToString()); //logging every event
	}

	void Application::Run()
	{
		while (m_Running) //our main loop
		{
			//test GLFW fns
			glClearColor(0.157f, 0.157f, 0.157f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false; //stopping the main Run() loop
		return true;
	}
}