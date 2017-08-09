//
//  GameplayState.cpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "GameEngine.h"
#include "GameState.h"

#include "GameplayState.h"
#include "IntroState.h"

#include "Grid.h"

GameplayState GameplayState::Instance;

GameplayState::GameplayState()
{
    m_showDebugInfo = true;
    m_frameCount = 0;
    
    m_timeToPushBlock = TIME_TILL_NEW_BLOCK;
    m_mouseClickDownPrevious = false;
    
    m_grid = new Grid(8, 8, Vector2(90, 30));
}

GameplayState::~GameplayState()
{
    if( m_grid != NULL ) delete m_grid;
}

void GameplayState::Init(GameEngine *game)
{
    // load all the things!
    std::cout << "Entering Gameplay State" << std::endl;
    
    m_board.LoadFromFile(game->MainRenderer(), "Data/board.png");
    m_scoreRect.LoadFromFile(game->MainRenderer(), "Data/score_rect.png");
    m_scoreRect.SetWidth(140);
    
    // center screen.
    m_boardPosition = Vector2( 10.0f, 10.0f );
    
    // screen background color.
    SDL_SetRenderDrawColor(game->MainRenderer(), 243, 243, 243, 255);
    
    // setup board
    m_grid->Reset();
    m_grid->LoadResources(game->MainRenderer());
    m_grid->GenerateGrid();
    
    m_fpsTimer.Start();
    
    m_gameOver = false;
    
    m_scoreText.str("");
    m_score = 0;
    
    m_scoreText << m_score;
    
}

void GameplayState::Cleanup()
{
    m_grid->Cleanup();
    m_grid->Reset();
}

void GameplayState::Resume()
{
    
}

void GameplayState::Pause()
{
    
}

void GameplayState::HandleEvent(GameEngine *game, SDL_Event event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->Quit();
            break;
        
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym )
            {
                case SDLK_F1:
                    m_showDebugInfo = !m_showDebugInfo;
                    break;
                case SDLK_r:
                    m_grid->GenerateGrid();
                    break;
                case SDLK_ESCAPE:
                    game->Quit();
                    break;
                default: break;
            }
            break;
        case SDL_MOUSEMOTION:
            // call on mouse over.
            break;
        case SDL_MOUSEBUTTONDOWN:
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                m_mouseClickDownPrevious = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if( event.button.button == SDL_BUTTON_LEFT && m_mouseClickDownPrevious )
            {
                m_mouseClickDownPrevious = false;
                Vector2 mousePos = Vector2(event.button.x, event.button.y);
                ClickedCell(mousePos);
                
            }
            break;
        default: break;
    }
}

void GameplayState::ClickedCell( Vector2 position )
{
    int cellsPopped = m_grid->PopCellsAt(position.x, position.y);
    if( cellsPopped > 1 )
    {
        m_scoreText.str("");
        m_score += pow(SCORE_BONUS, cellsPopped);
        m_scoreText << m_score;
    }
}

void GameplayState::Update(GameEngine *game)
{
    float timeStep = m_time.GetTicks() / 1000.f;
    
    m_scoreTexture.LoadFromRenderedText(game->MainFont(), game->MainRenderer(), m_scoreText.str().c_str(), {0, 0, 0, 255});
    
    if( m_grid->CheckEndGame() )
    {
        game->ChangeState(&IntroState::Instance);
    }
    else
    {
        m_grid->Update(timeStep);
        
        m_currentTime += timeStep;
        if( m_currentTime > m_timeToPushBlock )
        {
            m_currentTime -= m_timeToPushBlock;
            m_grid->MakeNewBlock();
        }
    }
    
    m_time.Start();
}

void GameplayState::Render(GameEngine *game)
{
    // Clear the renderer
    SDL_RenderClear(game->MainRenderer());
    
    // Render Board
    
    m_board.Render(game->MainRenderer(), m_boardPosition );
    m_scoreRect.Render(game->MainRenderer(), m_boardPosition + Vector2(640, 0));
    
    m_grid->RenderGrid(game->MainRenderer());
    
    m_grid->RenderCells(game->MainRenderer());
    
    if( m_showDebugInfo ) {
        SDL_Rect textDest;
        SDL_QueryTexture(m_fontTexture, NULL, NULL, &textDest.w, &textDest.h);
        
        textDest.x = 0;
        textDest.y = 0;
        
        SDL_RenderCopy(game->MainRenderer(), m_fontTexture, NULL, &textDest);
    }
    
    m_scoreTexture.Render(game->MainRenderer(), Vector2(680, 40));
    
    // Update screen
    SDL_RenderPresent(game->MainRenderer());
    
    m_frameCount++;
}
