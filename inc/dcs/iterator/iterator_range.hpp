/**
 * \file dcs/iterator/iterator_range.hpp
 *
 * \brief Encapsulate a pair of iterators.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2009 Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_ITERATOR_ITERATOR_RANGE_HPP
#define DCS_ITERATOR_ITERATOR_RANGE_HPP


#include <dcs/detail/config/boost.hpp>


// NOTE: use Boost until C++0x is out!

#if !defined(DCS_DETAIL_CONFIG_HAVE_BOOST) || (DCS_DETAIL_CONFIG_BOOST_VERSION < 103200)
# error "Need Boost version >= 1.32.0"
#endif


#include <boost/range.hpp>
//#include <boost/range/iterator_range.hpp>


namespace dcs { namespace iterator {

/**
 * \headerfile boost/range/iterator_range.hpp
 *
 * \brief Encapsulate two iterators so they fulfill the Forward Range concept.
 */
//template <typename ForwardTraversalIteratorT> class iterator_range;

//	template< class ForwardTraversalIterator >
//	class iterator_range
//	{
//	public: // Forward Range types
//		typedef ForwardTraversalIterator             iterator;
//		typedef ForwardTraversalIterator             const_iterator;
//		typedef iterator_difference<iterator>::type  difference_type;
//
//	public: // construction, assignment
//		template< class ForwardTraversalIterator2 >
//		iterator_range( ForwardTraversalIterator2 Begin, ForwardTraversalIterator2 End );
//					
//		template< class ForwardRange >
//		iterator_range( ForwardRange& r );
//
//		template< class ForwardRange >
//		iterator_range( const ForwardRange& r );
//		
//		template< class ForwardRange >
//		iterator_range& operator=( ForwardRange& r );
//
//		template< class ForwardRange >
//		iterator_range& operator=( const ForwardRange& r );
//
//	public: // Forward Range functions
//		iterator        begin() const;
//		iterator        end() const;
//		difference_type size() const;
//		bool            empty() const;
//		
//	public: // convenience
//		operator        unspecified_bool_type() const;
//		bool            equal( const iterator_range& ) const;
//		reference       front() const;
//		reference       back() const;
//		iterator_range& advance_begin( difference_type n );
//		iterator_range& advance_end( difference_type n );
//		// for Random Access Range only: 
//		reference       operator[]( difference_type at ) const;
//		value_type      operator()( difference_type at ) const;
//	};
//
//	// stream output
//	template< class ForwardTraversalIterator, class T, class Traits >
//	std::basic_ostream<T,Traits>& 
//	operator<<( std::basic_ostream<T,Traits>& Os,
//				const iterator_range<ForwardTraversalIterator>& r );
//
//	// comparison
//	template< class ForwardTraversalIterator, class ForwardTraversalIterator2 >
//	bool operator==( const iterator_range<ForwardTraversalIterator>& l, 
//					 const iterator_range<ForwardTraversalIterator2>& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator==( const iterator_range<ForwardTraversalIterator>& l, 
//					 const ForwardRange& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator==( const ForwardRange& l,
//					 const iterator_range<ForwardTraversalIterator>& r );
//
//	template< class ForwardTraversalIterator, class ForwardTraversalIterator2 >
//	bool operator!=( const iterator_range<ForwardTraversalIterator>& l, 
//					 const iterator_range<ForwardTraversalIterator2>& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator!=( const iterator_range<ForwardTraversalIterator>& l, 
//					 const ForwardRange& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator!=( const ForwardRange& l,
//					 const iterator_range<ForwardTraversalIterator>& r );
//
//	template< class ForwardTraversalIterator, class ForwardTraversalIterator2 >
//	bool operator<( const iterator_range<ForwardTraversalIterator>& l, 
//					const iterator_range<ForwardTraversalIterator2>& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator<( const iterator_range<ForwardTraversalIterator>& l, 
//					const ForwardRange& r );
//
//	template< class ForwardTraversalIterator, class ForwardRange >
//	bool operator<( const ForwardRange& l,
//					const iterator_range<ForwardTraversalIterator>& r );
//
//	// external construction
//	template< class ForwardTraversalIterator >
//	iterator_range< ForwardTraversalIterator >
//	make_iterator_range( ForwardTraversalIterator Begin, 
//						 ForwardTraversalIterator End );
//	   
//	template< class ForwardRange >
//	iterator_range< typename range_iterator<ForwardRange>::type >
//	make_iterator_range( ForwardRange& r );
//
//	template< class ForwardRange >
//	iterator_range< typename range_iterator<const ForwardRange>::type >
//	make_iterator_range( const ForwardRange& r );
//
//	template< class Range >
//	iterator_range< typename range_iterator<Range>::type >
//	make_iterator_range( Range& r,
//						 typename range_difference<Range>::type advance_begin,
//						 typename range_difference<Range>::type advance_end );
//
//	template< class Range >
//	iterator_range< typename range_iterator<const Range>::type >
//	make_iterator_range( const Range& r, 
//						 typename range_difference<Range>::type advance_begin,
//						 typename range_difference<Range>::type advance_end );
//
//	// convenience
//	template< class Sequence, class ForwardRange >
//	Sequence copy_range( const ForwardRange& r );

using ::boost::iterator_range;
using ::boost::make_iterator_range;

}} // Namespace dcs::iterator


#endif // DCS_ITERATOR_ITERATOR_RANGE_HPP
