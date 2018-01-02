/**
 * \file dcs/math/detail/float.hpp
 *
 * \brief Utilities for floating-point comparison.
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

#ifndef DCS_MATH_DETAIL_FLOAT_HPP
#define DCS_MATH_DETAIL_FLOAT_HPP


#include <algorithm>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
//#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <limits>


namespace dcs { namespace math { namespace detail {

// See also:
// - https://adtmag.com/Articles/2000/03/16/Comparing-Floats-How-To-Determine-if-Floating-Quantities-Are-Close-Enough-Once-a-Tolerance-Has-Been.aspx
// - https://adtmag.com/articles/2000/03/16/comparing-floatshow-to-determine-if-floating-quantities-are-close-enough-once-a-tolerance-has-been-r.aspx
// - https://bitbashing.io/comparing-floats.html
// - http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
// - https://docs.python.org/3/tutorial/floatingpoint.html#tut-fp-issues
// - http://floating-point-gui.de/errors/comparison/
// - http://fcmp.sourceforge.net/
// - http://grouper.ieee.org/groups/754/
// - https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#Floating-Point_Comparison
// - http://learningcppisfun.blogspot.com/2010/04/comparing-floating-point-numbers.html
// - https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
// - https://stackoverflow.com/questions/1343890/rounding-number-to-2-decimal-places-in-c
// - https://twistedape.me.uk/2016/02/02/comparing-floating-point-numbers/
// . http://www.boost.org/doc/libs/release/libs/math/doc/html/math_toolkit/float_comparison.html
// - http://www.boost.org/doc/libs/release/libs/test/doc/html/boost_test/testing_tools/extended_comparison/floating_point.html
// - https://www.codeproject.com/Articles/383871/Demystify-Csharp-floating-point-equality-and-relat
// - https://www.gnu.org/software/libc/manual/html_node/Floating-Point-Parameters.html
// - https://www.gnu.org/software/gsl/doc/html/math.html
// - http://www.parashift.com/c++-faq-lite/newbie.html#faq-29.16
// - http://www.petebecker.com/js/js200012.html
// .
//


/**
 * \brief Perform approximate floating-point comparison.
 *
 * This function determines whether \a x and \a y are approximately equal to a
 * relative accuracy \a epsilon.
 *
 * To perform the approximate floating-point comparison, this function
 * implements the algorithm proposed by D.E. Knuth in Section 4.2.2 of (Knuth,1997) (see REFERENCES).
 *
 * The relative accuracy is measured using an interval of size \f$2 \delta\f$,
 * where \f$\delta = 2^k \epsilon\f$ and \f$k\f$ is the maximum base-2 exponent
 * of \a x and \a y as computed by the function `std::frexp`.
 *
 * If \a x and \a y lie within this interval, they are considered approximately
 * equal and the function returns `0`.
 * Otherwise if \a x < \a y, the function returns `-1`, or if \a x > \a y, the
 * function returns `+1`.
 *
 * \note \a x and \a y are compared to relative accuracy, so this function is
 *       not suitable for testing whether a value is approximately zero.
 *       Also, this function may not work correctly with degenerate cases.
 *       For instance, when both \a x and \a y are NaN, this function return 0,
 *       which is incorrect because, according to the IEEE 754 standard, NaN is
 *       always different from any floating-point number including itself
 *       (indeed, NaN is "unordered").
 *
 * The implementation is based on the one provided by the GNU Scientific Library
 * (GSL) which in turns is based on the package fcmp by T.C. Belding.
 *
 * \copyright GNU Scientific Library (GSL) 2.4 Copyright (c) 2002 Gert Van den Eynde (https://www.gnu.org/software/gsl)
 * \copyright fcmp 1.2.2 Copyright (c) 1998-2000 Theodore C. Belding, University of Michigan Center for the Study of Complex Systems (Ted.Belding@umich.edu)
 *
 * REFERENCES
 * - D.E. Knuth "The Art of Computer Programming, Volume 2: Seminumerical Algorithms, 3rd Edition," Addison-Wesley, 1997.
 * .
 */
template <typename T>
inline
typename ::boost::enable_if<
	::boost::is_floating_point<T>,
	int
>::type fcmp(const T x, const T y, const T epsilon)
{
	// Find exponent of largest absolute value

	const T max = (std::fabs(x) > std::fabs(y)) ? x : y;

	int exponent;

	std::frexp(max, &exponent);

	// Form a neighborhood of size  2 * delta

	const T delta = std::ldexp(epsilon, exponent);

	const T difference = x - y;

	if (difference > delta) // x > y
	{
		return 1;
	}
	if (difference < -delta) // x < y
	{
		return -1;
	}
	// -delta <= difference <= delta => x ~=~ y
	return 0;
}


