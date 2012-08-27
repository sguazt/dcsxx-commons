/**
 * \file dcs/meta/iterator_tags.hpp
 *
 * \brief Provides definitions for tags of sequence iterator.
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

#ifndef DCS_META_ITERATOR_TAGS_HPP
#define DCS_META_ITERATOR_TAGS_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/iterator_tags.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::forward_iterator_tag;
using ::boost::mpl::bidirectional_iterator_tag;
using ::boost::mpl::random_access_iterator_tag;

}} // Namespace dcs::meta


#else


#include <dcs/meta/int.hpp>

namespace dcs { namespace meta {

struct forward_iterator_tag : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag: int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag: int_<2> { typedef random_access_iterator_tag type; };

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_ITERATOR_TAGS_HPP
