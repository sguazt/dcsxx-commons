/**
 * \file dcs/network/ip.hpp
 *
 * \brief Functions and classes for the IP protocol.
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

#ifndef DCS_NETWORK_IP_HPP
#define DCS_NETWORK_IP_HPP


#include <arpa/inet.h>
#include <boost/cstdint.hpp>
#include <boost/smart_ptr.hpp>
#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <dcs/network/pdu.hpp>
#include <netinet/ip.h> //FIXME: only available on systems conforming to 4.3BSD and SunOS
#include <iomanip>
#include <iostream>
#include <stdexcept>


namespace dcs { namespace network {

namespace detail { namespace /*<unnamed>*/ {

/// Extract the Version field
inline
::boost::uint8_t ip4_version(::boost::uint8_t vhl)
{
	return (vhl & 0xf0) >> 4;
}

/// Extract the Internet Header Length field
inline
::boost::uint8_t ip4_ihl(::boost::uint8_t vhl)
{
	return (vhl & 0x0f);
}

::std::string ip4_address_to_string(::in_addr const& addr)
{
	// NOTE: address must be in network byte order

	char buf[INET_ADDRSTRLEN];
	::inet_ntop(AF_INET, &addr, buf, sizeof(buf));
	return ::std::string(buf);
}

}} // Namespace detail::<unnamed>


/**
 * \brief The Internet Protocol (IP) datagram.
 *
 * The IP datagram header (from RFC791):
 * <pre>
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |Version|  IHL  |Type of Service|          Total Length         |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |         Identification        |Flags|      Fragment Offset    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Time to Live |    Protocol   |         Header Checksum       |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                       Source Address                          |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Destination Address                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Options                    |    Padding    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * </pre>
 */
class ip_packet: public base_pdu
{
	public: virtual ::boost::uint8_t version() const = 0;
}; // ip_packet

class ip4_packet: public ip_packet
{
	//TODO: private: typedef ::ip ip4_header;
//#define IP_RF 0x8000        /* reserved fragment flag */
//#define IP_DF 0x4000        /* dont fragment flag */
//#define IP_MF 0x2000        /* more fragments flag */
//#define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
	private: struct ip4_header
	{
		::boost::uint8_t vhl_; ///< Version and header length
		::boost::uint8_t tos_; ///< Type of service
		::boost::uint16_t len_; ///< Total length
		::boost::uint16_t id_; ///< Identification
		::boost::uint16_t off_;///< Fragment offset field
		::boost::uint8_t ttl_; ///< Time to live
		::boost::uint8_t proto_; ///< Protocol
		::boost::uint16_t sum_; ///< Checksum
		::in_addr src_; ///< Source address
		::in_addr dst_; ///< Destination address
	}; // ip4_header

	private: struct ip4_options_header
	{
		::boost::uint32_t opts_;
	}; // ip4_options_header


