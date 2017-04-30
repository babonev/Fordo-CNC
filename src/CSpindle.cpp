///=============================================================================
/// @file      CSpindle.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 30, 2017
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "CSpindle.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================


///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CSpindle::doMove( const CAxis::EAxisDir dir )
{
    mMoveDir = dir;
}

void CSpindle::set_spindle( const ESpindleState state )
{
    if ( state < essCount)
    {
        mState = state;
    }
}
