//
//  Rect.hpp
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>

#if __APPLE__
#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64
#include <SDL.h>
#endif

#include "Vector2.h"

class Rect 
{
public:
    Rect();
    Rect( Vector2 position, int width, int height );
    Rect( SDL_Rect rect );
        
    Vector2 GetCenter();
        
    bool IsColliding( SDL_Rect a, SDL_Rect b );
    bool Contains( float x, float y );
        
private:
    Vector2 m_Position;
    int m_Height;
    int m_Width;
        
    SDL_Rect rect;
};


