///=============================================================================
/// @file      CWord.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      13.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CWORD_H_
#define INC_CWORD_H_

/// @brief Forward declaration of classes used in CWord
class CAddressN_BlockNumber;
class CAxisMotionCommands;
class CAxisRelated;
class CPause;
class CSpeed;
class CFeedrate;
class CTool;
class CComments;

///=============================================================================
/// @brief Factory producing objects of G code group types. Also stores the
///        corresponding parameters.
///=============================================================================
class CWord
{
public:
    /// Virtual destructor
    virtual ~CWord();
    /// Returns a pointer to the required object type depending on the parameters
    static void assign( const uint8 address, const uint8* seqBlock, uint8* const pIndex );
    /// Processing of the G-code
    virtual void handler();

protected:
    static CWord mWord;

private:
    /// Create objects statically to avoid heap usage
    static CAddressN_BlockNumber mN_BlockNumber;
    static CAxisMotionCommands mAxisMotionCommands;
    static CAxisRelated mAxisRelated;
    static CPause mPause;
    static CSpeed mSpeed;
    static CFeedrate mFeedrate;
    static CTool mTool;
    static CComments mComment;

private:
    /// Auxiliary functions parsing the parameters of G codes
    static uint16 processInteger( const uint8* seqBlock, uint8* const pIndex );
    static float processFloat( const uint8* seqBlock, uint8* const pIndex );
    static void processComment( const uint8* seqBlock, uint8* const pIndex );
};

///=============================================================================
/// @brief N - BlockNumber
///=============================================================================
class CAddressN_BlockNumber: public CWord
{
public:
    uint16 param;
    void handler();
};

///=============================================================================
/// @brief G - Preparatory Commands Groups
///=============================================================================

/// @brief Forward declaration of classes used in CAddressG_PreparatoryCommands
class CAddressG_UnmodalCodes;
class CAddressG_MotionCommands;
class CAddressG_PlaneSelection;
class CAddressG_DimensionningMode;
class CAddressG_UnitsInput;
class CAddressG_Cycles;

/// @brief G - Base class
class CAddressG_PreparatoryCommands : public CWord
{
public:
    uint8 code;
    static CAddressG_PreparatoryCommands* assign( const uint8 code );
    virtual void handler();

protected:
    static CAddressG_PreparatoryCommands mG_PreparatoryCommands;

private:
    /// Create objects statically to avoid heap usage
    static CAddressG_UnmodalCodes mG_UnmodalCodes;
    static CAddressG_MotionCommands mG_MotionCommands;
    static CAddressG_PlaneSelection mG_PlaneSelection;
    static CAddressG_DimensionningMode mG_DimensionningMode;
    static CAddressG_UnitsInput mG_UnitsInput;
    static CAddressG_Cycles mG_Cycles;
};

/// @brief 00. Unmodal G codes
class CAddressG_UnmodalCodes: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

/// @brief 01. Motion Commands, Cutting Cycles
class CAddressG_MotionCommands: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

/// @brief 02. Plane Selection
class CAddressG_PlaneSelection: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

/// @brief 03. Dimensioning Mode
class CAddressG_DimensionningMode: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

/// @brief 06. Units Input
class CAddressG_UnitsInput: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

/// @brief 09. Cycles
class CAddressG_Cycles: public CAddressG_PreparatoryCommands
{
public:
    void handler();
};

///=============================================================================
/// @brief M - Auxiliary Functions Groups
///=============================================================================

/// @brief Forward declaration of classes used in CAddressM_AuxiliaryFunctions
class CAddressM_Program;

/// @brief M - Base class
class CAddressM_AuxiliaryFunctions : public CWord
{
public:
    uint8 code;
    static CAddressM_AuxiliaryFunctions* assign( const uint8 code );
    virtual void handler();

protected:
    static CAddressM_AuxiliaryFunctions mM_AuxiliaryFunctions;

private:
    /// Create objects statically to avoid heap usage
    static CAddressM_Program mM_Program;
};

/// @brief 00. Program
class CAddressM_Program: public CAddressM_AuxiliaryFunctions
{
public:
    void handler();
};

///=============================================================================
/// @brief X, Y, Z, A, B, C, U, V, W - AxisMotionCommands
///=============================================================================
class CAxisMotionCommands: public CWord
{
public:
    uint8 address;
    float param;
    void handler();
};

///=============================================================================
/// @brief I, J, K, R, Q - AxisRelated
///=============================================================================
class CAxisRelated: public CWord
{
public:
    uint8 address;
    float param;
    void handler();
};

///=============================================================================
/// @brief P - Pause
///=============================================================================
class CPause: public CWord
{
public:
    uint16 param;
    void handler();
};

///=============================================================================
/// @brief S - Speed
///=============================================================================
class CSpeed: public CWord
{
public:
    uint32 param;
    void handler();
};

///=============================================================================
/// @brief F - Feed
///=============================================================================
class CFeedrate: public CWord
{
public:
    float param;
    void handler();
};

///=============================================================================
/// @brief T - Tool
///=============================================================================
class CTool: public CWord
{
public:
    uint32 param;
    void handler();
};

///=============================================================================
/// @brief Comments handler
///=============================================================================
class CComments: public CWord
{
public:
    void handler();
};

#endif /* INC_CWORD_H_*/
