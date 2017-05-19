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
ESwitchState CDriverAdapter::mState = eSwitchStateCount;
EAxisDir CDriverAdapter::mMoveDir = mdNoMove;
float CDriverAdapter::mRetractPosition  = 0;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CDriverAdapter::execute()
{

}

void CDriverAdapter::doMoveX( const EAxisDir dir, const uint32 feedrate )
{
    drawStep((int)dir, 0, CDriverAdapter::mState);
}

void CDriverAdapter::doMoveY( const EAxisDir dir, const uint32 feedrate )
{
    drawStep((int)dir, 1, CDriverAdapter::mState);
}

void CDriverAdapter::doMoveZ( const EAxisDir dir, const uint32 feedrate )
{
    CDriverAdapter::mMoveDir = dir;
}

void CDriverAdapter::set_spindle( const ESwitchState state )
{
    if ( state < eSwitchStateCount)
    {
        CDriverAdapter::mState = state;
    }
}

