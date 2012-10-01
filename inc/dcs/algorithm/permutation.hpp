/**
 * \file dcs/algorithm/permutation.hpp
 *
 * \brief Algorithms for permutations.
 *
 * A permutation of size r of a range of size n is a (not necessarily) sorted
 * subsequence of size r of the total range, i.e., a subsequence of elements at
 * r positions among the n positions in the range.
 *
 * A permutation is without repetition if the r indices in the respective
 * definition are distinct (and necessarily r <= n), and with repetition otherwise.
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

#ifndef DCS_ALGORITHM_PERMUTATION_HPP
#define DCS_ALGORITHM_PERMUTATION_HPP


#include <algorithm>
#include <cstddef>
#include <dcs/algorithm/detail/combperm.hpp>
#include <dcs/detail/macro_cx11.hpp>
#include <stdexcept>
#include <iterator>
#include <limits>


namespace dcs { namespace algorithm {

// For each of the permutation algorithms, use for_each_combination (or
//    combine_discontinuous) to handle the "r out of N" part of the algorithm.
//    Thus each permutation algorithm has to deal only with an "N out of N"
//    problem.  I.e. For each combination of r out of N items, permute it thusly.
template <typename BidirIter, typename Function>
Function for_each_permutation(BidirIter first,
							  BidirIter mid,
                     		  BidirIter last,
							  Function f)
{
    typedef typename ::std::iterator_traits<BidirIter>::difference_type D;
    typedef detail::bound_range<Function&, BidirIter> Wf;
    typedef detail::call_permute<Wf, BidirIter> PF;
    Wf wfunc(f, first, mid);
    D d1 = ::std::distance(first, mid);
    PF pf(wfunc, first, mid, d1);
    detail::combine_discontinuous(first,
								  mid,
								  d1,
                                  mid,
								  last,
								  ::std::distance(mid, last),
                                  pf);

    return DCS_DETAIL_MACRO_CX11_STD_MOVE_(f);
}

template <typename UIntT>
UIntT count_each_permutation(UIntT d1, UIntT d2)
{
    // return (d1+d2)!/d2!
    if (d1 > ::std::numeric_limits<UIntT>::max() - d2)
	{
        throw ::std::overflow_error("overflow in count_each_permutation");
	}
    UIntT n = d1 + d2;
    UIntT r = 1;
    for (; n > d2; --n)
    {
        if (r > ::std::numeric_limits<UIntT>::max() / n)
		{
            throw ::std::overflow_error("overflow in count_each_permutation");
		}
        r *= n;
    }

    return r;
}

template <typename BidirIter>
inline
::std::size_t count_each_permutation(BidirIter first,
									 BidirIter mid,
									 BidirIter last)
{
    return count_each_permutation< ::std::size_t >(::std::distance(first, mid),
												   ::std::distance(mid, last));
}

template <typename BidirIter, typename Function>
inline
Function for_each_circular_permutation(BidirIter first,
                              		   BidirIter mid,
                              		   BidirIter last,
									   Function f)
{
    for_each_combination(first,
						 mid,
						 last,
						 detail::circular_permutation<Function&, BidirIter>(f,
																			::std::distance(first, mid)));

    return DCS_DETAIL_MACRO_CX11_STD_MOVE_(f);
}    

template <typename UIntT>
UIntT count_each_circular_permutation(UIntT d1, UIntT d2)
{
    // return d1 > 0 ? (d1+d2)!/(d1*d2!) : 1
    if (d1 == 0)
	{
        return 1;
	}
    UIntT r;
    if (d1 <= d2)
    {
        try
        {
            r = count_each_combination(d1, d2);
        }
        catch (const ::std::overflow_error&)
        {
            throw ::std::overflow_error("overflow in count_each_circular_permutation");
        }
        for (--d1; d1 > 1; --d1)
        {
            if (r > ::std::numeric_limits<UIntT>::max()/d1)
			{
                throw ::std::overflow_error("overflow in count_each_circular_permutation");
			}
            r *= d1;
        }
    }
    else
    {   // functionally equivalent but faster algorithm
        if (d1 > ::std::numeric_limits<UIntT>::max() - d2)
            throw ::std::overflow_error("overflow in count_each_circular_permutation");
        UIntT n = d1 + d2;
        r = 1;
        for (; n > d1; --n)
        {
            if (r > ::std::numeric_limits<UIntT>::max()/n)
			{
                throw ::std::overflow_error("overflow in count_each_circular_permutation");
			}
            r *= n;
        }
        for (--n; n > d2; --n)
        {
            if (r > ::std::numeric_limits<UIntT>::max()/n)
			{
                throw ::std::overflow_error("overflow in count_each_circular_permutation");
			}
            r *= n;
        }
    }

    return r;
}

template <typename BidirIter>
inline
::std::size_t count_each_circular_permutation(BidirIter first,
											  BidirIter mid,
											  BidirIter last)
{
    return count_each_circular_permutation< ::std::size_t >(::std::distance(first, mid),
															::std::distance(mid, last));
}

template <typename BidirIter, typename Function>
inline
Function for_each_reversible_permutation(BidirIter first,
                                		 BidirIter mid,
                                		 BidirIter last,
										 Function f)
{
    typedef typename ::std::iterator_traits<BidirIter>::difference_type D;
    for_each_combination(first,
						 mid,
						 last,
                  		 detail::reversible_permutation<Function&, D>(f,
																	  ::std::distance(first, mid)));

    return DCS_DETAIL_MACRO_CX11_STD_MOVE_(f);
}    

template <typename UIntT>
UIntT count_each_reversible_permutation(UIntT d1, UIntT d2)
{
    // return d1 > 1 ? (d1+d2)!/(2*d2!) : (d1+d2)!/d2!
    if (d1 > ::std::numeric_limits<UIntT>::max() - d2)
	{
        throw ::std::overflow_error("overflow in count_each_reversible_permutation");
	}
    UIntT n = d1 + d2;
    UIntT r = 1;
    if (d1 > 1)
    {
        r = n;
        if ((n & 1) == 0)
		{
            r /= 2;
		}
        --n;
        UIntT t = n;
        if ((t & 1) == 0)
		{
            t /= 2;
		}
        if (r > ::std::numeric_limits<UIntT>::max() / t)
		{
            throw ::std::overflow_error("overflow in count_each_reversible_permutation");
		}
        r *= t;
        --n;
    }
    for (; n > d2; --n)
    {
        if (r > ::std::numeric_limits<UIntT>::max() / n)
		{
            throw ::std::overflow_error("overflow in count_each_reversible_permutation");
		}
        r *= n;
    }
    return r;
}

template <typename BidirIter>
inline
::std::size_t count_each_reversible_permutation(BidirIter first,
												BidirIter mid,
												BidirIter last)
{
    return count_each_reversible_permutation< ::std::size_t >(::std::distance(first, mid),
															  ::std::distance(mid, last));
}

template <typename BidirIter, typename Function>
inline
Function for_each_reversible_circular_permutation(BidirIter first,
												  BidirIter mid,
												  BidirIter last,
												  Function f)
{
    for_each_combination(first,
						 mid,
						 last,
						 detail::reverse_circular_permutation<Function&, BidirIter>(f,
																					::std::distance(first, mid)));

    return DCS_DETAIL_MACRO_CX11_STD_MOVE_(f);
}    

template <typename UIntT>
UIntT count_each_reversible_circular_permutation(UIntT d1, UIntT d2)
{
    // return d1 == 0 ? 1 : d1 <= 2 ? (d1+d2)!/(d1*d2!) : (d1+d2)!/(2*d1*d2!)
    UIntT r;
    try
    {
        r = count_each_combination(d1, d2);
    }
    catch (const ::std::overflow_error&)
    {
        throw ::std::overflow_error("overflow in count_each_reversible_circular_permutation");
    }
    if (d1 > 3)
    {
        for (--d1; d1 > 2; --d1)
        {
            if (r > ::std::numeric_limits<UIntT>::max()/d1)
			{
                throw ::std::overflow_error("overflow in count_each_reversible_circular_permutation");
			}
            r *= d1;
        }
    }
    return r;
}

template <typename BidirIter>
inline
::std::size_t count_each_reversible_circular_permutation(BidirIter first,
														 BidirIter mid,
														 BidirIter last)
{
    return count_each_reversible_circular_permutation< ::std::size_t >(::std::distance(first, mid),
																	   ::std::distance(mid, last));
}

}} // Namespace dcs::algorithm


#endif // DCS_ALGORITHM_PERMUTATION_HPP
