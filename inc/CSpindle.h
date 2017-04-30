///=============================================================================
/// @file      CSpindle.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 30, 2017
///
/// @copyright
///=============================================================================

#ifndef INC_CSPINDLE_H_
#define INC_CSPINDLE_H_

#include "CAxis.h"

///
///@brief
///
class CSpindle
{
public:
    ///@brief
    typedef enum
    {
        essOFF,
        essON,
        essCount
    } ESpindleState;

    ///@brief
    void process();
    ///@brief
    void doMove( const CAxis::EAxisDir dir );
    ///@brief
    void set_spindle( const ESpindleState state );
private:
    ///@brief
    ESpindleState mState;
    ///@brief
    CAxis::EAxisDir mMoveDir;
    ///@brief
    float mRetractPosition;

};



#endif /* INC_CSPINDLE_H_ */
