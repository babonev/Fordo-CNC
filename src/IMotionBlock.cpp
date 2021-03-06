///=============================================================================
/// @file      IMotionBlock.cpp
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
#include "CDriverAdapter.h"
#include "CSettings.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
CAxis IMotionBlock::mAxis[aAxisCount];
float IMotionBlock::mRadius = 0;
EAxisDir IMotionBlock::mCircleDirection = mdNoMove;
uint32 IMotionBlock::mPauseCount = 0;
uint32 IMotionBlock::mFeedrate = 0;
uint32 IMotionBlock::mSpeed = 0;
uint32 IMotionBlock::mTool = 0;
EAxis IMotionBlock::mLeadingAxis = aAxisCount;
uint32 IMotionBlock::mAxisDeltaSteps = 0;
uint32 IMotionBlock::mAxisHalfDeltaSteps = 0;
bool IMotionBlock::mFastMode = false;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void IMotionBlock::init( void )
{
    mLeadingAxis = aAxisCount;
    mAxisDeltaSteps = 0;
    mAxisHalfDeltaSteps = 0;
}

IMotionBlock::~IMotionBlock()
{

}

void IMotionBlock::execute( void )
{
    for( uint32 a = aAxisX; a < aAxisCount; a++)
    {
        mAxis[static_cast<EAxis>(a)].finalize();
    }

    mRadius = 0;
}

void IMotionBlock::set_motion( const EMotionMode motionMode )
{
    if ( motionMode < mmCount )
    {
        /// Set to false because it is set to true only in one case
        mFastMode = false;

        switch(motionMode)
        {
        case mmRapidPositioning:
            mFastMode = true;
            /// TODO: Spindle up
            break;
        default:
            break;
        }
    }
}

void IMotionBlock::set_axisPos( const EAxis axis, const float value )
{
    mAxis[axis].position(value);
    CDebug::traceEvent(EVENT_AxisSet, value);
}

void IMotionBlock::set_radius( const float radius)
{
    /// Error handler. Should not enter here.
    CDebug::reportErrorLine(ERROR_Invalid_Motion);
}

void IMotionBlock::set_arcRadius( const float radius)
{
    /// Error handler. Should not enter here.
    CDebug::reportErrorLine(ERROR_Invalid_Motion);
}

void IMotionBlock::set_arcOffset( const EAxis axis, const float value )
{
    /// Error handler. Should not enter here.
    CDebug::reportErrorLine(ERROR_Invalid_Motion);
}

void IMotionBlock::set_cycle( const ECycle type, const bool active)
{
    /// TODO: Implement "cycle
}

void IMotionBlock::set_direction( const EAxisDir dir )
{
    mCircleDirection = dir;
}

void IMotionBlock::set_pause( const uint32 time)
{
    mPauseCount = time;
    CDebug::traceEvent(EVENT_PauseSet, mPauseCount);
}

void IMotionBlock::set_speed( const float speed )
{
    mSpeed = static_cast<uint32>(speed);
    CDebug::traceEvent(EVENT_SpeedChanged, mSpeed);
}

void IMotionBlock::set_tool( const uint16 tool )
{
    mTool = tool;
    CDebug::traceEvent(EVENT_ToolChanged, mTool);
}

void IMotionBlock::set_feedrate( const float feedrate )
{
    mFeedrate = static_cast<uint32>(feedrate);
    CDebug::traceEvent(EVENT_FeedrateChanged, mFeedrate);
}

///=============================================================================
/// @brief PROTECTED METHODS
///=============================================================================

sint32 IMotionBlock::convertToSteps( const float dist )
{
    return (dist * CSettings::STEPS_FACTOR());
}

void IMotionBlock::doStep( const EAxis axis, const EAxisDir dir )
{
    uint32 actualFeedrate;

    /// Spindle axis movement is individual
    if ( aAxisZ != axis )
    {
        /// If a RapidMotion is selected, move as fast as possible
        if ( mFastMode )
        {
            /// Determine if acceleration or deceleration profile is needed
            if ( mAxisDeltaSteps > mAxisHalfDeltaSteps )
            {
                actualFeedrate = (mFeedrate * CConfig::get_FeedrateAccelFactor(mAxisDeltaSteps)) / 100;
            }
            else
            {
                actualFeedrate = (mFeedrate * CConfig::get_FeedrateDecelFactor(mAxisDeltaSteps)) / 100;
            }
        }
        else
        {
            actualFeedrate = CConfig::F_MAX;
        }
    }
    else
    {
       actualFeedrate = CConfig::Z_F_MAX;
    }

    if ( mAxisDeltaSteps > 0 )
    {
        mAxisDeltaSteps--;
    }

    // Do the step with the calculated feed rate
    switch(axis)
    {
    case aAxisX:
        CDriverAdapter::doMoveX(dir, actualFeedrate);
        break;
    case aAxisY:
        CDriverAdapter::doMoveY(dir, actualFeedrate);
        break;
    default:
        // Do nothing
        break;
    }
}





