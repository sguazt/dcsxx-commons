/**
 * \file dcs/type_traits/is_const.hpp
 *
 * \brief Tells if a given type is a (top) level const-qualified type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2009 Marco Guazzone (marco.guazzone@gmail.com)
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
