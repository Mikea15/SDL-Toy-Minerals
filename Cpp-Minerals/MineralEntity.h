//
//  MineralEntity.hpp
//  Minerals
//
//  Created by Michael Adaixo on 27/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "GameObject.h"

class MineralEntity : public GameObject
{
public:
    MineralEntity( );
    ~MineralEntity( );
    
    void LoadTexture( SDL_Renderer *renderer, std::string path );
    
    void Start();
    void Update();
    void Cleanup();

};

