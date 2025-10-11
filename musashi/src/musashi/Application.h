//this is the main application header file
//for now just the Run fn is declared

#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace musashi{

	class MSSHI_API Application
	{
	public:
			Application();
			virtual ~Application();
	
		void Run();
	private:
		std::unique_ptr<Window> m_Window; //pointer to window object
		bool m_Running = true;
	};

	//will be defined in the CLIENT code
	Application* CreateApplication();
}
