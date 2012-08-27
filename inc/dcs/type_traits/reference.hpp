/**
 * \file dcs/type_traits/reference.hpp
 *
 * \brief Hold a reference to a type.
 *
 * Copyright (C) 2009  Distributed Computing System (DCS) Group, Computer
 * Science Department - University of Piemonte Orientale, Alessandria (Italy).
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
