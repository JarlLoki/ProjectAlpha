#pragma once

#include <map>
#include <string>


#include "BasicDataContainers/Vector2D.h"
#include "BasicDataContainers/Color.h"
#include "BasicDataContainers/Rect.h"
#include "BasicDataContainers/Point.h"

#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "../Log.h"

namespace ProjectAlpha {

class Renderer {
public:
	~Renderer();

	//
	void SetRenderWindowTarget(Window& window);
	//
	void ResetDrawBuffer();
	void DrawBufferToWindow();



	//Draw Functions:
	void DrawTexture(const Texture& texture, Rect dst, float scale);
	void DrawSprite(const Sprite& sprite, Rect dst, float scale);

	//Basic Draw Functions
	void DrawRect(Rect rect, Color color, bool fill, float scale);
	void DrawLine(Vector2D src, Vector2D dst, Color color, float scale);
	
	//Viewport
	Rect GetViewPort() const;
	int GetViewPortWidth() const;
	int GetViewPortHeight() const;

	//	
	SDL_Renderer* Get() { return m_renderer; }
private:
	Texture& GetTexture(const Sprite& sprite);
	Texture& LoadTextureFromFile(std::string filePath);
	


private:
	SDL_Renderer* m_renderer;
	std::map<std::string, Texture> m_loadedTextures;

};

}