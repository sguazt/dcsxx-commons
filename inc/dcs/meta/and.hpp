/**
 * \file dcs/meta/and.hpp
 *
 * \brief Returns the result of short-circuit logical and operation on its
 *  arguments.
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

#ifndef DCS_META_AND_HPP
#define DCS_META_AND_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/and.hpp>

namespace dcs { namespace meta {

/**
 * \brief Returns the result of short-circuit logical \c and (\c &lt;&lt;)
 *  operation on its arguments.
 *
 * \author Boost libraries
 */
using ::boost::mpl::and_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/bool.hpp>

namespace dcs { namespace meta {

/**
 * \brief Returns the result of short-circuit logical \c and (\c &lt;&lt;)
 *  operation on its arguments.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename C1, typename C2>
struct and_: bool_<C1::type::value && C2::type::value>
{
	// Empty
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_AND_HPP
