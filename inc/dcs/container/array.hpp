/**
 * \file dcs/container/array.hpp
 *
 * \brief Container wrapper for constant-size arrays.
 *
 * \brief Add a summary of functionalities provided by this file.
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

#ifndef DCS_CONTAINER_ARRAY_HPP
#define DCS_CONTAINER_ARRAY_HPP


#if __cpluscplus > 201103L
// C++0x has array
# 	include <array>
# 	define DCS_CONTAINER_ARRAY_NS_ ::std
#else
// Use boost::array
# 	include <dcs/detail/config/boost.hpp>
# 	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101700) // 1.17
# 		error "Required Boost library version >= 1.17."
# 	endif
# 	include <boost/array.hpp>
# 	define DCS_CONTAINER_ARRAY_NS_ ::boost
#endif // __cplusplus


namespace dcs { namespace container {

using DCS_CONTAINER_ARRAY_NS_::array;

}} // Namespace


#endif // DCS_CONTAINER_ARRAY_HPP
