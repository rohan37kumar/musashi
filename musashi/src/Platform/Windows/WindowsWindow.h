//Windows OS window of our musashi engine

#pragma once

#include "musashi/Window.h"

#include <GLFW/glfw3.h>

namespace musashi
{
	class WindowsWindow : public Window //this class has simple definitions of all attributes of a window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; } //inline as it will be copied at call site
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		struct WindowData //for passing it into event callbacks
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
			//has all the data might be required by GLFW
		};

		WindowData m_Data;
	};
}
