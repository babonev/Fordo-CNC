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

#include "Std_Types.h"
#include "CWords.h"
#include "IMotionBlock.h"
#include "CLinearMotion.h"
#include "CCircularMotion.h"
#include "CDriverAdapter.h"
#include "CSettings.h"
#include "DebugUtilities.h"

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
CAddressM_ZAxis                 CAddressM_AuxiliaryFunctions::mM_ZAxis;

CAxisMotionCommands             CWord::mAxisMotionCommands;
CAxisRelated                    CWord::mAxisRelated;
CPause                          CWord::mPause;
CSpeed                          CWord::mSpeed;
CFeedrate                       CWord::mFeedrate;
CTool                           CWord::mTool;
CComments                       CWord::mComment;

IMotionBlock*                   CWord::mpMotion = &CWord::mLinearMotion;
CLinearMotion                   CWord::mLinearMotion;
CCircularMotion                 CWord::mCircularMotion;

uint16                          CWord::mLineNumber = 0;
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
    CDebug::reportErrorLine(ERROR_Invalid_Word);
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
    else  if ( ('A' == address) || (('I' <= address) && (address <= 'K')) || ('Q' == address) || ('R' == address) )
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

    uint8 prevIndex;
    sint8 sign = 1;
    uint32 integer = 0;
    float result;

    CSettings::EDcimalFormat numFormat = CSettings::NUM_FORMAT();

    /// read sign of value
    while( '-' == seqBlock[*pIndex] )
    {
        sign = -1;
        (*pIndex)++;
    }

    /// read the whole value or the integer part depends on format
    prevIndex = *pIndex;
    integer = processInteger(seqBlock, pIndex);

    /// check if decimal point value
    if ( '.' == seqBlock[*pIndex] )
    {
        numFormat = CSettings::dfDecimalPoint;
    }

    switch( numFormat )
    {
    case CSettings::dfFullAddress:
        result = static_cast<float>(integer * CSettings::MIN_INCREMENT());
        break;
    case CSettings::dfTrailingZeros:
        result = static_cast<float>(integer / Pow10[CSettings::TZ_COUNT()]);
        break;
    case CSettings::dfLeadingZeroes:
        result = static_cast<float>(integer * Pow10[CSettings::LZ_COUNT() - (*pIndex - prevIndex)]);
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
    mLineNumber = param;
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
    else if ( ((0 <= code) && (code <= 3)) || (32 == code) || (33 == code) )
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
    CDebug::reportError(ERROR_Invalid_GCode, (uint32)code);
}

/// @brief Handling: G4, G9, G10, G11
void CAddressG_UnmodalCodes::handler()
{
    switch(code)
    {
    case 4:  /// G04 - Dwell
        mpMotion->set_pause(100);
        break;
    case 9:  /// G09 -
    case 10: /// G10 - Coordinate System Data Tool and Work Offset Tables
    case 11: /// G11 -
    default:
        break;
    }
}

/// @brief Handling: G0, G1, G2, G3, G32, G33
void CAddressG_MotionCommands::handler()
{
    switch(code)
    {
    case 0:  /// G00 - Rapid positioning
    case 1:  /// G01 - Linear interpolation
        mpMotion = &mLinearMotion;
        mpMotion->set_motion(static_cast<IMotionBlock::EMotionMode>(code));
        break;
    case 2:  /// G02 - Circular interpolation clockwise
    case 3:  /// G03 - Circular interpolation counterclockwise
        mpMotion = &mCircularMotion;
        mpMotion->set_motion(static_cast<IMotionBlock::EMotionMode>(code));
        break;
    case 32: /// G32 - Routed Circle Canned Cycle Clockwise
        mpMotion = &mCircularMotion;
        break;
    case 33: /// G33 - Routed Circle Canned Cycle Counterclockwise
        mpMotion = &mCircularMotion;
        break;
    default:
    	CDebug::reportErrorLine(ERROR_Invalid_GCode);
        break;
    }
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
    else if ( (15 <= code) && (code <= 16) )
    {
        res = &mM_ZAxis;
    }
    else
    {
        res = &mM_AuxiliaryFunctions;
    }

	res->code = code;

    return res;
}

/// @brief Handling: M0, M1, M2, M30
void CAddressM_Program::handler()
{

}

/// @brief Handling: M15, M16
void CAddressM_ZAxis::handler()
{
    CDriverAdapter::doMoveZ( static_cast<EAxisDir>(code -15), 0 );
}

/// @brief Handling all others
void CAddressM_AuxiliaryFunctions::handler()
{
    CDebug::reportError(ERROR_Invalid_MCode, (uint32)code);
}

///=============================================================================
/// @brief Motion Commands
///=============================================================================

/// @brief Handling: X, Y, Z
void CAxisMotionCommands::handler()
{
	mpMotion->set_axisPos( static_cast<EAxis>(address - 'X'), param );
}

///=============================================================================
/// @brief Axis Related
///=============================================================================

/// @brief Handling: A, I, J, K, R, Q
void CAxisRelated::handler()
{
    if ( 'A' == address )
    {
        mpMotion->set_arcRadius(param);
    }
    else if ( ('I' <= address) && (address <= 'K') )
    {
    	mpMotion->set_arcOffset( static_cast<EAxis>(address - 'I'), param );
    }
    else if ( 'R' == address )
    {
    	mpMotion->set_radius(param);
    }
    else
    {
        CDebug::reportErrorLine(ERROR_Invalid_Word);
    }
}

///=============================================================================
/// @brief Pause
///=============================================================================

/// @brief Handling: S
void CPause::handler()
{
	mpMotion->set_pause( param );
}

///=============================================================================
/// @brief Speed, Feed, Tool
///=============================================================================

/// @brief Handling: S
void CSpeed::handler()
{
	mpMotion->set_speed( param );
}

/// @brief Handling: F
void CFeedrate::handler()
{
	mpMotion->set_speed( param );
}

/// @brief Handling: T
void CTool::handler()
{
	mpMotion->set_tool( param );
}

///=============================================================================
/// @brief
///=============================================================================

/// @brief
void CComments::handler()
{
    /// Do nothing
}