	public: static const ::boost::uint16_t header_size = sizeof(ip4_header);
	public: static const ::boost::uint16_t max_packet_size = 65535;
	public: static const ::boost::uint8_t ip_version = 4;
	// For additional protocols, see https://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
	public: static const ::boost::uint8_t proto_ip = 0; ///< Dummy protocol for TCP
	public: static const ::boost::uint8_t proto_icmp = 1; ///< Internet Control Message Protocol
	public: static const ::boost::uint8_t proto_igmp = 2; ///< Internet Group Management Protocol
	public: static const ::boost::uint8_t proto_ipip = 4; ///< IPIP tunnels (older KA9Q tunnels use 94)
	public: static const ::boost::uint8_t proto_tcp = 6; ///< Transmission Control Protocol
	public: static const ::boost::uint8_t proto_egp = 8; ///< Exterior Gateway Protocol
	public: static const ::boost::uint8_t proto_pup = 12; ///< PUP protocol
	public: static const ::boost::uint8_t proto_udp = 17; ///< User Datagram Protocol
	public: static const ::boost::uint8_t proto_idp = 22; ///< XNS IDP protocol
	public: static const ::boost::uint8_t proto_tp = 29; ///< SO Transport Protocol Class 4
	public: static const ::boost::uint8_t proto_dccp = 33; ///< Datagram Congestion Control Protocol
	public: static const ::boost::uint8_t proto_rsvp = 46; ///< Reservation Protocol
	public: static const ::boost::uint8_t proto_gre = 47; ///< General Routing Encapsulation
	public: static const ::boost::uint8_t proto_esp = 50; ///< encapsulating security payload
	public: static const ::boost::uint8_t proto_ah = 51; ///< authentication header
	public: static const ::boost::uint8_t proto_mtp = 92; ///< Multicast Transport Protocol
	public: static const ::boost::uint8_t proto_encap = 98; ///< Encapsulation Header
	public: static const ::boost::uint8_t proto_pim = 103; ///< Protocol Independent Multicast
	public: static const ::boost::uint8_t proto_comp = 108; ///< Compression Header Protocol
	public: static const ::boost::uint8_t proto_sctp = 132; ///< Stream Control Transmission Protocol
	public: static const ::boost::uint8_t proto_udplite = 136; ///< UDP-Lite protocol
	public: static const ::boost::uint8_t proto_raw = 255; ///< Raw IP packets
//	public: static const ::boost::uint8_t proto_hopopts = 0; ///< IPv6 Hop-by-Hop options
//	public: static const ::boost::uint8_t proto_ipv6 = 41; ///< IPv6 header
//	public: static const ::boost::uint8_t proto_routing = 43; ///< IPv6 routing header
//	public: static const ::boost::uint8_t proto_fragment = 44; ///< IPv6 fragmentation header
//	public: static const ::boost::uint8_t proto_icmpv6 = 58; ///< ICMPv6
//	public: static const ::boost::uint8_t proto_none = 59; ///< IPv6 no next header
//	public: static const ::boost::uint8_t proto_dstopts = 60; ///< IPv6 destination options
	public: static const ::boost::uint8_t tos_tos_mask = 0x1e; ///< Mask for extracting the ToS info from the ToS field (deprecated)
	public: static const ::boost::uint8_t tos_tos_low_cost = 0x02;
	public: static const ::boost::uint8_t tos_tos_low_reliability = 0x04;
	public: static const ::boost::uint8_t tos_tos_low_throughput = 0x08;
	public: static const ::boost::uint8_t tos_tos_low_delay = 0x10;
	public: static const ::boost::uint8_t tos_dscp_mask = 0xfc; ///< Mask for extracting the Differentiated Services Code Points info from the ToS field
	public: static const ::boost::uint8_t tos_dscp_af11 = 0x28; 
	public: static const ::boost::uint8_t tos_dscp_af12 = 0x30; 
	public: static const ::boost::uint8_t tos_dscp_af13 = 0x38; 
	public: static const ::boost::uint8_t tos_dscp_af21 = 0x48; 
	public: static const ::boost::uint8_t tos_dscp_af22 = 0x50; 
	public: static const ::boost::uint8_t tos_dscp_af23 = 0x58; 
	public: static const ::boost::uint8_t tos_dscp_af31 = 0x68; 
	public: static const ::boost::uint8_t tos_dscp_af32 = 0x70; 
	public: static const ::boost::uint8_t tos_dscp_af33 = 0x78; 
	public: static const ::boost::uint8_t tos_dscp_af41 = 0x88; 
	public: static const ::boost::uint8_t tos_dscp_af42 = 0x90; 
	public: static const ::boost::uint8_t tos_dscp_af43 = 0x98; 
	public: static const ::boost::uint8_t tos_dscp_ef = 0xb8; 
	public: static const ::boost::uint8_t tos_ecn_mask = 0x03; ///< Mask for extracting the Explicit Congestion Notification info from the ToS field
	public: static const ::boost::uint8_t tos_ecn_not_ect = 0x00;
	public: static const ::boost::uint8_t tos_ecn_ect1 = 0x01;
	public: static const ::boost::uint8_t tos_ecn_ect0 = 0x02;
	public: static const ::boost::uint8_t tos_ecn_ce = 0x03;
	public: static const ::boost::uint8_t tos_cscp_mask = 0xe0; ///< Mask for extracting the Class Selector Code Points info from the ToS field
	public: static const ::boost::uint8_t tos_cscp_cs0 = 0x00;
	public: static const ::boost::uint8_t tos_cscp_cs1 = 0x20;
	public: static const ::boost::uint8_t tos_cscp_cs2 = 0x40;
	public: static const ::boost::uint8_t tos_cscp_cs3 = 0x60;
	public: static const ::boost::uint8_t tos_cscp_cs4 = 0x80;
	public: static const ::boost::uint8_t tos_cscp_cs5 = 0xa0;
	public: static const ::boost::uint8_t tos_cscp_cs6 = 0xc0;
	public: static const ::boost::uint8_t tos_cscp_cs7 = 0xe0;
	public: static const ::boost::uint8_t tos_tos_precedence_mask = tos_cscp_mask; ///< Mask for extracting the Precedence info from the ToS field (deprecated)
	public: static const ::boost::uint8_t tos_tos_precedence_net_control = tos_cscp_cs7;
	public: static const ::boost::uint8_t tos_tos_precedence_internet_control = tos_cscp_cs6;
	public: static const ::boost::uint8_t tos_tos_precedence_critic_ecp = tos_cscp_cs5;
	public: static const ::boost::uint8_t tos_tos_precedence_flash_override = tos_cscp_cs4;
	public: static const ::boost::uint8_t tos_tos_precedence_flash = tos_cscp_cs3;
	public: static const ::boost::uint8_t tos_tos_precedence_immediate = tos_cscp_cs2;
	public: static const ::boost::uint8_t tos_tos_precedence_priority = tos_cscp_cs1;
	public: static const ::boost::uint8_t tos_tos_precedence_routing = tos_cscp_cs0;
	public: static const ::boost::uint16_t offset_flags_mask = 0xe000; ///< Mask for extracting the Flags info from the Fragmentation Offset field
	public: static const ::boost::uint16_t offset_offset_mask = 0x1fff; ///< Mask for extracting the Fragmentation Offset info from the Fragmentation Offset field
	public: static const ::boost::uint8_t options_copy = 0x80;
	public: static const ::boost::uint8_t options_class_mask = 0x60;
	public: static const ::boost::uint8_t options_number_mask = 0x1f;
	public: static const ::boost::uint8_t options_control = 0x00;
	public: static const ::boost::uint8_t options_reserved1 = 0x20;
	public: static const ::boost::uint8_t options_debmeas = 0x40;
	public: static const ::boost::uint8_t options_reserved2 = 0x60;
	public: static const ::boost::uint8_t options_eol = 0x00;
	public: static const ::boost::uint8_t options_nop = 0x01;
	public: static const ::boost::uint8_t options_rr = 0x07;
	public: static const ::boost::uint8_t options_ts = 0x44;
	public: static const ::boost::uint8_t options_rfc1393 = 0x52;
	public: static const ::boost::uint8_t options_security = 0x82;
	public: static const ::boost::uint8_t options_lsrr = 0x83;
	public: static const ::boost::uint8_t options_sat_id = 0x88;
	public: static const ::boost::uint8_t options_ssrr = 0x89;
	public: static const ::boost::uint8_t options_ra = 0x94;
//	public: static const ::boost::uint8_t options_value = 0;
//	public: static const ::boost::uint8_t options_length = 1;
//	public: static const ::boost::uint8_t options_offset = 2;
//	public: static const ::boost::uint8_t options_min_offset = 4;
//	public: static const ::boost::uint8_t options_ts_ts = 0; ///< Timestamps only
//	public: static const ::boost::uint8_t options_ts_ts_and_address = 1; ///< Timestamps and addresses
//	public: static const ::boost::uint8_t options_ts_prespec = 3; ///< Specified module only
//	public: static const ::boost::uint32_t options_security_unclass = 0x0000;
//	public: static const ::boost::uint32_t options_security_confid = 0xf135;
//	public: static const ::boost::uint32_t options_security_efto = 0x789a;
//	public: static const ::boost::uint32_t options_security_mmmm = 0xbc4d;
//	public: static const ::boost::uint32_t options_security_restr = 0xaf13;
//	public: static const ::boost::uint32_t options_security_secret = 0xd788;
//	public: static const ::boost::uint32_t options_security_topsecret = 0x6bc5;


