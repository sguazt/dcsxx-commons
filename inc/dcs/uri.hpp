/**
 * \file dcs/uri.hpp
 *
 * \brief A class for Uniform Resource Identifiers, as specified by RFC 3986.
 *
 * Mainly based on Poco::URI class by POCO C++ Libraries.
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

#ifndef DCS_URI_HPP
#define DCS_URI_HPP


#include <algorithm>
#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <dcs/string/algorithm/to_lower.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace dcs {

/**
 * A Uniform Resource Identifier, as specified by RFC 3986.
 * 
 * The URI class provides methods for building URIs from their
 * parts, as well as for splitting URIs into their parts.
 * Furthermore, the class provides methods for resolving
 * relative URIs against base URIs.
 *
 * The class automatically performs a few normalizations on
 * all URIs and URI parts passed to it:
 *   * scheme identifiers are converted to lower case.
 *   * percent-encoded characters are decoded
 *   * optionally, dot segments are removed from paths (see normalize())
 */
class uri
{
	template <typename C, typename CT>
	friend
	::std::basic_ostream<C,CT>& operator<<(::std::basic_ostream<C,CT>& os, uri const& u);


	public: static const unsigned short invalid_port;
	private: static const ::std::string reserved_path;
	private: static const ::std::string reserved_query;
	private: static const ::std::string reserved_fragment;
	private: static const ::std::string illegal_chars;


	/// Creates an empty URI.
	public: uri()
	: port_(0)
	{
	}

	/**
	 * \brief Parses an URI from the given string \a s.
	 *
	 * Throws an exception if the given URI is not valid.
	 */
	public: explicit uri(::std::string const& str)
	: port_(0)
	{
		parse(str);
	}

	/**
	 * \brief Parses an URI from the given string \a s.
	 *
	 * Throws an exception if the given URI is not valid.
	 */
	public: explicit uri(char const* str)
	: port_(0)
	{
		parse(::std::string(str));
	}

	/// Creates an URI from its parts.
	public: uri(::std::string const& scheme, ::std::string const& path_etc)
	: scheme_(::dcs::string::to_lower_copy(scheme)),
	  port_(0)
	{
		port_ = well_known_port(scheme_);
		parse_path_etc(path_etc.begin(), path_etc.end());
	}

	/// Creates an URI from its parts.
	public: uri(::std::string const& scheme, ::std::string const& authority, ::std::string const& path_etc)
	: scheme_(::dcs::string::to_lower_copy(scheme)),
	  port_(0)
	{
		parse_authority(authority.begin(), authority.end());
		parse_path_etc(path_etc.begin(), path_etc.end());
	}

	/// Creates an URI from its parts.
	public: uri(::std::string const& scheme, ::std::string const& authority, ::std::string const& path, ::std::string const& query)
	: scheme_(::dcs::string::to_lower_copy(scheme)),
	  port_(0),
	  path_(path),
	  query_(query)
	{
		parse_authority(authority.begin(), authority.end());
	}

	/// Creates an URI from its parts.
	public: uri(::std::string const& scheme, ::std::string const& authority, ::std::string const& path, ::std::string const& query, ::std::string const& fragment)
	: scheme_(::dcs::string::to_lower_copy(scheme)),
	  port_(0),
	  path_(path),
	  query_(query),
	  fragment_(fragment)
	{
		parse_authority(authority.begin(), authority.end());
	}

	/// Copy constructor. Creates an URI from another one.
	public: uri(uri const& u)
	: scheme_(u.scheme_),
	  user_info_(u.user_info_),
	  host_(u.host_),
	  port_(u.port_),
	  path_(u.path_),
	  query_(u.query_),
	  fragment_(u.fragment_)
	{
	}

	/**
	 * \brief Creates an URI from a base URI and a relative URI, according to
	 *  the algorithm in section 5.2 of RFC 3986.
	 */
	public: uri(uri const& base_uri, ::std::string const& relative_uri)
	: scheme_(base_uri.scheme_),
	  user_info_(base_uri.user_info_),
	  host_(base_uri.host_),
	  port_(base_uri.port_),
	  path_(base_uri.path_),
	  query_(base_uri.query_),
	  fragment_(base_uri.fragment_)
	{
		resolve(relative_uri);
	}

