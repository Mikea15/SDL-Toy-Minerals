//
//  Timer.hpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>

#if __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64

#include <SDL.h>

#endif


class Timer
{
public:
    Timer();
        
    void Start();
    void Stop();
    void Pause();
    void Resume();
        
    Uint32 GetTicks();
        
    bool IsStarted( ) const {
        return m_isStarted;
    }
        
    bool IsPaused( ) const {
        return m_isStarted && m_isPaused;
    }
        
private:
    bool m_isPaused;
    bool m_isStarted;
        
    Uint32 m_startTicks;
    Uint32 m_pausedTicks;
};


