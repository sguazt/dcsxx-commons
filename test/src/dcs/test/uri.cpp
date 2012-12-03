/**
 * \file dcs/test/uri.cpp
 *
 * \brief Test suite for the dcs::uri class.
 *
 * Mainly based on the test suite for Poco::URI class by POCO C++ Library.
 *
 * \author POCO C++ Libraries (http://pocoproject.org)
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2004-2006  Applied Informatics Software Engineering GmbH
 *                          and Contributors.
 *
 * Copyright (C) 2012       Marco Guazzone (marco.guazzone@gmail.com)
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
#include <dcs/test.hpp>
#include <dcs/uri.hpp>


DCS_TEST_DEF( construction )
{
	dcs::uri u;

	DCS_TEST_CHECK( u.scheme().empty() );
	DCS_TEST_CHECK( u.authority().empty() );
	DCS_TEST_CHECK( u.user_info().empty() );
	DCS_TEST_CHECK( u.host().empty() );
	DCS_TEST_CHECK( u.port() == dcs::uri::invalid_port );
	DCS_TEST_CHECK( u.path().empty() );
	DCS_TEST_CHECK( u.query().empty() );
	DCS_TEST_CHECK( u.fragment().empty() );

	u.scheme("ftp");
	DCS_TEST_CHECK_EQ(u.scheme(), "ftp");
	DCS_TEST_CHECK_EQ(u.port(), 21);

	u.scheme("HTTP");
	DCS_TEST_CHECK_EQ(u.scheme(), "http");

	u.authority("www.example.com");
	DCS_TEST_CHECK_EQ(u.authority(), "www.example.com");
	DCS_TEST_CHECK_EQ(u.port(), 80);

	u.authority("user@people.example.com:8080");
	DCS_TEST_CHECK_EQ(u.user_info(), "user");
	DCS_TEST_CHECK_EQ(u.host(), "people.example.com");
	DCS_TEST_CHECK_EQ(u.port(), 8080);

	u.path("/index.html");
	DCS_TEST_CHECK_EQ(u.path(), "/index.html");

	u.path("/file%20with%20spaces.html");
	DCS_TEST_CHECK_EQ(u.path(), "/file with spaces.html");

	u.path_etc("/query.cgi?query=foo");
	DCS_TEST_CHECK_EQ(u.path(), "/query.cgi");
	DCS_TEST_CHECK_EQ(u.query(), "query=foo");
	DCS_TEST_CHECK(u.fragment().empty());
	DCS_TEST_CHECK_EQ(u.path_etc(), "/query.cgi?query=foo");
	DCS_TEST_CHECK_EQ(u.path_and_query(), "/query.cgi?query=foo");

	u.path_etc("/query.cgi?query=bar#frag");
	DCS_TEST_CHECK_EQ(u.path(), "/query.cgi");
	DCS_TEST_CHECK_EQ(u.query(), "query=bar");
	DCS_TEST_CHECK_EQ(u.fragment(), "frag");
	DCS_TEST_CHECK_EQ(u.path_etc(), "/query.cgi?query=bar#frag");
	DCS_TEST_CHECK_EQ(u.path_and_query(), "/query.cgi?query=bar");

	u.query("query=test");
	DCS_TEST_CHECK_EQ(u.query(), "query=test");

	u.fragment("result");
	DCS_TEST_CHECK_EQ(u.fragment(), "result");

	dcs::uri u2("file", "/home/foobar/foo.bar");
	DCS_TEST_CHECK_EQ(u2.scheme(), "file");
	DCS_TEST_CHECK_EQ(u2.path(), "/home/foobar/foo.bar");

	dcs::uri u3("http", "www.example.com", "/index.html");
	DCS_TEST_CHECK_EQ(u3.scheme(), "http");
	DCS_TEST_CHECK_EQ(u3.authority(), "www.example.com");
	DCS_TEST_CHECK_EQ(u3.path(), "/index.html");

	dcs::uri u4("http", "www.example.com:8080", "/index.html");
	DCS_TEST_CHECK_EQ(u4.scheme(), "http");
	DCS_TEST_CHECK_EQ(u4.authority(), "www.example.com:8080");
	DCS_TEST_CHECK_EQ(u4.path(), "/index.html");

	dcs::uri u5("http", "user@people.example.com:8080", "/index.html");
	DCS_TEST_CHECK_EQ(u5.scheme(), "http");
	DCS_TEST_CHECK_EQ(u5.user_info(), "user");
	DCS_TEST_CHECK_EQ(u5.host(), "people.example.com");
	DCS_TEST_CHECK_EQ(u5.port(), 8080);
	DCS_TEST_CHECK_EQ(u5.authority(), "user@people.example.com:8080");
	DCS_TEST_CHECK_EQ(u5.path(), "/index.html");

	dcs::uri u6("http", "user@people.example.com:80", "/index.html");
	DCS_TEST_CHECK_EQ(u6.scheme(), "http");
	DCS_TEST_CHECK_EQ(u6.user_info(), "user");
	DCS_TEST_CHECK_EQ(u6.host(), "people.example.com");
	DCS_TEST_CHECK_EQ(u6.port(), 80);
	DCS_TEST_CHECK_EQ(u6.authority(), "user@people.example.com");
	DCS_TEST_CHECK_EQ(u6.path(), "/index.html");

	dcs::uri u7("http", "user@people.example.com:", "/index.html");
	DCS_TEST_CHECK_EQ(u7.scheme(), "http");
	DCS_TEST_CHECK_EQ(u7.user_info(), "user");
	DCS_TEST_CHECK_EQ(u7.host(), "people.example.com");
	DCS_TEST_CHECK_EQ(u7.port(), 80);
	DCS_TEST_CHECK_EQ(u7.authority(), "user@people.example.com");
	DCS_TEST_CHECK_EQ(u7.path(), "/index.html");

	dcs::uri u8("http", "people.example.com", "/index.html", "query=test");
	DCS_TEST_CHECK_EQ(u8.scheme(), "http");
	DCS_TEST_CHECK_EQ(u8.authority(), "people.example.com");
	DCS_TEST_CHECK_EQ(u8.path(), "/index.html");
	DCS_TEST_CHECK_EQ(u8.query(), "query=test");

	dcs::uri u9("http", "people.example.com", "/index.html", "query=test", "fragment");
	DCS_TEST_CHECK_EQ(u9.scheme(), "http");
	DCS_TEST_CHECK_EQ(u9.authority(), "people.example.com");
	DCS_TEST_CHECK_EQ(u9.path(), "/index.html");
	DCS_TEST_CHECK_EQ(u9.path_etc(), "/index.html?query=test#fragment");
	DCS_TEST_CHECK_EQ(u9.query(), "query=test");
	DCS_TEST_CHECK_EQ(u9.fragment(), "fragment");

	u9.clear();
	DCS_TEST_CHECK(u9.scheme().empty());
	DCS_TEST_CHECK(u9.authority().empty());
	DCS_TEST_CHECK(u9.user_info().empty());
	DCS_TEST_CHECK(u9.host().empty());
	DCS_TEST_CHECK_EQ(u9.port(), dcs::uri::invalid_port);
	DCS_TEST_CHECK(u9.path().empty());
	DCS_TEST_CHECK(u9.query().empty());
	DCS_TEST_CHECK(u9.fragment().empty());

	dcs::uri u10("ldap", "[2001:db8::7]", "/c=GB?objectClass?one");
	DCS_TEST_CHECK_EQ(u10.scheme(), "ldap");
	DCS_TEST_CHECK(u10.user_info().empty());
	DCS_TEST_CHECK_EQ(u10.host(), "2001:db8::7");
	DCS_TEST_CHECK_EQ(u10.port(), 389);
	DCS_TEST_CHECK_EQ(u10.authority(), "[2001:db8::7]");
	DCS_TEST_CHECK_EQ(u10.path_etc(), "/c=GB?objectClass?one");

	dcs::uri u11("http", "www.example.com", "/index.html?query=test#fragment");
	DCS_TEST_CHECK_EQ(u11.scheme(), "http");
	DCS_TEST_CHECK_EQ(u11.authority(), "www.example.com");
	DCS_TEST_CHECK_EQ(u11.path(), "/index.html");
	DCS_TEST_CHECK_EQ(u11.path_etc(), "/index.html?query=test#fragment");
	DCS_TEST_CHECK_EQ(u11.query(), "query=test");
	DCS_TEST_CHECK_EQ(u11.fragment(), "fragment");
}


int main()
{
	DCS_TEST_SUITE( "URI Test Suite" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( construction );
	DCS_TEST_END();
}
