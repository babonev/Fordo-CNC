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
    eSwitchOFF,
    eSwitchON,
    eSwitchStateCount
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
    static void set_spindle( const ESwitchState state );
    ///@brief
    static void doMoveX( const EAxisDir dir, const uint32 feedrate );
    ///@brief
    static void doMoveY( const EAxisDir dir, const uint32 feedrate );
    ///@brief
    static void doMoveZ( const EAxisDir dir, const uint32 feedrate );

private:
    ///@brief
    static ESwitchState mState;
    ///@brief
    static EAxisDir mMoveDir;
    ///@brief
    static float mRetractPosition;
};

void drawStep( int dir, int axis, int state );

#endif /* INC_CDRIVERADAPTER_H_ */
