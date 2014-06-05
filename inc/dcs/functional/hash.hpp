/**
 * \file dcs/functional/hash.hpp
 *
 * \brief Hash function object that can be extended to hash user defined types
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

#ifndef DCS_FUNCTIONAL_HASH_HPP
#define DCS_FUNCTIONAL_HASH_HPP

#if __cplusplus > 201103L
// C++0x has unordered_map
#	include <functional>
#	define DCS_FUNCTIONAL_HASH_NS_ ::std
#else
#	include <dcs/detail/config/boost.hpp>
#	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103300) // 1.33
#		error "Required Boost libraries version >= 1.33."
#	endif
#	include <boost/functional/hash.hpp>
#	define DCS_FUNCTIONAL_HASH_NS_ ::boost
#endif // __cplusplus

namespace dcs { namespace functional {

using DCS_FUNCTIONAL_HASH_NS_::hash;

}} // Namespace dcs::functional

#endif // DCS_FUNCTIONAL_HASH_HPP
