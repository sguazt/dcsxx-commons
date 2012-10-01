/**
 * \file dcs/algorithm/order.hpp
 *
 * \brief Computed the permutation of indices which makes the given range
 *  ordered.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2009-2012  Marco Guazzone
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

#ifndef DCS_ALGORITHM_ORDER_HPP
#define DCS_ALGORITHM_ORDER_HPP


#include <algorithm>


namespace dcs { namespace algorithm {

namespace detail {

/// Auxiliary comparator used for comparing elements of input sequence during
/// the ordering of indices.
template <typename RandomAccessIteratorT>
struct index_less_than
{
	index_less_than(RandomAccessIteratorT first)
	: first_(first)
	{
	}

	bool operator()(const size_t a, const size_t b) const
	{
		return *(first_+a) < *(first_+b);
	}

	RandomAccessIteratorT first_;
};


/// Auxiliary comparator used for comparing elements of input sequence during
/// the ordering of indices; elements are compared according to the given
/// comparator functor.
template <typename RandomAccessIteratorT, typename ComparatorT>
struct index_less_than_cmp
{
	index_less_than_cmp(RandomAccessIteratorT first, ComparatorT comp)
	: first_(first),
	  comp_(comp)
	{
	}

	bool operator()(const size_t a, const size_t b) const
	{
		return comp_(*(first_+a), *(first_+b));
	}

	RandomAccessIteratorT first_;
	ComparatorT comp_;
};

} // Namespace detail


/**
 * \brief Computed the permutation of indices which makes the given range
 *  ordered.
 * \tparam RandomAccessIteratorT The type of the iterator to the input sequence.
 * \tparam ForwardIteratorT The type of the iterator to the resulting sequence
 *  of indices.
 * \param first The iterator to the beginning of the input sequence.
 * \param last The iterator to the end of the input sequence.
 * \param result The iterator to the beginning of the resulting sequence of
 *  indices.
 *
 * The input sequence is ordered according to the standard operator \c &lt;.
 */
template <typename RandomAccessIteratorT, typename ForwardIteratorT>
void order(RandomAccessIteratorT first, RandomAccessIteratorT last, ForwardIteratorT result)
{
	ForwardIteratorT result_begin = result;
	for (
		RandomAccessIteratorT it = first;
		it != last;
		++it
	) {
		*result = it-first;
		++result;
	}
	
	::std::sort(
		result_begin,
		result,
		detail::index_less_than<RandomAccessIteratorT&>(first)
	);
}


/**
 * \brief Computed the permutation of indices which makes the given range
 *  ordered.
 * \tparam RandomAccessIteratorT The type of the iterator to the input sequence.
 * \tparam ForwardIteratorT The type of the iterator to the resulting sequence
 *  of indices.
 * \tparam ComparatorT The comparator functor.
 * \param first The iterator to the beginning of the input sequence.
 * \param last The iterator to the end of the input sequence.
 * \param result The iterator to the beginning of the resulting sequence of
 *  indices.
 * \param comp An instance of the comparator functor used for ordering the input
 *  sequence.
 *
 * The input sequence is ordered according to the given comparator functor.
 */
template <typename RandomAccessIteratorT, typename ForwardIteratorT, typename ComparatorT>
void order(RandomAccessIteratorT first, RandomAccessIteratorT last, ForwardIteratorT result, ComparatorT comp)
{
	ForwardIteratorT result_begin = result;
	for (
		RandomAccessIteratorT it = first;
		it != last;
		++it
	) {
		*result = it-first;
		++result;
	}
	
	::std::sort(
		result_begin,
		result,
		detail::index_less_than_cmp<RandomAccessIteratorT&, ComparatorT&>(first, comp)
	);
}

}} // Namespace dcs::algorithm


#endif // DCS_ALGORITHM_ORDER_HPP
