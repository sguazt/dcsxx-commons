/**
 * \file dcs/type_traits/make_unsigned.hpp
 *
 * \brief Make a given type an unsigned type.
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
