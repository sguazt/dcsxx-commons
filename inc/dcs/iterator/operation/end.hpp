/**
 * \file dcs/iterator/operation/end.hpp
 *
 * \brief Return the iterator to the end of a range.
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

#ifndef DCS_ITERATOR_OPERATION_END_HPP
#define DCS_ITERATOR_OPERATION_END_HPP


#include <boost/range/end.hpp>


namespace dcs { namespace iterator {

using ::boost::end;

}} // Namespace dcs::iterator


#endif // DCS_ITERATOR_OPERATION_END_HPP
