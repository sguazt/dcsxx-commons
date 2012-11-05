/**
 * \file dcs/math/function/bind.hpp
 *
 * \brief Functions to bind a value either upper or lower.
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
 * along with dcsxx-commons. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_MATH_FUNCTION_BIND_HPP
#define DCS_MATH_FUNCTION_BIND_HPP


namespace dcs { namespace math {

/// Bind \a x to be not less than \a lb.
template <typename T>
inline
T bind_lower(T x, T lb)
{
	if (x < lb)
	{
		x = lb;
	}

	return x;
}

/// Bind \a x to be not greater than \a ub.
template <typename T>
inline
T bind_upper(T x, T ub)
{
	if (x > ub)
	{
		x = ub;
	}

	return x;
}

/// Bind \a x to be not less than \a lb and greater than \a ub.
template <typename T>
inline
T bind(T x, T lb, T ub)
{
	return bind_lower(bind_upper(x, ub), lb);

	return x;
}

/// Tells if \a lb is a lower bound of \a x.
template <typename T>
inline
bool bound_lower(T x, T lb)
{
	return x >= lb;
}

/// Tells if \a ub is an upper bound of \a x.
template <typename T>
inline
bool bound_upper(T x, T ub)
{
	return x <= ub;
}

/**
 * \brief Tells if \a lb and \a ub are a lower and an upper bound of \a x,
 *  respectively.
 */
template <typename T>
inline
bool bound(T x, T lb, T ub)
{
	return bound_lower(x, lb) && bound_upper(x, ub);
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_BIND_HPP
