///=============================================================================
/// @file       CWords.cpp
/// @brief
/// @details    Defines handler functions for G codes
/// @author     Boyan Bonev
/// @version    0.1
/// @date       13.Nov.2016
///
/// @copyright
/// @links      http://eng-serve.com/cnc/gcode_comment.html
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\CWords.h"
#include "..\inc\CPositioning.h"
#include "..\inc\CMotion.h"
#include "..\inc\CSettings.h"
#include "..\inc\DebugUtilities.h"

///=============================================================================
/// @brief Definition of static objects
///=============================================================================
CWord                           CWord::mWord;

CAddressN_BlockNumber           CWord::mN_BlockNumber;

CAddressG_PreparatoryCommands   CAddressG_PreparatoryCommands::mG_PreparatoryCommands;
CAddressG_UnmodalCodes          CAddressG_PreparatoryCommands::mG_UnmodalCodes;
CAddressG_MotionCommands        CAddressG_PreparatoryCommands::mG_MotionCommands;
CAddressG_PlaneSelection        CAddressG_PreparatoryCommands::mG_PlaneSelection;
CAddressG_DimensionningMode     CAddressG_PreparatoryCommands::mG_DimensionningMode;
CAddressG_UnitsInput            CAddressG_PreparatoryCommands::mG_UnitsInput;
CAddressG_Cycles                CAddressG_PreparatoryCommands::mG_Cycles;

CAddressM_AuxiliaryFunctions    CAddressM_AuxiliaryFunctions::mM_AuxiliaryFunctions;
CAddressM_Program               CAddressM_AuxiliaryFunctions::mM_Program;

CAxisMotionCommands             CWord::mAxisMotionCommands;
CAxisRelated                    CWord::mAxisRelated;
CPause                          CWord::mPause;
CSpeed                          CWord::mSpeed;
CFeedrate                       CWord::mFeedrate;
CTool                           CWord::mTool;
CComments                       CWord::mComment;

/// @brief Workarround for gcc warning: _DSO_HANDLE isn't defined
#ifdef STM32F103C8
    void* __dso_handle;
#endif

///=============================================================================
/// @brief Definition of main class: CWord
///=============================================================================

/// @brief
CWord::~CWord()
{

}

/// @brief
void CWord::handler()
{
    CDebug::reportError(ERROR_Invalid_Word);
}

/// @brief
/// @param
/// @param
/// @param
void CWord::assign( const uint8 address, const uint8* seqBlock, uint8* const pIndex )
{
    CWord* obj;

    if ( 'G' == address )
    {
        uint16 code = processInteger(seqBlock, pIndex);
        obj = CAddressG_PreparatoryCommands::assign(code);
    }
    else if ( 'N' == address )
    {
        obj = &mN_BlockNumber;
        mN_BlockNumber.param = processInteger(seqBlock, pIndex);
    }
    else if ( 'M' == address )
    {
        uint16 code = processInteger(seqBlock, pIndex);
        obj = CAddressM_AuxiliaryFunctions::assign(code);
    }
    else if ( ('X' <= address) && (address <= 'Z') )
    {
        obj = &mAxisMotionCommands;
        mAxisMotionCommands.address = address;
        mAxisMotionCommands.param = processFloat(seqBlock, pIndex);
    }
    else  if ( (('I' <= address) && (address <= 'K')) || ('Q' == address) || ('R' == address) )
    {
        obj = &mAxisRelated;
        mAxisRelated.address = address;
        mAxisRelated.param = processFloat(seqBlock, pIndex);
    }
    else if ( 'P' == address )
    {
        obj = &mPause;
        mPause.param = processInteger(seqBlock, pIndex);
    }
    else if ( 'S' == address )
    {
        obj = &mSpeed;
        mSpeed.param = processInteger(seqBlock, pIndex);
    }
    else if ( 'F' == address )
    {
        obj = &mFeedrate;
        mFeedrate.param = processFloat(seqBlock, pIndex);
    }
    else if ( 'T' == address )
    {
        obj = &mTool;
        mTool.param = processInteger(seqBlock, pIndex);
    }
    else if ( '(' == address )
    {
        obj = &mComment;
        mComment.processComment(seqBlock, pIndex);
    }
    else
    {
        /// Skip parameter
        while( ' ' < seqBlock[*pIndex] )
        {
            (*pIndex)++;
        }

        obj = &mWord;
    }

    obj->handler();
}

