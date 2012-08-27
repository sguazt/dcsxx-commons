/**
 * \file dcs/math/function/sign.hpp
 *
 * \brief Compute the \e signum function.
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

#ifndef DCS_MATH_FUNCTION_SIGN_HPP
#define DCS_MATH_FUNCTION_SIGN_HPP


#include <cmath>
#include <complex>


namespace dcs { namespace math {

/**
 * \brief Compute the \e signum function.
 *
 * The signum function is defined as
 * \f{equation}{
 * sign(x) = \begin{cases}
 *           -1, & x < 0,\\
 *            0, & x = 0,\\
 *           +1, & x > 0.
 *           \end{cases}
 *\f}
 *
 * For complex arguments, the signum function is defined as:
 * \f{equation}{
 * sign(z) = \frac{z}{|z|}
 *\f}
 */
template <typename T>
T sign(T t);

template <typename T>
T sign(T t)
{
    if (t == 0)
	{
    	return T(0);
	}
    else
	{
    	return (t < 0) ? T(-1) : T(1);
	}
}

template <typename RealT>
::std::complex<RealT> sign(::std::complex<RealT> const& c)
{
	typedef ::std::complex<RealT> complex_type;

	return	(c == 0)
			? complex_type(0)
			: complex_type(c/::std::abs(c));
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_SIGN_HPP
