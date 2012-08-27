/**
 * \file dcs/math/function/round.hpp
 *
 * \brief Round a floating-point number.
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

#ifndef DCS_MATH_FUNCTION_ROUND_HPP
#define DCS_MATH_FUNCTION_ROUND_HPP


#if __cplusplus > 201103L
// C++0x has bind
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

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_ROUND_HPP
