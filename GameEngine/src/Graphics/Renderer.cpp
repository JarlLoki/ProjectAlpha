

#include "Renderer.h"


namespace ProjectAlpha {
Renderer::~Renderer() {
	SDL_DestroyRenderer(m_renderer);
}
void Renderer::SetRenderWindowTarget(Window& window) {
	m_renderer = window.CreateRenderer();
}
void Renderer::ResetDrawBuffer() {
	SDL_SetRenderDrawColor(m_renderer,
		0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
}

void Renderer::DrawBufferToWindow() {
	SDL_RenderPresent(m_renderer);
}


//
//Draw Functions
/////////////////////////////////
void Renderer::DrawRect(Rect rect, Color color, bool fill, float scale) {
	//rect.w *= scale;
	//rect.h *= scale;
	rect *= scale;
	//SDL_Rect dst = rect.ToSDL_Rect();
	SDL_Rect dst = { rect.x, rect.y, rect.w, rect.h };


	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	if (fill)
		SDL_RenderFillRect(m_renderer, &dst);
	else
		SDL_RenderDrawRect(m_renderer, &dst);

}

void Renderer::DrawLine(Vector2D src, Vector2D dst, Color color, float scale) {
	src *= scale;
	Point pSrc = src.ToPoint();
	
	dst *= scale;
	Point pDst = dst.ToPoint();
	

	SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
	SDL_RenderDrawLine(m_renderer, pSrc.x, pSrc.y, pDst.x, pDst.y);

}

Rect Renderer::GetViewPort() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return Rect(viewport.x, viewport.y, viewport.w, viewport.h);
}

int Renderer::GetViewPortWidth() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return viewport.w;
}

int Renderer::GetViewPortHeight() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return viewport.h;

}



void Renderer::DrawTexture(const Texture &texture, Rect dst, float scale)  {

	SDL_Texture* sdlTexture = texture.data;
	//SDL_Rect sdlSrc = texture.SrcRect.ToSDL_Rect();
	SDL_Rect sdlSrc = { texture.SrcRect.x, texture.SrcRect.y,
					    texture.SrcRect.w, texture.SrcRect.h };

	dst.w *= scale;
	dst.h *= scale;
	//SDL_Rect sdlDst = dst.ToSDL_Rect();
	SDL_Rect sdlDst = { dst.x, dst.y, dst.w, dst.h };

	SDL_RenderCopy(m_renderer, sdlTexture, &sdlSrc, &sdlDst);
}

void Renderer::DrawSprite(const Sprite &sprite, Rect dst, float scale) {
	Texture& texture = GetTexture(sprite);

	DrawTexture(texture, dst, scale);
}




Texture& Renderer::GetTexture(const Sprite& sprite) {
	Texture& texture = m_loadedTextures[sprite.SpriteSheetPath];

	if (!texture.data) {
		PA_LOG_WARN("Texture " + sprite.SpriteSheetPath + " not preloaded. Attempting to load texture.");
		//No texture data found, try loading it from file path:
		texture = LoadTextureFromFile(sprite.SpriteSheetPath);
	}
	return texture;
}

Texture& Renderer::LoadTextureFromFile(std::string filePath) {
	Texture texture;


	return texture;
}


}//End ProjectAlpha namespace
