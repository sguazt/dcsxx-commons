/**
 * \file dcs/meta/bool.hpp
 *
 * \brief Boolean integral constant wrapper.
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

#ifndef DCS_META_BOOL_HPP
#define DCS_META_BOOL_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/bool.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::bool_;
using ::boost::mpl::true_;
using ::boost::mpl::false_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/integral_c_tag.hpp>

namespace dcs { namespace meta {

template <bool Cond>
struct bool_
{
	static const bool value = Cond;
	//enum { value = Cond }; // More portable version
    typedef integral_c_tag tag;
	typedef bool_ type;
	typedef bool value_type;
	operator bool() const { return value; }
};


typedef bool_<true> true_;
typedef bool_<false> false_;

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_BOOL_HPP
