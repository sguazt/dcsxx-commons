/**
 * \file dcs/type_traits/integral_constant.hpp
 *
 * \brief Base class for all the value-based type-traits.
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
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
