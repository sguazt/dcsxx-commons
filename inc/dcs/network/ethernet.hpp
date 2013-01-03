/**
 * \file dcs/network/ethernet.hpp
 *
 * \brief Functions and classes for the Ethernet protocol.
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

#ifndef DCS_NETWORK_ETHERNET_HPP
#define DCS_NETWORK_ETHERNET_HPP

#include <boost/cstdint.hpp>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/network/pdu.hpp>
#include <dcs/network/byte_order.hpp>
#include <iomanip>
#include <iostream>
#include <netinet/ether.h> //FIXME: only available on systems conforming to 4.3BSD and SunOS
#include <stdexcept>


namespace dcs { namespace network {

class ethernet_frame: public base_pdu
{
	public: static const ::boost::uint8_t address_size = 6; ///< Octects in one MAC address
	public: static const ::boost::uint8_t header_size = 14; ///< Total octects in header
	public: static const ::boost::uint8_t header_8021q_size = 4; ///< Octects in the optional 802.1q tag
	public: static const ::boost::uint16_t mtu = 1500; ///< Max octects in payload
	public: static const ::boost::uint8_t min_frame_size = 60; ///< Min octects in frame sans FCS
	public: static const ::boost::uint16_t max_frame_size = header_size+mtu; ///< Max octects in frame sans FCS
	public: static const ::boost::uint8_t fcs_size = 4; ///< Octects in the FCS
//	// Ethernet protocol ID's (taken from linux/if_ether.h)
//	public: static const ::boost::uint16_t type_loop = 0x0060; ///<Ethernet Loopback packet
//	public: static const ::boost::uint16_t type_pup = 0x0200; ///<Xerox PUP packet
//	public: static const ::boost::uint16_t type_pupat = 0x0201; ///<Xerox PUP Addr Trans packet
//	public: static const ::boost::uint16_t type_ip = 0x0800; ///<Internet Protocol packet
//	public: static const ::boost::uint16_t type_x25 = 0x0805; ///<CCITT X.25
//	public: static const ::boost::uint16_t type_arp = 0x0806; ///<Address Resolution packet
//	public: static const ::boost::uint16_t type_bpq = 0x08ff; ///<G8BPQ AX.25 Ethernet Packet    [ NOT AN OFFICIALLY REGISTERED ID ]
//	public: static const ::boost::uint16_t type_ieeepup = 0x0a00; ///<Xerox IEEE802.3 PUP packet
//	public: static const ::boost::uint16_t type_ieeepupat = 0x0a01; ///<Xerox IEEE802.3 PUP Addr Trans packet
//	public: static const ::boost::uint16_t type_dec = 0x6000; ///< DEC Assigned proto
//	public: static const ::boost::uint16_t type_dna_dl = 0x6001; ///< DEC DNA Dump/Load
//	public: static const ::boost::uint16_t type_dna_rc = 0x6002; ///< DEC DNA Remote Console
//	public: static const ::boost::uint16_t type_dna_rt = 0x6003; ///< DEC DNA Routing
//	public: static const ::boost::uint16_t type_lat = 0x6004; ///< DEC LAT
//	public: static const ::boost::uint16_t type_diag = 0x6005; ///< DEC Diagnostics
//	public: static const ::boost::uint16_t type_cust = 0x6006; ///< DEC Customer use
//	public: static const ::boost::uint16_t type_sca = 0x6007; ///< DEC Systems Comms Arch
//	public: static const ::boost::uint16_t type_teb = 0x6558; ///< Trans Ether Bridging
//	public: static const ::boost::uint16_t type_rarp = 0x8035; ///<Reverse Addr Res packet
//	public: static const ::boost::uint16_t type_atalk = 0x809b; ///<Appletalk DDP
//	public: static const ::boost::uint16_t type_aarp = 0x80f3; ///<Appletalk AARP
//	public: static const ::boost::uint16_t type_8021q = 0x8100; ///<802.1Q VLAN Extended Header
//	public: static const ::boost::uint16_t type_ipx = 0x8137; ///<IPX over DIX
//	public: static const ::boost::uint16_t type_ipv6 = 0x86dd; ///<IPv6 over bluebook
//	public: static const ::boost::uint16_t type_pause = 0x8808; ///<IEEE Pause frames. See 802.3 31B
//	public: static const ::boost::uint16_t type_slow = 0x8809; ///<Slow Protocol. See 802.3ad 43B
//	public: static const ::boost::uint16_t type_wccp = 0x883e; ///<Web-cache coordination proto defined in draft-wilson-wrec-wccp-v2-00.txt */
//	public: static const ::boost::uint16_t type_ppp_disc = 0x8863; ///<PPPoE discovery messages
//	public: static const ::boost::uint16_t type_ppp_ses = 0x8864; ///<PPPoE session messages
//	public: static const ::boost::uint16_t type_mpls_uc = 0x8847; ///<MPLS Unicast traffic
//	public: static const ::boost::uint16_t type_mpls_mc = 0x8848; ///<MPLS Multicast traffic
//	public: static const ::boost::uint16_t type_atmmpoa = 0x884c; ///<MultiProtocol Over ATM
//	public: static const ::boost::uint16_t type_link_ctl = 0x886c; ///< HPNA, wlan link local tunnel
//	public: static const ::boost::uint16_t type_atmfate = 0x8884; ///<Frame-based ATM Transp over Ethernet
//	public: static const ::boost::uint16_t type_pae = 0x888e; ///< Port Access Entity (IEEE 802.1X)
//	public: static const ::boost::uint16_t type_aoe = 0x88a2; ///<ATA over Ethernet
//	public: static const ::boost::uint16_t type_8021ad = 0x88a8; ///< 802.1ad Service VLAN
//	public: static const ::boost::uint16_t type_802_ex1 = 0x88b5; ///< 802.1 Local Experimental 1
//	public: static const ::boost::uint16_t type_tipc = 0x88ca; ///< TIPC
//	public: static const ::boost::uint16_t type_8021ah = 0x88e7; ///< 802.1ah Backbone Service Tag
//	public: static const ::boost::uint16_t type_1588 = 0x88f7; ///< IEEE 1588 Timesync
//	public: static const ::boost::uint16_t type_fcoe = 0x8906; ///< Fibre Channel over Ethernet
//	public: static const ::boost::uint16_t type_tdls = 0x890d; ///< TDLS
//	public: static const ::boost::uint16_t type_fip = 0x8914; ///< FCoE Initialization Protocol
//	public: static const ::boost::uint16_t type_qinq1 = 0x9100; ///< deprecated QinQ VLAN [ NOT AN OFFICIALLY REGISTERED ID ]
//	public: static const ::boost::uint16_t type_qinq2 = 0x9200; ///< deprecated QinQ VLAN [ NOT AN OFFICIALLY REGISTERED ID ]
//	public: static const ::boost::uint16_t type_qinq3 = 0x9300; ///< deprecated QinQ VLAN [ NOT AN OFFICIALLY REGISTERED ID ]
//	public: static const ::boost::uint16_t type_edsa = 0xdada; ///< Ethertype DSA [ NOT AN OFFICIALLY REGISTERED ID ]
//	public: static const ::boost::uint16_t type_af_iucv = 0xfbfb; ///< IBM af_iucv [ NOT AN OFFICIALLY REGISTERED ID ]
//	// Non DIX types. Won't clash for 1500 types.
//	public: static const ::boost::uint16_t type_802_3 = 0x0001; ///< Dummy type for 802.3 frames
//	public: static const ::boost::uint16_t type_ax25 = 0x0002; ///< Dummy protocol id for AX.25
//	public: static const ::boost::uint16_t type_all = 0x0003; ///< Every packet (be careful!!!)
//	public: static const ::boost::uint16_t type_802_2 = 0x0004; ///< 802.2 frames
//	public: static const ::boost::uint16_t type_snap = 0x0005; ///< Internal only
//	public: static const ::boost::uint16_t type_ddcmp = 0x0006; ///< DEC DDCMP: Internal only
//	public: static const ::boost::uint16_t type_wan_ppp = 0x0007; ///< Dummy type for WAN PPP frames
//	public: static const ::boost::uint16_t type_ppp_mp = 0x0008; ///< Dummy type for PPP MP frames
//	public: static const ::boost::uint16_t type_localtalk = 0x0009; ///< Localtalk pseudo type
//	public: static const ::boost::uint16_t type_can = 0x000C; ///< CAN: Controller Area Network
//	public: static const ::boost::uint16_t type_canfd = 0x000D; ///< CANFD: CAN flexible data rate
//	public: static const ::boost::uint16_t type_ppptalk = 0x0010; ///< Dummy type for Atalk over PPP
//	public: static const ::boost::uint16_t type_tr_802_2 = 0x0011; ///< 802.2 frames
//	public: static const ::boost::uint16_t type_mobitex = 0x0015; ///< Mobitex (kaz@cafe.net)
//	public: static const ::boost::uint16_t type_control = 0x0016; ///< Card specific control frames
//	public: static const ::boost::uint16_t type_irda = 0x0017; ///< Linux-IrDA
//	public: static const ::boost::uint16_t type_econet = 0x0018; ///< Acorn Econet
//	public: static const ::boost::uint16_t type_hdlc = 0x0019; ///< HDLC frames
//	public: static const ::boost::uint16_t type_arcnet = 0x001A; ///< 1A for ArcNet :-)
//	public: static const ::boost::uint16_t type_dsa = 0x001B; ///< Distributed Switch Arch
//	public: static const ::boost::uint16_t type_trailer = 0x001C; ///< Trailer switch tagging
//	public: static const ::boost::uint16_t type_phonet = 0x00F5; ///< Nokia Phonet frames
//	public: static const ::boost::uint16_t type_ieee802154 = 0x00F6; ///< IEEE802.15.4 frame
//	public: static const ::boost::uint16_t type_caif = 0x00F7; ///< ST-Ericsson CAIF protocol
	// Taken from net/ethernet.h. See also: http://standards.ieee.org/develop/regauth/ethertype/eth.txt
	public: static const ::boost::uint16_t ethertype_pup = 0x0200; ///< Xeror PUP
	public: static const ::boost::uint16_t ethertype_sprite = 0x0500; ///< Sprite
	public: static const ::boost::uint16_t ethertype_ipv4 = 0x0800; ///< IP
	public: static const ::boost::uint16_t ethertype_arp = 0x0806; ///< Address resolution
	public: static const ::boost::uint16_t ethertype_rarp = 0x8035; ///< Reverse ARP
	public: static const ::boost::uint16_t ethertype_atalk = 0x809B; ///< AppleTalk protocol (Ethertalk)
	public: static const ::boost::uint16_t ethertype_aarp = 0x80F3; ///< AppleTalk ARP
	public: static const ::boost::uint16_t ethertype_ieee8021q = 0x8100; ///< IEEE 802.1Q VLAN extended header
	public: static const ::boost::uint16_t ethertype_ipx = 0x8137; ///< IPX
	public: static const ::boost::uint16_t ethertype_ipv6 = 0x86dd; ///< IP protocol version 6
	public: static const ::boost::uint16_t ethertype_loopback = 0x9000; ///< Configuration testing protocol
	public: static const ::boost::uint16_t ethertype_ieee8021qinq1 = 0x9100; ///< Deprecated IEEE 802.1QinQ VLAN tagging
	public: static const ::boost::uint16_t ethertype_ieee8021qinq2 = 0x9200; ///< Deprecated IEEE 802.1QinQ VLAN tagging
	public: static const ::boost::uint16_t ethertype_ieee8021qinq3 = 0x9300; ///< Deprecated IEEE 802.1QinQ VLAN tagging
	public: static const ::boost::uint16_t ethertype_ieee8021ad = 0x88a8; ///< IEEE 802.1ad Service VLAN


	//private: struct ethernet_address
	//{
	//	::boost::uint8_t addr_[address_size]; ///< Address
	//};

	/// The Ethernet header
	private: struct ethernet_header
	{
		::boost::uint8_t dst_addr_[address_size]; ///< Destination address
		::boost::uint8_t src_addr_[address_size]; ///<  Source address
		::boost::uint16_t type_; ///<  Packet type ID
	};

	/// The optional IEEE 802.1q tag
	private: struct ethernet_8021q_header
	{
		uint16_t tpid_; ///< Tag Protocol Identifier
		uint16_t tci_; ///< Tag Control Identifier
	};

	public: ethernet_frame(::boost::uint8_t const* pkt, ::boost::uint32_t sz)
	: p_hdr_(0),
	  p_hdr_8021q_(0),
	  p_data_(0),
	  data_sz_(0)
	{
		parse_data(pkt, sz);
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

	public: ::boost::uint8_t const* source_address_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->src_addr_;
	}

	public: ::boost::uint8_t const* destination_address_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return p_hdr_->dst_addr_;
	}

	public: ::boost::uint16_t ethertype_field() const
	{
		DCS_DEBUG_ASSERT( p_hdr_ );

		return byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->type_);
	}

	public: ::std::string source_address() const
	{
		return ::std::string(::ether_ntoa(reinterpret_cast< ::ether_addr const* >(this->source_address_field())));
	}

	public: ::std::string destination_address() const
	{
		return ::std::string(::ether_ntoa(reinterpret_cast< ::ether_addr const* >(this->destination_address_field())));
	}

	/// Return \c true if this packet is an Ethernet II packet, \c false if it is an IEEE 802.3 packet
	public: bool ethernet2() const
	{
		return (this->ethertype_field() > mtu) ? true : false;
	}

	private: void parse_data(::boost::uint8_t const* p_data, ::boost::uint32_t sz)
	{
		DCS_ASSERT(header_size <= sz,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Not enough space for Ethernet header"));

		p_hdr_ = reinterpret_cast<ethernet_header const*>(p_data);
		::boost::uint32_t payload_pos = header_size;

		::boost::uint16_t type = byte_order< ::boost::uint16_t >::network_to_host(p_hdr_->type_);
		if (type == ethertype_ieee8021ad
			|| type == ethertype_ieee8021q
			|| type == ethertype_ieee8021qinq1
			|| type == ethertype_ieee8021qinq2
			|| type == ethertype_ieee8021qinq3)
		{
			DCS_ASSERT((header_size+header_8021q_size) <= sz,
					   DCS_EXCEPTION_THROW(::std::logic_error,
										   "Not enough space for Ethernet header and 802.1q tag"));

			p_hdr_8021q_ = reinterpret_cast<ethernet_8021q_header const*>(p_data+header_size);
			payload_pos += header_8021q_size;
		}

		p_data_ = p_data+payload_pos;
		data_sz_ = sz-header_size;
	}


	private: ethernet_header const* p_hdr_;
	private: ethernet_8021q_header const* p_hdr_8021q_;
	private: ::boost::uint8_t const* p_data_;
	private: ::boost::uint32_t data_sz_;
}; // ethernet_frame


