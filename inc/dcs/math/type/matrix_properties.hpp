/**
 * \file dcs/math/type/matrix_properties.hpp
 *
 * \brief Properties for matrix containers.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone (marco.guazzone@gmail.com)
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons (below referred to as "this program").
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
