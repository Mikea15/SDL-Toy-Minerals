//
//  GameObject.hpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>

#if __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64

#include <SDL.h>

#endif

#include <vector>

#include "Texture.h"
#include "Vector2.h"
#include "Rect.h"

class GameObject
{
public:
    GameObject( )
    {
        m_isActive = true;
        SetID( );
        m_gameObjects.push_back(this);
    }
        
    virtual ~GameObject() {};

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Cleanup() = 0;

    int ID() const { return m_ID; }
        
    static std::vector<GameObject*> GetGameObjects() {
        return m_gameObjects;
    }
        
    void SetActive( bool value ) {
        m_isActive = value;
    }
        
    bool IsActive( ) const {
        return m_isActive;
    }
        
    // bool IsColliding( SDL_Rect a, SDL_Rect b );
        
    void Render( SDL_Renderer *renderer ) {
        m_texture.Render(renderer, m_position);
    }
        
    Texture GetTexture( ) const {
        return m_texture;
    }
        
    void Translate( int x, int y ) {
        m_position.x += x;
        m_position.y += y;
    }
        
        
private:
    static int m_nextvalidID;
    static std::vector<GameObject*> m_gameObjects;

    int m_ID;
    bool m_isActive;
    void SetID( );
        
protected:
        
    // Still unsure about these 3...
    Vector2 m_position;
    Rect m_rect;
    SDL_Rect m_destRect;
        
    Texture m_texture;
};



