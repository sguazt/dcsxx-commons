/**
 * \file dcs/text/base64.hpp
 *
 * \brief Base64 coder/deconder.
 *
 * <hr/>
 *
 * Copyright (C) 2014 Marco Guazzone (marco.guazzone@gmail.com)
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
 *
 * Copyright (C) 2004-2008 René Nyffenegger
 *
 * This source code is provided 'as-is', without any express or implied
 * warranty. In no event will the author be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this source code must not be misrepresented; you must not
 *    claim that you wrote the original source code. If you use this source code
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original source code.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * \author René Nyffenegger (rene.nyffenegger@adp-gmbh.ch)
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_TEXT_BASE64_HPP
#define DCS_TEXT_BASE64_HPP


#include <cctype>
#include <cstddef>
#include <string>
#include <boost/cstdint.hpp>


namespace dcs { namespace text {

namespace /*<unnamed>*/ { namespace detail {

static const ::std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
										  "abcdefghijklmnopqrstuvwxyz"
										  "0123456789+/";

inline
static bool is_base64(::boost::uint8_t c)
{
	return (::std::isalnum(c) || (c == '+') || (c == '/'));
}

}} // Namespace <unnamed>::detail


::std::string base64_encode(::boost::uint8_t const* bytes_to_encode, ::std::size_t in_len)
{
	::std::string ret;
	::std::size_t i = 0;
	::std::size_t j = 0;
	::boost::uint8_t byte_array_3[3];
	::boost::uint8_t byte_array_4[4];

	while (in_len--)
	{
		byte_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			byte_array_4[0] = (byte_array_3[0] & 0xfc) >> 2;
			byte_array_4[1] = ((byte_array_3[0] & 0x03) << 4) + ((byte_array_3[1] & 0xf0) >> 4);
			byte_array_4[2] = ((byte_array_3[1] & 0x0f) << 2) + ((byte_array_3[2] & 0xc0) >> 6);
			byte_array_4[3] = byte_array_3[2] & 0x3f;

			for(i = 0; i < 4; ++i)
			{
				ret += detail::base64_chars[byte_array_4[i]];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; ++j)
		{
			byte_array_3[j] = '\0';
		}

		byte_array_4[0] = (byte_array_3[0] & 0xfc) >> 2;
		byte_array_4[1] = ((byte_array_3[0] & 0x03) << 4) + ((byte_array_3[1] & 0xf0) >> 4);
		byte_array_4[2] = ((byte_array_3[1] & 0x0f) << 2) + ((byte_array_3[2] & 0xc0) >> 6);
		byte_array_4[3] = byte_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); ++j)
		{
			ret += detail::base64_chars[byte_array_4[j]];
		}

		while (++i <= 3)
		{
			ret += '=';
		}
	}

	return ret;

}

::std::string base64_decode(::std::string const& encoded_string)
{
	const ::std::size_t in_len = encoded_string.size();

	::std::size_t i = 0;
	::std::size_t j = 0;
	::std::size_t k = 0;
	::boost::uint8_t byte_array_3[3];
	::boost::uint8_t byte_array_4[4];
	::std::string ret;

	while (in_len-- && (encoded_string[k] != '=') && detail::is_base64(encoded_string[k]))
	{
		byte_array_4[i++] = encoded_string[k];
		++k;
		if (i == 4)
		{
			for (i = 0; i < 4; ++i)
			{
				byte_array_4[i] = detail::base64_chars.find(byte_array_4[i]);
			}

			byte_array_3[0] = (byte_array_4[0] << 2) + ((byte_array_4[1] & 0x30) >> 4);
			byte_array_3[1] = ((byte_array_4[1] & 0xf) << 4) + ((byte_array_4[2] & 0x3c) >> 2);
			byte_array_3[2] = ((byte_array_4[2] & 0x3) << 6) + byte_array_4[3];

			for (i = 0; (i < 3); ++i)
			{
				ret += byte_array_3[i];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; ++j)
		{
			byte_array_4[j] = 0;
		}

		for (j = 0; j < 4; ++j)
		{
			byte_array_4[j] = detail::base64_chars.find(byte_array_4[j]);
		}

		byte_array_3[0] = (byte_array_4[0] << 2) + ((byte_array_4[1] & 0x30) >> 4);
		byte_array_3[1] = ((byte_array_4[1] & 0xf) << 4) + ((byte_array_4[2] & 0x3c) >> 2);
		byte_array_3[2] = ((byte_array_4[2] & 0x3) << 6) + byte_array_4[3];

		for (j = 0; j < (i-1); ++j)
		{
			ret += byte_array_3[j];
		}
	}

	return ret;
}

}} // Namespace dcs::text


#endif // DCS_TEXT_BASE64_HPP