	/// Assignment operator.
	public: uri& operator = (uri const& u)
	{
		if (this != &u)
		{
			scheme_ = u.scheme_;
			user_info_ = u.user_info_;
			host_ = u.host_;
			port_ = u.port_;
			path_ = u.path_;
			query_ = u.query_;
			fragment_ = u.fragment_;
		}

		return *this;
	}

//	/**
//	 * \brief Parses and assigns an URI from the given string.
//	 *
//	 * Throws an exception if the uri is not valid.
//	 */
//	public: uri& operator=(std::string const& s)
//	{
//		clear();
//		parse(s);
//
//		return *this;
//	}

//	/**
//	 * \brief Parses and assigns an URI from the given string.
//	 *
//	 * Throws an exception if the uri is not valid.
//	 */
//	public: uri& operator=(char const* s)
//	{
//		clear();
//		parse(::std::string(s));
//
//		return *this;
//	}

	/// Swaps the URI with another one.	
	public: void swap(uri& u)
	{
		::std::swap(scheme_, u.scheme_);
		::std::swap(user_info_, u.user_info_);
		::std::swap(host_, u.host_);
		::std::swap(port_, u.port_);
		::std::swap(path_, u.path_);
		::std::swap(query_, u.query_);
		::std::swap(fragment_, u.fragment_);
	}

	/// Clears all parts of the URI.
	public: void clear()
	{
		scheme_.clear();
		user_info_.clear();
		host_.clear();
		port_ = invalid_port;
		path_.clear();
		query_.clear();
		fragment_.clear();
	}

	/// Returns the scheme part of the URI.
	public: ::std::string scheme() const
	{
		return scheme_;
	}

	/**
	 * Sets the scheme part of the URI. The given scheme
	 * is converted to lower-case.
	 *
	 * A list of registered URI schemes can be found
	 * at <http://www.iana.org/assignments/uri-schemes>.
	 */
	public: void scheme(::std::string const& s)
	{
		scheme_ = ::dcs::string::to_lower_copy(s);
		if (invalid_port == port_)
		{
			port_ = well_known_port(scheme_);
		}
	}

	/// Returns the user-info part of the URI.
	public: ::std::string user_info() const
	{
		return user_info_;
	}

	/// Sets the user-info part of the URI.
	public: void user_info(::std::string const& str)
	{
		user_info_ = decode(str);
	}

	/// Returns the host part of the URI.
	public: ::std::string host() const
	{
		return host_;
	}

	/// Sets the host part of the URI.
	public: void host(std::string const& s)
	{
		host_ = s;
	}

	/// Returns the port number part of the URI.
	///
	/// If no port number (0) has been specified, the
	/// well-known port number (e.g., 80 for http) for
	/// the given scheme is returned if it is known.
	/// Otherwise, 0 is returned.
	public: unsigned short port() const
	{
		if (invalid_port == port_)
		{
			return well_known_port(scheme_);
		}

		return port_;
	}

	/// Sets the port number part of the URI.
	public: void port(unsigned short val)
	{
		//pre: 0 <= val <= 0xFFFF
//		DCS_ASSERT(/*0 <= val &&*/ 0xFFFF >= val,
//				   DCS_EXCEPTION_THROW(::std::invalid_argument,
//									   "Port is out-of-range"));
		port_ = val;
	}

	/// Returns the authority part (userInfo, host and port)
	/// of the URI. 
	///
	/// If the port number is a well-known port
	/// number for the given scheme (e.g., 80 for http), it
	/// is not included in the authority.
	public: ::std::string authority() const
	{
		::std::ostringstream oss;

		if (!user_info_.empty())
		{
			oss << user_info_ << '@';
		}
		if (::std::string::npos != host_.find(':'))
		{
			// IPv6 style host name
			oss << '[' << host_ << ']';
		}
		else
		{
			oss << host_;
		}
		if (invalid_port != port_ && well_known_port(scheme_) != port_)
		{
			oss << ':' << port_;
		}

		return oss.str();
	}

