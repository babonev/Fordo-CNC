///=============================================================================
/// @file      CCircularMotion.cpp
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      Apr 20, 2017
///
/// @copyright
///=============================================================================

#include "Std_Types.h"
#include "IMotionBlock.h"
#include "CCircularMotion.h"
#include "DebugUtilities.h"


///=============================================================================
/// @brief PUBLIC METHODS
///=============================================================================

CCircularMotion::~CCircularMotion()
{

}

void CCircularMotion::execute( void )
{
    if ( mRadius != 0 )
    {
        makeArc(0,0,mCircleDirection,0);

        IMotionBlock::execute();
    }
}

void CCircularMotion::set_radius( const float radius )
{
    mRadius = radius;
    CDebug::traceEvent(EVENT_RadiusSet, radius);
}

void CCircularMotion::set_arcRadius( const float radius )
{
    mRadius = radius;
    CDebug::traceEvent(EVENT_RadiusSet, radius);
}

void CCircularMotion::set_arcOffset( const EAxis axis, const float steps )
{

}


///=============================================================================
/// @brief PRIVATE METHODS
///=============================================================================

uint32 CCircularMotion::calcDamperingProfile( void )
{

    return 0;
}

void CCircularMotion::makeArc( const sint32 centerX, const sint32 centerY, const uint8 direction, const uint32 radius )
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
