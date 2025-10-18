#pragma once

#include "musashi/Core.h"
#include "musashi/Events/Event.h"

namespace musashi
{
	//how this should be used:
	//subclass this class and implement anything needed in the virtual fns
	class MSSHI_API Layer
	{
	public:

		Layer(const std::string& name = "Layer"); //naming, default is Layer
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; } //getter for debug name
	protected:
		std::string m_DebugName; //not for finding layers, just for debugging purposes
	};
}
