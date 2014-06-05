/**
 * \file dcs/meta/long.hpp
 *
 * \brief An integral constant wrapper for \c long.
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
