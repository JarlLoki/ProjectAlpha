#pragma once

#include <map>
#include <string>
#include <memory>

#include "Graphics.h"
#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "../Log.h"
#include "Text.h"
#include "FontManager.h"
#include "ImageManager.h"

namespace ProjectAlpha {
struct SpriteComponent;
struct TransformComponent;

class Renderer {
public:
	Renderer() = default;
	~Renderer();

	//

	void SetRenderWindowTarget(Window& window);

	//

	void ResetDrawBuffer();
	void DrawBufferToWindow();

	//Render Functions

	std::unique_ptr<RenderedText> RenderText(const Text& text);

	void LoadTextureFromFile(std::string filePath);
	void LoadTextureFromImage(Image image);
	void LoadAllTexturesFromImages(ImageManager images);
	void UnloadTexture(std::string filePath);

	//Draw Functions
	void DrawTexture(const Texture& texture, Vector2D pos, float scale);
	void DrawTexture(const Texture& texture, Rect src, Vector2D pos, float scale);
	void DrawSprite(const SpriteComponent& sprite, 
		            const TransformComponent& transform,
					float scale);

	//Basic Draw Functions
	void DrawRect(Rect rect, Color color, bool fill, float scale);
	void DrawLine(Vector2D src, Vector2D dst, Color color, float scale);
	
	//Viewport
	Rect GetViewPort() const;
	int GetViewPortWidth() const;
	int GetViewPortHeight() const;

	//		
	FontManager Fonts;//move this

private:	
	Texture& GetTexture(std::string filePath);


private:
	SDL_Renderer* m_renderer = nullptr;
	std::map<std::string, Texture> m_loadedTextures;

};


}