/**
 * \brief x is approximately equal to y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \approx y\,\text{ if and only if } |y-x|\le\epsilon\max(e_x,e_y)
 * \f]
 * where \f$e_x\f$ and \f$e_y\f$ are the exponent of \f$x\f$ and \f$y\f$,
 * respectively.
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
	// Try first with standard comparison (handles the case when both x and y are zero or have other special values like inf or NaN)
	if (x == y)
	{
		// Tolerance is useless when both numbers are exactly the same
		return true;
	}

	// Handle degenerate cases
	//if (::std::isnan(x) || ::std::isinf(x) || ::std::isnan(y) || ::std::isinf(y))
	if (!::std::isfinite(x) || !::std::isfinite(y))
	{
		// Tolerance is useless when at least one number is not finite
		return x == y;
	}

	return fcmp(x, y, tol) == 0;
}


/**
 * \brief x is definitely equal to y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \sim y\,\text{ if and only if } |y-x|\le\epsilon\min(e_x,e_y)
 * \f]
 * where \f$e_x\f$ and \f$e_y\f$ are the exponent of \f$x\f$ and \f$y\f$,
 * respectively.
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
	// Try first with standard comparison (handles the case when both x and y are zero or have other special values like inf or NaN)
	if (x == y)
	{
		// Tolerance is useless when both numbers are exactly the same
		return true;
	}

	// Handle degenerate cases
	//if (::std::isnan(x) || ::std::isinf(x) || ::std::isnan(y) || ::std::isinf(y))
	if (!::std::isfinite(x) || !::std::isfinite(y))
	{
		// Tolerance is useless when at least one number is not finite
		return x == y;
	}

	// Check for numbers tha are very close to zero
	const T zero = 0;
	const T min_val = std::numeric_limits<T>::min();
	const T diff = ::std::fabs(x-y);
	if (x == zero || y == zero || diff < min_val)
	{
		// x or y is zero or both are extremely close to it
		// relative error is less meaningful here
		return diff < (tol*min_val);
	}

	// Otherwise, use the Knuth's method

	// - Find the min(x,y) and gets its exponent
	const T min = (std::fabs(x) < std::fabs(y)) ? x : y;
	int exponent = 0;
	std::frexp(min, &exponent);

	// - Form a neighborhood of size  2 * delta
	const T delta = std::ldexp(tol, exponent);
	const T difference = x - y;

	// - Now check if the number are very close to each other
	if (difference > delta      // x > y
		|| difference < -delta) // x < y
	{
		return false;
	}
	return true; // -delta <= difference <= delta => x ~=~ y
}


/**
 * \brief x is definitely greater than y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \succ y\,\text{ if and only if } x-y > \epsilon\max(e_x,e_y)
 * \f]
 * where \f$e_x\f$ and \f$e_y\f$ are the exponent of \f$x\f$ and \f$y\f$,
 * respectively.
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
	// Handle degenerate cases
	//if (::std::isnan(x) || ::std::isinf(x) || ::std::isnan(y) || ::std::isinf(y))
	if (!::std::isfinite(x) || !::std::isfinite(y))
	{
		// Tolerance is useless when at least one number is not finite
		return x > y;
	}

	return fcmp(x, y, tol) > 0;
}


/**
 * \brief x is definitely less than y.
 *
 * Inspired by [1]:
 * \f[
 *  $x \prec y\,\text{ if and only if } y-x > \epsilon\max(e_x,e_y)
 * \f]
 * where \f$e_x\f$ and \f$e_y\f$ are the exponent of \f$x\f$ and \f$y\f$,
 * respectively.
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
	// NOTE: don't use standard comparison operators because they do not take into account the given tolerance.
	//       For instance:
	//         x = 0.1233
	//         y = 0.1234
	//         -> x <  y if tol >= 1e-4
	//            but
	//            x == y if tol <  1e-3

	// Handle degenerate cases
	//if (::std::isnan(x) || ::std::isinf(x) || ::std::isnan(y) || ::std::isinf(y))
	if (!::std::isfinite(x) || !::std::isfinite(y))
	{
		// Tolerance is useless when at least one number is not finite
		return x < y;
	}

	return fcmp(x, y, tol) < 0;
}

}}} // Namespace dcs::math::detail


#endif // DCS_MATH_DETAIL_FLOAT_HPP
