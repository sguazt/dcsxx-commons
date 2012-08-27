/**
 * \file dcs/functional/bind.hpp
 *
 * \brief Generalization of the standard functions \c std::bind1st and
 *  \c std::bind2nd.
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

#ifndef DCS_FUNCTIONAL_BIND_HPP
#define DCS_FUNCTIONAL_BIND_HPP


#if __cplusplus > 201103L
// C++0x has bind
# 	include <functional>
# 	define DCS_FUNCTIONAL_BIND_NS_ ::std
# 	define DCS_FUNCTIONAL_PLACEHOLDERS_NS_ ::std::placeholders
#else
#	include <dcs/detail/config/boost.hpp>
// Use Boost bind
#   if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102500) // 1.25
#       error "Required Boost libraries version >= 1.25."
#   endif
# 	include <boost/bind.hpp>
# 	define DCS_FUNCTIONAL_BIND_NS_ ::boost
# 	define DCS_FUNCTIONAL_PLACEHOLDERS_NS_ /**/
#endif // __cplusplus
//#include <boost/bind.hpp>

namespace dcs { namespace functional {

using DCS_FUNCTIONAL_BIND_NS_::bind;
using DCS_FUNCTIONAL_BIND_NS_::is_bind_expression;
using DCS_FUNCTIONAL_BIND_NS_::is_placeholder;

namespace placeholders {

using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_1;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_2;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_3;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_4;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_5;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_6;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_7;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_8;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_9;

} // Namespace placeholders

}} // Namespace dcs::functional


#endif // DCS_FUNCTIONAL_BIND_HPP
