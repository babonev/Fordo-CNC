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
#include "CSettings.h"
#include "DebugUtilities.h"

///=============================================================================
/// @brief
///=============================================================================
CAxis IMotionBlock::mAxis[aAxisCount];
uint32 IMotionBlock::mPauseCount = 0;
uint32 IMotionBlock::mFeedrate = 0;
uint32 IMotionBlock::mSpeed = 0;
uint32 IMotionBlock::mTool = 0;
IMotionBlock::EAxis IMotionBlock::mLeadingAxis = aAxisCount;
uint32 IMotionBlock::mActualFeedrate = 0;
uint32 IMotionBlock::mAxisDeltaSteps = 0;
uint32 IMotionBlock::mAxisHalfDeltaSteps = 0;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void IMotionBlock::init( void )
{
    mLeadingAxis = aAxisCount;
    mAxisDeltaSteps = 0;
    mAxisHalfDeltaSteps = 0;
    mActualFeedrate = 0;
}

IMotionBlock::~IMotionBlock()
{

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

void IMotionBlock::doStep( const EAxis axis, const CAxis::EAxisDir dir )
{
    if ( mLeadingAxis == axis )
    {
        /// Determine if acceleration or deceleration profile is needed
        if ( mAxisDeltaSteps > mAxisHalfDeltaSteps )
        {
            mActualFeedrate = (mFeedrate * CConfig::get_FeedrateAccelFactor(mAxisDeltaSteps)) / 100;
        }
        else
        {
            mActualFeedrate = (mFeedrate * CConfig::get_FeedrateDecelFactor(mAxisDeltaSteps)) / 100;
        }

        if ( mAxisDeltaSteps > 0 )
        {
            mAxisDeltaSteps--;
        }
    }
    else
    {
       if ( 0 == mActualFeedrate )
       {
           mActualFeedrate = mFeedrate >> 4;
       }
    }

    // TODO: Do the step with the calculated feed rate
}





