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

#include "../inc/CConfig.h"

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
    static inline float MIN_INCREMENT()
    {
        return (unitMetric == mUnit) ? MIN_INCEMENT_METRIC : MIN_INCEMENT_IMPERIAL;
    }

    ///@brief
    ///@return
    static inline EDcimalFormat NUM_FORMAT()
    {
        return mDecimFormat;
    }

    ///@brief
    ///@return
    static inline bool IS_MODE_ABSOLUTE()
    {
        return (modeAbsolute == mMode);
    }

    ///@brief
    ///@return
    static inline bool IS_UNIT_METRIC()
    {
        return (unitMetric == mUnit);
    }

    ///@brief
    ///@return
    static inline float STEPS_FACTOR()
    {
        return ((unitMetric == mUnit) ? (MM_TO_STEPS*CConfig::STEP_MODE) : (MILS_TO_STEPS*CConfig::STEP_MODE));
    }

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

#endif  /// INC_CSETTINGS_H_
