/**
 * \file dcs/util/holder.hpp
 *
 * \brief Holder for objects of any type.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_UTIL_HOLDER_HPP
#define DCS_UTIL_HOLDER_HPP


#include <dcs/type_traits/add_const.hpp>
#include <dcs/type_traits/add_reference.hpp>


namespace dcs { namespace util {

/**
 * \brief Holder for objects of any type.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename T>
class holder
{
	public: typedef T type;
	public: typedef typename ::dcs::type_traits::add_reference<T> reference_type;
	public: typedef typename ::dcs::type_traits::add_reference<typename ::dcs::type_traits::add_const<T>::type>::type const_reference_type;

	public: holder(type t)
		: t_(t)
	{
	}

	public: reference_type get()
	{
		return t_;
	}

	public: const_reference_type get() const
	{
		return t_;
	}

	private: type t_;
};

}} // Namespace dcs::util


#endif // DCS_UTIL_HOLDER_HPP
