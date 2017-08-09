//
//  StateMachine.hpp
//  Minerals
//
//  Created by Michael Adaixo on 26/09/15.
//  Copyright © 2015 SkyBelow. All rights reserved.
//

#pragma once

#include <string>
#include <cassert>

#include "State.h"


template <class entity_type>
class StateMachine
{   
public:
    StateMachine( entity_type* owner ) : m_pOwner(owner), m_pCurrentState(nullptr), m_pPreviousState(nullptr), m_pGlobalState(nullptr)
    {}
        
    void SetCurrentState(State<entity_type> *state)
    {
        m_pCurrentState = state;
    }
        
    void SetGlobalState( State<entity_type> *state)
    {
        m_pGlobalState = state;
    }
        
    void SetPreviousState( State<entity_type> * state)
    {
        m_pPreviousState = state;
    }
        
    void Update() const
    {
		if (m_pGlobalState) 
		{
			m_pGlobalState->Execute(m_pOwner);
		}
            
		if (m_pCurrentState) 
		{
			m_pCurrentState->Execute(m_pOwner);
		}
    }
        
    void ChangeState( State<entity_type> *newState)
    {
        assert(newState && "Statemachine::ChangeState: trying to change to NULL state");
            
        m_pPreviousState = m_pCurrentState;
            
        m_pCurrentState->Exit(m_pOwner);
            
        m_pCurrentState = newState;
            
        m_pCurrentState->Enter(m_pOwner);
    }
        
    void RevertToPreviousState( )
    {
        ChangeState( m_pPreviousState );
    }
        
    bool IsInState( const State<entity_type> * state ) const
    {
        return typeid( *m_pCurrentState ) == typeid( state );
    }
        
    State<entity_type> * CurrentState() const {
        return m_pCurrentState;
    }
    State<entity_type> * PreviousState() const {
        return m_pPreviousState;
    }
    State<entity_type> * GlobalState() const {
        return m_pGlobalState;
    }

protected:
	virtual ~StateMachine();

private:
	entity_type *   m_pOwner;

	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;

};

