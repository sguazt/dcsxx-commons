/**
 * \file dcs/type_traits/make_unsigned.hpp
 *
 * \brief Make a given type an unsigned type.
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

#ifndef DCS_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define DCS_TYPE_TRAITS_MAKE_UNSIGNED_HPP


#if __cplusplus > 201103L
// C++0x has type-traits
#	include <type_traits>
#	define DCS_TYPE_TRAITS_MAKE_UNSIGNED_NS_ ::std
#else
// Use Boost smart-pointers
#	include <dcs/detail/config/boost.hpp>
#	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101300) // 1.13
#		error "Required Boost library version >= 1.13"
#	endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION
#	include <boost/type_traits/make_unsigned.hpp>
#	define DCS_TYPE_TRAITS_MAKE_UNSIGNED_NS_ ::boost
#endif // __cplusplus

namespace dcs { namespace type_traits {

using DCS_TYPE_TRAITS_MAKE_UNSIGNED_NS_::make_unsigned;

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_MAKE_UNSIGNED_HPP
