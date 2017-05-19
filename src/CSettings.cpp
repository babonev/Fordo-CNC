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

#include "Std_Types.h"
#include "CSettings.h"
#include "CConfig.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
CSettings::EMode CSettings::mMode = modeAbsolute;
CSettings::EUnit CSettings::mUnit = unitMetric;
CSettings::EDcimalFormat CSettings::mDecimFormat = dfDecimalPoint;
CSettings::ECommandFormat CSettings::mCmdFormat = cfCommandFormat_2;
float CSettings::retractPosition = (1.2 + 0.254);

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CSettings::set_default()
{
    mMode = modeAbsolute;
    mUnit = unitMetric;
    mDecimFormat = dfLeadingZeroes;
    mCmdFormat = cfCommandFormat_2;
    retractPosition = (1.2 + 0.254);
}

void CSettings::set_mode(const EMode mode)
{
    if ( mode < modeCount )
    {
        mMode = mode;
    }
}

void CSettings::set_unit(const EUnit unit)
{
    if ( unit < unitCount )
    {
        mUnit = unit;
    }
}

void CSettings::set_decimFormat(const EDcimalFormat format)
{
    if ( format < dfCount )
    {
        mDecimFormat = format;
    }
}

void CSettings::set_comandFormat(const ECommandFormat format)
{
    if ( format < cfCount )
    {
        mCmdFormat = format;
    }
}

void CSettings::set_retract_pos(const float pos)
{
    retractPosition = pos;
}

