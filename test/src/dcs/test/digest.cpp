/**
 * \file dcs/test/digeset.cpp
 *
 * \brief Test suite for dcs::digest components.
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

#include <dcs/debug.hpp>
#include <dcs/digest/md5.hpp>
#include <dcs/test.hpp>
#include <iostream>
#include <string>
#include <vector>


DCS_TEST_DEF( md5 )
{
	DCS_TEST_CASE( "MD5 Digest" );

	dcs::digest::md5_algorithm dig;

	std::string test;
	std::string res;
	std::string expect;
	std::vector<dcs::digest::byte_type> bytes;

	DCS_TEST_TRACE( "Empty String" );
	test = "";
	expect = "d41d8cd98f00b204e9800998ecf8427e";
	bytes = dig.digest(test);
	//res = dcs::digest::hex_string(bytes.begin(), bytes.end());
	res = dcs::digest::hex_string(bytes.data(), bytes.size());
	DCS_DEBUG_TRACE("RES    = '" << res << "' (" << res.length() << ")");
	DCS_DEBUG_TRACE("EXPECT = '" << expect << "' (" << expect.length() << ")");
	DCS_TEST_CHECK_EQ( res, expect );

	DCS_TEST_TRACE( "String 'The quick brown fox jumps over the lazy dog'" );
	test = "The quick brown fox jumps over the lazy dog";
	expect = "9e107d9d372bb6826bd81d3542a419d6";
	bytes = dig.digest(test);
	//res = dcs::digest::hex_string(bytes.begin(), bytes.end());
	res = dcs::digest::hex_string(bytes.data(), bytes.size());
	DCS_DEBUG_TRACE("RES    = '" << res << "' (" << res.length() << ")");
	DCS_DEBUG_TRACE("EXPECT = '" << expect << "' (" << expect.length() << ")");
	DCS_TEST_CHECK_EQ( res, expect );
}


int main()
{
	DCS_TEST_SUITE( "Digest" );
	DCS_TEST_BEGIN();
		DCS_TEST_DO( md5 );
	DCS_TEST_END();
}
