/*
** EPITECH PROJECT, 2020
** LibMy - math module
** File description:
** The main header for the math module
*/

/// @file
///
/// Defines a variety of function related to calculations.

#ifndef __LIBMY_MATH_H__
#define __LIBMY_MATH_H__

#include "libmy/internal/attributes.h"

MY_API_BEGIN

#ifndef LIBMY_MODULE_MATH
    #error "LibMy: 'libmy/math.h' is included, \
but math module is not present"
#endif

/// The value of PI, we don't use M_PI for portablilty reasons
#define MY_PI (3.1415926535897932384)

/// Converts the passed double from radians to degrees.
///
/// @param radians
///
/// @returns The angle, converted to degrees.
/// @since 0.2.0
MY_INLINE double my_to_degrees(double radians)
{
    return radians * 180.0 / MY_PI;
}

/// Converts the passed float from radians to degrees.
///
/// @param radians
///
/// @returns The angle, converted to degrees.
/// @since 0.2.0
MY_INLINE float my_to_degreesf(float radians)
{
    return radians * 180.0 / MY_PI;
}

/// Converts the passed double from degrees to radians.
///
/// @param degrees
///
/// @returns The angle, converted to radians.
/// @since 0.2.0
MY_INLINE double my_to_radians(double degrees)
{
    return degrees * MY_PI / 180.0;
}

/// Converts the passed float from degrees to radians.
///
/// @param degrees
///
/// @returns The angle, converted to radians.
/// @since 0.2.0
MY_INLINE float my_to_radiansf(float degrees)
{
    return degrees * MY_PI / 180.0;
}

/// Computes @c nb to the power of @c power.
///
/// @param nb    The number.
/// @param power The exponent, cannot be @c NULL.
///
/// @returns The result, or 0 if it is above @c INT_MAX or below @c INT_MIN.
/// @since 0.1.0
MY_API int my_compute_power(int nb, int power);

/// Computes the integral square root of @c nb.
///
/// @param nb The number.
///
/// @returns The square root of @c nb, or 0 if it is not an integer.
/// @since 0.1.0
MY_API int my_compute_square_root(int nb);

/// Finds the next prime number after @c nb.
/// If @c nb is prime, then this function returns @c nb.
///
/// @param nb The number.
///
/// @returns The prime number.
/// @since 0.1.0
MY_API int my_find_prime_sup(int nb);

/// Is @c nb negative?
///
/// @param nb The number.
///
/// @returns Whether @c nb is negative.
/// @since 0.1.0
MY_API int my_isneg(int nb);

/// Checks whether @c nb is prime.
///
/// @param nb The number to check.
///
/// @returns Whether @c nb is prime.
/// @since 0.1.0
MY_API int my_is_prime(int nb);

MY_API_END

#endif
