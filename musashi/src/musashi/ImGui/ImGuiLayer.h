#pragma once

#include "musashi/Layer.h"

namespace musashi
{
	class MSSHI_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		//virtual void OnUpdate() override; //! OnImGuiRender() ?
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
		//previously did manual setup in OnUpdate(), better to have explicit fns
	};
}