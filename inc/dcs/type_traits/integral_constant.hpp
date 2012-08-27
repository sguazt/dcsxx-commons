/**
 * \file dcs/type_traits/integral_constant.hpp
 *
 * \brief Base class for all the value-based type-traits.
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

#ifndef DCS_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define DCS_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP


#include <dcs/detail/config/boost.hpp>

#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101300) // 1.13


#include <boost/type_traits/integral_constant.hpp>

namespace dcs { namespace type_traits {

using ::boost::integral_constant;

}} // Namespace dcs::type_traits


#else


namespace dcs { namespace type_traits {

/**
 * \brief Base class for all the value-based type-traits.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <class T, T val>
struct integral_constant
{
	typedef integral_constant<T, val> type;
	typedef T value_type;
	static const T value = val;
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
