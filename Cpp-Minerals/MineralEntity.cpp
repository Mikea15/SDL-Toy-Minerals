//
//  MineralEntity.cpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#if __APPLE__

#include <SDL2/SDL.h>

#elif _WIN32 || _WIN64

#include <SDL.h>

#endif

#include "MineralEntity.h"



MineralEntity::MineralEntity( ) : GameObject()
{
    
}

MineralEntity::~MineralEntity()
{
    
}

void MineralEntity::LoadTexture( SDL_Renderer *renderer, std::string path )
{
    m_texture.LoadFromFile(renderer, path);
}

void MineralEntity::Start()
{
    
}

void MineralEntity::Update()
{
    float timestep = SDL_GetTicks() / 1000.0f;
    int transX = sin( timestep ) * 2.0f + cos( timestep ) * 2.0f;
    int transY = sin( timestep ) * 2.0f + cos( timestep ) * 2.0f;
    Translate( transX, transY );
}

void MineralEntity::Cleanup()
{
    
}


