/**
 * \file dcs/meta/count_fwd.hpp
 *
 * \brief Forward declarations for the meta-function which returns the number of
 *  elements in a sequence that are identical to the given type.
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

#ifndef DCS_META_COUNT_FWD_HPP
#define DCS_META_COUNT_FWD_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/count_fwd.hpp>

namespace dcs { namespace meta {

namespace detail {

using ::boost::mpl::count_impl;

} // Namespace detail

using ::boost::mpl::count;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


namespace dcs { namespace meta {

namespace detail {

template <typename AssociativeSequenceTagT> struct count_impl;

} // Namespace detail

template <typename AssociativeSequenceT, typename KeyT> struct count;

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_COUNT_FWD_HPP
