/**
 * \file dcs/container/circular_buffer.hpp
 *
 * \brief A STL compliant container also known as ring or cyclic buffer.
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

#ifndef DCS_CONTAINER_CIRCULAR_BUFFER_HPP
#define DCS_CONTAINER_CIRCULAR_BUFFER_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101700) // 1.35
#	error "Required Boost library version >= 1.35."
#endif

#include <boost/circular_buffer.hpp>

namespace dcs { namespace container {

using ::boost::circular_buffer;

}} // Namespace dcs::container


#endif // DCS_CONTAINER_CIRCULAR_BUFFER_HPP
