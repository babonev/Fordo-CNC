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
#include "CDriverAdapter.h"
#include "CMathLib.h"
#include "CConfig.h"
#include "CSettings.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
CAxis::CAxis( const EAxis id ) : mID(id)
{
    mDeltaSteps = 0;
    mPosition = 0;
    mError = 0;
    mSteps = 0;
    mDeltaPosition = 0;
    mHalfDeltaSteps = 0;
    mDirection = mdNoMove;
}

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CAxis::position( const float newPos )
{
    if ( CSettings::IS_MODE_ABSOLUTE() )
    {
        if ( newPos > mPosition )
        {
            mDeltaPosition = -(mPosition - newPos);
            mDirection = mdForward;
        }
        else if ( newPos < mPosition )
        {
            mDeltaPosition = -(newPos - mPosition);
            mDirection = mdBackward;
        }
        else
        {
            mDirection = mdNoMove;
        }

        mPosition = newPos;
    }
    else
    {
        mDeltaPosition = newPos;
        mPosition = mPosition + newPos;
    }

    mDeltaSteps = distanceInSteps(mDeltaPosition);
    mHalfDeltaSteps = mDeltaSteps >> 1;
    /// TODO: Check if less than max possible
}


uint32 CAxis::deltaSteps( void )
{
    return mDeltaSteps;
}

EAxisDir CAxis::direction( void )
{
    return mDirection;
}

void CAxis::doStep( const EAxisDir dir )
{
    uint32 actualFeedrate;

    /// Determine if acceleration or deceleration profile is needed
    if ( mDeltaSteps > mHalfDeltaSteps )
    {
        actualFeedrate = CConfig::get_FeedrateAccelFactor(mDeltaSteps) / 100;
    }
    else
    {
        actualFeedrate = CConfig::get_FeedrateDecelFactor(mDeltaSteps) / 100;
    }

    if ( mDeltaSteps > 0 )
    {
        mDeltaSteps--;
    }

    CDriverAdapter::doMove(mID, dir, actualFeedrate);
}

///=============================================================================
/// @brief PROTECTED METHODS
///=============================================================================

void CAxis::finalize( void )
{
    mDeltaPosition = 0;
    mDeltaSteps = 0;
    mHalfDeltaSteps = 0;
    mDirection = mdNoMove;
}

///=============================================================================
/// @brief PRIVATE METHODS
///=============================================================================

uint32 CAxis::distanceInSteps( const float newPos )
{
    sint32 stepsToMove = 0;

    /// Convert distance to steps
    float pos = (newPos * CSettings::STEPS_FACTOR()) + mError;

    /// Partial steps cannot be executed
    stepsToMove = static_cast<sint32>(pos);
    /// Store final position
    mSteps += stepsToMove;
    /// Calculate conversion error
    mError = (pos - stepsToMove);

    return stepsToMove;
}
