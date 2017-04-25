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

    ///@brief Motor driver configuration type
    static const EStepMode STEP_MODE = drvQuaterStep;

    /// @brief Max length of line in bytes
    static const uint16 BLOCK_MAX_LENGHT = 256;

    ///@brief Boundary limits of axis
    static const uint32 X_MAX = 288; /// [ mm ]
    static const uint32 Y_MAX = 190; /// [ mm ]
    static const uint32 Z_MAX = 80;  /// [ mm ]

    ///@brief Max values of working parameters
    static const uint32 F_MAX = 120; /// [ mm/min ]
    static const uint32 S_MAX = 800; /// [ rpm ]

    ///@brief
    static const uint8 FEEDRATE_ACCEL_PROFILE[5];
    static const uint8 FEEDRATE_DECEL_PROFILE[5];
    ///@brief
    static const uint8 SPEED_ACCEL_PROFILE[5];
    static const uint8 SPEED_DECEL_PROFILE[5];

public: /// METHODS

    ///@brief
    ///@param
    static uint8 get_FeedrateAccelFactor( const uint32 index );
    ///@brief
    ///@param
    static uint8 get_FeedrateDecelFactor( const uint32 index );
};

#endif /* INC_CCONFIG_H_ */
