//
//  GameEngine.h
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#if __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>

#elif _WIN32 || _WIN64

    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>

#endif

#include <iostream>
#include <string>
#include <vector>

class GameState;

class GameEngine
{
public:
    GameEngine( );
    
    int Init( std::string windowName, int width, int height );

    void Run();
    void Cleanup();
    
    void ChangeState( GameState *state );
    void PushState( GameState *state );
    void PopState( );
    
    void HandleEvents( );
    void Update( );
    void Render( );
    
    void Load();
    void Save();
    void Quit();
        
    SDL_Window* MainWindow( ) {
        return pWindow;
    }
    
    SDL_Renderer* MainRenderer( ) {
        return pRenderer;
    }
    
    TTF_Font* MainFont() {
        return pMainFont;
    }

	int GetDeltaTime() const { 
		return m_timeNow - m_timePrevious; 
	}
    
private:
    std::string m_windowName;
    
    int m_windowHeight;
    int m_windowWidth;
    int m_windowBits;
    
    bool m_isRunning;
    bool m_fullscreen;

	int m_time;
	int m_timeNow;
	int m_timePrevious;

	SDL_Event m_event;
    
    std::vector<GameState*> m_gameStates;
    
    SDL_Window* pWindow;
    
    SDL_Renderer* pRenderer;
    
    TTF_Font* pMainFont;
};

