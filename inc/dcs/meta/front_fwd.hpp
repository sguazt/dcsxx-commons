/**
 * \file dcs/meta/front_fwd.hpp
 *
 * \brief Forward declarations for the meta-function which returns the first
 *  element in the sequence.
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

#ifndef DCS_META_FRONT_FWD_HPP
#define DCS_META_FRONT_FWD_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/front_fwd.hpp>

namespace dcs { namespace meta {

namespace detail {

using ::boost::mpl::front_impl;

} // Namespace detail

using ::boost::mpl::front;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


namespace dcs { namespace meta {

namespace detail {

template <typename SequenceTagT> struct front_impl;

} // Namespace detail

template <typename SequenceT> struct front;

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_FRONT_FWD_HPP
