//
//  App.cpp
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "GameEngine.h"
#include "GameState.h"

GameEngine::GameEngine()
{
    pWindow = nullptr;
    pRenderer = nullptr;
    
    m_timePrevious = m_timeNow = 0;
    
    m_time = 30; // milliseconds
    
    m_isRunning = true;
}

int GameEngine::Init( std::string windowName, int width = 800, int height = 600 )
{
    m_windowName = windowName;
    m_windowHeight = height;
    m_windowWidth = width;
    
    std::cout << "[SDL] - Initiating.. " << std::endl;
    
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        std::cout << "SDL_Init failed: " << SDL_GetError();
    }
    
    pWindow = SDL_CreateWindow( 
		m_windowName.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		m_windowWidth, 
		m_windowHeight, 
		SDL_WINDOW_OPENGL);
    if( pWindow == nullptr )
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		Cleanup();
		return 1;
    }
    
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED); // Vsync Disabled.
    if( pRenderer == nullptr )
    {
        SDL_DestroyWindow(pWindow);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		Cleanup();
		return 1;
    }
    
    // set default game background color
    SDL_SetRenderDrawColor(pRenderer, 243, 243, 243, 255);
    
    int imgFlags = IMG_INIT_PNG;
    if( !(IMG_Init(imgFlags) & imgFlags) )
    {
        std::cout << "SDL_image could not initialize : " << IMG_GetError() << std::endl;
		Cleanup();
		return 1;
    }
    
    if( TTF_Init() < 0 )
    {
        std::cout << "TTF Init failed: " << TTF_GetError() << std::endl;
		Cleanup();
		return 1;
    }
    
    pMainFont = TTF_OpenFont("Data/Nunito-Light.ttf", 24);
    if( pMainFont == nullptr )
    {
        std::cout << "Failed to load font " << TTF_GetError() << std::endl;
		Cleanup();
		return 1;
    }

	return 0;
}

void GameEngine::Run()
{
	while (m_isRunning)
	{
		SDL_PollEvent(&m_event);

		HandleEvents();

		m_timeNow = SDL_GetTicks();
		if (GetDeltaTime() > m_time)
		{
			Update();
			m_timePrevious = m_timeNow;
		}
		else
		{
			SDL_Delay(m_time - GetDeltaTime());
		}

		Render();
	}
}

void GameEngine::Cleanup()
{
    while( !m_gameStates.empty() )
    {
        m_gameStates.back()->Cleanup();
        m_gameStates.pop_back();
    }
    
	if (pRenderer != nullptr)
	{
		SDL_DestroyRenderer(pRenderer);
	}

	if (pWindow != nullptr)
	{
		SDL_DestroyWindow(pWindow);
	}

	if (pMainFont != nullptr)
	{
		TTF_CloseFont(pMainFont);
	}
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameEngine::ChangeState(GameState *state)
{
    if( !m_gameStates.empty() )
    {
        m_gameStates.back()->Cleanup();
        m_gameStates.pop_back();
    }
    
    m_gameStates.push_back(state);
    m_gameStates.back()->Init(this);
}

void GameEngine::PushState(GameState *state)
{
    if( !m_gameStates.empty() )
    {
        m_gameStates.back()->Pause();
    }
    
    m_gameStates.push_back(state);
    m_gameStates.back()->Init(this);
}

void GameEngine::PopState()
{
    if( !m_gameStates.empty() )
    {
        m_gameStates.back()->Cleanup();
        m_gameStates.pop_back();
    }
    
    if( !m_gameStates.empty() )
    {
        m_gameStates.back()->Resume();
    }
    else // Poping last gamestate, so, quit the game.
    {
        Quit();
    }
}

void GameEngine::HandleEvents()
{
	if (!m_gameStates.empty() && m_gameStates.back() != nullptr) 
	{
		m_gameStates.back()->HandleEvent(this, m_event);
	}
}

void GameEngine::Update()
{
	if (!m_gameStates.empty() && m_gameStates.back() != nullptr) 
	{
		m_gameStates.back()->Update(this);
	}
}

void GameEngine::Render()
{
	if (!m_gameStates.empty() && m_gameStates.back() != nullptr)
	{
		m_gameStates.back()->Render(this);
	}
}

void GameEngine::Load()
{
    std::cout << "Load some files.. " << std::endl;
}

void GameEngine::Save()
{
    std::cout << "Saving game.. maybe here.." << std::endl;
}

void GameEngine::Quit()
{
    Save();
    m_isRunning = false;
}