template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, ethernet_frame const& pkt)
{
	::std::ios_base::fmtflags io_flags = os.flags();

	os	<< "<Ethernet::"
		<< ::std::showbase
		<< "src: " << pkt.source_address()
		<< ", dst: " << pkt.destination_address()
		<< ", ethertype: " << ::std::hex << pkt.ethertype_field()
		<< ">";

//	if (pkt.ethertype_field() <= ethernet_frame::mtu)
//	{
//		os << "IEEE 802.3";
//	}
//	else
//	{
//		switch (pkt.ethertype_field())
//		{
//			case ethernet_frame::ethertype_pup:
//				os << "PUP";
//				break;
//			case ethernet_frame::ethertype_sprite:
//				os << "Sprite";
//				break;
//			case ethernet_frame::ethertype_ipv4:
//				os << "IPv4";
//				break;
//			case ethernet_frame::ethertype_arp:
//				os << "ARP";
//				break;
//			case ethernet_frame::ethertype_rarp:
//				os << "Reverse ARP";
//				break;
//			case ethernet_frame::ethertype_atalk:
//				os << "Appletalk";
//				break;
//			case ethernet_frame::ethertype_aarp:
//				os << "Appletalk ARP";
//				break;
//			case ethernet_frame::ethertype_ieee8021q:
//				os << "IEEE 802.1q";
//				break;
//			case ethernet_frame::ethertype_ipx:
//				os << "IPX";
//				break;
//			case ethernet_frame::ethertype_ipv6:
//				os << "IPv6";
//				break;
//			case ethernet_frame::ethertype_loopback:
//				os << "Loopback";
//				break;
//			case ethernet_frame::ethertype_ieee8021qinq1:
//				os << "IEEE 802.1QinQ (9100)";
//				break;
//			case ethernet_frame::ethertype_ieee8021qinq2:
//				os << "IEEE 802.1QinQ (9200)";
//				break;
//			case ethernet_frame::ethertype_ieee8021qinq3:
//				os << "IEEE 802.1QinQ (9300)";
//				break;
//			case ethernet_frame::ethertype_ieee8021ad:
//				os << "IEEE 802.1ad";
//				break;
//			detault:
//				os << "Unknown";
//		}
//	}
//
//	os << ::std::dec << ">";

	os.flags(io_flags);

	return os;
}

}} // Namespace dcs::network

#endif // DCS_NETWORK_ETHERNET_HPP
