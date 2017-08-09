//
//  State.hpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <stdio.h>


template <class entity_type>
class State
{
public:
    virtual void Enter( entity_type* ) = 0;
    virtual void Execute( entity_type* ) = 0;
    virtual void Exit( entity_type* ) = 0;

protected: 
	virtual ~State();
};


