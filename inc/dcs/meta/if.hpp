/**
 * \file dcs/meta/if.hpp
 *
 * \brief Returns one of its two arguments, \c T1 or \c T2, depending on the
 *  value of condition \c C.
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

#ifndef DCS_META_IF_HPP
#define DCS_META_IF_HPP

#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/if.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::if_c;
using ::boost::mpl::if_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

// \see "Modern C++ Design" (Alexandrescu), sec. 2.6

namespace dcs { namespace meta {

template <bool Cond, typename ThenT, typename ElseT2>
struct if_c
{
   typedef ThenT type;
};

template <typename ThenT, typename ElseT2>
struct if_c<false, ThenT, ElseT2>
{
   typedef ElseT2 type;
};


template <typename CondT, typename ThenT, typename ElseT>
struct if_
{
	typedef typename if_c<CondT::value, ThenT, ElseT>::type type;
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_IF_HPP
