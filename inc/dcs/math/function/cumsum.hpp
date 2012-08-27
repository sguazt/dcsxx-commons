/**
 * \file dcs/math/cumsum.hpp
 *
 * \brief Compute the cumulative sum of the given sequence.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_MATH_FUNCTION_CUMSUM_HPP
#define DCS_MATH_FUNCTION_CUMSUM_HPP


namespace dcs { namespace math {

template <typename T, typename ForwardIterator1T, typename ForwardIterator2T>
void cumsum(ForwardIterator1T first, ForwardIterator1T last, ForwardIterator2T result)
{
	T sum(0);

	while (first != last)
	{
		sum += *first;
		*result = sum;
		++first;
		++result;
	}
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_CUMSUM_HPP
