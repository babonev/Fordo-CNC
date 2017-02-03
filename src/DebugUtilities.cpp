///=============================================================================
/// @file      CDebug.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      03.Nov.2016
///
/// @copyright
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\DebugUtilities.h"

///=============================================================================
/// @brief
///=============================================================================
uint16 CDebug::lineNumber = 0;
uint8 CDebug::logLine = 0;
CDebug::SEventLog CDebug::log[TRACE_EVENT_COUNT] = { 0 };

///=============================================================================
/// @brief
///=============================================================================

/// @brief
/// @param
void CDebug::set_lineNumber(const uint16 number)
{
    lineNumber = number;
}

/// @brief
/// @param
/// @param
void CDebug::logEvent( const EEvent event, const uint8 param )
{
    log[logLine].timeStamp = 0xAAAA;
    log[logLine].event = event;
    log[logLine].param = param;

    logLine++;

    if ( logLine > TRACE_EVENT_COUNT )
    {
        logLine = 0;
    }
}

/// @brief
/// @param
void CDebug::reportError( const EError error )
{
    /// output it over some interface
}

/// @brief
/// @param
/// @param
void CDebug::reportError( const boolean condition, const EError error )
{
    if ( condition )
    {
        reportError(error);
    }
}

/// @brief
/// @param
/// @param
void CDebug::reportError( const EError error, const uint8 param )
{
    uint8 strParam[3];

    CDebug::makeString(param, strParam, sizeof(strParam));
    /// output it over some interface
}

/// @brief
/// @param
/// @param
void CDebug::reportError( const EError error, const uint16 param )
{
    uint8 strParam[5];

    CDebug::makeString(param, strParam, sizeof(strParam));
    /// output it over some interface
}

/// @brief
/// @param
/// @param
void CDebug::reportError( const EError error, const uint8* const param )
{
    /// output it over some interface
}

/// @brief Converts digital parameters into string
/// @param
/// @param
/// @param
/// @remark The user is responsible to supply long enough buffer
uint8 CDebug::makeString( uint32 indata, uint8* outdata, const uint8 len )
{
    uint8 bufLeft = 0;
    uint8 bufRight = 0;
    uint8 bufLen = 0;
    uint8 temp = 0;

    // Convert the number into string but reversed
    do
    {
        outdata[bufLen++] = (indata % 10) + '0';
        indata = indata / 10;
    }
    while(indata > 0);

    // Error checking
    if ( bufLen < len )
    {
        // Reverse the string
        for( bufLeft = 0, bufRight = (bufLen-1); bufRight > (bufLen/2); bufRight-- )
        {
            temp = outdata[bufLeft];
            outdata[bufLeft] = outdata[bufRight];
            outdata[bufRight] = temp;
        }
    }
    else
    {
        bufLen = 1;
    }

    return bufLen;
}

