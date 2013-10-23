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
 * This file is part of dcsxx-commons (below referred to as "this program").
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
#include <vector>


namespace dcs { namespace cli { namespace simple {

/// Find the option \a opt inside the given range of iterators.
template <typename FwdIterT>
FwdIterT find_option(FwdIterT first, FwdIterT last, ::std::string const& opt)
{
	FwdIterT it = ::std::find(first, last, opt);

	return (it != last) ? it : last;
}

/// Get the value of the option \a opt inside the given range of iterators.
template <typename T, typename FwdIterT>
T get_option(FwdIterT first, FwdIterT last, ::std::string const& opt)
{
	FwdIterT it = find_option(first, last, opt);

	if (it == last || ++it == last)
	{
		::std::ostringstream oss;
		oss << "Unable to find option: '" << opt << "'";

		DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
	}

	T value;

	::std::istringstream iss(*it);
	iss >> value;

	return value;
}

/**
 * \brief Get the value of the option \a opt inside the given range of
 *  iterators.
 *
 * \return The value of the found option, or the given default value if it is
 *  not found.
 */
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

template <typename T, typename FwdIterT>
::std::vector<T> get_options(FwdIterT first, FwdIterT last, ::std::string const& opt)
{
	::std::vector<T> values;
	bool ko(true);

	FwdIterT it = first;

	while (it != last)
	{
		it = find_option(it, last, opt);

		if (it == last)
		{
			// This is OK if we have already found an occurrence of this option.
			// Otherwise, it is not OK
			break;
		}
		if (++it == last)
		{
			// This is not OK since it is a malformed option
			ko = true;
			break;
		}

		T value;

		::std::istringstream iss(*it);
		iss >> value;

		values.push_back(value);

		ko = false;
	}

	if (ko)
	{
		::std::ostringstream oss;
		oss << "Unable to find option: '" << opt << "'";

		DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
	}

	return values;
}

template <typename T, typename FwdIterT>
::std::vector<T> get_options(FwdIterT first, FwdIterT last, ::std::string const& opt, T default_value)
{
	::std::vector<T> values;

	FwdIterT it = first;

	while (it != last)
	{
		it = find_option(it, last, opt);

		if (it != last && ++it != last)
		{
			::std::istringstream iss(*it);
			T value;
			iss >> value;
			values.push_back(value);
		}
	}

	if (values.size() == 0)
	{
		values.push_back(default_value);
	}

	return values;
}

}}} // Namespace dcs::cli::simple

#endif // DCS_CLI_SIMPLE_HPP
