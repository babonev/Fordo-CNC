///=============================================================================
/// @file      DebugUtilities.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      03.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_DEBUGUTILITIES_H_
#define INC_DEBUGUTILITIES_H_

/// @brief
typedef enum
{
    EVENT_MotorInitialized,
    EVENT_NoHeader,
    EVENT_UnitChanged,
    EVENT_AxisSet,
    EVENT_RadiusSet,
    EVENT_LineCreated,
    EVENT_CircleCreated,
    EVENT_ToolChanged,
    EVENT_FeedrateChanged,
    EVENT_SpeedChanged,
    EVENT_PauseSet,
    EVENT_Count
} EEvent;

/// @brief
typedef enum
{
    ERROR_BlockTooLong,
    ERROR_UnknownAddress,
    ERROR_PartiallyProcessed,
    ERROR_UnknownHeaderCommand,
    ERROR_TooManyWords,
    ERROR_Invalid_Word,
    ERROR_Invalid_GCode,
    ERROR_Invalid_MCode,
    ERROR_Invalid_Format,
    ERROR_Invalid_Motion,
    ERROR_Position_OutOfBounds,
    ERROR_StepsBufferFull,
    ERROR_Count
} EError;

///
///@brief
//
class CDebug
{
public:
    /// @brief
    /// @param
    static void set_seqNumber(const uint16 number);
    /// @brief
    /// @param
    /// @param
    static void logEvent( const EEvent event, const uint8 param );
    /// @brief
    /// @param
    static void traceEvent( const EEvent event, const float param );
    static void traceEvent( const EEvent event, const uint32 param );
    /// @brief
    /// @param
    /// @param
    static void reportError( const boolean condition, const EError error );
    /// @brief
    /// @param
    /// @param
    static void reportError( const EError error, const float param );
    /// @brief
    /// @param
    /// @param
    static void reportError( const EError error, const uint8* const param );
    /// @brief
    /// @param
    static void reportErrorLine( const EError error );

private:
    /// @brief
    typedef struct
    {
        uint16 timeStamp;
        EEvent event;
        uint8 param;
    } SEventLog;

    /// @brief
    static const uint8 TRACE_EVENT_COUNT = 20;

    /// @brief
    static SEventLog log[TRACE_EVENT_COUNT];
    static uint8 logLine;
    static uint16 seqNumber;

    /// @brief
    /// @param
    /// @param
    /// @param
    static uint32 getTimeStamp( void );

    /// @brief Converts digital parameters into string
    /// @param
    /// @param
    /// @param
    /// @remark The user is responsible to supply long enough buffer
    static uint8 makeString( float indata, uint8* outdata, const uint8 len, const bool isInt );
    /// @brief
    /// @param
    /// @param
    /// @param
    static void outputError( const EError error, const uint8* const message );
    /// @brief
    /// @param
    /// @param
    /// @param
    static void outputEvent( const EEvent event, const uint8* const message );
};

#endif /* INC_DEBUGUTILITIES_H_ */
