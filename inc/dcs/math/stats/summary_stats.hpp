/**
 * \file dcs/math/stats/summary_stats.hpp
 *
 * \brief Summary statistics for a set of observations.
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