	/// Parses the given authority part for the URI and sets
	/// the user-info, host, port components accordingly.
	public: void authority(::std::string const& str)
	{
		user_info_.clear();
		host_.clear();
		port_ = invalid_port;
		parse_authority(str.begin(), str.end());
	}

	/// Returns the path part of the URI.
	public: ::std::string path() const
	{
		return path_;
	}

	/// Sets the path part of the URI.
	public: void path(::std::string const& str)
	{
		path_ = decode(str);
	}

	/// Returns the query part of the URI.
	public: ::std::string query() const
	{
		return decode(query_);
	}

	/// Sets the query part of the URI.
	public: void query(::std::string const& str)
	{
		query_ = encode(str, reserved_query);
	}

	/// Returns the unencoded query part of the URI.
	public: ::std::string raw_query() const
	{
		return query_;
	}

	/// Sets the query part of the URI.
	public: void raw_query(::std::string const& str)
	{
		query_ = str;
	}

	/// Returns the fragment part of the URI.
	public: ::std::string fragment() const
	{
		return fragment_;
	}

	/// Sets the fragment part of the URI.
	public: void fragment(::std::string const& str)
	{
		fragment_ = decode(str);
	}

	/// Returns the path, query and fragment parts of the URI.
	public: ::std::string path_etc() const
	{
		::std::ostringstream oss;

		oss << encode(path_, reserved_path);
		if (!query_.empty())
		{
			oss << '?' << query_;
		}
		if (!fragment_.empty())
		{
			oss << '#' << encode(fragment_, reserved_fragment);
		}

		return oss.str();
	}

	/// Sets the path, query and fragment parts of the URI.
	public: void path_etc(::std::string const& str)
	{
		path_.clear();
		query_.clear();
		fragment_.clear();
		parse_path_etc(str.begin(), str.end());
	}

	/// Returns the path and query parts of the URI.	
	public: ::std::string path_and_query() const
	{
		::std::ostringstream oss;

		oss << encode(path_, reserved_path);

		if (!query_.empty())
		{
			oss << '?' << query_;
		}

		return oss.str();
	}

	/// Resolves the given relative URI against the base URI.
	/// See section 5.2 of RFC 3986 for the algorithm used.
	public: void resolve(::std::string const& relative_uri)
	{
		uri parsed_uri(relative_uri);
		resolve(parsed_uri);
	}

	/// Resolves the given relative URI against the base URI.
	/// See section 5.2 of RFC 3986 for the algorithm used.
	public: void resolve(uri const& relative_uri)
	{
		if (!relative_uri.scheme_.empty())
		{
			scheme_ = relative_uri.scheme_;
			user_info_ = relative_uri.user_info_;
			host_ = relative_uri.host_;
			port_ = relative_uri.port_;
			path_ = relative_uri.path_;
			query_ = relative_uri.query_;
			remove_dot_segments();
		}
		else
		{
			if (!relative_uri.host_.empty())
			{
				user_info_ = relative_uri.user_info_;
				host_ = relative_uri.host_;
				port_ = relative_uri.port_;
				path_ = relative_uri.path_;
				query_ = relative_uri.query_;
				remove_dot_segments();
			}
			else
			{
				if (relative_uri.path_.empty())
				{
					if (!relative_uri.query_.empty())
					{
						query_ = relative_uri.query_;
					}
				}
				else
				{
					if (relative_uri.path_[0] == '/')
					{
						path_ = relative_uri.path_;
						remove_dot_segments();
					}
					else
					{
						merge_path(relative_uri.path_);
					}
					query_ = relative_uri.query_;
				}
			}
		}
		fragment_ = relative_uri.fragment_;      
	}

	/// Returns true if the URI is a relative reference, false otherwise.
	///
	/// A relative reference does not contain a scheme identifier.
	/// Relative references are usually resolved against an absolute
	/// base reference.
	public: bool relative() const
	{
		return scheme_.empty();
	}

