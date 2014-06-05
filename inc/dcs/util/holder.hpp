/**
 * \file dcs/util/holder.hpp
 *
 * \brief Holder for objects of any type.
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

#ifndef DCS_UTIL_HOLDER_HPP
#define DCS_UTIL_HOLDER_HPP


#include <dcs/type_traits/add_const.hpp>
#include <dcs/type_traits/add_reference.hpp>


namespace dcs { namespace util {

/**
 * \brief Holder for objects of any type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
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
