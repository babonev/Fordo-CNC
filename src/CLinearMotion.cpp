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

#include "../inc/Std_Types.h"
#include "../inc/IMotionBlock.h"
#include "../inc/CLinearMotion.h"
#include "../inc/CAxis.h"
#include "../inc/CMathLib.h"
#include "../inc/DebugUtilities.h"

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

CLinearMotion::~CLinearMotion()
{

}

void CLinearMotion::process( void )
{
    /// 1) Decide if Z will be working
    if ( mtRapidPositioning == mMotionMode )
    {
        /// TODO: 2) Retract Z
    }
    else
    {
        /// TODO: 2) Put into working state Z if retracted
    }

    /// 3) Calculate feed rate acceleration factor
    calcDamperingProfile();

    /// 4) Move axis X and Y
    makeLine();
}

void CLinearMotion::set_motion( const EMotionMode motionMode )
{
    if ( (mtRapidPositioning == motionMode) || (mtLinearInterpolation == motionMode) )
    {
        mMotionMode = motionMode;
    }
}

void CLinearMotion::set_axisPos( const EAxis axis, const float value )
{
    mAxis[axis].position(value);
}

///=============================================================================
/// @brief PRIVATE METHODS
///=============================================================================

void CLinearMotion::calcDamperingProfile( void )
{
    const uint32 dX = mAxis[aAxisX].deltaStepsABS();
    const uint32 dY = mAxis[aAxisY].deltaStepsABS();

    if ( dX > dY )
    {
        mLeadingAxis = aAxisX;
        mAxisDeltaSteps = dX;
    }
    else
    {
        mLeadingAxis = aAxisY;
        mAxisDeltaSteps = dY;
    }

    mAxisHalfDeltaSteps = mAxisDeltaSteps >> 1;
}

void CLinearMotion::makeLine( void )
{
    /// Direction to move
    const CAxis::EAxisDir dirX = mAxis[aAxisX].direction();
    const CAxis::EAxisDir dirY = mAxis[aAxisX].direction();
    /// Get absolute values
    const uint32 dX = mAxis[aAxisX].deltaStepsABS();
    const uint32 dY = mAxis[aAxisY].deltaStepsABS();
    /// Variables used in next calculations
    uint32 over = 0;
    uint32 i;

    if ( dX > dY )
    {
        for( i = 0; i < dX; ++i )
        {
        	doStep(aAxisX, dirX);
            over += dY;
            if ( over >= dX )
            {
                over -= dX;
                doStep(aAxisY, dirY);
            }
        }
    }
    else
    {
        for( i = 0; i < dY; ++i )
        {
        	doStep(aAxisX, dirY);
            over += dX;
            if ( over >= dY )
            {
                over -= dY;
                doStep(aAxisY, dirX);
            }
        }
    }
}
