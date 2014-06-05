/**
 * \file dcs/iterator/counting_iterator.hpp
 *
 * \brief Iterator over a sequence of consecutive values.
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

#ifndef DCS_ITERATOR_COUNTING_ITERATOR_HPP
#define DCS_ITERATOR_COUNTING_ITERATOR_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102100) // 1.21
#	error "Required Boost libraries version >= 1.21."
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

#include <boost/iterator/counting_iterator.hpp>


namespace dcs { namespace iterator {

using ::boost::counting_iterator;

}} // Namespace dcs::iterator


#endif // DCS_ITERATOR_COUNTING_ITERATOR_HPP
