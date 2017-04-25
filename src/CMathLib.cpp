///=============================================================================
/// @file      CMathLib.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 20, 2017
///
/// @copyright
///=============================================================================

#include "../inc/Std_Types.h"
#include "../inc/CMathLib.h"

///=============================================================================
/// @brief CONSTANTS
///=============================================================================
const float CMathLib::SQRT_MAGIC_F = 0x5f3759df;

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

float CMathLib::SQRT( const float param )
{
    const float xhalf = 0.5f*param;
    // get bits for floating value
    union
    {
      float x;
      int i;
    } u;

    u.x = param;
    u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0

    // Newton step, repeating increases accuracy
    return param*u.x*(1.5f - xhalf*u.x*u.x);
}
