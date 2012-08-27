/**
 * \file dcs/meta/empty_sequence.hpp
 *
 * \brief Returns an empty sequence.
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

#ifndef DCS_META_EMPTY_SEQUENCE_HPP
#define DCS_META_EMPTY_SEQUENCE_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/empty_sequence.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::empty_sequence;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/int.hpp>
#include <dcs/meta/iterator_tags.hpp>

namespace dcs { namespace meta {

struct empty_sequence
{
	struct tag;
	struct begin { typedef random_access_iterator_tag category; };
	typedef begin end;
};

namespace detail {

template <>
struct size_impl<empty_sequence::tag>
{
	template <typename SequenceT> struct apply: public int_<0>
	{
	};
};

} // Namespace detail

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_EMPTY_SEQUENCE_HPP
