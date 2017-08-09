//
//  FrameAnimator.cpp
//  Minerals
//
//  Created by Michael Adaixo on 25/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "FrameAnimator.h"

FrameAnimator::FrameAnimator(): 
	m_currentFrame(0), m_frameIncrement(1), 
	m_frameRate(100), m_maxFrames(0), 
	m_oldTime(0), m_oscillate(false)
{
}

void FrameAnimator::OnAnimate()
{
    int time = SDL_GetTicks();
    if( m_oldTime + m_frameRate > time )
    {
        return;
    }
    
    m_oldTime = time;
    m_currentFrame += m_frameIncrement;
    
    if( m_oscillate )
    {
        if( m_frameIncrement > 0 )
        {
            if( m_currentFrame >= m_maxFrames - 1 )
            {
                m_frameIncrement = -m_frameIncrement;
            }
        }
        else
        {
            if( m_currentFrame <= 0 )
            {
                m_frameIncrement = -m_frameIncrement;
            }
        }
    }
    else
    {
        if( m_currentFrame >= m_maxFrames - 1 )
        {
            m_currentFrame = 0;
        }
    }
}

void FrameAnimator::SetCurrentFrame( int frame )
{
    if( frame < 0 || frame >= m_maxFrames )
        return;
    
    m_currentFrame = frame;
}

void FrameAnimator::SetFramerate( int milliseconds )
{
    m_frameRate = milliseconds;
}


int FrameAnimator::GetCurrentFrame()
{
    return m_currentFrame;
}


