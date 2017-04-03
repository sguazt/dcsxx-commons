/**
 * \file dcs/math/function/round.hpp
 *
 * \brief Round a floating-point number.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2012 Marco Guazzone (marco.guazzone@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DCS_MATH_FUNCTION_ROUND_HPP
#define DCS_MATH_FUNCTION_ROUND_HPP


#if __cplusplus > 201103L
// C++0x has 'round'
#	include <cmath>
#	define DCS_MATH_FUNCTION_ROUND_NS_ ::std
#elif defined(__GNUC__)
#	include <tr1/cmath>
#	define DCS_MATH_FUNCTION_ROUND_NS_ ::std::tr1
#else
#	include <dcs/detail/config/boost.hpp>
// Use Boost TR1
#	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103400) // 1.34
#		error "Required Boost libraries version >= 1.34."
#	endif
#	include <boost/tr1/cmath.hpp>
#	define DCS_MATH_FUNCTION_ROUND_NS_ ::std::tr1
#endif // __cplusplus


namespace dcs { namespace math {

using DCS_MATH_FUNCTION_ROUND_NS_::round;
using DCS_MATH_FUNCTION_ROUND_NS_::roundf;
using DCS_MATH_FUNCTION_ROUND_NS_::roundl;

/**
 * \brief Round the given value to the given precision.
 *
 * \param x The value to round.
 * \param digits The number of decimal places to be used- Negative values are allowed (see details).
 * \return The original value rounded to the given number of decimal places.
 *
 * Rounding to a negative number of digits means rounding to a power of ten, so for example `round(x, -2)` rounds to the nearest hundred.
 *
 * For instance:
 *  roundp(0.1234567, 0) -> 0
 *  roundp(0.1234567, 1) -> 0.1
 *  roundp(0.1234567, 2) -> 0.12
 *  roundp(0.1234567, 5) -> 0.12346
 *  roundp(0.1234567, 6) -> 0.123457
 *  roundp(123.4567, -1) -> 120
 *  roundp(123.4567, -2) -> 100
 *  roundp(123.4567, -3) -> 0
 */
template <typename RealT>
RealT roundp(RealT x, int digits)
{
	x *= std::pow(10, digits);
	x = round(x);
	x /= std::pow(10, digits);

	return x;
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_ROUND_HPP
