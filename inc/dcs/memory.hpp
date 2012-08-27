/**
 * \file dcs/memory.hpp
 *
 * \brief Smart pointers are objects which store pointers to dynamically
 * allocated (heap) objects.
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

#ifndef DCS_SMART_PTR_HPP
#define DCS_SMART_PTR_HPP


#if __cplusplus > 201103L
// C++0x has smart-pointers
# 	include <memory>
# 	define DCS_MEMORY_NS_ ::std
#else
// Use Boost smart-pointers
# 	include <dcs/detail/config/boost.hpp>
# 	if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102300)
# 		error "Required Boost library version >= 1.23."
# 	endif
# 	include <boost/smart_ptr.hpp>
# 	include <boost/smart_ptr/make_shared.hpp>
# 	define DCS_MEMORY_NS_ ::boost
#endif // __cplusplus


namespace dcs {

/// Object ownership shared among multiple pointers (\sa \c boost::shared_ptr).
using DCS_MEMORY_NS_::shared_ptr;
/// Non-owning observers of an object owned by \c shared_ptr.
using DCS_MEMORY_NS_::weak_ptr;
///
using DCS_MEMORY_NS_::static_pointer_cast;
///
using DCS_MEMORY_NS_::dynamic_pointer_cast;
///
using DCS_MEMORY_NS_::const_pointer_cast;
///
using DCS_MEMORY_NS_::get_deleter;
///
using DCS_MEMORY_NS_::swap;
///
//using DCS_MEMORY_NS_::owner_less;
///
using DCS_MEMORY_NS_::enable_shared_from_this;
///
using DCS_MEMORY_NS_::make_shared;
///
using DCS_MEMORY_NS_::allocate_shared;

/// Shared ownership of objects with an embedded reference count.
using ::boost::intrusive_ptr;
/// Array ownership shared among multiple pointers.
using ::boost::shared_array;
/// Simple sole ownership of arrays. Noncopyable.
using ::boost::scoped_array;
/// Simple sole ownership of single objects. Noncopyable.
using ::boost::scoped_ptr;
///
using ::boost::get_pointer;

} // Namespace dcs


#endif // DCS_SMART_PTR_HPP
