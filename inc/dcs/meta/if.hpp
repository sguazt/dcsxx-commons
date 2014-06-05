/**
 * \file dcs/meta/if.hpp
 *
 * \brief Returns one of its two arguments, \c T1 or \c T2, depending on the
 *  value of condition \c C.
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

#ifndef DCS_META_IF_HPP
#define DCS_META_IF_HPP

#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/if.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::if_c;
using ::boost::mpl::if_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

// \see "Modern C++ Design" (Alexandrescu), sec. 2.6

namespace dcs { namespace meta {

template <bool Cond, typename ThenT, typename ElseT2>
struct if_c
{
   typedef ThenT type;
};

template <typename ThenT, typename ElseT2>
struct if_c<false, ThenT, ElseT2>
{
   typedef ElseT2 type;
};


template <typename CondT, typename ThenT, typename ElseT>
struct if_
{
	typedef typename if_c<CondT::value, ThenT, ElseT>::type type;
};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_IF_HPP
