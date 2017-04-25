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

class IMotionBlock;

///
///@brief
//
class CLinearMotion : public IMotionBlock
{
public:
    ///@brief
    virtual ~CLinearMotion();
	/// @brief
	virtual void process( void );
    ///@brief
	///@param
    virtual void set_motion( const EMotionMode motionMode);

    ///@brief
    ///@param
    ///@param
    virtual void set_axisPos( const EAxis axis, const float value );

private:

    ///@brief
    static void calcDamperingProfile( void );
    /// @brief Uses Bresenham's line algorithm to move both motors
    /// @param
    /// @param
    static void makeLine( void );
};

#endif /* INC_CMOTIONLINEAR_H_ */
