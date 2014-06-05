/**
 * \file dcs/math/type/io.hpp
 *
 * \brief I/O facilities for math types.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2013 Marco Guazzone (marco.guazzone@gmail.com)
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
