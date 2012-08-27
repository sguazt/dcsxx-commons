/**
 * \file dcs/exception.hpp
 *
 * \brief Exceptions support.
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

#ifndef DCS_EXCEPTION_HPP
#define DCS_EXCEPTION_HPP


#include <boost/current_function.hpp>
#include <sstream>
#include <string>


namespace dcs { namespace exception { namespace detail { namespace /*<unnamed>*/ {

inline ::std::string make_msg(::std::string const& m, char const* func_name)
{
	::std::ostringstream oss;
	//oss << "[" << BOOST_CURRENT_FUNCTION << "] " << m;
	oss << "[" << func_name << "] " << m << ".";
	return oss.str();
}

}}}} // Namespace dcs::exception::detail::<unnamed>


//#define DCS_EXCEPTION_THROW(e,m) throw e(::dcs::exception::detail::make_msg(m))
#define DCS_EXCEPTION_THROW(e,m) throw e(::dcs::exception::detail::make_msg(m, BOOST_CURRENT_FUNCTION))

#define DCS_EXCEPTION_RETHROW(e) throw e;

#endif // DCS_EXCEPTION_HPP
