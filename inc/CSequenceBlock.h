///=============================================================================
/// @file      CGCodeProcessor.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      05.Nov.2016
///
/// @copyright
///=============================================================================

#ifndef INC_CSEQUENCEBLOCK_H_
#define INC_CSEQUENCEBLOCK_H_

/// @brief
class CSequenceBlock
{
public:
    /// Interface methods
    void process( const uint8* seqBlock, const uint8 length );

private:
    /// Constants
    static const uint8 BLOCK_MAX_LENGHT = 120;

    /// Temporary values indicating status of processing
    uint8 processIndex;

    /// Functions processing main elements
    void processWord(const uint8* seqBlock);

    /// Auxiliary functions
    void skipSpace(const uint8* seqBlock);
};


#endif /// INC_CSEQUENCEBLOCK_H_
