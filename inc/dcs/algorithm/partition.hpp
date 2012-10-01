/**
 * \file dcs/algorithm/lexicographic_partition.hpp
 *
 * \brief Generate a set partition in lexicographic order.
 *
 * This code is mainly based on [1,2].
 *
 * References:
 * -# M. Orlov.
 *    "Efficient Generation of Set Partitions"
 *    2002.
 * -# D. Knuth.
 *    "The Art of Computer Programming, Volume 4, Fascicle 3",
 *    Addison-Wesley, 2004.
 * .
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 * \author Michael Orlov (orlovm@cs.bgu.ac.il)
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

#ifndef DCS_COMMONS_ALGORITHM_PARTITION_HPP
#define DCS_COMMONS_ALGORITHM_PARTITION_HPP

#include <algorithm>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>


namespace dcs { namespace algorithm {

template <typename ValueT>
struct partition_traits
{
	typedef ValueT value_type;
	typedef ::std::vector<value_type> element_container;
	typedef typename element_container::iterator element_iterator;
	typedef typename element_container::const_iterator element_const_iterator;
	typedef ::std::vector<element_container> subset_container;
	typedef typename subset_container::iterator subset_iterator;
	typedef typename subset_container::const_iterator subset_const_iterator;
};

class lexicographic_partition
{
	protected: typedef ::std::vector< ::std::size_t > restricted_growth_string_type;
	protected: typedef restricted_growth_string_type const& reference;
	protected: typedef restricted_growth_string_type const* pointer;
	public: typedef lexicographic_partition self_type;
	public: typedef typename restricted_growth_string_type::iterator iterator;
	public: typedef typename restricted_growth_string_type::const_iterator const_iterator;


	public: explicit lexicographic_partition(::std::size_t n, bool first = true)
	: n_(n),
	  kappa_(n),
	  M_(n),
	  has_prev_(true),
	  has_next_(true)
	{
		DCS_ASSERT(n_ > 0,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Number of elements must be positive"));

		if (!first)
		{
			for (::std::size_t i = 1; i < n_; ++i)
			{
				kappa_[i] = i;
				M_[i] = i;
			}
		}

		DCS_DEBUG_DO( this->integrity_check() );
	}

	public: ::std::size_t num_elements() const
	{
		return n_;
	}

	public: ::std::size_t num_subsets() const
	{
		return M_[n_-1]+1;
	}

	public: self_type& operator++()
	{
		DCS_ASSERT(has_next_,
				   DCS_EXCEPTION_THROW(::std::overflow_error,
									   "No following partitions"));

		for (::std::size_t i = n_-1; i > 0; --i)
		{
			if (kappa_[i] <= M_[i-1])
			{
				++kappa_[i];

				const ::std::size_t new_max = ::std::max(M_[i], kappa_[i]);
				M_[i] = new_max;
				for (::std::size_t j = i + 1; j < n_; ++j)
				{
					kappa_[j] = 0;
					M_[j] = new_max;
				}

				DCS_DEBUG_DO( integrity_check() );

				// Since we are able to go forward by 1 step, surely, after
				// this, we will also be able to go backward by 1 step
				has_prev_ = true;

				break;
			}
		}

		// Check if #subsets == #elements, that is if we are in the case:
		//   ((x1),(x2),...,(xn))
		// NOTE: This works since this class builds partition in lexicographic order
		has_next_ = (M_[n_-1]+1) < n_;

		return *this;
	}

	public: bool has_next() const
	{
		return has_next_;
	}

	public: self_type& operator--()
	{
		DCS_ASSERT(has_prev_,
				   DCS_EXCEPTION_THROW(::std::underflow_error,
									   "No preceding partitions"));

		for (::std::size_t i = n_-1; i > 0; --i)
		{
			if (kappa_[i] > 0)
			{
				--kappa_[i];

				const ::std::size_t m_i = M_[i-1];
				M_[i] = m_i;
				for (::std::size_t j = i + 1; j < n_; ++j)
				{
					const ::std::size_t new_max = m_i + j - i;
					kappa_[j] = new_max;
					M_[j] = new_max;
				}

				DCS_DEBUG_DO( integrity_check() );

				// Since we are able to go backward by 1 step, surely, after
				// this, we will also be able to go forward by 1 step
				has_next_ = true;

				break;
			}
		}

		// Check if #subsets == 1, that is if we are in the case:
		//   ((x1,x2,...,xn)
		// NOTE: This works since this class builds partition in lexicographic order
		has_prev_ = (M_[n_-1]+1) > 1;

		return *this;
	}

	public: bool has_prev() const
	{
		return has_prev_;
	}

	public: template <typename ElemT>
			typename partition_traits<ElemT>::subset_container operator()(::std::vector<ElemT> const& v) const
	{
		typename partition_traits<ElemT>::subset_container subs(this->num_subsets());

		DCS_ASSERT(v.size() == n_,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Size does not match"));

		for (::std::size_t i = 0; i < n_; ++i)
		{
			subs[kappa_[i]].push_back(v[i]);
		}

		return subs;
	}

	public: template <typename IterT>
			typename partition_traits< typename ::std::iterator_traits<IterT>::value_type >::subset_container operator()(IterT first, IterT last) const
	{
		return this->operator()(::std::vector< typename ::std::iterator_traits<IterT>::value_type >(first, last));
	}

	public: iterator begin()
	{
		return kappa_.begin();
	}

	public: iterator end()
	{
		return kappa_.end();
	}

	public: const_iterator begin() const
	{
		return kappa_.begin();
	}

	public: const_iterator end() const
	{
		return kappa_.end();
	}

	protected: reference operator*() const
	{
		return kappa_;
	}

	protected: pointer operator->() const
	{
		return &kappa_;
	}

	protected: void integrity_check() const
	{
		::std::size_t max = kappa_[0];

		for (::std::size_t i = 0; i < n_; ++i)
		{
			max = ::std::max(max,kappa_[i]);

			if (max != M_[i])
			{
				DCS_EXCEPTION_THROW(::std::domain_error, "Integrity check failed");
			}
		}
	}


	private: ::std::size_t n_;
	private: restricted_growth_string_type kappa_;
	private: restricted_growth_string_type M_;
	private: bool has_prev_;
	private: bool has_next_;
}; // lexicographic_partition

template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os,
													lexicographic_partition const& part)
{
	os << '(';

	if (part.num_elements() > 1)
	{
		::std::copy(part.begin(),
					part.end()-1,
					::std::ostream_iterator< ::std::size_t >(os, " "));
	}

	os << *(part.end()-1) << ')';

	return os;
}

template <typename BidiIterT, typename PartitionT>
inline
typename partition_traits< typename ::std::iterator_traits<BidiIterT>::value_type >::subset_container
next_partition(BidiIterT first,
			   BidiIterT last,
			   PartitionT& part)
{
	typedef typename ::std::iterator_traits<BidiIterT>::value_type value_type;
	typedef typename partition_traits<value_type>::subset_container subset_container;

	subset_container subs = part(first, last);

	if (part.has_next())
	{
		++part;
	}

	return subs;
}

template <typename BidiIterT, typename PartitionT>
inline
typename partition_traits< typename ::std::iterator_traits<BidiIterT>::value_type >::subset_container
prev_partition(BidiIterT first,
			   BidiIterT last,
			   PartitionT& part)
{
	typedef typename ::std::iterator_traits<BidiIterT>::value_type value_type;
	typedef typename partition_traits<value_type>::subset_container subset_container;

	subset_container subs = part(first, last);

	if (part.has_prev())
	{
		--part;
	}

	return subs;
}

}} // Namespace dcs::algorithm

#endif // DCS_COMMONS_ALGORITHM_PARTITION_HPP
