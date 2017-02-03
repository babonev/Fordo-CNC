///=============================================================================
/// @file      CMotion.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      19.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CMOTION_H_
#define INC_CMOTION_H_

/// @brief
class CMotion
{
public:
	///
    CMotion();
    ~CMotion();

    /// @brief
    typedef enum
    {
        arcClockwise = 1,
        arcInvalid = 0,
        arcCounterClockwise = -1
    } EArcDir;

    /// @brief
    static uint8 getList( const uint16* pStepsList );
    /// @brief
    static void makeLine( const sint32 deltaX, const sint32 deltaY );
    static void makeArc( const sint32 centerX, const sint32 centerY, const uint8 direction, const uint32 radius );
    static void moveSpindle( const sint32 deltaZ );

private:
    /// @brief
    typedef enum
    {
        dForward = 1,
        dNoMove = 0,
        dBackward = -1
    } EDirection;

    /// @brief
    static const uint8 RECORDS_COUNT = 16;
    static const uint8 RECORD_LENGTH = 5;
    static const uint8 STEPS_LIST_LENGTH = RECORD_LENGTH * RECORDS_COUNT;
    static const uint8 FEEDRATE_XY_INDEX = 0;
    static const uint8 STEPS_AXIS_OFFSET = 2;
    static const uint8 STEPS_X_INDEX = 2;
    static const uint8 STEPS_Y_INDEX = 3;
    static const uint8 STEPS_Z_INDEX = 4;

    /// @brief
    static uint16* pCurrentStep;
    static uint16 StepsList[2][STEPS_LIST_LENGTH];
    static uint8 rwIndex;
    static uint8 slRecordIdx;

    /// @brief
    static void initMove();
    static void doStepX( const EDirection dir );
    static void doStepY( const EDirection dir );
    static void doStepZ( const EDirection dir );
    static void setFeedrate( const uint32 feedrate );

    /// @brief
    /// @param
    /// @return
    static inline uint32 _ABS( const sint32 param )
    {
        return (uint32)((param < 0) ? (param * (-1)) : (param));
    }

    /// @brief
    /// @param
    /// @return
    static inline EDirection _DIR( const sint32 param )
    {
        return (param < 0) ? (dBackward) : (dForward);
    }
};

#endif /// INC_CMOTION_H_
