/**
 * \file dcs/assert.hpp
 *
 * \brief Assertion utility.
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

#ifndef DCS_ASSERT_HPP
#define DCS_ASSERT_HPP


#include <cassert>


namespace dcs {

namespace detail {

// \see "Modern C++ Design" (Alexandrescu), sec. 2.1
template<bool> struct compile_time_checker
{
	compile_time_checker(...);
};
template<> struct compile_time_checker<false> {};

} // Namespace detail

} // Namespace dcs


#ifdef NDEBUG
#	define DCS_ASSERT(c,a) if (!(c)) { a; }
#	define DCS_ASSERT_DEBUG(c) /*empty*/
#	define DCS_ASSERT_RELATION(left, op, right) ((void)0)
#else
#	define DCS_ASSERT(c,a) assert((c))
#	define DCS_ASSERT_DEBUG(c) assert((c))

#	include <iostream> // can be quite bloaty, so only #include when needed i.e. when !defined(NDEBUG)
#	include <cstdlib> // abort()

	namespace dcs { namespace detail {

#	define DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(op) \
		template<typename Lhs, typename Rhs> \
		comparison<Lhs, Rhs> operator op(operand<Lhs> lhs, operand<Rhs> rhs) \
		{ \
			return comparison<Lhs, Rhs>(lhs.it, rhs.it, lhs.it op rhs.it); \
		} 

		template<typename T>
		struct operand
		{
			operand(T it) : it(it) { }
			T it;
		};

		template<typename T>
		operand<T> make_operand(T it) { return operand<T>(it); }

		template<typename Lhs, typename Rhs>
		struct comparison
		{
			comparison(Lhs lhs, Rhs rhs, bool result) : 
				lhs(lhs), 
				rhs(rhs), 
				result(result)
			{
			}

			bool check(const char *text, const char *file, unsigned line)
			{
				if (!result)
				{
					::std::cerr << file << ':' << line << ": "
								<< "failed assertion `" << text << "', "
								<< "where lhs=" << lhs << ", "
								<< "rhs=" << rhs << ::std::endl;
				}
				return result;
			}

			Lhs lhs;
			Rhs rhs;
			bool result;
		};

		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(<)
		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(>)
		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(<=)
		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(>=)
		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(==)
		DCS_ASSERT_DEFINE_OPERAND_OPERATOR_(!=)

	}} // Namespace dcs::detail

#define DCS_ASSERT_RELATION(left, op, right) \
    do \
    { \
        using ::dcs::detail::make_operand; \
        if (!(make_operand(left) op make_operand(right)).check(#left " " #op " " #right, __FILE__, __LINE__)) \
            abort(); \
    } \
    while (false)

#endif // NDEBUG


// \see "Modern C++ Design" (Alexandrescu), sec. 2.1
#define DCS_STATIC_CHECK(expr, msg_id) \
	{\
	   class ERROR_##msg {}; \
	   (void)sizeof(::dcs::detail::compile_time_checker<(expr) != 0>((ERROR_##msg_id())));\
	}


//namespace dcs {
//
//template <typename C, typename A>
//inline void expect(C& c, A& a)
//{
//#ifdef NDEBUG
//	if (!c) { a; }
//#else
//	assert(c);
//#endif
//}
//
//}

#endif // DCS_ASSERT_HPP
