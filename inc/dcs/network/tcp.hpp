/**
 * \file dcs/network/ip.hpp
 *
 * \brief Functions and classes for the TCP protocol.
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

#ifndef DCS_NETWORK_TCP_HPP
#define DCS_NETWORK_TCP_HPP


#include <arpa/inet.h>
#include <boost/cstdint.hpp>
#include <boost/smart_ptr.hpp>
#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <dcs/network/pdu.hpp>
//#include <netinet/tcp.h> //FIXME: only available on systems conforming to 4.3BSD and SunOS
#include <iomanip>
#include <iostream>
#include <stdexcept>


namespace dcs { namespace network {

/**
 * \brief The Transmission Control Protocol (TCP) segment.
 *
 * TCP header format (from RFC793):
 * <pre>
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |          Source Port          |       Destination Port        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                        Sequence Number                        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Acknowledgment Number                      |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |  Data |     |N|C|E|U|A|P|R|S|F|                               |
 * | Offset| 000 |S|W|C|R|C|S|S|Y|I|            Window             |
 * |       |     | |R|E|G|K|H|T|N|N|                               |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |           Checksum            |         Urgent Pointer        |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                    Options                    |    Padding    |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |                             data                              |
 * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * </pre>
 *
 */
class tcp_segment: public base_pdu
{
	//TODO: private: typedef ::tcphdr tcp_header;
	private: struct tcp_header
	{
		::boost::uint16_t src_port_; ///< Source port
		::boost::uint16_t dst_port_; ///< Destination port
		::boost::uint32_t seq_; ///< Sequence number
		::boost::uint32_t ack_; ///< Acknowledgement number
		::boost::uint8_t offx2_; ///< Data offset, rsvd
		::boost::uint8_t flags_;
		::boost::uint16_t win_; ///< Window
		::boost::uint16_t sum_; ///< Checksum
		::boost::uint16_t urp_; ///< Urgent pointer
	}; // tcp_header

	public: static const ::boost::uint32_t header_size = sizeof(tcp_header);
	public: static const ::boost::uint8_t offset_mask = 0xf0; ///< Mask used to extract Flags info from the Data Offset field
	public: static const ::boost::uint8_t flags_fin = 0x01; ///< No more data from sender
	public: static const ::boost::uint8_t flags_syn = 0x02; ///< Synchonize sequence numbers
	public: static const ::boost::uint8_t flags_rst = 0x04; ///< Reset the connection
	public: static const ::boost::uint8_t flags_push = 0x08; ///< Push function
	public: static const ::boost::uint8_t flags_ack = 0x10; ///< Acknowledgment field is significant
	public: static const ::boost::uint8_t flags_urg = 0x20; ///< Urgent pointer field is significant
	public: static const ::boost::uint8_t flags_ece = 0x40; ///< ECN Echo
	public: static const ::boost::uint8_t flags_cwr = 0x80; ///< Congestion Window Reduced (CWR)
	public: static const ::boost::uint8_t flags_ns = 0x80; ///< ECN Cwnd Reduced
	public: static const ::boost::uint8_t options_eol = 0;
	public: static const ::boost::uint8_t options_nop = 1;
	public: static const ::boost::uint8_t options_maxseg = 2;
	public: static const ::boost::uint8_t options_window_scale = 3; ///< Window scale factor (RFC 1323)
	public: static const ::boost::uint8_t options_sack_ok = 4; ///< Selective ACK OK (RFC 2018)
	public: static const ::boost::uint8_t options_sack = 5; ///< Selective ACK (RFC 2018)
	public: static const ::boost::uint8_t options_echo = 6; ///< Echo (RFC 1072)
	public: static const ::boost::uint8_t options_echo_replay = 7; ///< Echo replay (RFC 1072)
	public: static const ::boost::uint8_t options_timestamp = 8; ///< Timestamp (RFC 1323)
	public: static const ::boost::uint8_t options_cc = 11; ///< T/TCP CC options (RFC 1644)
	public: static const ::boost::uint8_t options_cc_new = 12; ///< T/TCP CC options (RFC 1644)
	public: static const ::boost::uint8_t options_cc_echo = 13; ///< T/TCP CC options (RFC 1644)
	public: static const ::boost::uint8_t options_signature = 19; ///< Keyed MD5 (RFC 2385)
	public: static const ::boost::uint8_t options_auth = 20; ///< Keyed Enhanced AUTH option
	public: static const ::boost::uint8_t options_user_timeout = 28; ///< TCP user timeout (RFC 5482)


