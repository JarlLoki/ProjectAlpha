#pragma once
#include <vector>
#include <memory>

#include "SDL.h"

#include "Layer.h"

namespace ProjectAlpha {

class LayerStack {
public:
	LayerStack() = default;
	LayerStack(const LayerStack&) = delete;
	LayerStack& operator=(const LayerStack&) = delete;

	void OnEvent(SDL_Event* event);
	void OnUpdate();

	void AddLayer(Layer* layer);

	Layer* operator[](std::string layerName);
private:
	std::vector<std::unique_ptr<Layer>> m_layers;

};

} //END namespace ProjectAlpha