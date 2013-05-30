/**
 * \file dcs/algorithm/subset.hpp
 *
 * \brief Generate the power set of a set in lexicographic order.
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

#ifndef DCS_COMMONS_ALGORITHM_SUBSET_HPP
#define DCS_COMMONS_ALGORITHM_SUBSET_HPP

#include <algorithm>
#include <boost/dynamic_bitset.hpp>
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
struct subset_traits
{
	typedef ValueT value_type;
	typedef ::std::vector<value_type> subset_container;
	typedef typename subset_container::iterator subset_iterator;
	typedef typename subset_container::const_iterator subset_const_iterator;
};

class lexicographic_subset
{
	public: class const_iterator;


	friend class const_iterator;


	private: typedef lexicographic_subset self_type;
	private: typedef ::boost::dynamic_bitset<> impl_type;
	private: typedef typename impl_type::size_type size_type;
	private: typedef unsigned long word_type;


	public: explicit lexicographic_subset(::std::size_t n, bool empty_set=true)
	: n_(n),
	  empty_set_(empty_set),
	  bits_(n, empty_set ? 0 : 1),
	  has_prev_(true),
	  has_next_(true)
	{
		DCS_ASSERT(n_ > 0,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Number of elements must be positive"));
	}

	public: ::std::size_t max_size() const
	{
		return n_;
	}

	public: ::std::size_t size() const
	{
		return bits_.count();
	}

	public: self_type& operator++()
	{
		DCS_ASSERT(has_next_,
				   DCS_EXCEPTION_THROW(::std::overflow_error,
									   "No following subsets"));

		has_next_ = bits_.count() < n_;

		if (has_next_)
		{
			bits_ = impl_type(n_, bits_.to_ulong()+1);
		}

		has_prev_ = bits_.to_ulong() > (empty_set_ ? 0 : 1);

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
									   "No preceding subsets"));

		has_prev_ = bits_.to_ulong() > (empty_set_ ? 0 : 1);

		if (has_prev_)
		{
			bits_ = impl_type(n_, bits_.to_ulong()-1);
		}

		has_next_ = bits_.to_ulong() < n_;

		return *this;
	}

	public: bool has_prev() const
	{
		return has_prev_;
	}

	//public: template <typename ElemT, typename IterT>
	public: template <typename ElemT>
			typename subset_traits<ElemT>::subset_container operator()(::std::vector<ElemT> const& v) const
	{
		DCS_ASSERT(v.size() == n_,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Size does not match"));

		typename subset_traits<ElemT>::subset_container subset;

		for (size_type pos = bits_.find_first();
			 pos != impl_type::npos;
			 pos = bits_.find_next(pos))
		{
			subset.push_back(v[pos]);
		}

		return subset;
	}

	public: template <typename IterT>
			typename subset_traits< typename ::std::iterator_traits<IterT>::value_type >::subset_container operator()(IterT first, IterT last) const
	{
			return this->operator()(::std::vector<typename ::std::iterator_traits<IterT>::value_type>(first, last));
	}

	public: const_iterator begin() const
	{
		return const_iterator(this, bits_.any() ? bits_.find_first() : impl_type::npos);
	}

	public: const_iterator end() const
	{
		return const_iterator(this, impl_type::npos);
	}


	public: class const_iterator: public ::std::iterator< ::std::bidirectional_iterator_tag,
														 typename lexicographic_subset::impl_type::size_type const>
	{
		private: typedef ::std::iterator< ::std::bidirectional_iterator_tag,
										  typename lexicographic_subset::impl_type::size_type const> base_type;
		private: typedef lexicographic_subset container_type;
		private: typedef typename container_type::impl_type bitset_type;
		private: typedef typename container_type::size_type size_type;
		public: typedef typename base_type::value_type value_type;
		public: typedef typename base_type::difference_type difference_type;
		public: typedef typename base_type::pointer pointer;
		public: typedef typename base_type::reference reference;
		public: typedef typename base_type::iterator_category iterator_category;


		public: const_iterator(container_type const* p_subset, size_type pos)
		: p_sub_(p_subset),
		  pos_(pos)
		{
		}

		public: reference operator*() const
		{
			return pos_;
		}

		public: pointer operator->() const
		{
			return &(operator*());
		}

		public: const_iterator& operator++()
		{
			pos_ = p_sub_->bits_.find_next(pos_);

			return *this;
		}

		public: const_iterator& operator++(int)
		{
			const_iterator tmp = *this;

			operator++();

			return tmp;
		}

		public: const_iterator& operator--()
		{
			size_type pos = bitset_type::npos;
			for (size_type pos2 = p_sub_->bits_.find_first();
				 pos2 != pos_;
				 pos2 = p_sub_->bits_.find_next(pos2))
			{
				pos = pos2;
			}

			pos_ = pos;

			return *this;
		}

		public: const_iterator& operator--(int)
		{
			const_iterator tmp = *this;

			operator--();

			return tmp;
		}

		public: const_iterator operator+(difference_type n) const
		{
			const_iterator it = *this;

			if (n > 0)
			{
				while (n--)
				{
					++it;
				}
			}
			else
			{
				while (n++)
				{
					--it;
				}
			}

			return it;
		}

		public: const_iterator operator-(difference_type n) const
		{
			return operator+(-n);
		}

		public: const_iterator& operator+=(difference_type n)
		{
			if (n > 0)
			{
				while (n--)
				{
					operator++();
				}
			}
			else
			{
				while (n++)
				{
					operator--();
				}
			}

			return *this;
		}

		public: const_iterator& operator-=(difference_type n)
		{
			return operator+=(-n);
		}

		friend
		bool operator==(const_iterator const& lhs, const_iterator const& rhs)
		{
			return lhs.p_sub_ == rhs.p_sub_ && lhs.pos_ == rhs.pos_;
		}

		friend
		bool operator!=(const_iterator const& lhs, const_iterator const& rhs)
		{
			return !(lhs == rhs);
		}


		private: container_type const* p_sub_;
		private: size_type pos_;
	}; // const_iterator


	private: ::std::size_t n_; ///< The max number of elements
	private: bool empty_set_; ///< Flag to enable or disable the inclusion of the empty set
	private: impl_type bits_; ///< The subset implementation
	private: bool has_prev_;
	private: bool has_next_;
}; // lexicographic_subset


template <typename CharT, typename CharTraitsT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os,
													lexicographic_subset const& subset)
{
	os << '(';

	if (subset.size() > 0)
	{
		if (subset.size() > 1)
		{
			::std::copy(subset.begin(),
						subset.end()-1,
						::std::ostream_iterator< ::std::size_t >(os, " "));
		}

		os << *(subset.end()-1);
	}

	os << ')';

	return os;
}

template <typename BidiIterT, typename SubsetT>
inline
typename subset_traits< typename ::std::iterator_traits<BidiIterT>::value_type >::subset_container
next_subset(BidiIterT first,
			BidiIterT last,
			SubsetT& subset)
{
	typedef typename ::std::iterator_traits<BidiIterT>::value_type value_type;
	typedef typename subset_traits<value_type>::subset_container subset_container;

	subset_container subs = subset(first, last);

	++subset;

	return subs;
}

template <typename BidiIterT, typename SubsetT>
inline
typename subset_traits< typename ::std::iterator_traits<BidiIterT>::value_type >::subset_container
prev_subset(BidiIterT first,
			BidiIterT last,
			SubsetT& subset)
{
	typedef typename ::std::iterator_traits<BidiIterT>::value_type value_type;
	typedef typename subset_traits<value_type>::subset_container subset_container;

	subset_container subs = subset(first, last);

	--subset;

	return subs;
}

}} // Namespace dcs::algorithm

#endif // DCS_COMMONS_ALGORITHM_SUBSET_HPP
