///=============================================================================
/// @file      CConfig.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      22.Apr.2017
///
/// @copyright
///=============================================================================
#ifndef INC_CCONFIG_H_
#define INC_CCONFIG_H_

///
/// SOURCE: https://web.archive.org/web/20071030075236/http://www.excellon.com/manuals/program.htm
///

///
///@brief Holds constant values hardware dependent
///
class CConfig
{
public: /// TYPES

    ///@brief Motor driver mode
    typedef enum
    {
        drvOneStep,         /// 1/1 - step
        drvHalfStep,        /// 1/2 - step
        drvQuaterStep,      /// 1/4 - step
        drvEighthStep,      /// 1/8 - step
        drvStepModeCount
    } EStepMode;

public: /// DATA MEMBERS
    /// @brief Max length of line in bytes
    static const uint16 BLOCK_MAX_LENGHT = 256;

    ///@brief Metric coordinates can be measured in microns (thousandths of a millimeter). Six digit micron resolution (000.000)
    static char const * const METRIC_FORMAT;
    ///@brief Inch coordinates are in six digits (00.0000) with increments as small as 0.0001 (1/10,000)
    static char const * const INCH_FORMAT;

    ///@brief Used in reading numbers from file
    static const uint32 METRIC_LZ = 3;
    static const uint32 METRIC_TZ = 3;
    static const uint32 INCH_LZ = 2;
    static const uint32 INCH_TZ = 4;

    ///@brief Motor driver configuration type
    static const EStepMode STEP_MODE = drvQuaterStep;

    ///@brief Boundary limits of axis
    static const uint32 X_MAX = 288; /// [ mm ]
    static const uint32 Y_MAX = 190; /// [ mm ]
    static const uint32 Z_MAX = 80;  /// [ mm ]

    ///@brief Max values of working parameters
    static const uint32 F_MAX = 120; /// [ mm/min ]
    static const uint32 S_MAX = 800; /// [ rpm ]
    static const uint32 Z_F_MAX = 40; /// [ mm/min ]

    ///@brief The lowest value that can be used in the selected metric system
    static const float MIN_INCEMENT_METRIC;
    static const float MIN_INCEMENT_IMPERIAL;
    static const float MM_TO_STEPS;
    static const float MILS_TO_STEPS;

    ///@brief
    static const uint8 FEEDRATE_ACCEL_PROFILE[5];
    static const uint8 FEEDRATE_DECEL_PROFILE[5];
    ///@brief
    static const uint8 SPEED_ACCEL_PROFILE[5];
    static const uint8 SPEED_DECEL_PROFILE[5];

public: /// METHODS

    ///@brief
    ///@param
    ///@return
    static uint8 get_FeedrateAccelFactor( const uint32 index );
    ///@brief
    ///@param
    ///@return
    static uint8 get_FeedrateDecelFactor( const uint32 index );
};

#endif /* INC_CCONFIG_H_ */
