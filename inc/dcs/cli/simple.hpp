/**
 * \file dcs/cli/simple.hpp
 *
 * \brief A minimal set of functions for a trivial parsing of command line
 *  options passed to programs.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons.
 *
 * dcsxx-commons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcsxx-commons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcsxx-commons. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_CLI_SIMPLE_HPP
#define DCS_CLI_SIMPLE_HPP


#include <algorithm>
#include <dcs/exception.hpp>
#include <sstream>
#include <stdexcept>
#include <string>


namespace dcs { namespace cli { namespace simple {

template <typename FwdIterT>
FwdIterT find_option(FwdIterT first, FwdIterT last, ::std::string const& option)
{
	FwdIterT it = ::std::find(first, last, option);

	return (it != last) ? it : last;
}

template <typename T, typename FwdIterT>
T get_option(FwdIterT first, FwdIterT last, ::std::string const& option)
{
	FwdIterT it = find_option(first, last, option);

	if (it == last || ++it == last)
	{
		::std::ostringstream oss;
		oss << "Unable to find option: '" << option << "'";

		DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
	}

	T value;

	::std::istringstream iss(*it);
	iss >> value;

	return value;
}

template <typename T, typename FwdIterT>
T get_option(FwdIterT first, FwdIterT last, ::std::string const& opt, T default_value)
{
	FwdIterT it = find_option(first, last, opt);

	T value(default_value);

	if (it != last && ++it != last)
	{
		::std::istringstream iss(*it);
		iss >> value;
	}

	return value;
}

/// Get a boolean option; also tell if a given option does exist.
template <typename FwdIterT>
bool get_option(FwdIterT first, FwdIterT last, ::std::string const& opt)
{
	FwdIterT it = find_option(first, last, opt);

	return it != last;
}

}}} // Namespace dcs::cli::simple

#endif // DCS_CLI_SIMPLE_HPP
