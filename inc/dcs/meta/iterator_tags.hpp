/**
 * \file dcs/meta/iterator_tags.hpp
 *
 * \brief Provides definitions for tags of sequence iterator.
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

#ifndef DCS_META_ITERATOR_TAGS_HPP
#define DCS_META_ITERATOR_TAGS_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/iterator_tags.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::forward_iterator_tag;
using ::boost::mpl::bidirectional_iterator_tag;
using ::boost::mpl::random_access_iterator_tag;

}} // Namespace dcs::meta


#else


#include <dcs/meta/int.hpp>

namespace dcs { namespace meta {

struct forward_iterator_tag : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag: int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag: int_<2> { typedef random_access_iterator_tag type; };

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_ITERATOR_TAGS_HPP
