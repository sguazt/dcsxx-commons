/**
 * \file dcs/meta/next.hpp
 *
 * \brief Returns the next iterator in the sequence.
 *
 * \note
 *  \c next has a number of overloaded meanings, depending on the type of its
 *  argument.
 *  For instance, if X is an integral constant, \c next&lt;X&gt; returns an
 *  incremented integral constant of the same type.
 *  This specification is iterator-specific.
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

#ifndef DCS_META_NEXT_HPP
#define DCS_META_NEXT_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION(103000) // 1.30


#include <boost/mpl/next.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::next_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION


namespace dcs { namespace meta {

template <typename T>
struct next
{
	typedef typename T::next type;
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION


#endif // DCS_META_NEXT_HPP
