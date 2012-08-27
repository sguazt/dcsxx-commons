/**
 * \file dcs/macro.hpp
 *
 * \brief Provide C-preprocessor (macro) support.
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

#ifndef DCS_MACRO_HPP
#define DCS_MACRO_HPP


namespace dcs { namespace macro { namespace detail {

template <typename T>
inline void suppress_unused_variable_warning(T const&) {}

}}} // Namespace dcs::macro::detail


/// Expand the given argument.
#define DCS_MACRO_EXPAND(x) x

/// The character '#' (hash).
#define DCS_MACRO_HASH_SYM #

/// Prefix the given argument with the character '#' (hash).
#define DCS_MACRO_HASHIFY(x) DCS_MACRO_EXPAND(DCS_MACRO_HASH_SYM)x

/// Concatenate the two specified arguments.
#define DCS_MACRO_JOIN(x,y) x##y

/// Stringify (quote) the given argument.
#define DCS_MACRO_QUOTE(x) #x

/// Suppress the "unused variable" warning issued during compilation.
#define DCS_MACRO_SUPPRESS_UNUSED_VARIABLE_WARNING(x) \
	::dcs::macro::detail::suppress_unused_variable_warning(x)


#endif // DCS_MACRO_HPP
