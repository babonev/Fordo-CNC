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
    EVENT_UnitChanged,
    EVENT_LineCreated,
    EVENT_CircleCreated,
    EVENT_Count
} EEvent;

/// @brief
typedef enum
{
    ERROR_BlockTooLong,
    ERROR_UnknownAddress,
    ERROR_PartiallyProcessed,
    ERROR_TooManyWords,
    ERROR_Invalid_Word,
    ERROR_Invalid_GCode,
    ERROR_Invalid_MCode,
    ERROR_Invalid_Format,
    ERROR_StepsBufferFull,
    ERROR_Count
} EError;


/// @brief
class CDebug
{
private:
    ///
    typedef struct
    {
        uint16 timeStamp;
        EEvent event;
        uint8 param;
    } SEventLog;

    ///
    static const uint8 TRACE_EVENT_COUNT = 20;

    ///
    static SEventLog log[TRACE_EVENT_COUNT];
    static uint8 logLine;
    static uint16 lineNumber;

    ///
    static uint8 makeString( uint32 indata, uint8* outdata, const uint8 len );

public:
    ///
    static void set_lineNumber(const uint16 number);
    static void logEvent( const EEvent event, const uint8 param );
    static void reportError( const EError error );
    static void reportError( const boolean condition, const EError error );
    static void reportError( const EError error, const uint8 param );
    static void reportError( const EError error, const uint16 param );
    static void reportError( const EError error, const uint8* const param );
};

#endif /* INC_DEBUGUTILITIES_H_ */
