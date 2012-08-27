/**
 * \file dcs/meta/int.hpp
 *
 * \brief An integral constant wrapper for \c int.
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

#ifndef DCS_META_INT_HPP
#define DCS_META_INT_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/int.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::int_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/integral_c_tag.hpp>

namespace dcs { namespace meta {

template <int> struct int_;

template <int Num>
struct int_
{
	//static const int value = Num;
	enum { value = Num }; // More portable version
	typedef int_ type;
	typedef int value_type;
	typedef integral_c_tag tag;
	typedef int_<Num+1> next;
	typedef int_<Num-1> prior;
	operator int() const { return value; }
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_INT_HPP
