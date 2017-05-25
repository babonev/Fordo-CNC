///=============================================================================
/// @file      CDriverAdapter.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 30, 2017
///
/// @copyright
///=============================================================================

#ifndef INC_CDRIVERADAPTER_H_
#define INC_CDRIVERADAPTER_H_

#include "CAxis.h"

///@brief
typedef enum
{
    eSwitchOFF = false,
    eSwitchON = true
} ESwitchState;

///
///@brief
///
class CDriverAdapter
{
public:
    ///@brief
    static void execute();
    ///@brief
    static const ESwitchState getSpindle();
    ///@brief
    ///@param
    static void setSpindle( const ESwitchState state );
    ///@brief
    ///@param
    ///@param
    ///@param
    static void doMove( const EAxis id, const EAxisDir dir, const uint32 feedrate );

private:
    ///@brief
    static ESwitchState mState;
    ///@brief
    static float mRetractPosition;
};

void drawStep( int dir, int axis, int state );

#endif /* INC_CDRIVERADAPTER_H_ */
