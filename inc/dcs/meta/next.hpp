/**
 * \file dcs/meta/next.hpp
 *
 * \brief Returns the next iterator in the sequence.
 *
 * \note
 *  \c next has a number of overloaded meanings, depending on the type of its
 *  argument.
 *  For instance, if X is an integral constant, \c next&lt;X&gt; returns an
 *  incremented integral constant of the same type.
 *  This specification is iterator-specific.
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

#ifndef DCS_META_NEXT_HPP
#define DCS_META_NEXT_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION(103000) // 1.30


#include <boost/mpl/next.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::next_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION


namespace dcs { namespace meta {

template <typename T>
struct next
{
	typedef typename T::next type;
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_DEFINE_VERSION


#endif // DCS_META_NEXT_HPP
