/**
 * \file dcs/meta/enable_if.hpp
 *
 * \brief Enable or disable a function template or a class template
 *  specialization.
 *
 * From the Boost.Utility library:
 * "The enable_if family of templates is a set of tools to allow a function
 * template or a class template specialization to include or exclude itself from
 * a set of matching functions or specializations based on properties of its
 * template arguments. For example, one can define function templates that are
 * only enabled for, and thus only match, an arbitrary set of types defined by
 * a traits class. The enable_if templates can also be applied to enable class
 * template specializations."
 * The "lazy" version is used in those cases whereby it is necessary to avoid
 * instantiating part of a function signature unless an enabling condition is
 * true.
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

#ifndef DCS_META_ENABLE_IF_HPP
#define DCS_META_ENABLE_IF_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103100)


#include <boost/utility/enable_if.hpp>

namespace dcs { namespace meta {

using ::boost::enable_if;
using ::boost::disable_if;
using ::boost::lazy_enable_if;
using ::boost::lazy_disable_if;
using ::boost::enable_if_c;
using ::boost::disable_if_c;
using ::boost::lazy_enable_if_c;
using ::boost::lazy_disable_if_c;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


namespace dcs { namespace meta {

// Use the SFINAE approach (can be tricky for some compilers)

//template <bool B, class T> struct enable_if {};
//template <class T> struct enable_if<true, T> { typedef T type; };

template <bool B, class T = void>
struct enable_if_c
{
	typedef T type;
};

template <typename T>
struct enable_if_c<false, T> {};

template <class Cond, typename T = void>
struct enable_if : public enable_if_c<Cond::value, T> {};


template <bool B, typename T>
struct lazy_enable_if_c
{
	typedef typename T::type type;
};

template <class T>
struct lazy_enable_if_c<false, T> {};

template <class Cond, class T>
struct lazy_enable_if : public lazy_enable_if_c<Cond::value, T> {};


template <bool B, class T = void>
struct disable_if_c
{
	typedef T type;
};

template <typename T>
struct disable_if_c<true, T> {};

template <typename Cond, typename T = void>
struct disable_if : public disable_if_c<Cond::value, T> {};


template <bool B, typename T>
struct lazy_disable_if_c
{
	typedef typename T::type type;
};

template <typename T>
struct lazy_disable_if_c<true, T> {};

template <typename Cond, typename T>
struct lazy_disable_if : public lazy_disable_if_c<Cond::value, T> {};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_ENABLE_IF_HPP
