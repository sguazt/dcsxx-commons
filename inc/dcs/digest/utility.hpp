/**
 * \file dcs/digest/utility.hpp
 *
 * \brief A collection of utilities to work with message digests.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_DIGEST_UTILITY_HPP
#define DCS_DIGEST_UTILITY_HPP


#include <cstddef>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>


namespace dcs { namespace digest {

inline
::std::string hex_string(byte_type const* digest, ::std::size_t len)
{
	::std::ostringstream oss;
	//oss.unsetf(::std::ios_base::showbase);
	//oss.setf(::std::ios_base::internal);
	//oss.fill('0');
	//oss.width(2);
	for (::std::size_t i = 0; i < len; i += 1)
	{
		oss << ::std::setw(2)
			<< ::std::setfill('0')
			<< ::std::hex
			<< ::std::noshowbase
			<< ::std::internal
			<< static_cast<unsigned short>(digest[i]);
	}
	return oss.str();
}

inline
::std::string hex_string(::std::vector<byte_type> const& digest)
{
	return hex_string(digest.data(), digest.size());
}

template <typename ByteIterT>
::std::string hex_string(ByteIterT first, ByteIterT last)
{
	return hex_string(static_cast<byte_type const*>(&*first), ::std::distance(first, last));
}

}} // Namespace dcs::digest


#endif // DCS_DIGEST_UTILITY_HPP
