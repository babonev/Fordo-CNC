///=============================================================================
/// @file      Axis.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      22.Apr.2017
///
/// @copyright
///=============================================================================

#ifndef INC_CAXIS_H_
#define INC_CAXIS_H_

/// @brief
typedef enum
{
    mdForward = 1,
    mdNoMove = 0,
    mdBackward = -1
} EAxisDir;

///
///@brief
//
class CAxis
{
public:

    ///@brief
    ///@param
    void position( const float offset );

    ///@brief
    ///@return
    uint32 deltaSteps();

    ///@brief
    ///@return
    EAxisDir direction();

    ///@brief
    void finalize();

private:
    ///@brief New offset of axis in measurement units
    float mDeltaPosition;    /// [units: mil/mm]
    ///@brief Current position of axis in measurement units
    float mPosition;         /// [units: mil/mm]
    ///@brief Current position of axis in step
    uint32 mDeltaSteps;      /// [steps]
    ///@brief Current position of axis in step
    sint32 mSteps;           /// [steps]
    ///@brief
    EAxisDir mDirection;
    ///@brief Cumulative error from calculations
    float mError;            /// [steps]

    ///@brief
    ///@param
    ///@return
    uint32 distanceInSteps( const float newPos );
};

#endif /* INC_CAXIS_H_ */
