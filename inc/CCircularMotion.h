///=============================================================================
/// @file      CCircularMotion.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      20.Apr.2017
///
/// @copyright
///=============================================================================

#ifndef INC_CCIRCULARMOTION_H_
#define INC_CCIRCULARMOTION_H_

class IMotionBlock;

///
///@brief
//
class CCircularMotion : public IMotionBlock
{
public:
    ///@brief
    virtual ~CCircularMotion();
	///@brief
	virtual void process( void );
    ///@brief
	///@param
    virtual void set_motion( const EMotionMode motionMode);

    ///@brief
    ///@param
    void set_radius( const float radius);
    ///@brief
    ///@param
    ///@param
    void set_arcOffset( const EAxis axis, const float steps );

private:
    ///@brief
    float mRadius;

    ///@brief
    static uint32 calcDamperingProfile( void );

    ///@brief http://members.chello.at/~easyfilter/bresenham.html
    ///@param
    ///@param
    ///@param
    static void makeArc( const sint32 centerX, const sint32 centerY, const uint8 direction, const uint32 radius );
};

#endif /* INC_CMOTIONCIRCULAR_H_ */