	/// Returns true if the URI is empty, false otherwise.
	public: bool empty() const
	{
		return scheme_.empty() && host_.empty() && path_.empty() && query_.empty() && fragment_.empty();
	}

	/// Returns true if both URIs are identical, false otherwise.
	///
	/// Two URIs are identical if their scheme, authority,
	/// path, query and fragment part are identical.
	public: bool operator==(uri const& u) const
	{
		return equals(u);
	}

	/// Parses the given URI and returns true if both URIs are identical,
	/// false otherwise.
	public: bool operator==(::std::string const& str) const
	{
		return equals(uri(str));
	}

	/// Returns true if both URIs are identical, false otherwise.
	public: bool operator!=(uri const& u) const
	{
		return !equals(u);
	}

	/// Parses the given URI and returns true if both URIs are identical,
	/// false otherwise.
	public: bool operator!=(::std::string const& str) const
	{
		return !equals(uri(str));
	}

	/// Normalizes the URI by removing all but leading . and .. segments from the path.
	///
	/// If the first path segment in a relative path contains a colon (:), 
	/// such as in a Windows path containing a drive letter, a dot segment (./) 
	/// is prepended in accordance with section 3.3 of RFC 3986.
	public: void normalize()
	{
		remove_dot_segments(!relative());
	}

	/// Places the single path segments (delimited by slashes) into the
	/// given vector.
	public: void path_segments(::std::vector< ::std::string >& segs)
	{
		path_segments(path_, segs);
	}

	/// Returns true if both uri's are equivalent.
	private: bool equals(uri const& u) const
	{
		return scheme_ == u.scheme_
			&& user_info_ == u.user_info_
			&& host_ == u.host_
			&& port() == u.port() // Needed in case of the two URIs uses unspecified (well-known) port
			&& path_ == u.path_
			&& query_ == u.query_
			&& fragment_ == u.fragment_;
	}

