//base class for all type of events

#pragma once

#include "musashi/Core.h"

namespace musashi
{
	enum class EventType  //types of specific events possible, numbers auto assigned
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory //categories of events, one event can belong to multiple categories
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};  //simple categorization using bit flags


//macro to define event class type and name functions in derived event classes
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; } //name for debugging purposes
//the need for two fns, first is to get event type without reference of the event, second is for when we have an instance of the event

//this macro will be used define the category flags for each derived event class
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	
	class MSSHI_API Event
	{
		friend class EventDispatcher; //allowing event dispatcher to access the private members of event class

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); } //debugging function, returns name of event as string with additional data if needed
		//all virtual fns above will be overridden in the derived event classes, having appropriate definitions

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category; //this is simple utility fn, checks category of event using bitwise AND, implementation of above event category enum
		}

	//protected:
		bool Handled = false; //to check if the event has been handled or not

	};


	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>; 

	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}


		//fn to dispatch event based on its type
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
		//this will help making the client side code very simple
/*
		above is a very clever design pattern
		we'll be able to chain multiple dispatcher eg:
		EventDispatcher dispatcher(someEvent);
			if (!dispatcher.Dispatch<KeyPressedEvent>(onKeyPressed))
				if (!dispatcher.Dispatch<MouseMovedEvent>(onMouseMoved))
					dispatcher.Dispatch<WindowClosedEvent>(onWindowClosed);
*/

	private:
		Event& m_Event; //reference to the event that needs to be dispatched
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) //overloading the "stream insertion operator (<<)" to print event details using our logger
	{
		return os << e.ToString();
	}
}
