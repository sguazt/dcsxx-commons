/**
 * \file dcs/type_traits/const_literal.hpp
 *
 * \brief Makes the given type suitable for const literals;
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

#ifndef DCS_TYPE_TRAITS_CONST_LITERAL_HPP
#define DCS_TYPE_TRAITS_CONST_LITERAL_HPP


#if __cplusplus > 201103L
# 	define CONST_REAL_ const 
#else
# 	define CONST_REAL_ /**/
#endif

namespace dcs { namespace type_traits {

/**
 * \brief Makes the given type suitable for const literals;
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename T>
struct const_literal;

template <typename T>
struct const_literal
{
	typedef T const type;
};

template <>
struct const_literal<float>
{
	typedef float CONST_REAL_ type;
};

template <>
struct const_literal<double>
{
	typedef double CONST_REAL_ type;
};

template <>
struct const_literal<long double>
{
	typedef long double CONST_REAL_ type;
};

}} // Namespace dcs::type_traits


#endif // DCS_TYPE_TRAITS_CONST_LITERAL_HPP
