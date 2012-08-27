/**
 * \file dcs/type_traits/remove_const.hpp
 *
 * \brief Make a new type by removing the \c const type specifier from the
 *  given type.
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

#ifndef DCS_TYPE_TRAITS_REMOVE_CONST_HPP
#define DCS_TYPE_TRAITS_REMOVE_CONST_HPP


namespace dcs { namespace type_traits {

/**
 * \file dcs/type_traits/remove_const.hpp
 *
 * \brief Make a new type by removing the \c const type specifier from the
 *  given type.
 *
 * The same type as \c T, but with any top level \c const-qualifier removed.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename T>
struct remove_const;

template <typename T>
struct remove_const
{
	typedef T type;
};

template <typename T>
struct remove_const<T const>
{
	typedef T type;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_REMOVE_CONST_HPP
