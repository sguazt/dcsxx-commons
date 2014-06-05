/**
 * \file dcs/digest/md5.hpp
 *
 * \brief The MD5 message digest algorithm.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
 * rights reserved.
 *
 * License to copy and use this software is granted provided that it
 * is identified as the "RSA Data Security, Inc. MD5 Message-Digest
 * Algorithm" in all material mentioning or referencing this software
 * or this function.
 *
 * License is also granted to make and use derivative works provided
 * that such works are identified as "derived from the RSA Data
 * Security, Inc. MD5 Message-Digest Algorithm" in all material
 * mentioning or referencing the derived work.
 *
 * RSA Data Security, Inc. makes no representations concerning either
 * the merchantability of this software or the suitability of this
 * software for any particular purpose. It is provided "as is"
 * without express or implied warranty of any kind.
 *
 * These notices must be retained in any copies of any part of this
 * documentation and/or software.
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

#ifndef DCS_DIGEST_MD5_HPP
#define DCS_DIGEST_MD5_HPP


#include <algorithm>
#include <boost/cstdint.hpp>
#include <cstring>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/digest/commons.hpp>
#include <dcs/digest/utility.hpp>
#include <dcs/exception.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace dcs { namespace digest {


/**
 * The MD5 message digest algorithm.
 *
 * See RFC-1321 (https://www.ietf.org/rfc/rfc1321.txt)
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
class md5_algorithm
{
	private: typedef ::boost::uint16_t uint16_type;
	private: typedef ::boost::uint32_t uint32_type;


	public: static const ::std::size_t digest_size = 16; ///< The size of digest buffer (in bytes)
	private: static const ::std::size_t block_size = 64;
	private: static const byte_type padding[block_size];


	private: struct context
	{
		static const ::std::size_t state_size = 4;
		static const ::std::size_t count_size = 2;

		uint32_type state[state_size]; ///< State (A,B,C,D) that contains the digest
		uint32_type count[count_size]; ///< 64 bit counter for number of bits (lo, hi)
		byte_type buffer[block_size]; ///< bytes that didn't fit in last 64 byte chunk
	};


	public: md5_algorithm()
	: finalized_(false)
	{
		this->reset();
	}

	// MD5 initialization. Begins an MD5 operation, writing a new context.
	public: void reset()
	{
		// Zeros sensitive information
		context_.count[0] = context_.count[1] = 0;
		::std::memset(context_.buffer, 0, block_size);

		// Load magic initialization constants.
		// Use binary integer part of the sines of integers (in radians) as constants
		context_.state[0] = 0x67452301;
		context_.state[1] = 0xefcdab89;
		context_.state[2] = 0x98badcfe;
		context_.state[3] = 0x10325476;

		finalized_ = false;
	}

	// MD5 block update operation. Continues an MD5 message-digest
	// operation, processing another message block, and updating the
	// context.
	public: void update(byte_type const* input, ::std::size_t len)
	{
		// pre: digest not finalized
		DCS_ASSERT(!finalized_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Cannot update an already finalized digest"));

		// Compute number of bytes mod 64
		//::std::size_t index = static_cast< ::std::size_t >((context_.count[0] >> 3) & 0x3F);
		::std::size_t index = context_.count[0] / 8 % block_size;

		// Update number of bits
		context_.count[0] += len << 3;
		//if ((context_.count[0] += (len << 3)) < (len << 3))
		if (context_.count[0]  < (len << 3))
		{
			++(context_.count[1]);
		}
		context_.count[1] += len >> 29;

		// number of bytes we need to fill in buffer
		::std::size_t part_len(block_size-index);
		::std::size_t i(0);

		// Transform as many times as possible.
		if (len >= part_len)
		{
			::std::memcpy(&context_.buffer[index], input, part_len);
			transform(context_.buffer);

			for (i = part_len; (i + block_size) <= len; i += block_size)
			{
				transform(&input[i]);
			}

			index = 0;
		}
		else
		{
			i = 0;
		}

		/* Buffer remaining input */
		::std::memcpy(&context_.buffer[index], &input[i], len-i);
	}

	public: void update(char const* input, ::std::size_t len)
	{
		update(reinterpret_cast<byte_type const*>(input), len);
	}

	// MD5 finalization. Ends an MD5 message-digest operation, writing the
	// the message digest and zeroizing the context.
	// Writes to digest_
	public: void finish()
	{
		// pre: digest not finalized
		DCS_ASSERT(!finalized_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Cannot finalize an already finalized digest"));

		byte_type bits[8];
		::std::size_t pad_len(0);

		// Save number of bits
		encode(bits, context_.count, 8);

		// Pad out to 56 mod 64.
		//::std::size_t index = static_cast< ::std::size_t >((context_.count[0] >> 3) & 0x3f);
		::std::size_t index = context_.count[0] / 8 % block_size;
		pad_len = (index < 56) ? (56 - index) : (120 - index);
		update(padding, pad_len);

		// Append length (before padding)
		update(bits, 8);

		// Store state in digest
		encode(digest_, context_.state, digest_size);

//		// Zeroize sensitive information.
//		::std::memset(reinterpret_cast<byte_type*>(&context_),
//					  0,
//					  sizeof(context_));

//		::std::vector<byte_type> dig(digest_, digest_+digest_size);
//
//		this->reset();

//		return dig;

		finalized_ = true;
	}

	public: ::std::vector<byte_type> digest() const
	{
		// pre: digest already finalized
		DCS_ASSERT(finalized_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Digest computation has not been finalized"));

		return ::std::vector<byte_type>(digest_, digest_+digest_size);
	}

	public: ::std::vector<byte_type> digest(byte_type const* data, ::std::size_t len)
	{
		reset();
		update(data, len);
		finish();

		return digest();
	}

	public: ::std::vector<byte_type> digest(::std::string const& s)
	{
		reset();
		update(s.c_str(), s.length());
		finish();

		return digest();
	}

	public: ::std::size_t digest_length() const
	{
		return digest_size;
	}

	public: byte_type const* raw_digest() const
	{
		// pre: digest already finalized
		DCS_ASSERT(finalized_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Digest computation has not been finalized"));

		return digest_;
	}

	// The core of the MD5 algorithm is here.
	// Apply MD5 algorithm on a block.
	private: void transform(byte_type const block[block_size])
	{
		// Constants specying the per-round shift amounts
		const uint32_type S11 =  7;
		const uint32_type S12 = 12;
		const uint32_type S13 = 17;
		const uint32_type S14 = 22;
		const uint32_type S21 =  5;
		const uint32_type S22 =  9;
		const uint32_type S23 = 14;
		const uint32_type S24 = 20;
		const uint32_type S31 =  4;
		const uint32_type S32 = 11;
		const uint32_type S33 = 16;
		const uint32_type S34 = 23;
		const uint32_type S41 =  6;
		const uint32_type S42 = 10;
		const uint32_type S43 = 15;
		const uint32_type S44 = 21;

		uint32_type a = context_.state[0];
		uint32_type b = context_.state[1];
		uint32_type c = context_.state[2];
		uint32_type d = context_.state[3];
		uint32_type x[16];

		decode(x, block, block_size);

		/* Round 1 */
		FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
		FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
		FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
		FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
		FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
		FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
		FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
		FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
		FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
		FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
		FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
		FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
		FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
		FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
		FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
		FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

		/* Round 2 */
		GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
		GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
		GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
		GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
		GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
		GG(d, a, b, c, x[10], S22,  0x2441453); /* 22 */
		GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
		GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
		GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
		GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
		GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
		GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
		GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
		GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
		GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
		GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

		/* Round 3 */
		HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
		HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
		HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
		HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
		HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
		HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
		HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
		HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
		HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
		HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
		HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
		HH(b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
		HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
		HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
		HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
		HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

		/* Round 4 */
		II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
		II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
		II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
		II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
		II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
		II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
		II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
		II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
		II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
		II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
		II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
		II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
		II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
		II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
		II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
		II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

		context_.state[0] += a;
		context_.state[1] += b;
		context_.state[2] += c;
		context_.state[3] += d;

		// Zeroize sensitive information.
		::std::memset(reinterpret_cast<byte_type*>(x), 0, sizeof(x));
	}

	// Encodes input (uint32) into output (byte). Assumes len is a multiple of 4.
	private: static void encode(byte_type* output, uint32_type const* input, ::std::size_t len)
	{
		::std::size_t i(0);
		::std::size_t j(0);

		while (j < len)
		{
			output[j]   = static_cast<byte_type>( input[i]        & 0xff);
			output[j+1] = static_cast<byte_type>((input[i] >>  8) & 0xff);
			output[j+2] = static_cast<byte_type>((input[i] >> 16) & 0xff);
			output[j+3] = static_cast<byte_type>((input[i] >> 24) & 0xff);
			++i;
			j += 4;
		}
	}

	// Decodes input (byte) into output (uint32). Assumes len is a multiple of 4.
	private: static void decode(uint32_type* output, byte_type const* input, ::std::size_t len)
	{
		::std::size_t i(0);
		::std::size_t j(0);

		while (j < len)
		{
			output[i] =    static_cast<uint32_type>(input[j  ])
						| (static_cast<uint32_type>(input[j+1]) <<  8)
						| (static_cast<uint32_type>(input[j+2]) << 16)
						| (static_cast<uint32_type>(input[j+3]) << 24);
			++i;
			j += 4;
		}
	}

	// low level logic operations

	// F, G, H and I are basic MD5 functions.
	private: static uint32_type F(uint32_type x, uint32_type y, uint32_type z)
	{
		return (x & y) | (~x & z);
	}

	private: static uint32_type G(uint32_type x, uint32_type y, uint32_type z)
	{
		return (x & z) | (y & ~z);
	}

	private: static uint32_type H(uint32_type x, uint32_type y, uint32_type z)
	{
		return x ^ y ^ z;
	}

	private: static uint32_type I(uint32_type x, uint32_type y, uint32_type z)
	{
		return y ^ (x | ~z);
	}

	// rotate_left rotates x left n bits.
	private: static uint32_type rotate_left(uint32_type x, int n)
	{
		return (x << n) | (x >> (32-n));
	}

	// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	// Rotation is separate from addition to prevent recomputation.
	private: static void FF(uint32_type &a, uint32_type b, uint32_type c, uint32_type d, uint32_type x, uint32_type s, uint32_type ac)
	{
		a = rotate_left(a+ F(b,c,d) + x + ac, s) + b;
	}

	private: static void GG(uint32_type &a, uint32_type b, uint32_type c, uint32_type d, uint32_type x, uint32_type s, uint32_type ac)
	{
		a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
	}

	private: static void HH(uint32_type &a, uint32_type b, uint32_type c, uint32_type d, uint32_type x, uint32_type s, uint32_type ac)
	{
		a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
	}

	private: static void II(uint32_type &a, uint32_type b, uint32_type c, uint32_type d, uint32_type x, uint32_type s, uint32_type ac)
	{
		a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
	}


	private: context context_;
	private: byte_type digest_[digest_size] ; ///< The MD5 digest (16-byte number, i.e., 32 hex digits)
	private: bool finalized_;
}; // md5_algorithm

const byte_type md5_algorithm::padding[] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, md5_algorithm const& md5)
{
	os << hex_string(md5.digest());

	return os;
}

inline
::std::vector<byte_type> md5_digest(byte_type const* data, ::std::size_t len)
{
	md5_algorithm md5;

	return md5.digest(data, len);
}

inline
::std::vector<byte_type> md5_digest(::std::string const& s)
{
	md5_algorithm md5;

	return md5.digest(s);
}

}} // Namespace dcs::digest

#endif // DCS_DIGEST_MD5_HPP
