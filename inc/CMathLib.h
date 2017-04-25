///=============================================================================
/// @file      CMathLib.h
/// @brief
/// @details
/// @author    Boyan Bonev
/// @version   0.1
/// @date      21.Apr.2017
///
/// @copyright
///=============================================================================

#ifndef CMATHLIB_H_
#define CMATHLIB_H_

///
///@brief
//
class CMathLib
{
public:
    /// @brief Optimized SQRT algorithm - "The Magic Number (Quake 3)"
    /// @param
    /// @return
    static float SQRT( const float param );

    /// @brief Returns an Absolute value
    template <class T> static inline const T ABS(const T& a)
    {
        return ((a < 0) ? (-a) : a);
    }

    /// @brief
    template <class T> static inline const T& MAX(const T& a, const T& b)
    {
        return ((a > b) ? a : b);
    }

    /// @brief
    template <class T> static inline const T& MIN(const T& a, const T& b)
    {
        return ((a < b) ? a : b);
    }

private:
    ///@brief Magic number for SQRT algorithm
    static const float SQRT_MAGIC_F;
};



#endif /* CMATHLIB_H_ */
