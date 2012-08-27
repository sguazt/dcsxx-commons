/**
 * \file dcs/math/detail/float.hpp
 *
 * \brief Utilities for floating-point comparison.
 *
 * Copyright (C) 2012       Distributed Computing System (DCS) Group,
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

#ifndef DCS_MATH_DETAIL_FLOAT_HPP
#define DCS_MATH_DETAIL_FLOAT_HPP


#include <algorithm>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
//#include <cfloat>
#include <cmath>


namespace dcs { namespace math { namespace detail {

/// See also:
/// - http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
/// - http://www.petebecker.com/js/js200012.html
/// - http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
/// - http://www.parashift.com/c++-faq-lite/newbie.html#faq-29.16
/// - http://adtmag.com/articles/2000/03/16/comparing-floats-how-to-determine-if-floating-quantities-are-close-enough-once-a-tolerance-has-been.aspx
/// - http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/utf/testing-tools/floating_point_comparison.html
/// - http://learningcppisfun.blogspot.com/2010/04/comparing-floating-point-numbers.html
/// .


/**
 * \brief x is approximately equal to y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \approx y\,\text{ if and only if } |y-x|\le\epsilon\max(|x|,|y|)
 * \f]
 *
 * References:
 * -# Knuth, "The Art of Computer Programming: Vol.2" 3rd Ed, 1998, Sec. 4.2.2.
 * .
 */
template <typename T>
inline
typename ::boost::enable_if<
	::boost::is_floating_point<T>,
	bool
>::type approximately_equal(T x, T y, T tol)
{
	if (::std::isnan(x) || ::std::isnan(y))
	{
		// According to IEEE, NaN are different event by itself
		return false;
	}

	return ::std::abs(x-y) <= (::std::max(::std::abs(x), ::std::abs(y))*tol);
}


/**
 * \brief x is definitely equal to y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \sim y\,\text{ if and only if } |y-x|\le\epsilon\min(|x|,|y|)
 * \f]
 *
 * References:
 * -# Knuth, "The Art of Computer Programming: Vol.2" 3rd Ed, 1998, Sec. 4.2.2.
 * .
 */
template <typename T>
inline
typename ::boost::enable_if<
	::boost::is_floating_point<T>,
	bool
>::type essentially_equal(T x, T y, T tol)
{
	if (::std::isnan(x) || ::std::isnan(y))
	{
		// According to IEEE, NaN are different event by itself
		return false;
	}

	return ::std::abs(x-y) <= (::std::min(::std::abs(x), ::std::abs(y))*tol);
}


/**
 * \brief x is definitely greater than y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \succ y\,\text{ if and only if } x-y > \epsilon\max(|x|,|y|)
 * \f]
 *
 * References:
 * -# Knuth, "The Art of Computer Programming: Vol.2" 3rd Ed, 1998, Sec. 4.2.2.
 * .
 */
template <typename T>
inline
typename ::boost::enable_if<
	::boost::is_floating_point<T>,
	bool
>::type definitely_greater(T x, T y, T tol)
{
	return (x-y) > (::std::max(::std::abs(x), ::std::abs(y))*tol);
}


/**
 * \brief x is definitely less than y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \prec y\,\text{ if and only if } y-x > \epsilon\max(|x|,|y|)
 * \f]
 *
 * References:
 * -# Knuth, "The Art of Computer Programming: Vol.2" 3rd Ed, 1998, Sec. 4.2.2.
 * .
 */
template <typename T>
inline
typename ::boost::enable_if<
	::boost::is_floating_point<T>,
	bool
>::type definitely_less(T x, T y, T tol)
{
	return (y-x) > (::std::max(::std::abs(x), ::std::abs(y))*tol);
}

}}} // Namespace dcs::math::detail


#endif // DCS_MATH_DETAIL_FLOAT_HPP
