/**
 * \file dcs/detail/cx11_macro.hpp
 *
 * \brief A collection of macros that replace C++11 functions/types when they
 *  are not available.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons.
 *
 * dcsxx-commons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcsxx-commons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcsxx-commons.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_DETAIL_MACRO_CX11_HPP
#define DCS_DETAIL_MACRO_CX11_HPP

#if __cplusplus >= 201103L // C++11 or new

#include <cstdint>
#include <iterator>
#include <utility>

# define DCS_DETAIL_MACRO_CX11_STD_MOVE_ ::std::move
# define DCS_DETAIL_MACRO_CX11_STD_NEXT_ ::std::next
# define DCS_DETAIL_MACRO_CX11_STD_PREV_ ::std::prev
# define DCS_DETAIL_MACRO_CX11_STD_UINTMAX_T_ ::std::uintmax_t

#else // Old C++ standard

#include <boost/cstdint.hpp>
#include <boost/move/move.hpp>
#include <boost/next_prior.hpp>

# define DCS_DETAIL_MACRO_CX11_STD_MOVE_ ::boost::move
# define DCS_DETAIL_MACRO_CX11_STD_NEXT_ ::boost::next
# define DCS_DETAIL_MACRO_CX11_STD_PREV_ ::boost::prior
# define DCS_DETAIL_MACRO_CX11_STD_UINTMAX_T_ ::boost::uintmax_t

#endif // __cplusplus

#endif // DCS_DETAIL_MACRO_CX11_HPP
