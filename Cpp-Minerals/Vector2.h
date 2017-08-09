//
//  Vector2.hpp
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <cmath>
#include <stdio.h>

#include "Math.h"

struct Vector2
{
    float x;
    float y;
    
    Vector2( ) : x(0), y(0)
    {
    }
        
    Vector2( float x, float y ): x(x), y(y)
    {
    }

    Vector2( const Vector2& v ) : x(v.x), y(v.y)
    {
    }
        
    float Dot( Vector2 other )
    {
        return x * other.x + y * other.y;
    }
        
    float LengthSqr( )
    {
        return x * x + y * y;
    }
        
    float Length( )
    {
        return sqrtf( Length() );
    }
        
    Vector2 Lerp( Vector2 a, Vector2 b, float t )
    {
        return Vector2( Math::Lerp(a.x, b.x, t), Math::Lerp(a.y, b.y, t) );
    }
        
    Vector2 EaseInOutQuad( Vector2 a, Vector2 b, float t, float duration )
    {
        return Vector2( Math::EaseInOutQuad(t, a.x, b.x, duration), Math::EaseInOutQuad(t, a.y, b.y, duration) );
    }
        
    Vector2 Normalized( )
    {
        return Vector2( x / Length(), y / Length() );
    }
        
    Vector2 operator+( const Vector2& a ) const {
        return Vector2( x + a.x, y + a.y );
    }
        
    Vector2 operator-( const Vector2& a ) const {
        return Vector2( x - a.x, y - a.y );
    }
        
    Vector2 operator+=( const Vector2& a ) {
        x += a.x;
        y += a.y;
        return *this;
    }
        
    Vector2 operator-=( const Vector2& a ) {
        x -= a.x;
        y -= a.y;
        return *this;
    }
        
    Vector2 operator*( const float scale ) {
        return Vector2( x * scale, y * scale );
    }
        
    Vector2 operator*=( const float scale ) {
        x *= scale;
        y *= scale;
        return *this;
    }
        
    bool operator==(const Vector2 other ) const {
        return ( x == other.x && y == other.y );
    }
};