	public: tcp_segment(::boost::uint8_t const* data, ::boost::uint32_t sz)
	: p_hdr_(0),
	  p_opts_hdr_(0),
	  p_data_(0),
	  data_sz_(0)
	{
		parse_data(data, sz);
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

	public: ::boost::uint16_t source_port_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->src_port_);
	}

	public: ::boost::uint16_t destination_port_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->dst_port_);
	}

	public: ::boost::uint32_t sequence_number_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint32_t >::network_to_host(p_hdr_->seq_);
	}

	public: ::boost::uint32_t acknowledgment_number_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint32_t >::network_to_host(p_hdr_->ack_);
	}

	public: ::boost::uint8_t data_offset_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return (p_hdr_->offx2_ & offset_mask) >> 4;
	}

	public: ::boost::uint8_t flags_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->flags_;
	}

	public: ::boost::uint16_t window_size_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->win_);
	}

	public: ::boost::uint16_t checksum_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->sum_);
	}

	public: ::boost::uint16_t urgent_pointer_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->urp_);
	}

	public: ::boost::uint8_t header_length() const
	{
		// The data offset field specifies the size of the TCP header in 32-bit
		// words. The minimum size header is 5 words and the maximum is 15 words
		// thus giving the minimum size of 20 bytes and maximum of 60 bytes,
		// allowing for up to 40 bytes of options in the header. This field gets
		// its name from the fact that it is also the offset from the start of
		// the TCP segment to the actual data.
		return this->data_offset_field() * 4;
	}

	public: bool have_options() const
	{
		return p_opts_hdr_ ? true : false;
	}

//	public: bool have_options(::boost::uint8_t mask) const
//	{
//		return this->have_options() && (p_opts_hdr
//	}

	public: bool have_flags(::boost::uint8_t mask) const
	{
		return this->flags_field() & mask;
	}

	private: void parse_data(::boost::uint8_t const* data, ::boost::uint32_t sz)
	{
		DCS_ASSERT(data,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Empty packet for TCP"));
		DCS_ASSERT(header_size <= sz,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Not enough space for TCP header"));

		p_hdr_ = reinterpret_cast<tcp_header const*>(data);

		const ::boost::uint8_t hlen = this->header_length();

		DCS_ASSERT(header_size <= hlen,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "IP header shorter than expected"));

		if (header_size < hlen)
		{
			p_opts_hdr_ = data+header_size;
		}

		if (sz > hlen)
		{
			p_data_ = data+hlen;
			data_sz_ = sz-hlen;
		}
	}


	private: tcp_header const* p_hdr_;
	private: ::boost::uint8_t const* p_opts_hdr_;
	private: ::boost::uint8_t const* p_data_;
	private: ::boost::uint32_t data_sz_;
}; // tcp_segment


//struct ip4_tag { };
//struct ip6_tag { };

template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, tcp_segment const& pkt)
{
	::std::ios_base::fmtflags io_flags = os.flags();

	os  << "<TCP::"
		<< ::std::showbase
		<< ", src port: " << ::std::dec << pkt.source_port_field()
		<< ", dst port: " << ::std::dec << pkt.destination_port_field()
		<< ", seq: " << ::std::dec << pkt.sequence_number_field()
		<< ", ack: " << ::std::dec << pkt.acknowledgment_number_field()
		<< ", offset: " << ::std::dec << static_cast<unsigned int>(pkt.data_offset_field())
		<< ", flags: " << ::std::hex << static_cast<unsigned int>(pkt.flags_field())
		<< ", window: " << ::std::dec << pkt.window_size_field()
		<< ", checksum: " << ::std::hex << pkt.checksum_field()
		<< ", urgent: " << ::std::dec << pkt.urgent_pointer_field()
		<< ">";

	os.flags(io_flags);

	return os;
}

}} // Namespace dcs::network

#endif // DCS_NETWORK_TCP_HPP
