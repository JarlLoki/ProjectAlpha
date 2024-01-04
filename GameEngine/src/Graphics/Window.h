#pragma once
#include <string>
#include "SDL.h"


namespace ProjectAlpha {

/*
// Is this needed?
struct WindowProps {
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "ProjectAlpha Engine",
				unsigned int width = 1280,
				unsigned int height = 720)
		: Title(title), Width(width), Height(height) {
	}

};
*/

class Window {
public:
	Window(const std::string& title = "ProjectAlpha Engine",
		unsigned int width = 1280, 
		unsigned int height = 720);
	~Window();

	SDL_Renderer* CreateRenderer();

	void OnUpdate();
	void OnEvent(SDL_Event& event);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	
private:


private:
	std::string m_title;
	unsigned int m_width;
	unsigned int m_height;

	SDL_Window* m_window;
	
	
};

}