	/// Parses and assigns an URI from the given string. Throws a
	/// SyntaxException if the uri is not valid.
	private: void parse(::std::string const& str)
	{
		typedef ::std::string::const_iterator string_iterator;

		string_iterator it(str.begin());
		string_iterator end_it(str.end());

		if (it == end_it)
		{
			return;
		}

		if (*it != '/' && *it != '.' && *it != '?' && *it != '#')
		{
			::std::ostringstream oss;
			for (; it != end_it && *it != ':' && *it != '?' && *it != '#' && *it != '/'; ++it)
			{
				oss << *it;
			}
			if (it != end_it && *it == ':')
			{
				++it;
				if (it == end_it)
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"URI scheme must be followed by authority or path: " + str);
				}
				scheme(oss.str());
				if (*it == '/')
				{
					++it;
					if (it != end_it && *it == '/')
					{
						++it;
						it = parse_authority(it, end_it);
					}
					else
					{
						--it;
					}
				}
				it = parse_path_etc(it, end_it);
			}
			else 
			{
				it = str.begin();
				it = parse_path_etc(it, end_it);
			}
		}
		else
		{
			it = parse_path_etc(it, end_it);
		}
	}

	/// Parses and sets the user-info, host and port from the given data.
	private: template <typename IterT>
			 IterT parse_authority(IterT first, IterT last)
	{
		::std::string user;
		::std::ostringstream oss;
		for (; first != last && *first != '/' && *first != '?' && *first != '#'; ++first)
		{
			if (*first == '@')
			{
				user = oss.str();
				oss.str("");
			}
			else
			{
				oss << *first;
			}
		}

		::std::string part(oss.str());

		parse_host_and_port(part.begin(), part.end());

		user_info_ = user;

		return first;
	}

	/// Parses and sets the host and port from the given data.
	private: template <typename IterT>
			 IterT parse_host_and_port(IterT first, IterT last)
	{
		if (first == last)
		{
			return first;
		}
		::std::string h;
		::std::ostringstream oss;
		if (*first == '[')
		{
			// IPv6 address
			++first;
			while (first != last && *first != ']')
			{
				oss << *first++;
			}
			if (first == last)
			{
				DCS_EXCEPTION_THROW(::std::logic_error,
									"Unterminated IPv6 address");
			}
			++first;
		}
		else
		{
			while (first != last && *first != ':')
			{
				oss << *first++;
			}
		}
		h = oss.str();
		oss.str("");
		if (first != last && *first == ':')
		{
			++first;
			std::string p;
			while (first != last)
			{
				oss << *first++;
			}
			p = oss.str();
			if (!p.empty())
			{
				int nport = 0;
				try
				{
					::std::istringstream iss(p);
					iss >> nport;
					if (nport <= 0 || nport >= 65536)
					{
						DCS_EXCEPTION_THROW(::std::logic_error,
											"Bad or invalid port number: " + p);
					}
				}
				catch (...)
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"Bad or invalid port number: " + p);
				}
				port_ = nport;
			}
			else
			{
				port_ = well_known_port(scheme_);
			}
		}
		else
		{
			port_ = well_known_port(scheme_);
		}

		host_ = ::dcs::string::to_lower_copy(h);

		return first;
	}

	/// Parses and sets the path from the given data.
	private: template <typename IterT>
			 IterT parse_path(IterT first, IterT last)
	{
		::std::ostringstream oss;
		for (; first != last && *first != '?' && *first != '#'; ++first)
		{
			oss << *first;
		}

		//FIXME: should we use '+=' or '='?
		path_ += decode(oss.str());

		return first;
	}

	/// Parses and sets the path, query and fragment from the given data.
	private: template <typename IterT>
			 IterT parse_path_etc(IterT first, IterT last)
	{
		if (first == last)
		{
			return first;
		}
		if (*first != '?' && *first != '#')
		{
			first = parse_path(first, last);
		}
		if (first != last && *first == '?')
		{
			++first;
			first = parse_query(first, last);
		}
		if (first != last && *first == '#')
		{
			++first;
			first = parse_fragment(first, last);
		}

		return first;
	}

	/// Parses and sets the query from the given data.
	private: template <typename IterT>
			 IterT parse_query(IterT first, IterT last)
	{
		query_.clear();
		for (; first != last && *first != '#'; ++first)
		{
			query_ += *first;
		}

		return first;
	}

	/// Parses and sets the fragment from the given data.
	private: template <typename IterT>
			 IterT parse_fragment(IterT first, IterT last)
	{
		::std::ostringstream oss;
		for (; first != last; ++first)
		{
			oss << *first;
		}

		//FIXME: should we use '+=' or '='?
		fragment_ += decode(oss.str());

		return first;
	}

	/// Appends a path to the URI's path.
	private: void merge_path(::std::string const& str)
	{
		::std::vector< ::std::string > segs;
		::std::vector< ::std::string > norm_segs;
		bool add_leading_slash = false;
		if (!path_.empty())
		{
			path_segments(segs);
			bool ends_with_slash = *(path_.rbegin()) == '/';
			if (!ends_with_slash && !segs.empty())
			{
				segs.pop_back();
			}
			add_leading_slash = path_[0] == '/';
		}
		path_segments(str, segs);
		add_leading_slash = add_leading_slash || (!str.empty() && str[0] == '/');
		bool has_trailing_slash = (!str.empty() && *(str.rbegin()) == '/');
		bool add_trailing_slash = false;
		::std::vector< ::std::string >::const_iterator end_it(segs.end());
		for (::std::vector< ::std::string >::const_iterator it = segs.begin(); it != end_it; ++it)
		{
			if (*it == "..")
			{
				add_trailing_slash = true;
				if (!norm_segs.empty())
					norm_segs.pop_back();
			}
			else if (*it != ".")
			{
				add_trailing_slash = false;
				norm_segs.push_back(*it);
			}
			else
			{
				add_trailing_slash = true;
			}
		}
		build_path(norm_segs, add_leading_slash, has_trailing_slash || add_trailing_slash);
	}

	/// Removes all dot segments from the path.
	private: void remove_dot_segments(bool remove_leading = true)
	{
		typedef ::std::vector< ::std::string > string_container;
		typedef string_container::const_iterator string_iterator;

		if (path_.empty())
		{
			return;
		}
		
		bool leading_slash = *(path_.begin()) == '/';
		bool trailing_slash = *(path_.rbegin()) == '/';
		string_container segments;
		string_container norm_segments;
		path_segments(segments);
		string_iterator end_it(segments.end());
		for (string_iterator it = segments.begin(); it != end_it; ++it)
		{
			::std::string const& s(*it);
			if (s == "..")
			{
				if (!norm_segments.empty())
				{
					if (norm_segments.back() == "..")
					{
						norm_segments.push_back(s);
					}
					else
					{
						norm_segments.pop_back();
					}
				}
				else if (!remove_leading)
				{
					norm_segments.push_back(s);
				}
			}
			else if (s != ".")
			{
				norm_segments.push_back(s);
			}
		}
		build_path(norm_segments, leading_slash, trailing_slash);
	}

	/// Returns true if the URI's port number is a well-known one
	/// (for example, 80, if the scheme is http).
	private: static bool well_known_port(::std::string const& scheme, unsigned short port)
	{
		return port == well_known_port(scheme);
	}

	/// Returns the well-known port number for the URI's scheme,
	/// or 0 if the port number is not known.
	private: static unsigned short well_known_port(::std::string const& scheme)
	{
		//TODO: incomplete
		// See:
		// - https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers
		// - https://www.iana.org/assignments/uri-schemes.html
		// - http://www.iana.org/assignments/port-numbers

		if (scheme == "ftp")
		{
			return 21;
		}
		else if (scheme == "ssh")
		{
			return 22;
		}
		else if (scheme == "telnet")
		{
			return 23;
		}
		else if (scheme == "http")
		{
			return 80;
		}
		else if (scheme == "nntp")
		{
			return 119;
		}
		else if (scheme == "ldap")
		{
			return 389;
		}
		else if (scheme == "https")
		{
			return 443;
		}
		else if (scheme == "rtsp")
		{
			return 554;
		}
		else if (scheme == "sip")
		{
			return 5060;
		}
		else if (scheme == "sips")
		{
			return 5061;
		}
		else if (scheme == "xmpp")
		{
			return 5222;
		}

		return invalid_port;
	}

	/// URI-encodes the given string by escaping reserved and non-ASCII
	/// characters.
	public: static ::std::string encode(::std::string const& str, ::std::string const& reserved)
	{
		typedef ::std::string::const_iterator string_iterator;

		::std::ostringstream oss;
		string_iterator end_it(str.end());
		for (string_iterator it = str.begin(); it != end_it; ++it)
		{
			char c = *it;
			if (   (c >= 'a' && c <= 'z')
				|| (c >= 'A' && c <= 'Z')
				|| (c >= '0' && c <= '9')
				|| c == '-'
				|| c == '_'
				|| c == '.'
				|| c == '~')
			{
				oss << c;
			}
			else if (c <= 0x20 || c >= 0x7F || illegal_chars.find(c) != ::std::string::npos || reserved.find(c) != ::std::string::npos)
			{
				oss << '%' << ::std::setw(2) << ::std::hex << c;
			}
			else
			{
				oss << c;
			}
		}

		return oss.str();
	}

	/// URI-decodes the given string by replacing percent-encoded
	/// characters with the actual character.
	public: static ::std::string decode(::std::string const& str)
	{
		typedef ::std::string::const_iterator string_iterator;

		::std::ostringstream oss;

		string_iterator it(str.begin());
		string_iterator end_it(str.end());
		while (it != end_it)
		{
			char c = *it++;
			if (c == '%')
			{
				if (it == end_it)
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"No hex digit following percent sign: " + str);
				}

				char hi = *it++;
				if (it == end_it)
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"Two hex digits must follow percent sign: " + str);
				}

				char lo = *it++;
				if (hi >= '0' && hi <= '9')
				{
					c = hi - '0';
				}
				else if (hi >= 'A' && hi <= 'F')
				{
					c = hi - 'A' + 10;
				}
				else if (hi >= 'a' && hi <= 'f')
				{
					c = hi - 'a' + 10;
				}
				else
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"Not a hex digit");
				}
				c *= 16;
				if (lo >= '0' && lo <= '9')
				{
					c += lo - '0';
				}
				else if (lo >= 'A' && lo <= 'F')
				{
					c += lo - 'A' + 10;
				}
				else if (lo >= 'a' && lo <= 'f')
				{
					c += lo - 'a' + 10;
				}
				else
				{
					DCS_EXCEPTION_THROW(::std::logic_error,
										"Not a hex digit");
				}
			}
			oss << c;
		}

		return oss.str();
	}

	/// Places the single path segments (delimited by slashes) into the
	/// given vector.
	private: static void path_segments(::std::string const& path, ::std::vector< ::std::string >& segs)
	{
		typedef ::std::string::const_iterator string_iterator;

		std::string seg;
		::std::ostringstream oss;
		string_iterator end_it(path.end());
		for (string_iterator it = path.begin(); it != end_it; ++it)
		{
			if (*it == '/')
			{
				seg = oss.str();
				if (!seg.empty())
				{
					segs.push_back(seg);
					oss.str("");
				}
			}
			else
			{
				oss << *it;
			}
		}
		seg = oss.str();
		if (!seg.empty())
		{
			segs.push_back(seg);
		}
	}

	/// Builds the path from the given segments.
	private: void build_path(::std::vector< ::std::string > const& segs, bool leading_slash, bool trailing_slash)
	{
		typedef ::std::vector< ::std::string >::const_iterator seg_iterator;
		path_.clear();

		bool first = true;
		::std::ostringstream oss;
		seg_iterator end_it(segs.end());
		for (seg_iterator it = segs.begin(); it != end_it; ++it)
		{
			if (first)
			{
				first = false;
				if (leading_slash)
				{
					oss << '/';
				}
				else if (scheme_.empty() && it->find(':') != ::std::string::npos)
				{
					oss << "./";
				}
			}
			else
			{
				oss << '/';
			}
			oss << *it;
		}
		if (trailing_slash) 
		{
			oss << '/';
		}

		path_ = oss.str();
	}


	private: ::std::string scheme_;
	private: ::std::string user_info_;
	private: ::std::string host_;
	private: unsigned short port_;
	private: ::std::string path_;
	private: ::std::string query_;
	private: ::std::string fragment_;
}; // uri

