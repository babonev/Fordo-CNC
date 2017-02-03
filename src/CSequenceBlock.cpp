///=============================================================================
/// @file      CGCodeProcessor.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      03.Nov.2016
///
/// @copyright
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\CSequenceBlock.h"
#include "..\inc\CWords.h"
#include "..\inc\DebugUtilities.h"


///============================================================================
/// @brief class CSequenceBlock - parses program lines
///============================================================================

/// @brief
/// @param
/// @param
void CSequenceBlock::process( const uint8* seqBlock, const uint8 length )
{
    if ( length < BLOCK_MAX_LENGHT )
    {
        ///
        processIndex = 0;

        ///
        while( processIndex < length )
        {
            processWord(seqBlock);
            skipSpace(seqBlock);
        }
    }
    else
    {
        CDebug::reportError(ERROR_BlockTooLong);
    }
}

/// @brief
void CSequenceBlock::processWord( const uint8* seqBlock )
{
    uint8 address = seqBlock[processIndex++];
    CWord::assign(address, seqBlock, &processIndex);
}

/// @brief
void CSequenceBlock::skipSpace( const uint8* seqBlock )
{
    while(  (' '  == seqBlock[processIndex]) ||
            ('\n' == seqBlock[processIndex]) ||
            ('\r' == seqBlock[processIndex]) )
    {
        processIndex++;
    }
}
