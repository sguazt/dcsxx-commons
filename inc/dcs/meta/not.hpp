/**
 * \file dcs/meta/not.hpp
 *
 * \brief Returns the result of logical \c not operation on its argument.
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

#ifndef DCS_META_NOT_HPP
#define DCS_META_NOT_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/not.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::not_;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <dcs/meta/bool.hpp>

namespace dcs { namespace meta {

//template<typename T> struct nested_type_wknd: public T::type
//{
//};

template <typename CondT>
//struct not_: bool_<!nested_type_wknd<CondT>::value>
struct not_: bool_<!CondT::type::value>
{
};

//XXX: does not handle nested types
//template <bool C>
//struct not_: bool_<!C>
//{
//};

}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_NOT_HPP
