///=============================================================================
/// @file      CLinearMotion.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      20.Apr.2017
///
/// @copyright
///=============================================================================

#ifndef INC_CLINEARMOTION_H_
#define INC_CLINEARMOTION_H_

#include "CAxis.h"

///
///@brief
///
class CLinearMotion
{
public:
    ///@brief
    virtual ~CLinearMotion();
    ///@brief
    virtual void init();
	/// @brief
	virtual void execute();
    ///@brief
    ///@param
    ///@param
    virtual void set_axisPos( const EAxis axis, const float value );

protected:
    ///@brief
    static CAxis mAxis[aAxisCount];
    ///@brief
    static EAxis mLeadingAxis;

private:
    ///@brief
    static void calcDamperingProfile( void );
    /// @brief Uses Bresenham's line algorithm to move both motors
    static void makeLine( void );

};

#endif /* INC_CMOTIONLINEAR_H_ */
