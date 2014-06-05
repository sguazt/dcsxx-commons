/**
 * \file dcs/meta/empty_sequence.hpp
 *
 * \brief Returns an empty sequence.
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

#ifndef DCS_META_EMPTY_SEQUENCE_HPP
#define DCS_META_EMPTY_SEQUENCE_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/empty_sequence.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::empty_sequence;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/int.hpp>
#include <dcs/meta/iterator_tags.hpp>

namespace dcs { namespace meta {

struct empty_sequence
{
	struct tag;
	struct begin { typedef random_access_iterator_tag category; };
	typedef begin end;
};

namespace detail {

template <>
struct size_impl<empty_sequence::tag>
{
	template <typename SequenceT> struct apply: public int_<0>
	{
	};
};

} // Namespace detail

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_EMPTY_SEQUENCE_HPP
