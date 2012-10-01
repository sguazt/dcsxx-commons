/**
 * \file dcs/math/functional/approximately_greater_equal.hpp
 *
 * \brief Functor for checking if two numbers are approximately greater or
 *  equal (with respect to floating-point comparison).
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

#ifndef DCS_MATH_FUNCTIONAL_APPROXIMATELY_GREATER_EQUAL_HPP
#define DCS_MATH_FUNCTIONAL_APPROXIMATELY_GREATER_EQUAL_HPP


#include <dcs/math/traits/float.hpp>
#include <functional>


namespace dcs { namespace math {

template <typename T>
struct approximately_greater_equal: ::std::binary_function <T,T,bool>
{
	bool operator()(T const& x, T const& y) const
    {
		return float_traits<T>::approximately_greater_equal(x, y);
	}

	bool operator()(T const& x, T const& y, T const& tol) const
    {
		return float_traits<T>::approximately_greater_equal(x, y, tol);
	}
};

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTIONAL_APPROXIMATELY_GREATER_EQUAL_HPP
