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
#include <stdio.h>

///=============================================================================
/// @brief
///=============================================================================
uint16 CDebug::seqNumber = 0;
uint8 CDebug::logLine = 0;
CDebug::SEventLog CDebug::log[TRACE_EVENT_COUNT] = { 0 };

///=============================================================================
/// @brief
///=============================================================================

void CDebug::set_seqNumber(const uint16 number)
{
    seqNumber = number;
}

void CDebug::logEvent( const EEvent event, const uint8 param )
{
    log[logLine].timeStamp = getTimeStamp();
    log[logLine].event = event;
    log[logLine].param = param;

    logLine++;

    if ( logLine > TRACE_EVENT_COUNT )
    {
        logLine = 0;
    }
}

void CDebug::traceEvent( const EEvent event, const uint32 param )
{
    uint8 strParam[11];

    (void)CDebug::makeString(param, strParam, sizeof(strParam));

    /// output it over some interface
    outputEvent(event, strParam);
}

void CDebug::reportError( const boolean condition, const EError error )
{
    if ( !condition )
    {
        /// output it over some interface
        outputError(error, NULL);
    }
}

void CDebug::reportError( const EError error, const uint32 param )
{
    uint8 strParam[11];

    (void)CDebug::makeString(param, strParam, sizeof(strParam));

    /// output it over some interface
    outputError(error, strParam);
}

void CDebug::reportError( const EError error, const uint8* const param )
{
    /// output it over some interface
	outputError(error, param);
}

void CDebug::reportErrorLine( const EError error )
{
	reportError(error, seqNumber);
}

uint8 CDebug::makeString( uint32 indata, uint8* outdata, const uint8 len )
{
    uint8 bufLen = 0;

    // Convert the number into string but reversed
    do
    {
        outdata[bufLen++] = (indata % 10) + '0';
        indata = indata / 10;
    }
    while(indata > 0);

    // Error checking
    if ( (1 < bufLen) && (bufLen < len) )
    {
        uint8 bufLeft;
        uint8 bufRight;
        uint8 temp;

        // Reverse the string
        for( bufLeft = 0; bufLeft < (bufLen/2); bufLeft++  )
        {
            bufRight = bufLen - bufLeft - 1;
            temp = outdata[bufLeft];
            outdata[bufLeft] = outdata[bufRight];
            outdata[bufRight] = temp;
        }
    }
    else
    {
        bufLen = 0;
    }

    outdata[bufLen] = '\0';

    return bufLen;
}

uint32 CDebug::getTimeStamp( void )
{
    return 0xABCD;
}

void CDebug::outputError( const EError error, const uint8* const message )
{
    char errString[20];

    switch(error)
    {
    case ERROR_Invalid_Word:
        sprintf(errString, "Invalid word");
        break;
    case ERROR_Invalid_GCode:
        sprintf(errString, "Invalid G-CODE");
        break;
    case ERROR_Invalid_MCode:
        sprintf(errString, "Invalid M-CODE");
        break;
    case ERROR_Position_OutOfBounds:
        sprintf(errString, "Position out of bounds");
        break;
    default:
        sprintf(errString, "%d", (int)error);
        break;
    }

    printf("ERROR %s: %s\n", errString, message);
}

void CDebug::outputEvent( const EEvent event, const uint8* const message )
{
    char eventString[20];

    switch(event)
    {
    case EVENT_ToolChanged:
        sprintf(eventString, "Tool changed");
        break;
    default:
        sprintf(eventString, "%d", (int)event);
        break;
    }

    printf("<%s> %s\n", eventString, message);
}

