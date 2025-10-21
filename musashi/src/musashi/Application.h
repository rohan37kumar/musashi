//this is the main application header file
//for now just the Run fn is declared

#pragma once

#include "Core.h"
#include "musashi/LayerStack.h"
#include "musashi/Events/Event.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; //unique ptr represents exclusive ownership of a dynamically allocated object, here Window
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	//will be defined in the CLIENT code
	Application* CreateApplication();
}
