/**
 * \file dcs/meta/long.hpp
 *
 * \brief An integral constant wrapper for \c long.
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

#ifndef DCS_META_LONG_HPP
#define DCS_META_LONG_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/long.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::long_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/integral_c_tag.hpp>

namespace dcs { namespace meta {

template <long Num>
struct long_
{
	typedef integral_c_tag tag;
	typedef long_ type;
	typedef long value_type;
	static const long value = static_cast<long>(Num);
	//enum { value = Num }; // More portable version
	typedef long_<Num+1> next;
	typedef long_<Num-1> prior;
	operator long() const { return static_cast<long>(value); }
};


}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_LONG_HPP
