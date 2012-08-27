/**
 * \file dcs/math/stats/function/prediction_interval.hpp
 *
 * \brief Computes a two-sided prediction interval at the specified level.
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

#ifndef DCS_MATH_STATS_FUNCTION_PREDICTION_INTERVAL_HPP
#define DCS_MATH_STATS_FUNCTION_PREDICTION_INTERVAL_HPP


#include <utility>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Computes a two-sided prediction interval at the specified level.
 *
 * \tparam SampleT The sample type.
 * \tparam ValueT The value type.
 *
 * \param sample The sample over which computing the prediction interval.
 * \param level The level at which computing the prediction interval.
 * \return A pair of values (of type ValueT) given the lower and upper limits of
 *  the prediction interval at level \a level.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename SampleT, typename ValueT>
::std::pair<ValueT,ValueT> prediction_interval(SampleT const& sample, ValueT level=0.95);

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_PREDICTION_INTERVAL_HPP
