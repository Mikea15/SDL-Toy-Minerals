//
//  Texture.hpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>

#if __APPLE__
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>
#endif

class Vector2;

class Texture
{
public:
    Texture();
    ~Texture();
        
    bool LoadFromFile( SDL_Renderer *renderer, std::string path );
    bool LoadFromRenderedText(TTF_Font *font, SDL_Renderer *renderer, std::string textureText, SDL_Color textColor );
        
    void Clear();
        
    void SetColor( Uint8 red, Uint8 green, Uint8 blue );
    void SetBlendMode( SDL_BlendMode blending );
    void SetAlpha( Uint8 alpha );
        
    void Render( SDL_Renderer *renderer, Vector2 position, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
        
    int GetWidth( ) const { return m_width; }
    int GetHeight( ) const { return m_height; }
        
    void SetWidth( float width ) {
        m_width = width;
    }
        
    void SetHeight( float height ) {
        m_height = height;
    }
        
    SDL_Texture* GetTexture( ) const {
        return m_texture;
    }
                
private:
    SDL_Texture* m_texture;
        
    int m_width;
    int m_height;
};


