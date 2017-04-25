///=============================================================================
/// @file      CConfig.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      23.Apr.2017
///
/// @copyright
///=============================================================================

#include "../inc/Std_Types.h"
#include "../inc/CSettings.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
const uint8 CConfig::FEEDRATE_ACCEL_PROFILE[5] = { 24, 40, 56, 72, 100 };
const uint8 CConfig::FEEDRATE_DECEL_PROFILE[5] = { 100, 84, 68, 52, 24 };
const uint8 CConfig::SPEED_ACCEL_PROFILE[5] = { 20, 30, 40, 50, 100 };
const uint8 CConfig::SPEED_DECEL_PROFILE[5] = { 100, 80, 60, 40, 20 };

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

uint8 CConfig::get_FeedrateAccelFactor( const uint32 index )
{
    uint8 factor;

    if ( index < sizeof(FEEDRATE_ACCEL_PROFILE) )
    {
        factor = FEEDRATE_ACCEL_PROFILE[index];
    }
    else
    {
        factor = FEEDRATE_ACCEL_PROFILE[sizeof(FEEDRATE_ACCEL_PROFILE) - 1];
    }

    return factor;
}

uint8 CConfig::get_FeedrateDecelFactor( const uint32 index )
{
    uint8 factor;

    if ( index < sizeof(FEEDRATE_DECEL_PROFILE) )
    {
        factor = FEEDRATE_DECEL_PROFILE[index];
    }
    else
    {
        factor = FEEDRATE_DECEL_PROFILE[sizeof(FEEDRATE_DECEL_PROFILE) - 1];
    }

    return factor;
}

