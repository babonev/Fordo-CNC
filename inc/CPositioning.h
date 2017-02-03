///=============================================================================
/// @file      CPositioning.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      06.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CPOSITIONING_H_
#define INC_CPOSITIONING_H_

class CMotion;

/// @brief Cartesian coordinate system
class CPositioning
{
public:
    ///
    typedef enum
    {
        aAxisX,
        aAxisY,
        aAxisZ,
        aAxisCount
    } EAxis;

    ///
    typedef enum
    {
        mtRapidPositioning,
        mtLinearInterpolation,
        mtCircularInterpolationCW,
        mtCircularInterpolationCCW,
        mtDwell,
        mtCount
    } EMoveType;

	///
	typedef enum
	{
	    cycleStopped,
	    cyclePecking,
	    cycleCount
	} ECycle;

public:
    ///
    static void makeMove();

    /// Setters of move parameters
    static void set_motion( const EMoveType type);
    static void set_deltaAxis( const float steps, const CPositioning::EAxis axis );
    static void set_arcOffset( const float steps, const CPositioning::EAxis axis );
    static void set_radius( const float radius);
    static void set_cycle( const ECycle type, const bool active);
    static void set_pause( const uint16 time);
    static void set_feedrate( const float feedrate );
    static void set_speed( const float speed );
    static void set_tool( const float tool );

private:
    /// @brief
    typedef enum
    {
        umAxisX = 0x001,
        umAxisY = 0x002,
        umAxisZ = 0x003,
        umArcOffsetX = 0x004,
        umArcOffsetY = 0x008,
        umArcOffsetZ = 0x010,
        umRadius = 0x020,
        umPause = 0x040,
        umFeedrate = 0x080,
        umSpeed = 0x100,
        umTool = 0x200,
        umMotionType = 0x400,
        umCycle = 0x800,
        umCount = 0x1000
    } EUpdatedMask;

    /// @brief
    typedef struct
    {
        sint32 steps[CPositioning::aAxisCount];
        sint32 arcOffset[CPositioning::aAxisCount];
        sint32 radius;
        uint16 updated;
        uint16 pausetime;
        uint16 feedrate;
        uint16 speed;
        uint8  tool;
        EMoveType type;
        ECycle cycle;
    } SMotion;

    /// Boundary limits
    static const uint16 X_MAX = 288; /// [ mm ]
    static const uint16 Y_MAX = 190; /// [ mm ]
    static const uint16 Z_MAX = 80;  /// [ mm ]
    static const uint16 F_MAX = 120; /// [ mm/min ]
    static const uint16 S_MAX = 800; /// [ rpm ]

    /// Current position and state
    static SMotion moveSequence;
    static float position[aAxisCount];  /// [steps]
    static float error[aAxisCount];     /// [steps]

    /// Conversion functions
    static sint32 distanceInSteps( const float newPos, const CPositioning::EAxis axis );
    static sint32 distanceInSteps( const float dist );
};

#endif /* INC_CPOSITIONING_H_ */
