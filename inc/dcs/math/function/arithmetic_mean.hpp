/**
 * \file dcs/math/arithmetic_mean.hpp
 *
 * \brief Compute the arithmetic mean of the given sequence.
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

#ifndef DCS_MATH_FUNCTION_ARITHMETIC_MEAN_HPP
#define DCS_MATH_FUNCTION_ARITHMETIC_MEAN_HPP


#include <cstddef>


namespace dcs { namespace math {

template <typename T, typename ForwardIteratorT>
T arithmetic_mean(ForwardIteratorT first, ForwardIteratorT last)
{
	T sum(0);
	::std::size_t n(0);

	while (first != last)
	{
		sum += *first;
		++first;
		++n;
	}

	return sum/n;
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_ARITHMETIC_MEAN_HPP
