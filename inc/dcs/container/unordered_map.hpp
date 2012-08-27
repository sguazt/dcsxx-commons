/**
 * \file dcs/container/unordered_map.hpp
 *
 * \brief Unordered associative maps.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
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
