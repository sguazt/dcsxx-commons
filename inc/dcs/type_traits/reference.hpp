/**
 * \file dcs/type_traits/reference.hpp
 *
 * \brief Hold a reference to a type.
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

#ifndef DCS_TYPE_TRAITS_REFERENCE_HPP
#define DCS_TYPE_TRAITS_REFERENCE_HPP


#include <dcs/type_traits/add_reference.hpp>
#include <dcs/type_traits/remove_reference.hpp>


namespace dcs { namespace type_traits {

/**
 * \brief Hold a reference to a type.
 *
 * \tparam The type for which holding the reference.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename T>
struct reference
{
	typedef typename remove_reference<T>::type type;
	typedef typename add_reference<T>::type reference_type;
	typedef typename add_reference<T const>::type const_reference_type;


	explicit reference(reference_type t) : t_(t) {}


//	operator type() { return static_cast<type>(t_); }


//	operator reference_type() { return static_cast<reference_type>(t_); }


//	operator const_reference_type() const { return static_cast<const_reference_type>(t_); }

	//type cast() { return static_cast<type>(t_); }


	reference_type cast() { return static_cast<reference_type>(t_); }


	const_reference_type cast() const { return static_cast<reference_type>(t_); }

//	reference_type ref() { return t_; }


//	const_reference_type ref() const { return t_; }


	private: reference_type t_;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_REFERENCE_HPP
