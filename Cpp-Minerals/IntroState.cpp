//
//  IntroState.cpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "IntroState.h"

#include "GameEngine.h"
#include "GameState.h"

#include "GameplayState.h"
#include "Vector2.h"

IntroState IntroState::Instance;

IntroState::IntroState()
{
    m_time = m_startTime = 0;
    m_timeToNextScreen = 3000; // 2 seconds
}

IntroState::~IntroState()
{

}

void IntroState::Init(GameEngine *game)
{
    // load all the things!
    std::cout << "Entering Intro State" << std::endl;
    
    m_text.LoadFromRenderedText(game->MainFont(), game->MainRenderer(), "Minerals", {0, 0, 0, 255});

    SDL_QueryTexture(m_text.GetTexture(), NULL, NULL, &textDest.w, &textDest.h);
    
    textDest.x = 800 * 0.5f - textDest.w * 0.5f;
    textDest.y = 600 * 0.5f - textDest.h * 0.5f;
    
    m_startTime = SDL_GetTicks();
    
    SDL_SetRenderDrawColor(game->MainRenderer(), 243, 243, 243, 255);
}

void IntroState::Cleanup()
{
    
}

void IntroState::Resume()
{
    
}

void IntroState::Pause()
{
    
}

void IntroState::HandleEvent(GameEngine *game, SDL_Event event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            game->Quit();
            break;
        
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    game->Quit();
                    break;
                default: break;
            }
            break;
        default: break;
    }
}

void IntroState::Update(GameEngine *game)
{
    if( SDL_TICKS_PASSED(SDL_GetTicks(), m_startTime + m_timeToNextScreen) )
    {
        std::cout << "Change state to gameplay please" << std::endl;
        game->ChangeState(&GameplayState::Instance);
    }
}

void IntroState::Render(GameEngine *game)
{
    // Clear the renderer
    SDL_RenderClear(game->MainRenderer());
    
    m_text.Render(game->MainRenderer(), Vector2(textDest.x, textDest.y));
    
    // Update screen
    SDL_RenderPresent(game->MainRenderer());
}
