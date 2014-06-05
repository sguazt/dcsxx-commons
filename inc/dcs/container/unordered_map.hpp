/**
 * \file dcs/container/unordered_map.hpp
 *
 * \brief Unordered associative maps.
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

#ifndef DCS_CONTAINER_UNORDERED_MAP_HPP
#define DCS_CONTAINER_UNORDERED_MAP_HPP


#if __cplusplus > 201103L
// C++0x has unordered_map
# 	include <unordered_map>
# 	define DCS_CONTAINER_UNORDERED_MAP_NS_ ::std
#else
# 	include <dcs/detail/config/boost.hpp>
# 	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103600) // 1.36
# 		error "Required Boost library version >= 1.36."
# 	endif
# 	include <boost/unordered_map.hpp>
# 	define DCS_CONTAINER_UNORDERED_MAP_NS_ ::boost
#endif // __cplusplus


namespace dcs { namespace container {

using DCS_CONTAINER_UNORDERED_MAP_NS_::unordered_map;

}} // Namespace dcs::container

#endif // DCS_CONTAINER_UNORDERED_MAP_HPP