	public: ip4_packet(::boost::uint8_t const* data, ::boost::uint32_t sz)
	: p_hdr_(0),
	  p_opts_hdr_(0),
	  p_data_(0),
	  data_sz_(0)
	{
		parse_data(data, sz);
	}

	public: ::boost::uint8_t version() const
	{
		return ip_version;
	}

	public: virtual ::boost::uint8_t const* payload() const
	{
		DCS_DEBUG_ASSERT( p_data_ );

		return p_data_;
	}

	public: virtual ::boost::uint32_t payload_size() const
	{
		return data_sz_;
	}

	public: ::boost::uint8_t version_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

	 	return detail::ip4_version(p_hdr_->vhl_);
	}

	public: ::boost::uint8_t internet_header_length_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

	 	return detail::ip4_ihl(p_hdr_->vhl_);
	}

	public: ::boost::uint8_t type_of_service_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->tos_ & tos_tos_mask;
	}

	public: ::boost::uint16_t total_length_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->len_);
	}

	public: ::boost::uint16_t identification_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->id_);
	}

	public: ::boost::uint8_t flags_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->off_) & offset_flags_mask;
	}

	public: ::boost::uint16_t fragment_offset_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->off_) & offset_offset_mask;
	}

	public: ::boost::uint8_t time_to_live_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->ttl_;
	}

	public: ::boost::uint8_t protocol_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->proto_;
	}

	public: ::boost::uint16_t header_checksum_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->sum_);
	}

	public: ::boost::uint32_t source_address_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint32_t >::network_to_host(p_hdr_->src_.s_addr);
	}

	public: ::boost::uint32_t destination_address_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint32_t >::network_to_host(p_hdr_->dst_.s_addr);
	}

	public: ::boost::uint32_t options_field() const
	{
		DCS_DEBUG_ASSERT( p_opts_hdr_ );

		return byte_order< ::boost::uint32_t >::network_to_host(p_opts_hdr_->opts_);
	}

	public: ::boost::uint16_t header_length() const
	{
		return this->internet_header_length_field() * 4;
	}

	/// Differentiated Services Code Point (DSCP), see RFC 2474
	public: ::boost::uint8_t differentiated_service_code_point() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->tos_ & tos_dscp_mask;
	}

	/// Explicit Congestion Notification (ECN), see RFC 3168
	public: ::boost::uint8_t explicit_congestion_notification() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->tos_ & tos_ecn_mask;
	}

	/// Class Selector Code Point, see RFC 2474
	public: ::boost::uint8_t class_selector_code_point() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->tos_ & tos_cscp_mask;
	}

	public: ::boost::uint16_t fragment_offset() const
	{
		return this->fragment_offset_field() * 8;
	}

	public: ::std::string source_address() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		// NOTE: address must be in network byte order
		return detail::ip4_address_to_string(p_hdr_->src_);
	}

	public: ::std::string destination_address() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		// NOTE: address must be in network byte order
		return detail::ip4_address_to_string(p_hdr_->dst_);
	}

	public: bool have_options() const
	{
		return p_opts_hdr_ ? true : false;
	}

	private: void parse_data(::boost::uint8_t const* data, ::boost::uint32_t sz)
	{
		DCS_ASSERT(data,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Empty packet for IPv4"));
		DCS_ASSERT(header_size <= sz,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Not enough space for IPv4 header"));

		p_hdr_ = reinterpret_cast<ip4_header const*>(data);

		const ::boost::uint8_t ver = detail::ip4_version(p_hdr_->vhl_);
		// Internet Header Length (IHL) is the number of 32-bit words in the
		// header. Thus the real header length is IHL*4
		const ::boost::uint8_t hlen = this->header_length();

		DCS_ASSERT(ip_version == ver,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Unexpected IP version"));
		DCS_ASSERT(header_size <= hlen,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "IP header shorter than expected"));
		DCS_ASSERT(this->total_length_field() <= sz,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Truncated IP packet"));
		DCS_ASSERT(this->total_length_field() >= hlen,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "IP packet shorter than expected"));

		if ((hlen - header_size) > 0)
		{
			p_opts_hdr_ = reinterpret_cast<ip4_options_header const*>(data+header_size);
		}

		p_data_ = data+hlen;
		data_sz_ = sz-hlen;
	}


	private: ip4_header const* p_hdr_;
	private: ip4_options_header const* p_opts_hdr_;
	private: ::boost::uint8_t const* p_data_;
	private: ::boost::uint32_t data_sz_;
}; // ip4_packet


//struct ip4_tag { };
//struct ip6_tag { };

template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, ip4_packet const& pkt)
{
	::std::ios_base::fmtflags io_flags = os.flags();

	os  << "<IPv4::"
		<< ::std::showbase
		<< ", ihl: " << ::std::dec << static_cast<unsigned int>(pkt.internet_header_length_field())
		<< ", tos: " << ::std::hex << static_cast<unsigned int>(pkt.type_of_service_field())
		<< ", length: " << ::std::dec << pkt.total_length_field()
		<< ", id: " << ::std::dec << pkt.identification_field()
		<< ", flags: " << ::std::hex << static_cast<unsigned int>(pkt.flags_field())
		<< ", offset: " << ::std::dec << pkt.fragment_offset()
		<< ", ttl: " << ::std::dec << static_cast<unsigned int>(pkt.time_to_live_field())
		<< ", protocol: " << ::std::dec << static_cast<unsigned int>(pkt.protocol_field())
		<< ", checksum: " << ::std::hex << pkt.header_checksum_field()
		<< ", src: " << pkt.source_address()
		<< ", dst: " << pkt.destination_address()
		<< ", options: ";

	if (pkt.have_options())
	{
		os << ::std::hex << pkt.options_field();
	}
	else
	{
		os << "<empty>";
	}

	os << ">";

	os.flags(io_flags);

	return os;
}

inline
::boost::shared_ptr<ip_packet> make_ip_packet(::boost::uint8_t const* data, ::boost::uint32_t sz)
{
	// pre: data != null
	DCS_ASSERT(data,
			   DCS_EXCEPTION_THROW(::std::invalid_argument,
								   "Empty packet"));

	::boost::uint8_t ver = detail::ip4_version(data[0]);
	switch (ver)
	{
		case 4:
			return ::boost::make_shared<ip4_packet>(data, sz);
		default:
			break;
	}

	::std::ostringstream oss;
	oss << "Unknown IP version: " << ver;
	DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
}

}} // Namespace dcs::network

#endif // DCS_NETWORK_IP_HPP
