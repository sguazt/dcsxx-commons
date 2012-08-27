/**
 * \file dcs/math/stats/function/coefficient_of_variation.hpp
 *
 * \brief Compute the coefficient-of-variation for various statistics.
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

#ifndef DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP
#define DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP


#include <dcs/math/stats/function/mean.hpp>
#include <dcs/math/stats/function/standard_deviation.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Compute the coefficient-of-variation for various statistics.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename SampleT, typename ValueT>
ValueT coefficient_of_variation(SampleT const& sample)
{
	return standard_deviation(sample)/mean(sample);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP
