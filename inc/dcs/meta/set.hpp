/**
 * \file dcs/meta/set.hpp
 *
 * \brief A variadic, associative, extensible sequence of types that supports
 *  constant-time insertion and removal of elements, and testing for membership.
 *  A set may contain at most one element for each key.
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

#ifndef DCS_META_SET_HPP
#define DCS_META_SET_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30


#include <boost/mpl/set.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::set0;
using ::boost::mpl::set1;
using ::boost::mpl::set2;
using ::boost::mpl::set3;
using ::boost::mpl::set4;
using ::boost::mpl::set;

/// Alias for the zero-elements set
typedef set0<> empty_set;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


// Code based primarily on:
// - "Modern C++ Design" by Alexandrescu (2001)
// . The Boost.MPL library (http://www.boost.org/)
// .

#include <dcs/meta/bool.hpp>
#include <dcs/meta/clear_fwd.hpp>
#include <dcs/meta/count_fwd.hpp>
#include <dcs/meta/empty_fwd.hpp>
#include <dcs/meta/empty_type.hpp>
#include <dcs/meta/front_fwd.hpp>
#include <dcs/meta/has_key_fwd.hpp>
#include <dcs/meta/if.hpp>
#include <dcs/meta/is_same.hpp>
#include <dcs/meta/long.hpp>
#include <dcs/meta/next.hpp>
#include <dcs/meta/not.hpp>
#include <dcs/meta/size_fwd.hpp>
#include <dcs/meta/void.hpp>

namespace dcs { namespace meta {

/// The tag for type-sets.
struct set_tag {};

// Forward declaration
template <typename Dummy=empty_type_tag> struct set0;

namespace detail
{

//template <typename T> static T const& ptr_to_ref(T*);
//template <typename T> struct type_wrapper { typedef T type; };

/// A node of a type-set
template <typename ElemT, typename BaseT>
struct set_node: public BaseT
{
	//typedef void_ last_masked_;
    typedef set_node<ElemT,BaseT> item;
    typedef ElemT item_type;
    typedef BaseT base;
	typedef typename dcs::meta::next<typename BaseT::size>::type size;
	typedef typename dcs::meta::next<typename BaseT::order>::type order;
	//typedef char (&order_tag_)[order::value];
	//static order_tag_ order_by_key(set_node const&, type_wrapper<ElemT>*);
	//static no_tag is_masked_(set_node const&, type_wrapper<ElemT>*);
};

/*
template <typename T, typename BaseT>
struct set_mask: public BaseT
{
	typedef set_mask item_;
	typedef T last_masked_;
	typedef void_ item_type_;
	typedef BaseT base;
	typedef typename dcs::meta::prior<typename BaseT::size>::type size;
};

template <typename T, typename BaseT>
struct set_unmask: public BaseT
{
	typedef set_unmask item_;
	typedef T last_masked_;
	typedef void_ item_type_;
	typedef BaseT base;
	typedef typename dcs::meta::next<typename BaseT::size>::type size;
};
*/


/// Tag dispatcher specialization for the \c size operation.
template <>
struct size_impl<set_tag>
{
	template <typename SequenceT>
	struct apply: public SequenceT::size
	{
	};
};


/// Tag dispatcher specialization for the \c empty operation.
template <>
struct empty_impl<set_tag>
{
	template <typename SequenceT>
	struct apply: public dcs::meta::not_< typename SequenceT::size >
	{
	};
};


/// Tag dispatcher specialization for the \c front operation.
template <>
struct front_impl<set_tag>
{
	template <typename SequenceT>
	struct apply
	{
		typedef typename SequenceT::item_type type;
	};
};


/// Auxiliary type for the \c has_key_impl type.
template <typename AssociativeSequenceT, typename KeyT>
struct has_key_impl_aux;
// Auxiliary type: recursion
template <typename AssociativeSequenceT, typename KeyT>
struct has_key_impl_aux
{
	typedef typename dcs::meta::if_<dcs::meta::is_same<typename AssociativeSequenceT::item_type, KeyT>, dcs::meta::true_, typename has_key_impl_aux<typename AssociativeSequenceT::base, KeyT>::type>::type type;
};
// Auxiliary type: base cases
template <typename KeyT>
struct has_key_impl_aux<dcs::meta::set0<>, KeyT>
{
	typedef dcs::meta::false_ type;
};
template <>
struct has_key_impl_aux<dcs::meta::set0<>, dcs::meta::empty_type_tag>
{
	typedef dcs::meta::true_ type;
};

