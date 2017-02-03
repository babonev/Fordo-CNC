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

class CSettings
{
public:
    ///
    typedef enum
    {
        modeAbsolute,
        modeIncremental,
        modeCount
    } EMode;

    ///
    typedef enum
    {
        unitMetric,
        unitImperial,
        unitCount
    } EUnit;

    ///
    typedef enum
    {
        dfFullAddress,
        dfTrailingZeros,
        dfLeadingZeroes,
        dfDecimalPoint,
        dfCount
    } EFormat;

    ///
    typedef enum
    {
        drvOneStep,         /// 1/1 - step
        drvHalfStep,        /// 1/2 - step
        drvQuaterStep,      /// 1/4 - step
        drvEighthStep,      /// 1/8 - step
        drvStepModeCount
    } EStepMode;

    /// Functions setting configuration properties
    static void set_mode(const EMode systemMode);
    static void set_unit(const EUnit systemUnit);
    static void set_format(const EFormat systemFormat);
    static void set_retract_pos(const float pos);

private:
    /// Constants
    static const float MIN_INCEMENT_METRIC;
    static const float MIN_INCEMENT_IMPERIAL;
    static const float MM_TO_STEPS;
    static const float MILS_TO_STEPS;

    /// Current configuration
    static EMode mode;
    static EUnit unit;
    static EFormat format;
    static EStepMode stepMode;
    static float retractPosition;

public:
    /// @brief
    /// @return
    static inline float MIN_INCREMENT()
    {
        return (unitMetric == unit) ? MIN_INCEMENT_METRIC : MIN_INCEMENT_IMPERIAL;
    }

    /// @brief
    /// @return
    static inline EFormat NUM_FORMAT()
    {
        return format;
    }

    /// @brief
    /// @return
    static inline bool IS_MODE_ABSOLUTE()
    {
        return (modeAbsolute == mode);
    }

    /// @brief
    /// @return
    static inline bool IS_UNIT_METRIC()
    {
        return (unitMetric == unit);
    }

    /// @brief
    /// @return
    static inline float STEPS_FACTOR()
    {
        return ((unitMetric == unit) ? (MM_TO_STEPS*stepMode) : (MILS_TO_STEPS*stepMode));
    }
};

#endif  /// INC_CSETTINGS_H_
