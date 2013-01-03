/**
 * \file dcs/network/pdu.hpp
 *
 * \brief Common functions and classes for network Protocol Data Units (PDUs).
 *
 * In telecommunications, the term protocol data unit (PDU) has the following
 * meanings:
 * - Information that is delivered as a unit among peer entities of a network
 *   and that may contain control information, such as address information, or
 *   user data.
 * - In a layered system, a unit of data which is specified in a protocol of a
 *   given layer and which consists of protocol-control information and possibly
 *   user data of that layer.
 * .
 * For instance, for the first 4 layers of the OSI model we have:
 * - The Layer 1 (Physical Layer) PDU is the bit or, more generally, symbol
 *   (can also been seen as "stream")
 * - The Layer 2 (Data Link Layer) PDU is the frame
 * - The Layer 3 (Network Layer) PDU is the packet
 * - The Layer 4 (Transport Layer) PDU is the segment for TCP, or the datagram
 *   for UDP
 * .
 *
 * REFERENCES
 * -# "Protocol Data Unit", Wikipedia, 2013
 *    [<a href="https://en.wikipedia.org/wiki/Protocol_data_unit">Wiki page</a>]
 * .
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

#ifndef DCS_NETWORK_PDU_HPP
#define DCS_NETWORK_PDU_HPP


#include <boost/cstdint.hpp>


namespace dcs { namespace network {

class base_pdu
{
	public: virtual ~base_pdu()
	{
	}

	public: virtual ::boost::uint8_t const* payload() const = 0;

	public: virtual ::boost::uint32_t payload_size() const = 0;
}; // base_pdu

}} // Namespace dcs::network

#endif // DCS_NETWORK_PDU_HPP
