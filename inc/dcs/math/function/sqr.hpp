/**
 * \file dcs/math/function/sqr.hpp
 *
 * \brief The square function.
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

#ifndef DCS_MATH_FUNCTION_SQR_HPP
#define DCS_MATH_FUNCTION_SQR_HPP


namespace dcs { namespace math {

/**
 * \brief The square function.
 * \tparam The numerical type of input and output values.
 * \param The numerical value to be squared.
 * \return The square of \a value.
 */
template <typename ValueT>
inline ValueT sqr(ValueT value)
{
	return value*value;
}

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_SQR_HPP
