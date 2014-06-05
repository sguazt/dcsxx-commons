/**
 * \file dcs/functional/bind.hpp
 *
 * \brief Generalization of the standard functions \c std::bind1st and
 *  \c std::bind2nd.
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

#ifndef DCS_FUNCTIONAL_BIND_HPP
#define DCS_FUNCTIONAL_BIND_HPP


#if __cplusplus > 201103L
// C++0x has bind
# 	include <functional>
# 	define DCS_FUNCTIONAL_BIND_NS_ ::std
# 	define DCS_FUNCTIONAL_PLACEHOLDERS_NS_ ::std::placeholders
#else
#	include <dcs/detail/config/boost.hpp>
// Use Boost bind
#   if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102500) // 1.25
#       error "Required Boost libraries version >= 1.25."
#   endif
# 	include <boost/bind.hpp>
# 	define DCS_FUNCTIONAL_BIND_NS_ ::boost
# 	define DCS_FUNCTIONAL_PLACEHOLDERS_NS_ /**/
#endif // __cplusplus
//#include <boost/bind.hpp>

namespace dcs { namespace functional {

using DCS_FUNCTIONAL_BIND_NS_::bind;
using DCS_FUNCTIONAL_BIND_NS_::is_bind_expression;
using DCS_FUNCTIONAL_BIND_NS_::is_placeholder;

namespace placeholders {

using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_1;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_2;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_3;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_4;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_5;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_6;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_7;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_8;
using DCS_FUNCTIONAL_PLACEHOLDERS_NS_::_9;

} // Namespace placeholders

}} // Namespace dcs::functional


#endif // DCS_FUNCTIONAL_BIND_HPP
