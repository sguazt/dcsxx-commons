/**
 * \file dcs/type_traits/const_literal.hpp
 *
 * \brief Makes the given type suitable for const literals;
 *
 * Copyright (C) 2009-2010  Distributed Computing System (DCS) Group, Computer
 * Science Department - University of Piemonte Orientale, Alessandria (Italy).
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */

#ifndef DCS_TYPE_TRAITS_CONST_LITERAL_HPP
#define DCS_TYPE_TRAITS_CONST_LITERAL_HPP


#if __cplusplus > 201103L
# 	define CONST_REAL_ const 
#else
# 	define CONST_REAL_ /**/
#endif

namespace dcs { namespace type_traits {

/**
 * \brief Makes the given type suitable for const literals;
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename T>
struct const_literal;

template <typename T>
struct const_literal
{
	typedef T const type;
};

template <>
struct const_literal<float>
{
	typedef float CONST_REAL_ type;
};

template <>
struct const_literal<double>
{
	typedef double CONST_REAL_ type;
};

template <>
struct const_literal<long double>
{
	typedef long double CONST_REAL_ type;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_CONST_LITERAL_HPP
