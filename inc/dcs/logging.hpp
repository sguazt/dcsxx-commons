/**
 * \file dcs/logging.hpp
 *
 * \brief Logging facilities.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_LOGGING_HPP
#define DCS_LOGGING_HPP


#include <cstddef>
#include <iostream>
#include <string>


#define DCS_LOGGING_EXPAND_(x) x
#define DCS_LOGGING_STRINGIFY_(x) #x
#define DCS_LOGGING_TOSTRING_(x) DCS_LOGGING_STRINGIFY_(x)

#define DCS_LOGGING_AT0_ __FILE__ ":" DCS_LOGGING_TOSTRING_(__LINE__)
#if __STDC_VERSION__ >= 199901L || defined(__GNUC__)
// C99 or more recent versions of GCC have __func__ macro
//#define DCS_LOGGING_AT_ __FILE__ ":" DCS_LOGGING_TOSTRING_(__LINE__) ":(" __func__ ")"
#define DCS_LOGGING_AT1_ ::std::string(":(")+::std::string(__func__)+::std::string(")")
#elif defined(__GNUC__) || defined(__MSC_VER__)
// GCC and MS Visual Studio have __FUNCTION__ macro
#define DCS_LOGGING_AT1_ ::std::string(":(")+::std::string(__FUNCTION__)+::std::string(")")
#else
// Can't provide function name info
#define DCS_LOGGING_AT1_ /*empty*/
#endif // __STDC_VERSION__

#define DCS_LOGGING_AT (::std::string(DCS_LOGGING_AT0_)+::std::string(DCS_LOGGING_AT1_))

#define DCS_LOGGING_ERROR(msg) ::dcs::log_error(DCS_LOGGING_AT, msg)

#define DCS_LOGGING_INFO(msg) ::dcs::log_info(DCS_LOGGING_AT, msg)

#define DCS_LOGGING_WARN(msg) ::dcs::log_warn(DCS_LOGGING_AT, msg)


namespace dcs {

namespace detail { namespace /*<unnamed>*/ { namespace logging {

//template <typename T>
//inline
//void log(T const& t)
//{
//	::std::clog << t << ::std::endl;
//}
//

enum log_category
{
	error_log,
	info_log,
	warning_log
};

inline
::std::string to_string(log_category cat)
{
	switch (cat)
	{
		case error_log:
			return "E";
		case info_log:
			return "I";
		case warning_log:
			return "W";
	}

	return "?";
}

inline
void log(log_category cat, ::std::string const& at, ::std::string const& msg)
{
	::std::size_t pos(at.find_last_of("/\\")); // handle both win and *nix

	if (pos != ::std::string::npos)
	{
		::std::clog << "[" << to_string(cat) << ":" << at.substr(pos+1) << "] " << msg << ::std::endl;
	}
	else
	{
		::std::clog << "[" << to_string(cat) << ":" << at << "] " << msg << ::std::endl;
	}
}

}}} // Namespace detail::<unnamed>::logging

//TODO: When C++0x is out we can use something like this
//
//template <typename... Args>
//inline
//void log_warn(Args const&... args)
//{
//	detail::logging::log(args...);
//}

inline
void log_error(::std::string const& at, ::std::string const& msg)
{
	detail::logging::log(detail::logging::error_log, at, msg);
}

inline
void log_info(::std::string const& at, ::std::string const& msg)
{
	detail::logging::log(detail::logging::info_log, at, msg);
}

inline
void log_warn(::std::string const& at, ::std::string const& msg)
{
	detail::logging::log(detail::logging::warning_log, at, msg);
}

} // Namespace dcs

#endif // DCS_LOGGING_HPP
