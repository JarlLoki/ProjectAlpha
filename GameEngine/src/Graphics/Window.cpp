#include "Window.h"
#include "../Log.h"

namespace ProjectAlpha {

/*
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

	Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED;
	bool useVSync = true;
	if (useVSync) {
		windowFlags |= SDL_RENDERER_PRESENTVSYNC;
	}

	if (m_fullscreen) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	if (true) {
		windowFlags |= SDL_WINDOW_RESIZABLE;
	}


	m_window = SDL_CreateWindow(m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, windowFlags);

	if (!m_window) {
		//Error check
		PA_LOG_ERROR("Window creation failed.");
	}
	else {
		PA_LOG_INFO("Window created successfully.");
	}

}
*/

Window::Window(WindowProperties props) : 
	m_title(props.Title),
	m_width(props.Width),
	m_height(props.Height),
	m_fullscreen(props.Fullscreen),
	m_vsync(props.VSync)
{


	Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_RENDERER_ACCELERATED;
	
	if (m_vsync) {
		windowFlags |= SDL_RENDERER_PRESENTVSYNC;
	}

	if (m_fullscreen) {
		windowFlags |= SDL_WINDOW_FULLSCREEN;
	}

	if (props.ResizableWindow) {
		windowFlags |= SDL_WINDOW_RESIZABLE;
	}


	m_window = SDL_CreateWindow(m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height, windowFlags);

	if (!m_window) {
		//Error check
		PA_LOG_ERROR("Window creation failed.");
	} else {
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
	case SDL_KEYDOWN: 
		//On first key press, then ignores key being held:
		if (event.key.repeat == 0) {
			switch (event.key.keysym.sym) {

			/* 
			* Alt-Enter toggles Fullscreen/Windowed
			* 
			* Toggles between full screen and windowed mode
			* if alt is held down and enter is pressed:			
			*/
			case SDLK_RETURN:
				auto state = SDL_GetKeyboardState(nullptr);
				if (state[SDL_SCANCODE_LALT] || state[SDL_SCANCODE_RALT]) {
					m_fullscreen = !m_fullscreen;
					SDL_SetWindowFullscreen(m_window, m_fullscreen);

				}
				break;

			}
			
		}		
	}

}

void Window::SetSize(int w, int h) {
	int m_width = w;
	int m_height = h;
	SDL_SetWindowSize(m_window, m_width, m_height);
	SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

Size Window::GetSize() {	
	return Size(m_width, m_height);
}

int Window::GetWidth() const {
	return m_width;
}

int Window::GetHeight() const {
	return m_height;
}



}
