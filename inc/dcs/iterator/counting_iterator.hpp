/**
 * \file dcs/iterator/counting_iterator.hpp
 *
 * \brief Iterator over a sequence of consecutive values.
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

#ifndef DCS_ITERATOR_COUNTING_ITERATOR_HPP
#define DCS_ITERATOR_COUNTING_ITERATOR_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102100) // 1.21
#	error "Required Boost libraries version >= 1.21."
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

#include <boost/iterator/counting_iterator.hpp>


namespace dcs { namespace iterator {

using ::boost::counting_iterator;

}} // Namespace dcs::iterator


#endif // DCS_ITERATOR_COUNTING_ITERATOR_HPP
