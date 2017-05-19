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
#include "IMotionBlock.h"
#include "CLinearMotion.h"
#include "CAxis.h"
#include "CMathLib.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

CLinearMotion::~CLinearMotion()
{

}

void CLinearMotion::execute( void )
{
    if ( (mAxis[aAxisX].deltaSteps() != 0) || (mAxis[aAxisY].deltaSteps() != 0) )
    {
        /// 3) Calculate feed rate acceleration factor
        calcDamperingProfile();

        /// 4) Move axis X and Y
        makeLine();

        /// 5) Finalize move
        IMotionBlock::execute();
    }
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
    const EAxisDir dirX = mAxis[aAxisX].direction();
    const EAxisDir dirY = mAxis[aAxisX].direction();
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
        	doStep(aAxisY, dirY);
            over += dX;
            if ( over >= dY )
            {
                over -= dY;
                doStep(aAxisX, dirX);
            }
        }
    }
}

