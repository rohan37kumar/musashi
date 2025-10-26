//understand this functionality as a wrapper over a vector of Layers
#pragma once

#include "musashi/Core.h"
#include "Layer.h"

#include <vector>

namespace musashi
{
	class MSSHI_API LayerStack //stack of layers, pushing and popping
	{
	public:

		LayerStack();
		~LayerStack();


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		//overlays are debugging graphics which will be rendered on top of everything else

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0; //no more iterator, simple index tracking to insert layers
	};
}