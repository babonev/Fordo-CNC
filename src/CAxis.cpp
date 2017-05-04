///=============================================================================
/// @file      Axis.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      22.Apr.2017
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "CAxis.h"
#include "CMathLib.h"
#include "CSettings.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================


///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CAxis::position( const float offset )
{
    if ( CSettings::IS_MODE_ABSOLUTE() )
    {
        mDeltaPosition = mPosition + offset;
        mPosition = offset;
    }
    else
    {
        mDeltaPosition = offset;
        mPosition = mPosition + offset;
    }

    mDeltaSteps = distanceInSteps(mDeltaPosition);
    /// TODO: Check if less than max possible
}


sint32 CAxis::deltaSteps( void )
{
    return mDeltaSteps;
}

uint32 CAxis::deltaStepsABS( void )
{
    return CMathLib::ABS(mDeltaSteps);
}

EAxisDir CAxis::direction( void )
{
    return (mDeltaSteps > 0) ? (mdForward) : (mdBackward);
}

///=============================================================================
/// @brief PRIVATE METHODS
///=============================================================================

sint32 CAxis::distanceInSteps( const float newPos )
{
    sint32 stepsToMove = 0;

    /// Convert distance to steps
    float pos = (newPos * CSettings::STEPS_FACTOR()) + mError;

    /// Store final position
    mSteps += pos;
    /// Partial steps cannot be executed
    stepsToMove = static_cast<sint32>(pos);
    /// Calculate conversion error
    mError = (pos - stepsToMove);

    return stepsToMove;
}