/// Tag dispatcher specialization for the \c has_key operation.
/// Return a boolean type if the set has the given element
template <>
struct has_key_impl<set_tag>
{
	template <typename AssociativeSequenceT, typename KeyT>
	//struct apply: dcs::meta::bool_<(sizeof(AssociativeSequenceT::is_masked_(static_cast<AssociativeSequenceT*>(0), static_cast<type_wrapper<KeyT>*>(0))) == sizeof(no_tag))>
	struct apply: public has_key_impl_aux<AssociativeSequenceT, KeyT>::type
	{
	};
};


/// Tag dispatcher specialization for the \c clear operation.
/// Return an empty set.
template <>
struct clear_impl<set_tag>
{
	template <typename SequenceT>
	struct apply
	{
		typedef dcs::meta::set0<> type;
	};
};


/// Tag dispatcher specialization for the \c count operation.
/// Return the (type) number of elements in the set having the KeyT as key
/// (which for set can be 0 or 1).
template <>
struct count_impl<set_tag>
{
	template <typename AssociativeSequenceT, typename KeyT>
	struct apply
	{
		typedef typename dcs::meta::if_< typename dcs::meta::has_key<AssociativeSequenceT, KeyT>::type, long_<1>, long_<0> >::type type;
	};
};

} // Namespace detail


/// Zero-elements type-set.
template <typename Dummy/*=empty_type_tag*/>
struct set0
{
	typedef set0<> item;
    typedef Dummy item_type;
	typedef set0<> base;
	typedef set0<> type;
	typedef set_tag tag;
	//typedef void_ last_masked_;
	//typedef void_ item_type_;
	typedef long_<0> size;
	typedef long_<1> order;
};

/// One-element type-set (the empty set).
template <typename T1>
struct set1: public detail::set_node<T1, typename set0<>::item>
{
	typedef set1 type;
};

/// Two-elements type-set.
template <typename T1, typename T2>
struct set2: public detail::set_node<T2, typename set1<T1>::item>
{
	typedef set2 type;
};

/// Three-elements type-set.
template <typename T1, typename T2, typename T3>
struct set3: public detail::set_node<T3, typename set2<T1,T2>::item>
{
	typedef set3 type;
};

/// Four-elements type-set.
template <typename T1,typename T2,  typename T3, typename T4>
struct set4: public detail::set_node<T4, typename set3<T1,T2,T3>::item>
{
	typedef set4 type;
};

// ... and so forth.


// SET sequence aliases and wrappers

/// Alias for the zero-elements set
typedef set0<> empty_set;

/// Four-elements type-set wrapper.
//template <typename T1=empty_type_tag, typename T2=empty_type_tag,  typename T3=empty_type_tag, typename T4=empty_type_tag>
template <typename T1=empty_type_tag, typename T2=empty_type_tag,  typename T3=empty_type_tag, typename T4=empty_type_tag>
struct set: public set4<T1,T2,T3,T4>
{
	typedef typename set4<T1,T2,T3,T4>::type type;
};

/// Three-elements type-set wrapper.
template <typename T1,typename T2,  typename T3>
struct set<T1,T2,T3,empty_type_tag>: public set3<T1,T2,T3>
{
	typedef typename set3<T1,T2,T3>::type type;
};

/// Two-elements type-set wrapper.
template <typename T1,typename T2>
struct set<T1,T2,empty_type_tag,empty_type_tag>: public set2<T1,T2>
{
	typedef typename set2<T1,T2>::type type;
};

/// One-element type-set wrapper.
template <typename T1>
struct set<T1,empty_type_tag,empty_type_tag,empty_type_tag>: public set1<T1>
{
	typedef typename set1<T1>::type type;
};

/// Zero-elements type-set wrapper (the empty set).
template <>
struct set<empty_type_tag,empty_type_tag,empty_type_tag,empty_type_tag>: public set0<>
{
	typedef set0<>::type type;
};


}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_SET_HPP
