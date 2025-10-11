//abstract representaion of a window in our engine

#pragma once

#include "msshi_pch.h"

#include "musashi/Core.h"
#include "musashi/Events/Event.h"

namespace musashi
{
	struct WindowProps //an abstract window attributes
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		WindowProps(const std::string& title = "musashi",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	//desktop based window interface
	class MSSHI_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>; //type alias of the event callback fn, takes Event as param

		//pure virtual fns
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0; //setting the event callback fn
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//fn to create a window
		static Window* Create(const WindowProps& props = WindowProps());
		//this Create fn will have to be defined per platform
	};

}