/// @brief
/// @param
/// @param
/// @return
uint16 CWord::processInteger( const uint8* seqBlock, uint8* const pIndex )
{
    uint32 res = 0;

    while( ('0' <= seqBlock[*pIndex]) && (seqBlock[*pIndex] <= '9') )
    {
        res = res * 10;
        res = res + (seqBlock[*pIndex] - '0');
        (*pIndex)++;
    }

    return res;
}

/// @brief Reads the value according to the active format.
///          Imperial units - input 0.625 inches:
///          Full format:        X00006250
///          No leading zeros:   X6250
///          No trailing zeros:  X0000625
///          Decimal point:      X0.625 or X.625
///
///          Metric units - input 0.42 mm:
///          Full format:        X00000420
///          No leading zeros:   X420
///          No trailing zeros:  X0000042
///          Decimal point:      X0.42 or X.42
///
/// @param
/// @param
/// @return
float CWord::processFloat( const uint8* seqBlock, uint8* const pIndex )
{
    /// Power of 10
    static const float Pow10[] = { 1.0, 10.0, 100.0, 1000.0, 10000.0 };
    /// Maximum number of digits that represents a parameter
    static const uint8 FULL_ADDRESS_LENGTH = 8;

    uint8 prevIndex;
    sint8 sign = 1;
    uint32 integer = 0;
    float result;

    /// read sign of value
    while( '-' == seqBlock[*pIndex] )
    {
        sign = -1;
        (*pIndex)++;
    }

    /// read the whole value or the integer part depends on format
    prevIndex = *pIndex;
    integer = processInteger(&seqBlock[*pIndex], pIndex);

    switch( CSettings::NUM_FORMAT() )
    {
    case CSettings::dfFullAddress:
        result = static_cast<float>(integer * CSettings::MIN_INCREMENT());
        break;
    case CSettings::dfTrailingZeros:
        result = static_cast<float>(integer * CSettings::MIN_INCREMENT());
        break;
    case CSettings::dfLeadingZeroes:
        result = static_cast<float>(integer * Pow10[FULL_ADDRESS_LENGTH - (*pIndex - prevIndex)] * CSettings::MIN_INCREMENT());
        break;
    case CSettings::dfDecimalPoint:
        result = static_cast<float>(integer);

        /// read decimal point
        while('.' == seqBlock[*pIndex])
        {
            (*pIndex)++;
        }

        /// read the fractal part
        prevIndex = *pIndex;
        integer = processInteger(seqBlock, pIndex);

        /// calculate final result
        result += (integer / Pow10[*pIndex - prevIndex]);
        break;
    default:
        result = 0;
        break;
    }

    /// Calculate final result
    return (result * sign);
}

/// @brief
/// @param
/// @param
void CWord::processComment( const uint8* seqBlock, uint8* const pIndex )
{
    while( seqBlock[*pIndex] != ')' )
    {
        (*pIndex)++;
    }
    (*pIndex)++;
}

///=============================================================================
/// @brief N - Sequence Block Number
///=============================================================================

/// @brief
void CAddressN_BlockNumber::handler()
{
    CDebug::set_lineNumber(param);
}

///=============================================================================
/// @brief G - Preparatory Commands
///=============================================================================

/// @brief
/// @param
CAddressG_PreparatoryCommands* CAddressG_PreparatoryCommands::assign( const uint8 code )
{
    CAddressG_PreparatoryCommands* res;

    if ( (4 == code) || ((9 <= code) && (code <= 11)) )
    {
        res = &mG_UnmodalCodes;
    }
    else if ( (0 <= code) && (code <= 3) )
    {
        res = &mG_MotionCommands;
    }
    else if ( (17 <= code) && (code <= 19) )
    {
        res = &mG_PlaneSelection;
    }
    else if ( (90 == code) || (91 == code) )
    {
        res = &mG_DimensionningMode;
    }
    else if ( (20 == code) || (21 == code) )
    {
        res = &mG_UnitsInput;
    }
    else if ( ((73 <= code) && (code <= 76)) || ((80 <= code) && (code <= 89)) )
    {
        res = &mG_Cycles;
    }
    else
    {
        res = &mG_PreparatoryCommands;
    }

    res->code = code;

    return res;
}

