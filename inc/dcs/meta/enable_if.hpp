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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2009 Marco Guazzone (marco.guazzone@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
