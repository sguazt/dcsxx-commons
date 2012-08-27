/**
 * \file dcs/math/constants.hpp
 *
 * \brief Type-safe mathematical constants.
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

#ifndef DCS_MATH_CONSTANTS_HPP
#define DCS_MATH_CONSTANTS_HPP


#include <dcs/type_traits/const_literal.hpp>
#include <limits>


namespace dcs { namespace math { namespace constants {

/// The mathematical constant \f$\infty\f$.
template <typename T>
struct infinity
{
	typedef T value_type;
	static typename ::dcs::type_traits::const_literal<value_type>::type value;
};
template <typename T>
typename ::dcs::type_traits::const_literal<T>::type infinity<T>::value = ::std::numeric_limits<T>::has_infinity ? ::std::numeric_limits<T>::infinity() : ::std::numeric_limits<T>::max();


/// The mathematical constant \f$e=2.71828\ldots\f$, also known as the
/// <em>Euler's number</em>.
template <typename T>
struct e
{
	typedef T value_type;
	static typename ::dcs::type_traits::const_literal<value_type>::type value; // = 2.718281828459045;
};
template <typename T>
typename ::dcs::type_traits::const_literal<T>::type e<T>::value = static_cast<T>(2.718281828459045);

template <>
struct e<double>
{
	typedef double value_type;
	static ::dcs::type_traits::const_literal<value_type>::type value; // = 2.7182818284590452354;
};
::dcs::type_traits::const_literal<double>::type e<double>::value = static_cast<double>(2.7182818284590452354);

template <>
struct e<long double>
{
	typedef long double value_type;
	static ::dcs::type_traits::const_literal<value_type>::type value; // = 2.7182818284590452353602874713526625L;
};
::dcs::type_traits::const_literal<long double>::type e<long double>::value = static_cast<long double>(2.7182818284590452353602874713526625L);


/// The mathematical constant \f$\pi=3.141593\ldots\f$.
template <typename T>
struct pi
{
	typedef T value_type;
	static typename ::dcs::type_traits::const_literal<value_type>::type value; // = 3.141592653589793;
};
template <typename T>
typename ::dcs::type_traits::const_literal<T>::type pi<T>::value = static_cast<T>(3.141592653589793);

template <>
struct pi<double>
{
	typedef double value_type;
	static ::dcs::type_traits::const_literal<value_type>::type value; // = 3.14159265358979323846;
};
::dcs::type_traits::const_literal<double>::type pi<double>::value = static_cast<double>(3.14159265358979323846);

template <>
struct pi<long double>
{
	typedef long double value_type;
	static ::dcs::type_traits::const_literal<value_type>::type value; // = 3.1415926535897932384626433832795029L;
};
::dcs::type_traits::const_literal<long double>::type pi<long double>::value = static_cast<long double>(3.1415926535897932384626433832795029L);


/// The half of the mathematical constant \f$\pi=3.141593\ldots\f$.
template <typename T>
struct half_pi
{
	typedef T value_type;
	static typename ::dcs::type_traits::const_literal<value_type>::type value; // = pi<value_type>::value / value_type(2);
};
template <typename T>
typename ::dcs::type_traits::const_literal<T>::type half_pi<T>::value = pi<T>::value / T(2);


/// The double of the mathematical constant \f$\pi=3.141593\ldots\f$.
template <typename T>
struct double_pi
{
	typedef T value_type;
	static typename ::dcs::type_traits::const_literal<value_type>::type value; // = pi<value_type>::value * value_type(2);
};
template <typename T>
typename ::dcs::type_traits::const_literal<T>::type double_pi<T>::value = pi<T>::value * T(2);

}}} // Namespace dcs::math::constants


#endif // DCS_MATH_CONSTANTS_HPP
