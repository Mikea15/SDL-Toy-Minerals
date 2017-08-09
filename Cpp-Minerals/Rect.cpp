//
//  Rect.cpp
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "Rect.h"

Rect::Rect( ) : m_Position(0, 0), m_Height(0), m_Width(0)
{
    
}

Rect::Rect( Vector2 position, int width, int height ) : m_Position(position), m_Width(width), m_Height(height)
{
    
}

Rect::Rect( SDL_Rect rect )
{
    this->rect = rect;
    
    m_Position.x = rect.x;
    m_Position.y = rect.y;
    
    m_Height = rect.h;
    m_Width = rect.w;
}

Vector2 Rect::GetCenter()
{
    return Vector2( m_Position.x + m_Width * 0.5f, m_Position.y + m_Height * 0.5f );
}

bool Rect::IsColliding( SDL_Rect a, SDL_Rect b )
{
    int aLeft = a.x;
    int aTop = a.y;
    int aRight = a.x + a.w;
    int aBottom = a.y + a.h;
    
    int bLeft = b.x;
    int bTop = b.y;
    int bRight = b.x + b.w;
    int bBottom = b.y + b.h;
    
    // AABB Bounding Box Collision Detection.
    if( aBottom <= bTop ) return false;
    if( aTop >= bBottom ) return false;
    if( aRight <= bLeft ) return false;
    if( aLeft >= bRight ) return false;
    
    return true;
}

bool Rect::Contains( float x, float y )
{
    float left = m_Position.x;
    float right = m_Position.x + m_Width;
    float top = m_Position.y;
    float bottom = m_Position.y + m_Height;
    
    if( x >= left && x <= right && y >= top && y <= bottom )
        return true;
    
    return false;
}

