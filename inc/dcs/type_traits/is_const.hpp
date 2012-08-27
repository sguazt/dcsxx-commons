/**
 * \file dcs/type_traits/is_const.hpp
 *
 * \brief Tells if a given type is a (top) level const-qualified type.
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

#ifndef DCS_TYPE_TRAITS_IS_CONST_HPP
#define DCS_TYPE_TRAITS_IS_CONST_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101300) // 1.13


#include <boost/type_traits/is_const.hpp>

namespace dcs { namespace type_traits {

using boost::is_const;

}} // Namespace dcs::type_traits


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/type_traits/integral_constant.hpp>

namespace dcs { namespace type_traits {

template <typename T>
struct is_const
{
	static const bool value = false;
	//enum { value = false }; // More portable but loose bool type
	typedef false_type type;
	typedef bool value_type;
};

template <typename T>
struct is_const<T const>
{
	static const bool value = true;
	//enum { value = true }; // More portable but loose bool type
	typedef true_type type;
	typedef bool value_type;
};

}} // Namespace dcs::type_traits


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_TYPE_TRAITS_IS_CONST_HPP
