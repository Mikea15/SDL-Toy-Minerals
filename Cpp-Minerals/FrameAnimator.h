//
//  FrameAnimator.hpp
//  Minerals
//
//  Created by Michael Adaixo on 25/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#if __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64

#include <SDL.h>

#endif

#include <stdio.h>

class FrameAnimator
{
public:
    FrameAnimator();
        
    void OnAnimate();
        
    void SetFramerate( int milliseconds );
    void SetCurrentFrame( int frame );
    int GetCurrentFrame( );
        
private:
    int m_currentFrame;
    int m_frameIncrement;
    int m_frameRate;
    long m_oldTime;
        
    int m_maxFrames;
    bool m_oscillate;
};


