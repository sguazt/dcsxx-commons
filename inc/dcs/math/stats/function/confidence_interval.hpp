/**
 * \file dcs/math/stats/function/confidence_interval.hpp
 *
 * \brief Compute the confidence interval for various statistics.
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

#ifndef DCS_MATH_STATS_FUNCTION_CONFIDENCE_INTERVAL_HPP
#define DCS_MATH_STATS_FUNCTION_CONFIDENCE_INTERVAL_HPP


#include <cmath>
#include <dcs/math/stats/distribution/normal.hpp>
#include <dcs/math/stats/distribution/students_t.hpp>
#include <dcs/math/stats/function/count.hpp>
#include <dcs/math/stats/function/mean.hpp>
#include <dcs/math/stats/function/standard_deviation.hpp>
#include <utility>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Computes a two-sided confidence interval for the sample mean
 *  at the specified level and with known variance.
 *
 * \tparam SampleT The sample type.
 * \tparam ValueT The value type.
 *
 * \param sample The sample over which computing the confidence interval.
 * \param s The population (true) standard deviation.
 * \param level The level at which computing the confidence interval.
 * \return A pair of values (of type ValueT) given the lower and upper limits of
 * the confidence interval at level \a level.
 */
template <typename SampleT, typename ValueT>
::std::pair<ValueT,ValueT> confidence_interval_mean(SampleT const& sample, ValueT s, ValueT level)
{
	ValueT n = count(sample);

	normal<ValueT> dist;
	ValueT z = dist.quantile((1+level)/ValueT(2));

	ValueT m = mean(sample);
	ValueT h = z*s/::std::sqrt(n);

	return ::std::make_pair(m-h, m+h);
}

/**
 * \brief Computes a two-sided confidence interval for the sample mean
 *  at the specified level and with unknown variance.
 *
 * \tparam SampleT The sample type.
 * \tparam ValueT The value type.
 *
 * \param sample The sample over which computing the confidence interval.
 * \param level The level at which computing the confidence interval.
 * \return A pair of values (of type ValueT) given the lower and upper limits of
 * the confidence interval at level \a level.
 */
template <typename SampleT, typename ValueT>
::std::pair<ValueT,ValueT> confidence_interval_mean(SampleT const& sample, ValueT level)
{
	ValueT n = count(sample);

	students_t<ValueT> dist(n-1);
	ValueT t = dist.quantile((1+level)/ValueT(2));

	ValueT s = standard_deviation(sample);
	ValueT m = mean(sample);
	ValueT h = t*s/::std::sqrt(n);

	return ::std::make_pair(m-h, m+h);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_CONFIDENCE_INTERVAL_HPP
