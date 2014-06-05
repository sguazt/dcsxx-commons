/**
 * \file dcs/math/type/detail/storage.hpp
 *
 * \brief Helper classes for storage management.
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
