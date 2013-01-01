/**
 * \file dcs/network/byte_order.hpp
 *
 * \brief Handle the conversion network <-> host byte order.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone (marco.guazzone@gmail.com)
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons (below referred to as "this program").
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_NETWORK_BYTE_ORDER_HPP
#define DCS_NETWORK_BYTE_ORDER_HPP


#include <arpa/inet.h> // Available in POSIX.1-2001 systems


namespace dcs { namespace network {

template <typename T>
struct byte_order
{
	T host_to_network(T v);
	T network_to_host(T v);
};

template <>
struct byte_order< ::boost::uint32_t >
{
	static ::boost::uint32_t host_to_network(::boost::uint32_t v)
	{
		return ::htonl(v);
	}

	static ::boost::uint32_t network_to_host(::boost::uint32_t v)
	{
		return ::ntohl(v);
	}
};

template <>
struct byte_order< ::boost::uint16_t >
{
	static ::boost::uint16_t host_to_network(::boost::uint16_t v)
	{
		return ::htons(v);
	}

	static ::boost::uint16_t network_to_host(::boost::uint16_t v)
	{
		return ::ntohs(v);
	}
};

}} // Namespace dcs::network

#endif // DCS_NETWORK_BYTE_ORDER_HPP
