///=============================================================================
/// @file      CDriverAdapter.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 30, 2017
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "CDriverAdapter.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
ESwitchState CDriverAdapter::mState = eSwitchOFF;
float CDriverAdapter::mRetractPosition  = 0;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CDriverAdapter::execute()
{

}

void CDriverAdapter::doMove( const EAxis id, const EAxisDir dir, const uint32 feedrate )
{
    if ( id == aAxisZ )
    {
        if ( dir == mdForward )
        {
            setSpindle(eSwitchON);
        }
        else
        {
            setSpindle(eSwitchOFF);
        }
    }
    else
    {
        drawStep((int)dir, id, CDriverAdapter::mState);
    }
}

const ESwitchState CDriverAdapter::getSpindle()
{
    return CDriverAdapter::mState;
}

void CDriverAdapter::setSpindle( const ESwitchState state )
{
    if ( CDriverAdapter::mState != state )
    {
        CDriverAdapter::mState = state;
    }
}

