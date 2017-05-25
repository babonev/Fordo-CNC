///=============================================================================
/// @file      CLinearMotion.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 20, 2017
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "CLinearMotion.h"
#include "CAxis.h"
#include "CDriverAdapter.h"
#include "CMathLib.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
CAxis CLinearMotion::mAxis[aAxisCount] = { CAxis(aAxisX), CAxis(aAxisY), CAxis(aAxisZ) };
EAxis CLinearMotion::mLeadingAxis = aAxisCount;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

CLinearMotion::~CLinearMotion()
{

}

void CLinearMotion::init()
{
    mLeadingAxis = aAxisCount;
}

void CLinearMotion::execute()
{
    if ( (mAxis[aAxisX].deltaSteps() != 0) || (mAxis[aAxisY].deltaSteps() != 0) )
    {
        ///< Calculate feed rate acceleration factor
        calcDamperingProfile();

        ///< Move axis X and Y
        makeLine();
    }
}

void CLinearMotion::set_axisPos( const EAxis axis, const float value )
{
    mAxis[axis].position(value);
    CDebug::traceEvent(EVENT_AxisSet, value);
}

///=============================================================================
/// @brief PRIVATE METHODS
///=============================================================================

void CLinearMotion::calcDamperingProfile( void )
{
    const uint32 dX = mAxis[aAxisX].deltaSteps();
    const uint32 dY = mAxis[aAxisY].deltaSteps();

    if ( dX > dY )
    {
        mLeadingAxis = aAxisX;
    }
    else
    {
        mLeadingAxis = aAxisY;
    }
}

void CLinearMotion::makeLine( void )
{
    /// Direction to move
    const EAxisDir dirX = mAxis[aAxisX].direction();
    const EAxisDir dirY = mAxis[aAxisY].direction();
    /// Get absolute values
    const uint32 dX = mAxis[aAxisX].deltaSteps();
    const uint32 dY = mAxis[aAxisY].deltaSteps();
    /// Variables used in next calculations
    uint32 over = 0;
    uint32 i;

    if ( dX > dY )
    {
        for( i = 0; i < dX; ++i )
        {
            mAxis[aAxisX].doStep(dirX);
            over += dY;
            if ( over >= dX )
            {
                over -= dX;
                mAxis[aAxisY].doStep(dirY);
            }
        }
    }
    else
    {
        for( i = 0; i < dY; ++i )
        {
            mAxis[aAxisY].doStep(dirY);
            over += dX;
            if ( over >= dY )
            {
                over -= dY;
                mAxis[aAxisX].doStep(dirX);
            }
        }
    }
}

