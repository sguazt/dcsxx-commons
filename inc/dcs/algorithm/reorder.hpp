/**
 * \file dcs/algorithm/reorder.hpp
 *
 * \brief Reorder a given sequence according to a permutation of indices.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone
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

#ifndef DCS_ALGORITHM_REORDER_HPP
#define DCS_ALGORITHM_REORDER_HPP


#include <algorithm>
#include <dcs/debug.hpp>
#include <iterator>
#include <vector>


namespace dcs { namespace algorithm {

/**
 * \brief Applies the permutation of indices to the given sequence.
 */
template <typename IdxFwdIterT, typename InFwdIterT, typename OutFwdIterT>
void reorder_copy(IdxFwdIterT idx_first, IdxFwdIterT idx_last, InFwdIterT in_first, OutFwdIterT out_first)
{
	while (idx_first != idx_last)
	{
		InFwdIterT in_it(in_first);
		::std::advance(in_it, *idx_first);
		*out_first = *in_it;
		++idx_first;
		++out_first;
	}
}

template <typename IdxFwdIterT, typename InFwdIterT>
void reorder(IdxFwdIterT idx_first, IdxFwdIterT idx_last, InFwdIterT in_first)
{
	typedef typename ::std::iterator_traits<InFwdIterT>::value_type value_type;

	InFwdIterT in_last(in_first);
	::std::advance(in_last, ::std::distance(idx_first, idx_last));
	::std::vector<value_type> tmp(in_first, in_last);
	::std::size_t i(0);
	while (idx_first != idx_last)
	{
		*in_first = tmp[*idx_first];

		++idx_first;
		++in_first;
		++i;
	}
}

}} // Namespace dcs::algorithm


#endif // DCS_ALGORITHM_REORDER_HPP
