/**
 * \file dcs/string/algorithm/to_lower.hpp
 *
 * \brief Case-lowering string algorithm.
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

#ifndef DCS_STRING_ALGORITHM_TO_LOWER_HPP
#define DCS_STRING_ALGORITHM_TO_LOWER_HPP


#include <boost/algorithm/string/case_conv.hpp>


namespace dcs { namespace string {

using ::boost::algorithm::to_lower;
using ::boost::algorithm::to_lower_copy;

}} // Namespace dcs::string


#endif // DCS_STRING_ALGORITHM_TO_LOWER_HPP
