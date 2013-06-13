/**
 * \file dcs/math/type/io.hpp
 *
 * \brief I/O facilities for math types.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_MATH_TYPE_IO_HPP
#define DCS_MATH_TYPE_IO_HPP


#include <dcs/math/type/matrix.hpp>
#include <dcs/math/type/vector.hpp>
#include <iostream>


namespace dcs { namespace math {

template <typename CharT,
          typename CharTraitsT,
          typename RealT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, ::dcs::math::matrix<RealT> const& m)
{
	typedef typename ::dcs::math::matrix<RealT>::size_type size_type;

	const size_type nr(m.num_rows());
	const size_type nc(m.num_columns());

	os << "(" << nr << "," << nc << ")[";
	for (size_type r = 0; r < nr; ++r)
	{
		if (r > 0)
		{
			os << "; ";
		}
		for (size_type c = 0; c < nc; ++c)
		{
			if (c > 0)
			{
				os << " ";
			}
			os << m(r,c);
		}
	}
	os << "]";

	return os;
}

template <typename CharT,
          typename CharTraitsT,
          typename RealT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, ::dcs::math::vector<RealT> const& v)
{
	typedef typename ::dcs::math::vector<RealT>::size_type size_type;

	const size_type n(v.length());

	os << "(" << n << ")[";
	for (size_type i = 0; i < n; ++i)
	{
		if (i > 0)
		{
			os << "; ";
		}
		os << v(i);
	}
	os << "]";

	return os;
}

}} // Namespace dcs::math


#endif // DCS_MATH_TYPE_IO_HPP
