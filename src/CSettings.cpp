///=============================================================================
/// @file      Csettings.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      01.Dec.2016
///
/// @copyright
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\CSettings.h"

///============================================================================
/// @brief
///============================================================================

/// @brief The lowest value that can be used in the selected metric system
const float CSettings::MIN_INCEMENT_METRIC = 0.001;
const float CSettings::MIN_INCEMENT_IMPERIAL = 0.0001;
const float CSettings::MM_TO_STEPS = 4.2;
const float CSettings::MILS_TO_STEPS = (0.0254 * 4.2);

/// @brief Declaration configuration storing members
CSettings::EMode CSettings::mode = modeAbsolute;
CSettings::EUnit CSettings::unit = unitMetric;
CSettings::EFormat CSettings::format = dfDecimalPoint;
CSettings::EStepMode CSettings::stepMode = drvQuaterStep;
float CSettings::retractPosition = (1.2 + 0.254);

///============================================================================
/// @brief
///============================================================================

/// @brief
/// @param
void CSettings::set_mode(const EMode systemMode)
{
    if ( systemMode < modeCount )
    {
        mode = systemMode;
    }
}

/// @brief
/// @param
void CSettings::set_unit(const EUnit systemUnit)
{
    if ( systemUnit < unitCount )
    {
        unit = systemUnit;
    }
}

/// @brief
/// @param
void CSettings::set_format(const EFormat systemFormat)
{
    if ( systemFormat < dfCount )
    {
        format = systemFormat;
    }
}

/// @brief
/// @param
void CSettings::set_retract_pos(const float pos)
{
    retractPosition = pos;
}
