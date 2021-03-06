///=============================================================================
/// @file      IMotionBlock.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      20.Apr.2017
///
/// @copyright
///=============================================================================

#ifndef INC_IMOTIONBLOCK_H_
#define INC_IMOTIONBLOCK_H_

#include "CAxis.h"

///@brief Names and number of axis
typedef enum
{
    aAxisX,
    aAxisY,
    aAxisZ,
    aAxisCount
} EAxis;

///
///@brief
///
class IMotionBlock
{
public:
    ///@brief
    typedef enum
    {
        mmRapidPositioning,
        mmLinearInterpolation,
        mmCircularInterpolationCW,
        mmCircularInterpolationCCW,
        mmDwell,
        mmCount
    } EMotionMode;

    ///@brief
    typedef enum
    {
        cycleStopped,
        cyclePecking,
        cycleCount
    } ECycle;

    /// @brief
    static void init( void );
    /// @brief Virtual destructor
    virtual ~IMotionBlock();
    /// @brief
    virtual void execute( void );
    /// @brief
    /// @param
    virtual void set_motion( const EMotionMode motionMode);
    /// @brief
    /// @param
    /// @param
    virtual void set_axisPos( const EAxis axis, const float value );
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

    /// @brief
    /// @param
    static void set_feedrate( const float feedrate );
    /// @brief
    /// @param
    static void set_speed( const float speed );
    /// @brief
    /// @param
    static void set_tool( const uint16 tool );
    /// @brief
    /// @param
    /// @param
    static void set_cycle( const ECycle type, const bool active);
    /// @brief
    /// @param
    static void set_pause( const uint32 time);

protected:
    ///@brief
    static CAxis mAxis[aAxisCount];
    ///@brief
    static EAxis mLeadingAxis;
    ///@brief
    static uint32 mAxisDeltaSteps;
    ///@brief
    static uint32 mAxisHalfDeltaSteps;
    ///@brief
    static float mRadius;
    ///@brief Sub-type of motion
    static bool mFastMode;
    ///@brief
    static EAxisDir mCircleDirection;

    /// @brief Convert to number of steps a distance in current unit
    /// @param New coordinate in current mode and unit
    /// @return Signed offset of current position
    static sint32 convertToSteps( const float dist );

    /// @brief
    /// @param
    /// @param
    static void doStep( const EAxis axis, const EAxisDir dir );

private:
    ///@brief
    static uint32 mPauseCount;
    ///@brief
    static uint32 mFeedrate;
    ///@brief
    static uint32 mSpeed;
    ///@brief
    static uint32 mTool;

};


#endif /* INC_IMOTIONBLOCK_H_ */
