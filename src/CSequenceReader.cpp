///=============================================================================
/// @file      CSequenceReader.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      03.Nov.2016
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "CSequenceReader.h"
#include "CWords.h"
#include "CConfig.h"
#include "CSettings.h"
#include "DebugUtilities.h"

///============================================================================
/// @brief INITIALIZATION
///============================================================================
CExellonHeader CSequenceReader::hdr;
uint16 CSequenceReader::sequenceCount = 0;

///============================================================================
/// @brief class CSequenceBlock - parses program lines
///============================================================================

void CSequenceReader::init( void )
{
	sequenceCount = 0;

	CExellonHeader::init();
	CWord::init();
	CSettings::set_default();
}

/// @brief
/// @param
/// @param
void CSequenceReader::process( const uint8* seqBlock, const uint32 length )
{
	uint8 byteIndex = 0;

	CDebug::set_seqNumber(++sequenceCount);

    if ( length < CConfig::BLOCK_MAX_LENGHT )
    {
    	if ( hdr.headerParsed() )
    	{
			/// iterate whole line
			while( byteIndex < length )
			{
				processWord(seqBlock, &byteIndex);
				skipSpace(seqBlock, &byteIndex);
			}
			/// Execute the command
			CWord::execute();
    	}
    	else
    	{
    	    // Parse header
    		hdr.process(seqBlock, length);
    	}
    }
    else
    {
        CDebug::reportErrorLine(ERROR_BlockTooLong);
    }
}

/// @brief
void CSequenceReader::processWord( const uint8* seqBlock, uint8* const byteIndex )
{
    uint8 address = seqBlock[(*byteIndex)++];
    CWord::assign(address, seqBlock, byteIndex);
}

/// @brief
void CSequenceReader::skipSpace( const uint8* seqBlock, uint8* const byteIndex )
{
    while(  (' '  == seqBlock[*byteIndex]) ||
            ('\n' == seqBlock[*byteIndex]) ||
            ('\r' == seqBlock[*byteIndex]) )
    {
        (*byteIndex)++;
    }
}
