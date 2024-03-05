#pragma once
#include <string>
#include "SDL.h"

#include "BasicDataContainers/Size.h"


namespace ProjectAlpha {


// Is this needed?
struct WindowProperties {
	std::string Title = "ProjectAlpha Engine";
	int Width = 1280;
	int Height = 720;
	bool Fullscreen = true;
	bool VSync = true;
	bool ResizableWindow = true;

	//WindowProps(const std::string& title = "ProjectAlpha Engine",
	//			unsigned int width = 1280,
	//			unsigned int height = 720)
	//	: Title(title), Width(width), Height(height) {
	//}

};


class Window {
public:
	//Window(const std::string& title = "ProjectAlpha Engine",
	//	unsigned int width = 1280, 
	//	unsigned int height = 720);
	Window(WindowProperties props = WindowProperties());
	~Window();

	SDL_Renderer* CreateRenderer();

	void OnUpdate();
	void OnEvent(SDL_Event& event);

	void SetSize(int w, int h);
	Size GetSize();

	int GetWidth() const;
	int GetHeight() const;

	
private:


private:
	std::string m_title;
	int m_width;
	int m_height;
	bool m_fullscreen;
	bool m_vsync;

	SDL_Window* m_window;
	
};

}