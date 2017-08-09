//
//  Texture.cpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "Texture.h"
#include "Vector2.h"

Texture::Texture() : m_texture(NULL), m_width(NULL), m_height(NULL)
{
    
}

Texture::~Texture()
{
    Clear();
}

bool Texture::LoadFromFile( SDL_Renderer *renderer, std::string path )
{
    Clear();
    
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        std::cout << "Unable to load image " << path.c_str() << " - " << IMG_GetError() << std::endl;
        return false;
    }
    
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0xFF) );
    
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if( m_texture == NULL )
    {
        std::cout << "Unable to create texture from surface " << SDL_GetError() << std::endl;
        return false;
    }
    
    m_width = surface->w;
    m_height = surface->h;
    
    SDL_FreeSurface(surface);
    
    return m_texture != NULL;
}

bool Texture::LoadFromRenderedText( TTF_Font *font, SDL_Renderer *renderer, std::string textureText, SDL_Color textColor )
{
    Clear();
    
    SDL_Surface* surface = TTF_RenderText_Blended( font, textureText.c_str(), textColor );
    if( surface == NULL )
    {
        std::cout << "Unable to create font " << TTF_GetError() << std::endl;
        return false;
    }
    
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if( m_texture == NULL )
    {
        std::cout << "Unable to create texture from surface " << SDL_GetError() << std::endl;
        return false;
    }
    
    m_width = surface->w;
    m_height = surface->h;
    
    SDL_FreeSurface(surface);
    
    return m_texture != NULL;
}

void Texture::Clear()
{
    if( m_texture != NULL )
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;
        m_width = 0;
        m_height = 0;
    }
}


void Texture::SetColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Texture::SetBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode(m_texture, blending);
}

void Texture::SetAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod(m_texture, alpha);
}

void Texture::Render(SDL_Renderer *renderer, Vector2 position, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { (int)position.x, (int)position.y, m_width, m_height };
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    SDL_RenderCopyEx(renderer, m_texture, clip, &renderQuad, angle, center, flip);
}









