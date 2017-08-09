//
//  GameState.h
//  Minerals
//
//  Created by Michael Adaixo on 25/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include "GameEngine.h"

class GameState
{
public:

    virtual void Init( GameEngine *game) = 0;
    virtual void HandleEvent( GameEngine *game, SDL_Event event ) = 0;
    virtual void Update( GameEngine *game ) = 0;
    virtual void Render( GameEngine *game ) = 0;
    virtual void Cleanup() = 0;
    
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    
    void ChangeState( GameEngine *game, GameState *state )
    {
        game->ChangeState(state);
    }
        
protected:
    GameState() 
	{
	};

};

