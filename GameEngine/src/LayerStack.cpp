#include "LayerStack.h"

#include "Log.h"

namespace ProjectAlpha {

void LayerStack::OnEvent(SDL_Event* event) {
	for (auto layer = m_layers.rbegin(); layer != m_layers.rend(); ++layer) {
		(*layer)->OnEvent(event);
	}
}

void LayerStack::OnUpdate() {
	for (auto& layer : m_layers) {
		layer->OnUpdate();
	}
}

void LayerStack::AddLayer(Layer* layer) {
	layer->OnAttach();
	m_layers.push_back(std::move(std::unique_ptr<Layer>(layer)));
}

Layer* LayerStack::operator[](std::string layerName) {
	for (auto& layer : m_layers) {
		if (layer->GetName() == layerName) {
			return layer.get();
		}
	}
	/*TODO: change this to an assert?*/
	PA_LOG_ERROR("Layer: " + layerName + " not found!");
	return nullptr;
}

}//END namespace ProjectAlpha 
