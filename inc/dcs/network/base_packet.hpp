/**
 * \file dcs/network/base_packet.hpp
 *
 * \brief Base class for network packets.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012-2013  Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_NETWORK_BASE_PACKET_HPP
#define DCS_NETWORK_BASE_PACKET_HPP


#include <boost/cstdint.hpp>


namespace dcs { namespace network {

class base_packet
{
	public: virtual ~base_packet()
	{
	}

	public: virtual ::boost::uint8_t const* payload() const = 0;

	public: virtual ::boost::uint32_t payload_size() const = 0;
}; // base_packet

}} // Namespace dcs::network

#endif // DCS_NETWORK_BASE_PACKET_HPP
