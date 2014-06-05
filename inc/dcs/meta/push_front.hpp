/**
 * \file dcs/meta/push_front.hpp
 *
 * \brief Performs an insertion at the beginning of the sequence
 *
 * It guarantees a \f$\mathcal{O}(1)\f$ complexity.
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

#ifndef DCS_META_PUSH_FRONT_HPP
#define DCS_META_PUSH_FRONT_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/push_front.hpp>
//#include <boost/mpl/push_front_fwd.hpp>

namespace dcs { namespace meta {

//using ::boost::mpl::push_front_impl;
using ::boost::mpl::push_front;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/push_front_fwd.hpp>
#include <dcs/meta/sequence_tag.hpp>

namespace dcs { namespace meta {

template <typename SequenceT>
struct push_front: public detail::push_front_impl< typename sequence_tag<SequenceT>::type >::template apply<SequenceT>
{
};


}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_PUSH_FRONT_HPP
