/**
 * \file dcs/meta/has_key_fwd.hpp
 *
 * \brief Forward declarations for the meta-function which returns a true-valued
 *  integral constant if the sequence contains an element with a given key.
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

#ifndef DCS_META_HAS_KEY_FWD_HPP
#define DCS_META_HAS_KEY_FWD_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/has_key_fwd.hpp>

namespace dcs { namespace meta {

namespace detail {

using ::boost::mpl::has_key_impl;

} // Namespace detail

using ::boost::mpl::has_key;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


namespace dcs { namespace meta {

namespace detail {

template <typename AssociativeSequenceTagT> struct has_key_impl;

} // Namespace detail

template <typename AssociativeSequenceT, typename KeyT> struct has_key;

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_HAS_KEY_FWD_HPP
