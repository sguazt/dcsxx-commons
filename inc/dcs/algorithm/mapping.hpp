/**
 * \file dcs/algorithm/mapping.hpp
 *
 * \brief Algorithms for mappings.
 *
 * Also see:
 * -# <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2639.pdf">N2639</a>
 * -# <a href="http://home.roadrunner.com/~hinnant/combinations.html">Combinations and Permutations</a>
 * .
 *
 * \author Howard Hinnant (howard.hinnant@gmail.com)
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 *  (C) Copyright Howard Hinnant 2005-2011.
 *      [http://home.roadrunner.com/~hinnant/combinations.html]
 *  Use, modification and distribution are subject to the Boost Software License,
 *  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt).
 *
 *  See http://www.boost.org/libs/type_traits for most recent version including
 *  documentation.
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons.
 *
 * dcsxx-commons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcsxx-commons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcsxx-commons.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_ALGORITHM_MAPPING_HPP
#define DCS_ALGORITHM_MAPPING_HPP


#include <dcs/algorithm/detail/combperm.hpp>


namespace dcs { namespace algorithm {

template <typename BidirectionalIterator, typename T>
inline
bool next_mapping(BidirectionalIterator first,
				  BidirectionalIterator last,
				  T first_value,
				  T last_value)
{
	return detail::next_mapping(first, last, first_value, last_value, detail::default_incrementor<T>());
}

template <typename BidirectionalIterator, typename T, typename Incrementor>
inline
bool next_mapping(BidirectionalIterator first,
				  BidirectionalIterator last,
				  T first_value,
				  T last_value,
				  Incrementor increment)
{
	return detail::next_mapping(first, last, first_value, last_value, increment);
}

template <typename BidirectionalIterator, typename T>
inline
bool prev_mapping(BidirectionalIterator first,
				  BidirectionalIterator last,
				  T first_value,
				  T last_value)
{
	return detail::prev_mapping(first, last, first_value, last_value, detail::default_decrementor<T>());
}

template <typename BidirectionalIterator, typename T, typename Decrementor>
inline
bool prev_mapping(BidirectionalIterator first,
				  BidirectionalIterator last,
				  T first_value,
				  T last_value,
				  Decrementor decrement)
{
	return detail::prev_mapping(first, last, first_value, last_value, decrement);
}

}} // Namespace dcs::algorithm


#endif // DCS_ALGORITHM_MAPPING_HPP
