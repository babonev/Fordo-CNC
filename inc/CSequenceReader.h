///=============================================================================
/// @file      CSequenceReader.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      05.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CSEQUENCEREADER_H_
#define INC_CSEQUENCEREADER_H_

#include "../inc/CExellonHeader.h"

///
///@brief
//
class CSequenceReader
{
public:
	///@brief Initialize internal variables
	static void init( void );
    ///@brief Interface methods
	static void process( const uint8* seqBlock, const uint32 length );

private:
    ///@brief
    static CExellonHeader hdr;
    ///@brief Counter of sequences used for debug
    static uint16 sequenceCount;

    ///@brief Functions processing main elements
    static void processWord(const uint8* seqBlock, uint8* const byteIndex);

    ///@brief Auxiliary functions
    static void skipSpace(const uint8* seqBlock, uint8* const byteIndex);
};


#endif /// INC_CSEQUENCEREADER_H_
