#pragma once
#include <vector>
#include <memory>

#include "Layer.h"

namespace ProjectAlpha {

class LayerManager {
public:
	void AddLayer(Layer* layer) {}
	
	//std::vector<std::unique_ptr<Layer>>::iterator Begin
private:
	std::vector<std::unique_ptr<Layer>> m_layers;

};

} //END namespace ProjectAlpha