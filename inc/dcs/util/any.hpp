/**
 * \file dcs/util/any.hpp
 *
 * \brief Safe, generic container for single values of different value types.
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

#ifndef DCS_UTIL_ANY_HPP
#define DCS_UTIL_ANY_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102300) // 1.23
# 	error "Required Boost library >= 1.23"
#endif

#include <boost/any.hpp>


namespace dcs { namespace util {

using ::boost::any;
using ::boost::any_cast;

}} // Namespace dcs::util


#endif // DCS_UTIL_ANY_HPP
