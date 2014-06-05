/**
 * \file dcs/meta/list.hpp
 *
 * \brief A list is a variadic, forward, extensible sequence of types that
 *  supports constant-time insertion and removal of elements at the beginning,
 *  and linear-time insertion and removal of elements at the end and in the
 *  middle.
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

#ifndef DCS_META_LIST_HPP
#define DCS_META_LIST_HPP


#include <dcs/detail/config/boost.hpp>


#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103000) // 1.30

#include <boost/mpl/list.hpp>

namespace dcs { namespace meta {

using ::boost::mpl::list0;
using ::boost::mpl::list1;
using ::boost::mpl::list2;
using ::boost::mpl::list3;
using ::boost::mpl::list4;
using ::boost::mpl::list;

/// Alias for the zero-elements list
typedef list0<> empty_list;

}} // Namespace dcs::meta


#else // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


// Code based primarily on:
// - "Generic Programming: Typelists and Applications" by Alexandrescu
//   (http://www.ddj.com/cpp/184403813)
// - The Tiny Template Library (http://ttl.sourceforge.net)
// . The Boost.MPL library (http://www.boost.org/)
// .

#include <dcs/meta/empty_fwd.hpp>
#include <dcs/meta/empty_type.hpp>
#include <dcs/meta/front_fwd.hpp>
#include <dcs/meta/long.hpp>
#include <dcs/meta/next.hpp>
#include <dcs/meta/not.hpp>
#include <dcs/meta/pop_front_fwd.hpp>
#include <dcs/meta/push_front_fwd.hpp>
#include <dcs/meta/size_fwd.hpp>

namespace dcs { namespace meta {

/// The tag for type-lists.
struct list_tag {};

namespace detail
{

/// A node of a type-list
template <typename SizeT, typename ElemT, typename NextT>
struct list_node
{
	typedef SizeT size;
    typedef ElemT item;
    typedef NextT next;
	typedef list_tag tag;
	typedef list_node type;
};

/// Tag dispatcher specialization for the \c size operation.
template <>
struct size_impl<list_tag>
{
	template <typename SequenceT>
	struct apply
	{
		typedef typename SequenceT::size type;
	};
};

/// Tag dispatcher specialization for the \c empty operation.
template <>
struct empty_impl<list_tag>
{
	template <typename SequenceT>
	struct apply: public dcs::meta::not_< typename SequenceT::size >
	{
	};
};

/// Tag dispatcher specialization for the \c front operation.
template <>
struct front_impl<list_tag>
{
	template <typename SequenceT>
	struct apply
	{
		typedef typename SequenceT::item type;
	};
};

/*
/// Tag dispatcher specialization for the \c back operation.
template <>
struct back_impl<list_tag>
{
	template <typename SequenceT>
	struct apply
	{
		typedef typename SequenceT::next type;
	};
};
*/

/// Tag dispatcher specialization for the \c push_front operation.
/// Attach a new node in front of the given type list.
template <>
struct push_front_impl<list_tag>
{
	template <typename SequenceT, typename T>
	struct apply
	{
		typedef list_node<typename dcs::meta::next<typename SequenceT::size>::type, T, typename SequenceT::type> type;
	};
};

/// Tag dispatcher specialization for the \c pop_front operation.
/// Detach the node in front of the given type list.
template <>
struct pop_front_impl<list_tag>
{
	template <typename SequenceT, typename T>
	struct apply
	{
		typedef typename dcs::meta::next<SequenceT>::type type;
	};
};

} // Namespace detail


/// Zero-elements type-list.
template <typename Dummy=empty_type_tag>
struct list0
{
	typedef long_<0> size;
    typedef empty_type_tag item;
    typedef list0 next;
	typedef list_tag tag;
	typedef list0 type;
};

/// One-element type-list (the empty list).
template <typename T1>
struct list1: public detail::list_node< long_<1>, T1, list0<> >
{
	typedef list1 type;
};

/// Two-elements type-list.
template <typename T1, typename T2>
struct list2: public detail::list_node< long_<2>, T1, list1<T2> >
{
	typedef list2 type;
};

/// Three-elements type-list.
template <typename T1, typename T2, typename T3>
struct list3: public detail::list_node< long_<3>, T1, list2<T2,T3> >
{
	typedef list3 type;
};

/// Four-elements type-list.
template <typename T1,typename T2,  typename T3, typename T4>
struct list4: public detail::list_node< long_<4>, T1, list3<T2,T3,T4> >
{
	typedef list4 type;
};

// ... and so forth.


// List sequence aliases and wrappers

/// Alias for the zero-elements list
typedef list0<> empty_list;

/// Four-elements type-list wrapper.
template <typename T1=empty_type_tag, typename T2=empty_type_tag,  typename T3=empty_type_tag, typename T4=empty_type_tag>
struct list: public list4<T1,T2,T3,T4>
{
	typedef typename list4<T1,T2,T3,T4>::type type;
};

/// Three-elements type-list wrapper.
template <typename T1,typename T2,  typename T3>
struct list<T1,T2,T3,empty_type_tag>: public list3<T1,T2,T3>
{
	typedef typename list3<T1,T2,T3>::type type;
};

/// Two-elements type-list wrapper.
template <typename T1,typename T2>
struct list<T1,T2,empty_type_tag,empty_type_tag>: public list2<T1,T2>
{
	typedef typename list2<T1,T2>::type type;
};

/// One-element type-list wrapper.
template <typename T1>
struct list<T1,empty_type_tag,empty_type_tag,empty_type_tag>: public list1<T1>
{
	typedef typename list1<T1>::type type;
};

/// Zero-elements type-list wrapper (the empty list).
template <>
struct list<empty_type_tag,empty_type_tag,empty_type_tag,empty_type_tag>: public list0<>
{
	typedef list0<>::type type;
};


}} // Namespace dcs::meta


#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#endif // DCS_META_LIST_HPP
