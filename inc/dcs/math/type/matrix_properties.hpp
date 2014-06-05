/**
 * \file dcs/math/type/matrix_properties.hpp
 *
 * \brief Properties for matrix containers.
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

#ifndef DCS_MATH_TYPE_MATRIX_PROPERTIES_HPP
#define DCS_MATH_TYPE_MATRIX_PROPERTIES_HPP

namespace dcs { namespace math {

// Storage layouts

/// Column-major data order
struct column_major_storage_layout { };

/// Row-major data order
struct row_major_storage_layout { };


/// Properties for matrix containers
template <typename StorageLayoutT = row_major_storage_layout>
struct matrix_properties
{
	typedef StorageLayoutT storage_layout;
}; // matrix_properties

typedef matrix_properties<> default_matrix_properties;

}} // Namespace dcs::math

#endif // DCS_MATH_TYPE_MATRIX_PROPERTIES_HPP
