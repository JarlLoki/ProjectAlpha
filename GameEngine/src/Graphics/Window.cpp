#include "Window.h"
#include "../Log.h"

namespace ProjectAlpha {

Window::Window(const std::string& title, 
	unsigned int width, unsigned int height) 
	: m_title(title), m_width(width), m_height(height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		//Error Check
		PA_LOG_ERROR("SDL Initilization failed.");
	}
	else {
		SDL_version version;
		SDL_VERSION(&version);

		PA_LOG_INFO("SDL Intilized successfully.");
		PA_LOG_INFO("SDL Version: " + std::to_string(version.major) + "." +
			                          std::to_string(version.minor) + "." +
			                          std::to_string(version.patch));
	}

	m_window = SDL_CreateWindow(m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_window) {
		//Error check
		PA_LOG_ERROR("Window creation failed.");
	}
	else {
		PA_LOG_INFO("Window created successfully.");
	}

}

Window::~Window() {
	SDL_DestroyWindow(m_window);
}

SDL_Renderer* Window::CreateRenderer() {
	SDL_Renderer* renderer = nullptr;

	renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		PA_LOG_ERROR("Renderer failed to create.");
	} 
	else {
		PA_LOG_INFO("Renderer created successfully.");
	}

	return renderer;
}

void Window::OnUpdate() {

}

void Window::OnEvent(SDL_Event& event) {

	switch (event.type) {
	case SDL_WINDOWEVENT:
		switch (event.window.event) {
		case SDL_WINDOWEVENT_RESIZED:
			m_width = event.window.data1;
			m_height = event.window.data2;
			break;
		}
		break;
		
	}

}

unsigned int Window::GetWidth() const {
	return m_width;
}

unsigned int Window::GetHeight() const {
	return m_height;
}



}
