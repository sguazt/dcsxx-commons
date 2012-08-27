/**
 * \file dcs/type_traits/add_reference.hpp
 *
 * \brief Make a new type representing a reference to the given type.
 *
 * Copyright (C) 2009-2010  Distributed Computing System (DCS) Group, Computer
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

#ifndef DCS_TYPE_TRAITS_ADD_REFERENCE_HPP
#define DCS_TYPE_TRAITS_ADD_REFERENCE_HPP


namespace dcs { namespace type_traits {

/**
 * \brief Make a new type representing a reference to the given type.
 *
 * If \c T  is not a reference type then creates \c T&, otherwise \c T.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename T>
struct add_reference;

template <typename T>
struct add_reference
{
	typedef T& type;
};


template <typename T>
struct add_reference<T&>
{
	typedef T& type;
};


template <typename T>
struct add_reference<T*>
{
	typedef T& type;
};


template <>
struct add_reference<void>
{
	typedef void type;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_ADD_REFERENCE_HPP
