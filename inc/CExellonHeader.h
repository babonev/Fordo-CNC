///=============================================================================
/// @file      CHeader.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 23, 2017
///
/// @copyright
///=============================================================================

#ifndef INC_CHEADER_H_
#define INC_CHEADER_H_

///
///@brief
//
class CExellonHeader
{
public:
    ///@brief
    CExellonHeader();
    ///@brief
    static void init();
    ///@brief
    ///@param
	static void process( const uint8* hdrBlock, const uint32 length );
    ///@brief
    ///@return
    static bool headerParsed();
    ///@brief
    ///@param
    static void skipDelimiter( const uint8* hdrBlock, uint8* const byteIndex );
    ///@brief
    ///@param
    static void skipLine( const uint8* hdrBlock, uint8* const byteIndex );
    ///@brief
    ///@return
    virtual bool applySetting();
    ///@brief
	virtual ~CExellonHeader() {};

protected:
    ///@brief
    CExellonHeader( const uint8* cmd, const uint8 len );
    ///@brief
    const uint8* mCmdString;
    ///@brief
    const uint8 mCmdLength;
    ///@brief
    static bool mHeaderStarted;
	///@brief
	static bool mHeaderFinished;

private:
    ///@brief
    static CExellonHeader* mCommands[15];
    ///@brief
    static uint8 getMatch( const uint8* hdrBlock, uint8* const byteIndex );
};

///
///@brief
//
class CStartCommand : public CExellonHeader
{
public:
    ///@brief
    CStartCommand() : CExellonHeader((uint8*)"M48", 3) {};
};

///
///@brief
//
class CInchUnitCommand : public CExellonHeader
{
public:
    ///@brief
    CInchUnitCommand() : CExellonHeader((uint8*)"INCH", 4) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CMetricUnitCommand : public CExellonHeader
{
public:
    ///@brief
    CMetricUnitCommand() : CExellonHeader((uint8*)"METRIC", 6) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CLeadingZeroesCommand : public CExellonHeader
{
public:
    ///@brief
    CLeadingZeroesCommand() : CExellonHeader((uint8*)"LZ", 2) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CTrailingZeroesCommand : public CExellonHeader
{
public:
    ///@brief
    CTrailingZeroesCommand() : CExellonHeader((uint8*)"TZ", 2) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CModeCommand : public CExellonHeader
{
public:
    ///@brief
    CModeCommand() : CExellonHeader((uint8*)"ICI", 3) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CVersionCommand : public CExellonHeader
{
public:
    ///@brief
    CVersionCommand() : CExellonHeader((uint8*)"VER", 3) {};
};

///
///@brief
//
class CFormatCommand : public CExellonHeader
{
public:
    ///@brief
    CFormatCommand() : CExellonHeader((uint8*)"FMAT", 4) {};
};

///
///@brief
//
class CDetectCommand : public CExellonHeader
{
public:
    ///@brief
    CDetectCommand() : CExellonHeader((uint8*)"DETECT", 6) {};
};

///
///@brief
//
class CAtcCommand : public CExellonHeader
{
public:
    ///@brief
    CAtcCommand() : CExellonHeader((uint8*)"ATC", 3) {};
};

///
///@brief
//
class CToolCommand : public CExellonHeader
{
public:
    ///@brief
    CToolCommand() : CExellonHeader((uint8*)"T", 1) {};
};

///
///@brief
//
class CEndOfHeaderCommand : public CExellonHeader
{
public:
    ///@brief
    CEndOfHeaderCommand() : CExellonHeader((uint8*)"M95", 3) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class CRewindCommand : public CExellonHeader
{
public:
    ///@brief
    CRewindCommand() : CExellonHeader((uint8*)"%", 1) {};
    ///@brief
    bool applySetting();
};

///
///@brief
//
class COnCommand : public CExellonHeader
{
public:
    ///@brief
    COnCommand() : CExellonHeader((uint8*)"ON", 2) {};
};

///
///@brief
//
class COffCommand : public CExellonHeader
{
public:
    ///@brief
    COffCommand() : CExellonHeader((uint8*)"OFF", 3) {};
};

#endif /* INC_CHEADER_H_ */
