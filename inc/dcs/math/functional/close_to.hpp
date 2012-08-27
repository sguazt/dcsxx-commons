/**
 * \file dcs/math/functional/close_to.hpp
 *
 * \brief Functor for the closeness to comparison operator.
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

#ifndef DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP
#define DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP


#include <cmath>
#include <functional>


namespace dcs { namespace math {

template <typename T>
struct close_to: ::std::binary_function <T,T,bool>
{
	close_to() : tol_(0) { }

	close_to(T tol) : tol_(tol) { }

	bool operator()(T const& x, T const& y) const
    {
		return (::std::fabs(x-y) <= tol_);
	}

	bool operator()(T const& x, T const& y, T const& tol) const
    {
		return (::std::abs(x-y) <= tol);
	}

	private: T tol_;
};

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTIONAL_CLOSE_TO_HPP
