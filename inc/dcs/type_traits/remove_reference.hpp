/**
 * \file dcs/type_traits/remove_reference.hpp
 *
 * \brief Make a new type by removing the reference modifier from the given
 *  type.
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

#ifndef DCS_TYPE_TRAITS_REMOVE_REFERENCE_HPP
#define DCS_TYPE_TRAITS_REMOVE_REFERENCE_HPP


namespace dcs { namespace type_traits {

/**
 * \brief Make a new type by removing the reference modifier from the given
 *  type.
 *
 * The same type as \c T, but with any reference modifier removed. 
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename T>
struct remove_reference;

template <typename T>
struct remove_reference
{
	typedef T type;
};


template <typename T>
struct remove_reference<T&>
{
	typedef T type;
};


template <typename T>
struct remove_reference<T*>
{
	typedef T type;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_REMOVE_REFERENCE_HPP
