//this is the main application header file
//for now just the Run fn is declared

#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "musashi/Events/ApplicationEvent.h"
#include "Window.h"

namespace musashi{

	class MSSHI_API Application
	{
	public:
			Application();
			virtual ~Application();
	
		void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; //unique ptr represents exclusive ownership of a dynamically allocated object, here Window
		bool m_Running = true;
	};

	//will be defined in the CLIENT code
	Application* CreateApplication();
}
