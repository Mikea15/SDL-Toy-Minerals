//
//  main.cpp
//  Minerals
//
//  Created by Michael Adaixo on 23/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//
//



#if __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64

#include <SDL.h>

#endif

#include "GameEngine.h"
#include "IntroState.h"

#include <iostream>
#include <string>

std::string GetResourcePath( const std::string &subDir = "" )
{
#ifdef _WIN32 
    const char PATH_SEPARATOR = '\\';
#else
    const char PATH_SEPARATOR = '/';
#endif
    
    static std::string baseRes;
    if( baseRes.empty() )
    {
        char *basePath = SDL_GetBasePath();
        if( basePath != NULL )
        {
            baseRes = basePath;
            SDL_free(basePath);
        }
        else
        {
            std::cout << "Error getting resource path: " << SDL_GetError() << std::endl;
            return "";
        }
        
        size_t position = baseRes.rfind("bin");
        baseRes = baseRes.substr(0, position) + "res" + PATH_SEPARATOR;
    }
    
    return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEPARATOR;
}


int main(int argc, char * arg[])
{
    GameEngine pGame;

	if (pGame.Init("Minerals", 800, 600) == 0)
	{
		pGame.ChangeState(&IntroState::Instance);

		pGame.Run();

		pGame.Cleanup();
		pGame.Quit();

		return 0;
	}

	return 1;
}