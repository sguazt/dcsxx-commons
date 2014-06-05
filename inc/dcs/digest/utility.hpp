/**
 * \file dcs/digest/utility.hpp
 *
 * \brief A collection of utilities to work with message digests.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2013 Marco Guazzone (marco.guazzone@gmail.com)
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
