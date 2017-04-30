///=============================================================================
/// @file      CSettings.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      01.Dec.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CSETTINGS_H_
#define INC_CSETTINGS_H_

#include "CConfig.h"

///
///@brief File dependent values. Usually set from header.
///
class CSettings
{
public:
    ///@brief
    typedef enum
    {
        modeAbsolute,
        modeIncremental,
        modeCount
    } EMode;

    ///@brief
    typedef enum
    {
        unitMetric,
        unitImperial,
        unitCount
    } EUnit;

    ///@brief
    typedef enum
    {
        dfFullAddress,
        dfTrailingZeros,
        dfLeadingZeroes,
        dfDecimalPoint,
        dfCount
    } EDcimalFormat;

    ///@brief
    typedef enum
    {
        cfCommandFormat_1,
        cfCommandFormat_2,
        cfCount
    } ECommandFormat;

    ///@brief
    ///@param
    static void set_default();
    ///@brief
    ///@param
    static void set_mode(const EMode mode);
    ///@brief
    ///@param
    static void set_unit(const EUnit unit);
    ///@brief
    ///@param
    static void set_decimFormat(const EDcimalFormat format);
    ///@brief
    ///@param
    static void set_comandFormat(const ECommandFormat format);
    ///@brief
    ///@param
    static void set_retract_pos(const float pos);

    ///@brief
    ///@return
    static inline float MIN_INCREMENT();
    ///@brief
    ///@return
    static inline uint32 LZ_COUNT();
    ///@brief
    ///@return
    static inline uint32 TZ_COUNT();
    ///@brief
    ///@return
    static inline EDcimalFormat NUM_FORMAT();
    ///@brief
    ///@return
    static inline bool IS_MODE_ABSOLUTE();
    ///@brief
    ///@return
    static inline bool IS_UNIT_METRIC();
    ///@brief
    ///@return
    static inline float STEPS_FACTOR();

private:
    ///@brief The lowest value that can be used in the selected metric system
    static const float MIN_INCEMENT_METRIC;
    static const float MIN_INCEMENT_IMPERIAL;
    static const float MM_TO_STEPS;
    static const float MILS_TO_STEPS;

    ///@brief Configuration storing members
    static EMode mMode;
    static EUnit mUnit;
    static EDcimalFormat mDecimFormat;
    static ECommandFormat mCmdFormat;
    static float retractPosition;

};


inline float CSettings::MIN_INCREMENT()
{
    return (unitMetric == mUnit) ? MIN_INCEMENT_METRIC : MIN_INCEMENT_IMPERIAL;
}

inline uint32 CSettings::LZ_COUNT()
{
    return (unitMetric == mUnit) ? CConfig::METRIC_LZ : CConfig::INCH_LZ;
}

inline uint32 CSettings::TZ_COUNT()
{
    return (unitMetric == mUnit) ? CConfig::METRIC_TZ : CConfig::INCH_TZ;
}

inline CSettings::EDcimalFormat CSettings::NUM_FORMAT()
{
    return mDecimFormat;
}

inline bool CSettings::IS_MODE_ABSOLUTE()
{
    return (modeAbsolute == mMode);
}

inline bool CSettings::IS_UNIT_METRIC()
{
    return (unitMetric == mUnit);
}

inline float CSettings::STEPS_FACTOR()
{
    return ((unitMetric == mUnit) ? (MM_TO_STEPS*CConfig::STEP_MODE) : (MILS_TO_STEPS*CConfig::STEP_MODE));
}

#endif  /// INC_CSETTINGS_H_
