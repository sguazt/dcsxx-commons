/**
 * \file dcs/meta/and.hpp
 *
 * \brief Returns the result of short-circuit logical and operation on its
 *  arguments.
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

#ifndef DCS_META_AND_HPP
#define DCS_META_AND_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/and.hpp>

namespace dcs { namespace meta {

/**
 * \brief Returns the result of short-circuit logical \c and (\c &lt;&lt;)
 *  operation on its arguments.
 *
 * \author Boost libraries
 */
using ::boost::mpl::and_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/bool.hpp>

namespace dcs { namespace meta {

/**
 * \brief Returns the result of short-circuit logical \c and (\c &lt;&lt;)
 *  operation on its arguments.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename C1, typename C2>
struct and_: bool_<C1::type::value && C2::type::value>
{
	// Empty
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_AND_HPP
