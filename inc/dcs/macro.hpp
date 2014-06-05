/**
 * \file dcs/macro.hpp
 *
 * \brief Provide C-preprocessor (macro) support.
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

#ifndef DCS_MACRO_HPP
#define DCS_MACRO_HPP


namespace dcs { namespace macro { namespace detail {

template <typename T>
inline void suppress_unused_variable_warning(T const&) {}

}}} // Namespace dcs::macro::detail


/// Expands the given argument.
#define DCS_MACRO_EXPAND(x) x

/// The character '#' (hash).
#define DCS_MACRO_HASH_SYM #

/// Prefixes the given argument with the character '#' (hash).
#define DCS_MACRO_HASHIFY(x) DCS_MACRO_EXPAND(DCS_MACRO_HASH_SYM)x

/// Concatenates the two specified arguments.
#define DCS_MACRO_JOIN(x,y) x##y

/// Stringifies (quote) the given argument.
#define DCS_MACRO_QUOTE(x) #x

/// Suppresses the "unused variable" warning issued during compilation.
#define DCS_MACRO_SUPPRESS_UNUSED_VARIABLE_WARNING(x) \
	::dcs::macro::detail::suppress_unused_variable_warning(x)

/// Declares a function, a variable or a type declaration as deprecated. Add it at the end of the declaration you want to deprecate.
#if defined(_WIN32) || defined(__HP_cc)
# define DCS_MACRO_DECL_DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__) && defined(__linux__)
# define DCS_MACRO_DECL_DEPRECATED __attribute__ ((deprecated))
#elif defined(__SUNPRO_C)
# define DCS_MACRO_DECL_DEPRECATED
#else
# define DCS_MACRO_DECL_DEPRECATED
#endif

/// Marks a function, a variable or a type declaration that should be exported from DLLs or binaries for runtime linking.
#if defined(_WIN32) || defined(__HP_cc)
# define DCS_MACRO_DECL_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) && defined(__linux__)
# define DCS_MACRO_DECL_EXPORT __attribute__ ((visibility("default")))
#elif defined(__SUNPRO_C)
# define DCS_MACRO_DECL_EXPORT __global
#else
# define DCS_MACRO_DECL_EXPORT
#endif


#endif // DCS_MACRO_HPP