const unsigned short uri::invalid_port = 0;

const ::std::string uri::reserved_path = "?#";

const ::std::string uri::reserved_query = "#";

const ::std::string uri::reserved_fragment = "";

const ::std::string uri::illegal_chars = "%<>{}|\\\"^`";

//const ::std::string uri::reserved_chars = ":/?#[]@!$&'()*+,;="; // Delimiting characters that are distinguishable from other data within a URI


inline
void swap(uri& u1, uri& u2)
{
	u1.swap(u2);
}

/**
 * Writes a string representation of the URI.
 *
 * Characters in the path, query and fragment parts will be 
 * percent-encoded as necessary.
 */
template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, uri const& u)
{
	::std::ostringstream oss;
	if (u.relative())
	{
		oss << dcs::uri::encode(u.path(), uri::reserved_path);
	}
	else
	{
		oss << u.scheme();
		oss << ':';
		std::string auth = u.authority();
		if (!auth.empty() || u.scheme() == "file")
		{
			oss << "//" << auth;
		}
		if (!u.path().empty())
		{
			if (!auth.empty() && u.path()[0] != '/')
			{
				oss << '/';
			}
			oss << dcs::uri::encode(u.path(), uri::reserved_path);
		}
		else if (!u.query().empty() || !u.fragment().empty())
		{
			oss << '/';
		}
	}
	if (!u.query().empty())
	{
		oss << '?';
		oss << u.query();
	}
	if (!u.fragment().empty())
	{
		oss << '#' << dcs::uri::encode(u.fragment(), uri::reserved_fragment);
	}

	os << oss.str();

	return os;
}

} // Namespace dcs

#endif // DCS_URI_HPP
