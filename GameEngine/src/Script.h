#pragma once
#include <string>
#include "Scene/Entity.h"

namespace ProjectAlpha{
struct ScriptComponent;

struct Script {
	Script() = default;
	~Script() = default;
	//Entity entity;

	virtual void OnInit() {}
	virtual void OnEvent() {}
	virtual void OnUpdate() {}
	virtual void OnDestroy() {}

protected:
	std::string m_type;
	Entity m_entity;
	
	friend ScriptComponent;
};

}//END namespace ProjectAlpha