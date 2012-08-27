/**
 * \file dcs/debug.hpp
 *
 * \brief Provides helper functions and macros for debugging purpose.
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

#ifndef DCS_DEBUG_HPP
#define DCS_DEBUG_HPP

#ifndef NDEBUG
//@{ for C99 and C++0x
//# 	include <cstdio>
//# 	define DCS_DEBUG_WHERESTR_  "[file %s, function %s, line %d]: "
//#	define DCS_DEBUG_WHEREARG_  __FILE__, __func__, __LINE__
//#	define DCS_DEBUG_PRINT2_(...)       fprintf(stderr, __VA_ARGS__)
//#	define DCS_DEBUG_PRINT(fmt, ...)  DCS_DEBUG_PRINT2_(DCS_DEBUG_WHERESTR_ fmt, DCS_DEBUG_WHEREARG_, __VA_ARGS__)
//@} for C99 and C++0x

#	include <cassert>
#	include <iostream>
# 	include <typeinfo>
/// Macro for telling whether we are in debug mode.
# 	define DCS_DEBUG /**/
/// Macro for expanding its argument \c x
#	define DCS_DEBUG_EXPAND__(x) x
/// Macro for writing to standard error its argument \c x
#	if !defined(DCS_DEBUG_LEVEL) || (DCS_DEBUG_LEVEL > 0)
#		define DCS_DEBUG_TRACE(x) ::std::cerr << "[Debug (" << __FILE__ << ":" << __func__ << ":" << __LINE__ << ")>> " << DCS_DEBUG_EXPAND__(x) << ::std::endl;
#	else
#		define DCS_DEBUG_TRACE(x) /**/
#	endif // !defined(DCS_DEBUG_LEVEL) ...
#	ifdef DCS_DEBUG_LEVEL
#		define DCS_DEBUG_TRACE_L(l,x) if (DCS_DEBUG_EXPAND__(l) <= DCS_DEBUG_LEVEL) { ::std::cerr << "[Debug (" << __FILE__ << ":" << __func__ << ":" << __LINE__ << ")>> " << DCS_DEBUG_EXPAND__(x) << ::std::endl; }
#	else
#		define DCS_DEBUG_TRACE_L(l,x) DCS_DEBUG_TRACE(x)
#	endif // DCS_DEBUG_LEVEL
/// Macro for getting the underlying debug output stream.
# 	define DCS_DEBUG_STREAM ::std::cerr
/// Macro for setting flags \c x of the underlying debug output stream.
# 	define DCS_DEBUG_STREAM_SETFLAGS(x) ::std::cerr.setf((x))
/// Macro for converting the given argumento into a string.
# 	define DCS_DEBUG_STRINGIFY(x) #x
/// Macro for converting the a type into a string.
# 	define DCS_DEBUG_TYPE2STR(x) typeid(x).name()
/// Macro for executing one or more statements only when debug is enabled.
#	define DCS_DEBUG_DO(x) x
/// Macro for assertion
#	define DCS_DEBUG_ASSERT(x) assert(x)
#else
/// Macro for telling that we are in debug mode.
# 	undef DCS_DEBUG /**/
/// Macro for telling what level of debugging to enable.
# 	undef DCS_DEBUG_LEVEL /**/
/// Macro for writing to standard error its argument \c x
#	define DCS_DEBUG_TRACE(x) /**/
/// Macro for writing to standard error its argument \c x only when the
/// debugging level is greater than or equal to \c l.
#	define DCS_DEBUG_TRACE_L(l,x) /**/
/// Macro for getting the underlying debug output stream.
# 	define DCS_DEBUG_STREAM /**/
/// Macro for setting flags \c x of the underlying debug output stream.
# 	define DCS_DEBUG_STREAM_SETFLAGS(x) /**/
/// Macro for converting the given argumento into a string.
# 	define DCS_DEBUG_STRINGIFY(x) /**/
/// Macro for converting the a type into a string.
# 	define DCS_DEBUG_TYPE2STR(x) /**/
/// Macro for executing one or more statements only when debug is enabled.
#	define DCS_DEBUG_DO(x) /**/
/// Macro for assertion
#	define DCS_DEBUG_ASSERT(x) /**/
#endif // NDEBUG

#endif // DCS_DEBUG_HPP
