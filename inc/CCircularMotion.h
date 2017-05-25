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

#include "CAxis.h"

///
///@brief
//
class CCircularMotion
{
public:
    ///@brief
    virtual ~CCircularMotion();
    ///@brief
    virtual void init();
	///@brief
	virtual void execute();
    /// @brief
    /// @param
    virtual void set_radius( const float radius);
    /// @brief
    /// @param
    virtual void set_arcRadius( const float radius);
    /// @brief
    /// @param
    /// @param
    virtual void set_arcOffset( const EAxis axis, const float value );
    /// @brief
    /// @param
    virtual void set_direction( const EAxisDir dir );

protected:
    ///@brief
    static float mRadius;
    ///@brief
    static EAxisDir mCircleDirection;

private:
    ///@brief
    ///@return
    static uint32 calcDamperingProfile( void );
    ///@brief http://members.chello.at/~easyfilter/bresenham.html
    ///@param
    ///@param
    ///@param
    static void makeArc( const sint32 centerX, const sint32 centerY, const uint8 direction, const uint32 radius );
};

#endif /* INC_CMOTIONCIRCULAR_H_ */
