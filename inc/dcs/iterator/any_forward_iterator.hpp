/**
 * \file dcs/iterator/any_forward_iterator.hpp
 *
 * \brief Generic (type-erased) forward iterator.
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

#ifndef DCS_ITERATOR_ANY_FORWARD_ITERATOR_HPP
#define DCS_ITERATOR_ANY_FORWARD_ITERATOR_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103100) // 1.31
#	error "Required Boost libraries version >= 1.31"
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/static_assert.hpp>
#include <cstddef>
#include <dcs/iterator/any_iterator.hpp>
#include <dcs/type_traits/remove_const.hpp>
#include <iterator>


namespace dcs { namespace iterator {

/**
 * \brief Generic (type-erased) forward iterator.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template<typename ValueT, typename ReferenceT, typename DifferenceT>
class any_forward_iterator;


namespace detail {

template<class SomeIterator>
struct is_any_forward_iterator : public ::boost::mpl::bool_<false>
{
	// empty
};


template<
	typename ValueT,
	typename ReferenceT,
	typename DifferenceT
>
struct is_any_forward_iterator< any_forward_iterator<ValueT,ReferenceT,DifferenceT> >: public ::boost::mpl::bool_<true>
{
	// empty
};

} // Namespace detail


template<
	typename ValueT,
	typename ReferenceT = ValueT&,
	typename DifferenceT = std::ptrdiff_t
>
class any_forward_iterator: public any_iterator<ValueT, ::std::forward_iterator_tag, ReferenceT, DifferenceT>
{

	// We make every other any_iterator our friend. This is needed only for
	// the conversion from non-const to const, but there should be no harm
	// in being overly friendly here.
	template<
		typename OtherValueT,
		typename OtherReferenceT,
		typename OtherDifferenceT
	>
	friend class any_forward_iterator;

	private: typedef any_iterator<ValueT,::std::forward_iterator_tag,ReferenceT,DifferenceT> base_type;
	public: typedef typename base_type::traversal_type traversal_type;


	private: struct enabler{};  // a private type avoids misuse
	private: struct disabler{};  // a private type avoids misuse


	public: any_forward_iterator()
		: base_type()
	{
		// empty
	}


	public: any_forward_iterator(any_forward_iterator const& rhs)
		: base_type(*static_cast<base_type const*>(&rhs))
	{
		// empty
	}


	public: any_forward_iterator& operator=(any_forward_iterator const& rhs)
	{
		if (this != &rhs)
		{
			base_type::operator=(*static_cast<base_type const*>(&rhs));
		}

		return *this;
	}


	public: template<class WrappedIteratorT>
		explicit any_forward_iterator(WrappedIteratorT const& wrapped_iterator, typename boost::disable_if<detail::is_any_forward_iterator<WrappedIteratorT>, disabler>::type = disabler())
		: base_type(wrapped_iterator)
	{
		// empty
	}


	public: template<class WrappedIteratorT>
		typename boost::enable_if<
			boost::mpl::and_<
				detail::is_iterator_type_erasure_compatible<
					WrappedIteratorT,
					any_forward_iterator
				>,
				boost::mpl::not_< detail::is_any_forward_iterator<WrappedIteratorT> >
			>,
			any_forward_iterator
		>::type&
		operator=(WrappedIteratorT const& wrapped_iterator)
		{
			//any_forward_iterator tmp(wrapped_iterator);
			//swap(tmp);
			//return *this;

			//base_type base;
			base_type::operator=(wrapped_iterator);
			return *this;
		}
};


// Metafunction that takes an iterator and returns an any_iterator with the same
// traits.
template<class IteratorT>
struct make_any_forward_iterator_type
{
	typedef any_forward_iterator<
		//typename ::boost::iterator_value<IteratorT>::type,
		typename ::std::iterator_traits<IteratorT>::value_type,
		////typename ::boost::iterator_category<IteratorT>::type,
		//typename ::boost::iterator_reference<IteratorT>::type,
		typename ::std::iterator_traits<IteratorT>::reference,
		//typename ::boost::iterator_difference<IteratorT>::type
		typename ::std::iterator_traits<IteratorT>::difference_type
	> type;
};

/*
  namespace detail {
  template <typename IteratorT>
  struct iterator_traits
  {
      typedef typename boost::iterator_value<IteratorT>::type value_type;
      typedef typename boost::iterator_category<IteratorT>::type category_type;
      typedef typename boost::iterator_reference<IteratorT>::type reference;
      typedef typename boost::iterator_difference<IteratorT>::type difference_type;
      typedef typename boost::iterator_pointer<IteratorT>::type pointer;
  };
  }
  template<class IteratorT, class IteratorTraitsT=detail::iterator_traits<IteratorT> >
  struct make_any_iterator_type
  {
    typedef  
    any_iterator<
      typename IteratorTraitsT::value_type,
      typename IteratorTraitsT::iterator_category,
      typename IteratorTraitsT::reference,
      typename IteratorTraitsT::difference_type
    > type;
  };
//@}[sguazt]
*/

// Function that takes an iterator and returns an any_iterator with the same
// traits.
template<class IteratorT>
typename make_any_forward_iterator_type<IteratorT>::type make_any_forward_iterator(IteratorT it)
{
	typedef typename make_any_forward_iterator_type<IteratorT>::type any_iterator_type;
	return any_iterator_type(it);
}

/*
//@{[sguazt]
  template<class IteratorT, class IteratorTraitsT>
  typename make_any_iterator_type<IteratorT,IteratorTraitsT>::type make_any_iterator(IteratorT it)
  {
	typedef typename make_any_iterator_type<IteratorT,IteratorTraitsT>::type any_iterator_type;
	return any_iterator_type(it);
  }
//@}[sguazt]
*/

}} // Namespace dcs::iterator

#endif // DCS_ITERATOR_ANY_FORWARD_ITERATOR_HPP
