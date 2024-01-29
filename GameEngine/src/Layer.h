#pragma once
#include "string"
namespace ProjectAlpha {

class Layer {
public:
	Layer(const std::string = "Layer") {}
	virtual ~Layer();
	virtual void OnAttach();
	virtual void OnDetach();
	virtual void OnUpdate();
	virtual void OnEvent();

	inline const std::string& GetName() { return m_name; }

	
private:
	std::string m_name;

};

} //END namespace ProjectAlpha 