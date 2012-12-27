/**
 * \file dcs/math/type/detail/storage.hpp
 *
 * \brief Helper classes for storage management.
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

#ifndef DCS_MATH_TYPE_DETAIL_STORAGE_HPP
#define DCS_MATH_TYPE_DETAIL_STORAGE_HPP


#include <dcs/math/type/matrix_properties.hpp>


namespace dcs { namespace math { namespace detail {

template <typename LT>
struct matrix_storage_helper;

template <>
struct matrix_storage_helper< column_major_storage_layout >
{
	template <typename S>
	static S linearize(S nr, S /*nc*/, S r, S c)
	{
		return r+c*nr;
	}

	template <typename S>
	static S leading_dimension(S nr, S /*nc*/)
	{
		return nr;
	}

	template <typename V, typename S>
	static V& at(V* data, S nr, S nc, S r, S c)
	{
		return data[linearize(nr, nc, r, c)];
	}

	template <typename V, typename S>
	static V const& at(V const* data, S nr, S nc, S r, S c)
	{
		return data[linearize(nr, nc, r, c)];
	}

	template <typename V, typename S>
	static void copy(V const* in_data, S in_nr, S in_nc, V* out_data, S out_nr, S out_nc, S nr, S nc)
	{
		for (S r = 0; r < nr; ++r)
		{
			for (S c = 0; c < nc; ++c)
			{
				const S in_idx(linearize(in_nr, in_nc, r, c));
				const S out_idx(linearize(out_nr, out_nc, r, c));

				out_data[out_idx] = in_data[in_idx];
			}
		}
	}
}; // matrix_storage_helper< row_major_storage_layout >

template <>
struct matrix_storage_helper< row_major_storage_layout >
{
	template <typename S>
	static S linearize(S /*nr*/, S nc, S r, S c)
	{
		return c+r*nc;
	}

	template <typename S>
	static S leading_dimension(S /*nr*/, S nc)
	{
		return nc;
	}

	template <typename V, typename S>
	static V& at(V* data, S nr, S nc, S r, S c)
	{
		return data[linearize(nr, nc, r, c)];
	}

	template <typename V, typename S>
	static V const& at(V const* data, S nr, S nc, S r, S c)
	{
		return data[linearize(nr, nc, r, c)];
	}

	template <typename V, typename S>
	static void copy(V const* in_data, S in_nr, S in_nc, V* out_data, S out_nr, S out_nc, S nr, S nc)
	{
		for (S r = 0; r < nr; ++r)
		{
			for (S c = 0; c < nc; ++c)
			{
				const S in_idx(linearize(in_nr, in_nc, r, c));
				const S out_idx(linearize(out_nr, out_nc, r, c));

				out_data[out_idx] = in_data[in_idx];
			}
		}
	}
}; // matrix_storage_helper< row_major_storage_layout >

}}} // Namespace dcs::math::detail

#endif // DCS_MATH_TYPE_DETAIL_STORAGE_HPP
