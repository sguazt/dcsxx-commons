/**
 * \file dcs/math/stats/function/prediction_interval.hpp
 *
 * \brief Computes a two-sided prediction interval at the specified level.
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename SampleT, typename ValueT>
::std::pair<ValueT,ValueT> prediction_interval(SampleT const& sample, ValueT level=0.95);

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_PREDICTION_INTERVAL_HPP
