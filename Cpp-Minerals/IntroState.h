//
//  IntroState.hpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>

#include "GameState.h"

#include "Texture.h"

class IntroState : public GameState
{
    
public:

	void Init(GameEngine* game) override;
    void HandleEvent( GameEngine* game, SDL_Event event ) override;
    void Update( GameEngine* game ) override;
    void Render( GameEngine* game ) override;
    void Cleanup() override;
    
    void Pause() override;
    void Resume() override;
    

public:
	static IntroState Instance;
   
protected:
    IntroState();
    ~IntroState();
    
private:
    
    Texture m_text;
    SDL_Rect textDest;
    SDL_Texture *m_fontTexture;
    
    int m_time;
    int m_startTime;
    int m_timeToNextScreen;
};


