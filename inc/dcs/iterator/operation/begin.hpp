/**
 * \file dcs/iterator/operation/begin.hpp
 *
 * \brief Return the iterator to the beginning of a range.
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

#ifndef DCS_ITERATOR_OPERATION_BEGIN_HPP
#define DCS_ITERATOR_OPERATION_BEGIN_HPP


#include <boost/range/begin.hpp>


namespace dcs { namespace iterator {

using ::boost::begin;

}} // Namespace dcs::iterator


#endif // DCS_ITERATOR_OPERATION_BEGIN_HPP
