///=============================================================================
/// @file      CPositioning.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      06.Nov.2016
///
/// @copyright
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\CPositioning.h"
#include "..\inc\CSettings.h"
#include "..\inc\CMotion.h"

///============================================================================
/// @brief
///============================================================================
CPositioning::SMotion CPositioning::moveSequence = { 0 };
float CPositioning::position[CPositioning::aAxisCount] = { 0 };
float CPositioning::error[CPositioning::aAxisCount] = { 0 };

///============================================================================
/// @brief
///============================================================================

/// @brief Convert to number of steps the offset of current position
/// @param New coordinate in current mode and unit
/// @param Axis id
/// @return Signed offset of current position
sint32 CPositioning::distanceInSteps( const float newPos, const CPositioning::EAxis axis )
{
    sint32 stepsToMove = 0;

    /// Error check
    if ( aAxisCount > axis )
    {
        /// Convert distance to steps
        float pos = (newPos * CSettings::STEPS_FACTOR()) + error[axis];

        if ( CSettings::IS_MODE_ABSOLUTE() )
        {
            /// Absolute mode
            pos = pos - position[axis];
        }

        /// Store final position
        position[axis] += pos;
        /// Partial steps cannot be executed
        stepsToMove = static_cast<sint32>(pos);
        /// Calculate conversion error
        error[axis] = (pos - stepsToMove);
    }

    return stepsToMove;
}

/// @brief Convert to number of steps a distance in current unit
/// @param New coordinate in current mode and unit
/// @return Signed offset of current position
sint32 CPositioning::distanceInSteps( const float dist )
{
    return (dist * CSettings::STEPS_FACTOR());
}

/// @brief
/// @param
/// @param
void CPositioning::set_deltaAxis( const float newPos, const CPositioning::EAxis axis )
{
    moveSequence.steps[axis] = distanceInSteps(newPos, axis);
    moveSequence.updated |= (umAxisX << axis);
}

/// @brief
/// @param
/// @param
void CPositioning::set_arcOffset( const float newVal, const CPositioning::EAxis axis )
{
    moveSequence.arcOffset[axis] = distanceInSteps(newVal);
    moveSequence.updated |= (umArcOffsetX << axis);
}

/// @brief
/// @param
void CPositioning::set_radius( const float radius )
{
    moveSequence.radius = distanceInSteps(radius);
    moveSequence.updated |= umRadius;
}

/// @brief
/// @param
/// @param
void CPositioning::set_cycle( const ECycle type, const bool active)
{
    moveSequence.cycle = type;
    moveSequence.updated |= umCycle;
}

/// @brief
/// @param
void CPositioning::set_pause( const uint16 time)
{
    moveSequence.pausetime = time;
    moveSequence.updated |= umPause;
}

/// @brief
/// @param
void CPositioning::set_speed( const float speed )
{
    moveSequence.speed = speed;
    moveSequence.updated |= umSpeed;
}

/// @brief
/// @param
void CPositioning::set_tool( const float tool )
{
    moveSequence.tool = tool;
    moveSequence.updated |= umTool;
}

/// @brief
/// @param
void CPositioning::set_feedrate( const float feedrate )
{
    moveSequence.feedrate = feedrate;
    moveSequence.updated |= umFeedrate;
}

/// @brief
/// @param
void CPositioning::set_motion( const EMoveType type)
{
    moveSequence.type = type;
    moveSequence.updated |= umMotionType;
}

/// @brief
void CPositioning::makeMove()
{
    CMotion::initMove();

    switch(moveSequence.type)
    {
    case mtRapidPositioning:
        CMotion::moveSpindle(20);
        CMotion::makeLine(moveSequence.steps[aAxisX], moveSequence.steps[aAxisY]);
        break;
    case mtLinearInterpolation:
        CMotion::moveSpindle(0);
        CMotion::makeLine(moveSequence.steps[aAxisX], moveSequence.steps[aAxisY]);
        break;
    case mtCircularInterpolationCW:
        /// Z to 0
        /// makeArc   X, Y, CMotion::arcClockwise,
        break;
    case mtCircularInterpolationCCW:
        /// Z to 0
        /// makeArc   X, Y, CMotion::arcCounterClockwise,
        break;
    case mtDwell:
        /// Fill with zeroes for a P ms
        break;
    default:
        break;
    }
}
