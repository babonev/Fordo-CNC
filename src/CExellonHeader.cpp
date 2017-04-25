///=============================================================================
/// @file      CHeader.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 23, 2017
///
/// @copyright
///=============================================================================

#include "../inc/Std_Types.h"
#include "../inc/CExellonHeader.h"
#include "../inc/CSettings.h"
#include "../inc/DebugUtilities.h"

///=============================================================================
/// @brief INITIALIZATION
///=============================================================================
static CStartCommand mStart;
static CInchUnitCommand mInchUnit;
static CMetricUnitCommand mMetricUnit;
static CLeadingZeroesCommand mLeadingZeroes;
static CTrailingZeroesCommand mTrailingZeroes;
static CModeCommand mMode;
static CVersionCommand mVersion;
static CFormatCommand mFormat;
static CDetectCommand mDetect;
static CAtcCommand mAtc;
static CToolCommand mTool;
static CEndOfHeaderCommand mEndOfHeader;
static CRewindCommand mRewind;
static COnCommand mOn;
static COffCommand mOff;

bool CExellonHeader::mHeaderStarted = false;
bool CExellonHeader::mHeaderFinished = false;
CExellonHeader* CExellonHeader::mCommands[15] =
{
    &mStart,
    &mInchUnit,
    &mMetricUnit,
    &mLeadingZeroes,
    &mTrailingZeroes,
    &mMode,
    &mVersion,
    &mFormat,
    &mDetect,
    &mAtc,
    &mTool,
    &mEndOfHeader,
    &mRewind,
    &mOn,
    &mOff
};

CExellonHeader::CExellonHeader() :
	mCmdString(0),
	mCmdLength(0)
{
}

CExellonHeader::CExellonHeader( const uint8* cmd, const uint8 len ) :
	mCmdString(cmd),
	mCmdLength(len)
{
}

void CExellonHeader::init()
{
    mHeaderStarted = false;
    mHeaderFinished = false;
}

///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

void CExellonHeader::process( const uint8* hdrBlock, const uint32 length )
{
	uint8 byteIndex = 0;
	uint8 cmdIndex = 0;
	bool res;

	if ( !mHeaderStarted )
	{
        // Search "Header start"
        cmdIndex = getMatch(&hdrBlock[byteIndex], &byteIndex);

        if ( 0 == cmdIndex )
        {
            mHeaderStarted = true;
            skipLine(hdrBlock, &byteIndex);
        }
        else
        {
            mHeaderFinished = true;
            CDebug::traceEvent(EVENT_NoHeader, 0);
        }
	}
	else
	{
		while( (mHeaderFinished == false) && (byteIndex < length) )
		{
			cmdIndex = getMatch(&hdrBlock[byteIndex], &byteIndex);

			if ( cmdIndex < (sizeof(mCommands)/sizeof(mCommands[0])) )
			{
				res = mCommands[cmdIndex]->applySetting();

				if ( !res )
				{
					skipLine(hdrBlock, &byteIndex);
				}
			}
			else
			{
				CDebug::reportErrorLine(ERROR_UnknownHeaderCommand);
			}

			skipDelimiter(hdrBlock, &byteIndex);
		}
	}
}

uint8 CExellonHeader::getMatch( const uint8* hdrBlock, uint8* const byteIndex )
{
    uint8 res = 0xff;
    uint8 cmdIndex = 0;
    uint8 readIndex = 0;
    CExellonHeader const*  cmd;

    for( cmdIndex = 0; cmdIndex < (sizeof(mCommands)/sizeof(mCommands[0])); cmdIndex++ )
    {
        cmd = mCommands[cmdIndex];

        for( ; readIndex < cmd->mCmdLength; readIndex++ )
        {
            if ( hdrBlock[readIndex] != cmd->mCmdString[readIndex] )
            {
				break;
            }
        }

        if ( readIndex == cmd->mCmdLength )
        {
            res = cmdIndex;
        	break;
        }
    }

    (*byteIndex) += readIndex;

    return res;
}

void CExellonHeader::skipDelimiter( const uint8* hdrBlock, uint8* const byteIndex )
{
    while(  (','  == hdrBlock[(*byteIndex)]) ||
            (' '  == hdrBlock[(*byteIndex)]) ||
            ('\n' == hdrBlock[(*byteIndex)]) ||
            ('\r' == hdrBlock[(*byteIndex)]) )
    {
        (*byteIndex)++;
    }
}

void CExellonHeader::skipLine( const uint8* hdrBlock, uint8* const byteIndex )
{
    while(  ('\n' != hdrBlock[(*byteIndex)]) &&
            ('\r' != hdrBlock[(*byteIndex)]) )
    {
        (*byteIndex)++;
    }
}

bool CExellonHeader::headerParsed( void )
{
	return mHeaderFinished;
}

///=============================================================================
/// @brief DERIVED METHODS
///=============================================================================

bool CExellonHeader::applySetting( void )
{
	// Command not used
	return false;
}

bool CInchUnitCommand::applySetting( void )
{
	CSettings::set_unit(CSettings::unitImperial);
	return true;
}

bool CMetricUnitCommand::applySetting( void )
{
	CSettings::set_unit(CSettings::unitMetric);
	return true;
}

bool CLeadingZeroesCommand::applySetting( void )
{
	CSettings::set_decimFormat(CSettings::dfLeadingZeroes);
	return true;
}

bool CTrailingZeroesCommand::applySetting( void )
{
	CSettings::set_decimFormat(CSettings::dfTrailingZeros);
	return true;
}

bool CModeCommand::applySetting( void )
{
	CSettings::set_mode(CSettings::modeAbsolute);
	return true;
}

bool CEndOfHeaderCommand::applySetting( void )
{
	mHeaderFinished = true;
	return true;
}

bool CRewindCommand::applySetting( void )
{
	mHeaderFinished = true;
	return true;
}


