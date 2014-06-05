/**
 * \file dcs/math/stats/summary_stats.hpp
 *
 * \brief Summary statistics for a set of observations.
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

#ifndef DCS_MATH_STATS_SUMMARY_STATS_HPP
#define DCS_MATH_STATS_SUMMARY_STATS_HPP


#include <cmath>
#include <dcs/math/stats/operation/count.hpp>
#include <dcs/math/stats/operation/mean.hpp>
#include <dcs/math/stats/operation/standard_deviation.hpp>
#include <dcs/math/stats/operation/variance.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Summary statistics for a set of observations.
 *
 * Summary statistics include:
 * - count
 * - min
 * - max
 * - mean
 * - variance / standard deviation
 * .
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ValueT>
class summary_stats;

template <typename SampleT, typename ValueT>
summary_stats<ValueT> summary(SampleT const&);

template <typename ValueT>
class summary_stats
{
	public: typedef ValueT value_type;

	public: value_type count() const { return count_; }
	protected: void count(value_type value) { count_ = value; }
	public: value_type min() const { return min_; }
	protected: void min(value_type value) { min_ = value; }
	public: value_type mean() const { return mean_; }
	protected: void mean(value_type value) { mean_ = value; }
	public: value_type variance() const { return var_; }
	protected: void variance(value_type value) { var_ = value; }
	public: value_type max() const { return max_; }
	protected: void max(value_type value) { max_ = value; }
	public: value_type standard_deviation() const { return ::std::sqrt(var_); }
	protected: void standard_deviation(value_type value) { var_ = value*value; }

	private: template <typename S, typename V> friend summary_stats<V> summary(S const&);

	private: value_type count_;
	private: value_type min_;
	//private: value_type q1; // TODO
	private: value_type mean_;
	//private: value_type median; // TODO
	private: value_type var_;
	//private: value_type q3; // TODO
	private: value_type max_;
};


template <typename ValueT>
ValueT count(summary_stats<ValueT> const& stats)
{
	return stats.count();
}

template <typename ValueT>
ValueT mean(summary_stats<ValueT> const& stats)
{
	return stats.mean();
}

template <typename ValueT>
ValueT standard_deviation(summary_stats<ValueT> const& stats)
{
	return stats.standard_deviation();
}

template <typename ValueT>
ValueT variance(summary_stats<ValueT> const& stats)
{
	return stats.variance();
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_SUMMARY_STATS_HPP
