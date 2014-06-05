/**
 * \file dcs/math/stats/function/summary.hpp
 *
 * \brief Compute summary statistics for various statistics.
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

#ifndef DCS_MATH_STATS_FUNCTION_SUMMARY_HPP
#define DCS_MATH_STATS_FUNCTION_SUMMARY_HPP


#include <dcs/math/stats/function/count.hpp>
#include <dcs/math/stats/function/max.hpp>
#include <dcs/math/stats/function/mean.hpp>
#include <dcs/math/stats/function/min.hpp>
#include <dcs/math/stats/function/variance.hpp>
#include <dcs/math/stats/summary_stats.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Compute summary statistics for various statistics.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename SampleT, typename ValueT>
summary_stats<ValueT> summary(SampleT const& sample)
{
	summary_stats<ValueT> stats;
	stats.count(count(sample));
	stats.min(min(sample));
	stats.mean(mean(sample));
	stats.variance(variance(sample));
	stats.max(max(sample));

	return stats;
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_SUMMARY_HPP
