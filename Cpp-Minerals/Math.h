//
//  Math.hpp
//  Minerals
//
//  Created by Michael Adaixo on 29/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <stdio.h>


class Math
{
public:
    static double Random01( )
    {
        return ((double) rand() / (RAND_MAX));
    }
        
    static float Lerp( float a, float b, float t )
    {
        return ( 1 - t ) * a + t * b;
    }
        
    //
    // http://gizma.com/easing/#quad3
    //
    static float EaseInOutQuad( float time, float b, float c, float duration )
    {
        time /= duration / 2;
        if( time < 1 )
            return c / 2 * time * time + b;
        time--;
        return -c / 2 * ( time * ( time - 2 ) - 1 ) + b;
    }
};


