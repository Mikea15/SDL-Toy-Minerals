//
//  GameObject.cpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#include "GameObject.h"

#include <cassert>

int GameObject::m_nextvalidID = 0;
std::vector<GameObject*> GameObject::m_gameObjects = std::vector<GameObject*>();

void GameObject::SetID( )
{
    m_nextvalidID++;
    m_ID = m_nextvalidID;
}
