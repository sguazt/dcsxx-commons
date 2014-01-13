#ifndef DCS_MATH_FUNCTION_ISZERO_HPP
#define DCS_MATH_FUNCTION_ISZERO_HPP


#include <cmath>
#include <complex>
//#include <limits>


namespace dcs { namespace math {

/**
 * \brief Tells if the given real number is zero.
 *
 * \tparam RealT The real type of the argument
 * \param x The number to test for zero
 * \return \c true if \a x is zero, \c false otherwise.
 */
template <typename RealT>
bool iszero(RealT x)
{
    //return ::std::fabs(x) < ::std::numeric_limits<RealT>::epsilon();
    return ::std::fpclassify(x) == FP_ZERO;
}

/**
 * \brief Tells if the given complex number is zero.
 *
 * \tparam RealT The real type of the complex argument
 * \param z The number to test for zero
 * \return \c true if \a z is zero, \c false otherwise.
 */
template <typename RealT>
bool iszero(::std::complex<RealT> const& z)
{
    return iszero(z.real()) && iszero(z.imag());
}

}} // Namespace dcs::math

#endif // DCS_MATH_FUNCTION_ISZERO_HPP
