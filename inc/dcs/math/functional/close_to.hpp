/**
 * \file dcs/math/functional/close_to.hpp
 *
 * \brief Functor for checking if two numbers are close to each other (with
 *  respect to floating-point comparison).
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

#ifndef DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP
#define DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP


#include <cmath>
#include <functional>
#include <limits>


namespace dcs { namespace math {

/**
 * \brief Check if two real numbers are close each other, with respect to a
 *  given tolerance.
 */
//TODO: add a specialization for complex numbers (hints: use enable_if).
template <typename T>
struct close_to: ::std::binary_function <T,T,bool>
{
	bool operator()(T const& x, T const& y) const
    {
		return this->operator()(x, y, T(100)*::std::numeric_limits<T>::epsilon());
	}

	bool operator()(T const& x, T const& y, T const& tol) const
    {
		if (::std::isnan(x) || ::std::isnan(y))
		{
			// According to IEEE, NaN are different event by itself
			return false;
		}
		return ::std::abs(x-y) <= (::std::max(static_cast<T>(::std::abs(x)), static_cast<T>(::std::abs(y)))*tol);
	}
}; // close_to

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP
