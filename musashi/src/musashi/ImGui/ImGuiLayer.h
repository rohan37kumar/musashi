#pragma once

#include "musashi/Layer.h"

namespace musashi
{
	class MSSHI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:

	};
}