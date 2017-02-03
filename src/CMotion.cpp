///=============================================================================
/// @file      CMotion.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      19.Nov.2016
///
/// @copyright
/// @links     http://goldberg.berkeley.edu/pubs/XY-Interpolation-Algorithms.pdf
///=============================================================================

#include "..\inc\Std_Types.h"
#include "..\inc\CMotion.h"
#include "..\inc\DebugUtilities.h"

///=============================================================================
/// @brief Definition of static members
///=============================================================================
uint8 CMotion::rwIndex = 0;
uint8 CMotion::slRecordIdx = (uint8)(-1);
uint16* CMotion::pCurrentStep = CMotion::StepsList[0];
uint16 CMotion::StepsList[2][STEPS_LIST_LENGTH] = { 0 };

///=============================================================================
/// @brief
///=============================================================================
CMotion::CMotion()
{

}

/// @brief
/// @param
void CMotion::moveSpindle( const sint32 deltaZ )
{
    EDirection dir = _DIR(deltaZ);

    for( uint32 steps = 0; steps < _ABS(deltaZ); steps++ )
    {
        doStepZ(dir);
    }
}

/// @brief Uses Bresenham's line algorithm to move both motors
/// @param
/// @param
void CMotion::makeLine( const sint32 deltaX, const sint32 deltaY )
{
    /// Direction to move
    const EDirection dirX = _DIR(deltaX);
    const EDirection dirY = _DIR(deltaY);
    /// Get absolute values
    const uint32 dX = _ABS(deltaX);
    const uint32 dY = _ABS(deltaY);
    /// Variables used in next calculations
    uint32 over = 0;
    uint32 i;
    /// Initialize the next record in steps list
    initMove();

    if ( dX > dY )
    {
        for( i = 0; i < dX; ++i )
        {
            doStepX(dirX);
            over += dY;
            if ( over >= dX )
            {
                over -= dX;
                doStepY(dirY);
            }
        }
    }
    else
    {
        for( i = 0; i < dY; ++i )
        {
            doStepX(dirY);
            over += dX;
            if ( over >= dY )
            {
                over -= dY;
                doStepY(dirX);
            }
        }
    }
}


/// @brief http://members.chello.at/~easyfilter/bresenham.html
/// @param
void CMotion::makeArc( const sint32 centerX, const sint32 centerY, const uint8 direction, const uint32 radius )
{
    static const sint8 map[2][16] =
    {
    /*xo*/  {  0, -1,  1,  0,  1,  0,  0, -1, -1,  0,  0,  1,  0,  1, -1,  0 },
    /*yo*/  { -1,  0,  0,  1,  0, -1,  1,  0,  0,  1, -1,  0,  1,  0,  0, -1 }
    };

    sint32 fxy, dX, dY;
    sint32 relX = centerX;
    sint32 relY = centerY;
    sint32 outDirX = 0;
    sint32 outDirY = 0;
    sint32 d = direction;
    sint32 rad2 = (radius * radius);
    uint32 binrep = 0;
    sint8 f, a, b;

    do
    {
        fxy = (relX * relX) + (relY * relY) - rad2;
        dX = 2 * relX;
        dY = 2 * relY;
        f = (fxy < 0) ? 0 : 1;
        a = (dX < 0)  ? 0 : 1;
        b = (dY < 0)  ? 0 : 1;

        if(d) binrep = binrep + 8;
        if(f) binrep = binrep + 4;
        if(a) binrep = binrep + 2;
        if(b) binrep = binrep + 1;

        if ( binrep < sizeof(map)/sizeof(map[0]) )
        {
            outDirX = map[0][binrep];
            outDirY = map[1][binrep];
        }

        relX = relX + outDirX;
        relY = relY + outDirY;
    }
    while( (relX != centerX) || (relY = centerY) );
}

/// @brief
/// @param
/// @return
uint8 CMotion::getList( const uint16* pStepsList )
{
    uint8 listLength = slRecordIdx * RECORD_LENGTH;
    /// Return pointer to already filled list
    pStepsList = StepsList[rwIndex];
    /// Change the index to point to an empty list
    rwIndex = 1 - rwIndex;
    /// The other list start from the beginning
    slRecordIdx = 0;
    /// Return the number of records in the list
    return listLength;
}

/// @brief
void CMotion::initMove()
{
    slRecordIdx += RECORD_LENGTH;

    if ( slRecordIdx < STEPS_LIST_LENGTH )
    {
        pCurrentStep = &StepsList[rwIndex][slRecordIdx];
        /// Initialize all fields
        for(uint32 i = 0; i < RECORD_LENGTH; i++ )
        {
            pCurrentStep[i] = 0;
        }
    }
    else
    {
        CDebug::reportError(ERROR_StepsBufferFull);
    }
}

/// @brief
/// @param
void CMotion::doStepX( const EDirection dir )
{
    pCurrentStep[STEPS_X_INDEX] = 32;//CPositioning::get_feedrate()/2;
    /// TODO: Set direction.
}

/// @brief
/// @param
void CMotion::doStepY( const EDirection dir )
{
    pCurrentStep[STEPS_Y_INDEX] = 32;//CPositioning::get_feedrate()/2;
    /// TODO: Set direction.
}

/// @brief
/// @param
void CMotion::doStepZ( const EDirection dir )
{
    pCurrentStep[STEPS_Z_INDEX] = 32;//CPositioning::get_feedrate()/2;
    /// TODO: Set direction.
}
