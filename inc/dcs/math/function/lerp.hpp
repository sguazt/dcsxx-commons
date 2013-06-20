/**
 * \file dcs/math/function/lerp.hpp
 *
 * \brief Linear interpolation.
 *
 * Perform the linear interpolation between two inputs (x0,x1) for a parameter
 * (t) in the range [0,1] 
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone
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

#ifndef DCS_MATH_FUNCTION_LERP_HPP
#define DCS_MATH_FUNCTION_LERP_HPP


namespace dcs { namespace math {

/**
 * Computes the linear combination of x0 and x1 with parameter t:
 *  (1-t)*x0 + t*x1
 */
template <typename RealT> 
inline 
RealT lerp(RealT x0, RealT x1, RealT t) 
{ 
	return x0+(x1-x0)*t; 
} 

}} // Namespace dcs::math


#endif // DCS_MATH_FUNCTION_LERP_HPP
