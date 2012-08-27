/**
 * \file dcs/container/circular_buffer.hpp
 *
 * \brief A STL compliant container also known as ring or cyclic buffer.
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

#ifndef DCS_CONTAINER_CIRCULAR_BUFFER_HPP
#define DCS_CONTAINER_CIRCULAR_BUFFER_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101700) // 1.35
#	error "Required Boost library version >= 1.35."
#endif

#include <boost/circular_buffer.hpp>

namespace dcs { namespace container {

using ::boost::circular_buffer;

}} // Namespace dcs::container


#endif // DCS_CONTAINER_CIRCULAR_BUFFER_HPP
