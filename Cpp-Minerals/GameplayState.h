//
//  GameplayState.hpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include "GameState.h"

#include "Texture.h"

#include "Timer.h"

#include "Vector2.h"

class Grid;
class IntroState;
class GameObject;
class MineralEntity;

#define SCORE_BONUS 2
#define TIME_TILL_NEW_BLOCK 1
#define TIME_TILL_NEW_GAME 2

class GameplayState : public GameState
{
    
public:

    void Init(GameEngine* game);
    void HandleEvent( GameEngine* game, SDL_Event event );
    void Update( GameEngine* game );
    void Render( GameEngine* game );
    void Cleanup();
    
    void ClickedCell( Vector2 position );
    
    void Pause();
    void Resume();
    
protected:
    GameplayState();

    ~GameplayState();

public:
	static GameplayState Instance;
    
private:
    
    Grid *m_grid;
    
    Texture m_board;
    Vector2 m_boardPosition;
    
    SDL_Texture *m_fontTexture;
    
    Texture m_scoreRect;
    
    Timer m_time;
    float m_timeToPushBlock;
    float m_currentTime;
    
    float m_timeToBeginNew;
    
    Timer m_fpsTimer;
    std::stringstream m_timeText;
    
    int m_score;
    std::stringstream m_scoreText;
    Texture m_scoreTexture;
    
    bool m_gameOver;
    Texture m_gameOverText;
    
    int m_frameCount;
    
    bool m_showDebugInfo;
    
    bool m_mouseClickDownPrevious;
};


