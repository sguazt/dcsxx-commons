/**
 * \file dcs/test/math/type/base_array.hpp
 *
 * \brief Base class for numerical arrays.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2012 Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_MATH_TYPE_BASE_ARRAY_HPP
#define DCS_MATH_TYPE_BASE_ARRAY_HPP

namespace dcs { namespace math {

template <typename ValueT>
class base_array
{
	public: virtual ~base_array()
	{
	}
}; // base_array

}} // Namespace dcs::math

#endif // DCS_MATH_TYPE_BASE_ARRAY_HPP
