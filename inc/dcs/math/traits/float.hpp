/**
 * \file dcs/math/traits/float.hpp
 *
 * \brief Traits class for floating-point type.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_MATH_TRAITS_FLOAT_HPP
#define DCS_MATH_TRAITS_FLOAT_HPP


#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <dcs/math/detail/float.hpp>
#include <limits>


namespace dcs { namespace math {

template <typename T, typename Enable_ = void>
struct float_traits;

template <typename T>
struct float_traits<T, typename ::boost::enable_if< ::boost::is_floating_point<T> >::type>
{
	/// Default tolerance for floating-point comparison.
	static const T tolerance;

	static bool approximately_equal(T x, T y, T tol)
	{
		return detail::approximately_equal(x, y, tol);
	}


	static bool approximately_equal(T x, T y)
	{
		return detail::approximately_equal(x, y, tolerance);
	}


	static bool essentially_equal(T x, T y, T tol)
	{
		return detail::essentially_equal(x, y, tol);
	}


	static bool essentially_equal(T x, T y)
	{
		return detail::essentially_equal(x, y, tolerance);
	}


	static bool definitely_less(T x, T y, T tol)
	{
		return detail::definitely_less(x, y, tol);
	}


	static bool definitely_less(T x, T y)
	{
		return detail::definitely_less(x, y, tolerance);
	}


	static bool definitely_less_equal(T x, T y, T tol)
	{
		return definitely_less(x, y, tol) || approximately_equal(x, y, tol);
	}


	static bool definitely_less_equal(T x, T y)
	{
		return definitely_less_equal(x, y, tolerance);
	}


	static bool definitely_greater(T x, T y, T tol)
	{
		return detail::definitely_greater(x, y, tol);
	}


	static bool definitely_greater(T x, T y)
	{
		return detail::definitely_greater(x, y, tolerance);
	}


	static bool definitely_greater_equal(T x, T y, T tol)
	{
		return definitely_greater(x, y, tol) || approximately_equal(x, y, tol);
	}


	static bool definitely_greater_equal(T x, T y)
	{
		return definitely_greater_equal(x, y, tolerance);
	}


/*
bool is_nan(float f)
{
    return (*reinterpret_cast<uint32_t*>(&f) & 0x7f800000) == 0x7f800000 && (*reinterpret_cast<uint32_t*>(&f) & 0x007fffff) != 0;
}

bool is_finite(float f)
{
    return (*reinterpret_cast<uint32_t*>(&f) & 0x7f800000) != 0x7f800000;
}

// if this symbol is defined, NaNs are never equal to anything (as is normal in IEEE floating point)
// if this symbol is not defined, NaNs are hugely different from regular numbers, but might be equal to each other
#define UNEQUAL_NANS 1
// if this symbol is defined, infinites are never equal to finite numbers (as they're unimaginably greater)
// if this symbol is not defined, infinities are 1 ULP away from +/- FLT_MAX
#define INFINITE_INFINITIES 1
//
// test whether two IEEE floats are within a specified number of representable values of each other
// This depends on the fact that IEEE floats are properly ordered when treated as signed magnitude integers
bool equal_float(float lhs, float rhs, uint32_t max_ulp_difference)
{
#ifdef UNEQUAL_NANS
	if(is_nan(lhs) || is_nan(rhs))
	{
		return false;
	}
#endif
#ifdef INFINITE_INFINITIES
	if((is_finite(lhs) && !is_finite(rhs)) || (!is_finite(lhs) && is_finite(rhs)))
	{
		return false;
	}
#endif
	int32_t left(*reinterpret_cast<int32_t*>(&lhs));
	// transform signed magnitude ints into 2s complement signed ints
	if(left < 0)
	{
		left = 0x80000000 - left;
	}
	int32_t right(*reinterpret_cast<int32_t*>(&rhs));
	// transform signed magnitude ints into 2s complement signed ints
	if(right < 0)
	{
		right = 0x80000000 - right;
	}
	if(static_cast<uint32_t>(std::abs(left - right)) <= max_ulp_difference)
	{
		return true;
	}
	return false;
}
*/
};

template <typename T>
const T float_traits<T, typename ::boost::enable_if< ::boost::is_floating_point<T> >::type>::tolerance = static_cast<T>(100)*::std::numeric_limits<T>::epsilon();

}} // Namespace dcs::math


#endif // DCS_MATH_TRAITS_FLOAT_HPP