/// @brief Handling all others
void CAddressG_PreparatoryCommands::handler()
{
    CDebug::reportError(ERROR_Invalid_GCode);
}

/// @brief Handling: G4, G9, G10, G11
void CAddressG_UnmodalCodes::handler()
{
    switch(code)
    {
    case 4:  /// G04 - Dwell
        CPositioning::set_pause(100);
        break;
    case 9:  /// G09 -
    case 10: /// G10 - Coordinate System Data Tool and Work Offset Tables
    case 11: /// G11 -
    default:
        break;
    }
}

/// @brief Handling: G0, G1, G2, G3
void CAddressG_MotionCommands::handler()
{
    /// G00 - Rapid positioning
    /// G01 - Linear interpolation
    /// G02 - Circular interpolation clockwise
    /// G03 - Circular interpolation counterclockwise
    CPositioning::set_motion(static_cast<CPositioning::EMoveType>(code));
}

/// @brief Handling: G17, G18, G19
void CAddressG_PlaneSelection::handler()
{
}

/// @brief Handling: G90, G91
void CAddressG_DimensionningMode::handler()
{
    CSettings::set_mode( (CSettings::EMode)(code - 90) );
}

/// @brief Handling: G20, G21
void CAddressG_UnitsInput::handler()
{
    CSettings::set_unit( (CSettings::EUnit)(code - 20) );
}

/// @brief Handling: G73, G74, G76, G80, G81, G82, G83, G84, G85, G86, G87, G88, G89
void CAddressG_Cycles::handler()
{
}

///=============================================================================
/// @brief M - Auxiliary Functions
///=============================================================================

/// @brief
/// @param
CAddressM_AuxiliaryFunctions* CAddressM_AuxiliaryFunctions::assign( const uint8 code )
{
    CAddressM_AuxiliaryFunctions* res;

	if ( ((0 <= code) && (code <= 2)) || (30 == code) )
	{
        res = &mM_Program;
    }
    else
    {
        res = &mM_AuxiliaryFunctions;
    }

	res->code = code;

    return res;
}

/// @brief Handling all others
void CAddressM_AuxiliaryFunctions::handler()
{
    CDebug::reportError(ERROR_Invalid_MCode);
}

/// @brief Handling: M0, M1, M2, M30
void CAddressM_Program::handler()
{

}

///=============================================================================
/// @brief Motion Commands
///=============================================================================

/// @brief Handling: X, Y, Z
void CAxisMotionCommands::handler()
{
    CPositioning::set_deltaAxis(param, static_cast<CPositioning::EAxis>(address - 'X'));
}

///=============================================================================
/// @brief Axis Related
///=============================================================================

/// @brief Handling: I, J, K, R, Q
void CAxisRelated::handler()
{
    if ( ('I' <= address) && (address <= 'K') )
    {
        CPositioning::set_arcOffset(param, static_cast<CPositioning::EAxis>(address - 'I'));
    }
    else if ( 'R' == address )
    {
        CPositioning::set_radius(param);
    }
    else
    {
        CDebug::reportError(ERROR_Invalid_Word);
    }
}

///=============================================================================
/// @brief Pause
///=============================================================================

/// @brief Handling: S
void CPause::handler()
{
    CPositioning::set_pause( param );
}

///=============================================================================
/// @brief Speed, Feed, Tool
///=============================================================================

/// @brief Handling: S
void CSpeed::handler()
{
    CPositioning::set_speed( param );
}

/// @brief Handling: F
void CFeedrate::handler()
{
    CPositioning::set_speed( param );
}

/// @brief Handling: T
void CTool::handler()
{
    CPositioning::set_tool( param );
}

///=============================================================================
/// @brief
///=============================================================================

/// @brief
void CComments::handler()
{
    /// Do nothing
}
