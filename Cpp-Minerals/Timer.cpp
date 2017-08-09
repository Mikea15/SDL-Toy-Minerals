//
//  Timer.cpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "Timer.h"


Timer::Timer( )
{
    m_startTicks = m_pausedTicks = 0;

    m_isPaused = m_isStarted = false;
}

void Timer::Start()
{
    m_isStarted = true;
    m_isPaused = false;
    
    m_startTicks = SDL_GetTicks();
    
    m_pausedTicks = 0;
}

void Timer::Stop()
{
    m_isStarted = false;
    m_isPaused = false;
    
    m_startTicks = 0;
    m_pausedTicks = 0;
}

void Timer::Pause()
{
    if( m_isStarted && !m_isPaused )
    {
        m_isPaused = true;
        
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        
        m_startTicks = 0;
    }
}

void Timer::Resume()
{
    if( m_isStarted && m_isPaused )
    {
        m_isPaused = false;
        
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        
        m_pausedTicks = 0;
    }
}

Uint32 Timer::GetTicks()
{
    Uint32 time = 0;
    
    if( m_isStarted )
    {
        if( m_isPaused )
        {
            time = m_pausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - m_startTicks;
        }
    }
    
    return time;
}


