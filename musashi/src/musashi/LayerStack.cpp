#include "msshi_pch.h"
#include "LayerStack.h"

namespace musashi
{
	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer; //deleting all layers
	}


	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
	//layers get pushed into first half of vector, overlays into second half
	//m_LayerInsertindex keeps track of where the division is
}
