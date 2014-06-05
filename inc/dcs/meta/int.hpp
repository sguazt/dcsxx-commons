/**
 * \file dcs/meta/int.hpp
 *
 * \brief An integral constant wrapper for \c int.
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
