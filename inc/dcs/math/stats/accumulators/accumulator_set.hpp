/**
 * \file dcs/math/stats/accumulators/accumulator_set.hpp
 *
 * \brief Data values accumulator.
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

#ifndef DCS_MATH_STATS_ACCUMULATORS_ACCUMULATOR_SET_HPP
#define DCS_MATH_STATS_ACCUMULATORS_ACCUMULATOR_SET_HPP


#include <algorithm>
#include <cmath>
#include <dcs/math/stats/operation/confidence_interval.hpp>
#include <dcs/math/stats/operation/count.hpp>
#include <dcs/math/stats/operation/max.hpp>
#include <dcs/math/stats/operation/mean.hpp>
#include <dcs/math/stats/operation/min.hpp>
#include <dcs/math/stats/operation/prediction_interval.hpp>
#include <dcs/math/stats/operation/standard_deviation.hpp>
#include <dcs/math/stats/operation/sum.hpp>
#include <dcs/math/stats/operation/summary.hpp>
#include <dcs/math/stats/operation/variance.hpp>
#include <dcs/math/stats/distribution/students_t.hpp>
#include <limits>
#include <utility>


namespace dcs { namespace math { namespace stats {

namespace detail {
template <typename T>
struct min_value
{
	static T value()
	{
		return ::std::numeric_limits<T>::is_signed
						   ? -(::std::numeric_limits<T>::has_infinity
							   ? ::std::numeric_limits<T>::infinity()
							   : ::std::numeric_limits<T>::min())
						   : (::std::numeric_limits<T>::has_infinity
							  ? ::std::numeric_limits<T>::infinity()
							  : ::std::numeric_limits<T>::min());
	}
};

template <typename T>
struct max_value
{
	static T value()
	{
		return ::std::numeric_limits<T>::has_infinity
					 ? ::std::numeric_limits<T>::infinity()
					 : ::std::numeric_limits<T>::max();
	}
};

} // Namespace detail

/**
 * \brief Data values accumulator.
 *
 * \tparam ValueT The type of the accumulated values.
 *
 * \note For computing the variance the algorithm due to (Welford, 1962) is used
 * (also found on (Knuth, 1998, pp. 232)).
 * For another alternative see (Press, 2007, pp. 724).
 *
 * \sa D. Knuth. "The Art of Computer Programming, Vol.II", 3rd edition. Addison-Wesley, 1998.
 * \sa W.H. Press, S.A. Teukolsky, W.T. Vetterling, and B.P. Flannery. "Numerical Recipes: The Art of Scientific Computing", 3rd edition. Cambridge University Press, 2007.
 * \sa B.P. Welford."Note on a method for calculating corrected sums of squares and products". Technometrics 4(3):419–420, 1962.
 */
template <typename ValueT>
class accumulator_set
{
	public: typedef ValueT value_type;
	public: typedef ::std::size_t size_type;


	public: template <typename V> friend V count(accumulator_set<V> const& acc);
	public: template <typename V> friend V max(accumulator_set<V> const& acc);
	public: template <typename V> friend V mean(accumulator_set<V> const& acc);
	public: template <typename V> friend V min(accumulator_set<V> const& acc);
	public: template <typename V> friend V sum(accumulator_set<V> const& acc);
	public: template <typename V> friend V variance(accumulator_set<V> const& acc);


	public: accumulator_set()
		: count_(0),
		  //max_(::std::numeric_limits<value_type>::min()),
		  max_(detail::min_value<value_type>::value()),
		  //min_(::std::numeric_limits<value_type>::max()),
		  min_(detail::max_value<value_type>::value()),
		  //sum_(0),
		  //sum2_(0),
		  m1_(0),
		  m2_(0)
	{
		// empty
	}


	public: void operator()(value_type const& value)
	{
		++count_;
		//sum_ += value;
		//sum2_ += value*value;
		max_ = ::std::max(max_, value);
		min_ = ::std::min(min_, value);

		// This algorithm comes from Knuth, "The Art of Computer Programming,
		// Vol II" and is used to avoid round-off errors
		value_type delta = value - m1_;
		m1_ += delta/value_type(count_); // Uses the new value of count_!
		m2_ += delta*(value-m1_); // Uses the new value of m1!

	}


	private: size_type count_;
	private: value_type max_;
	private: value_type min_;
	//private: value_type sum_;
	//private: value_type sum2_;
	private: value_type m1_;
	private: value_type m2_;
};


template <typename V>
V count(accumulator_set<V> const& acc)
{
	return acc.count_;
}


template <typename V>
V max(accumulator_set<V> const& acc)
{
	return acc.max_;
}


template <typename V>
V mean(accumulator_set<V> const& acc)
{
	//return acc.sum_/V(acc.count_);
	return acc.m1_;
}


template <typename V>
V min(accumulator_set<V> const& acc)
{
	return acc.min_;
}


template <typename V>
V standard_deviation(accumulator_set<V> const& acc)
{
	V var = variance(acc);
	return (var > 0) ? ::std::sqrt(variance(acc)) : 0;
}


template <typename V>
V sum(accumulator_set<V> const& acc)
{
	return acc.m1_*V(acc.count_);
}


template <typename V>
V variance(accumulator_set<V> const& acc)
{
	if (acc.count_ <= 1)
	{
		return 0;
	}

	// More elegant computation ... but slower
	//V m = mean(acc);
	//return (acc.sum2_ - V(acc.count_)*m*m)/V(acc.count_-1);

	// Quicker computation: (1/(n-1))*(sum(x^2)-(1/n)*(sum(x)^2))
	// However suffer of roundoff-errors
	//return (acc.sum2_ - acc.sum_*acc.sum_/V(acc.count_))/V(acc.count_-1);

	// This come from Knuth, "The Art of Computer Programming, Vol II"
	return acc.m2_/V(acc.count_-1);
}


template <typename V>
summary_stats<V> summary(accumulator_set<V> const& acc)
{
	// The default implementation is good
	return summary<accumulator_set<V>,V>(acc);
}


template <typename V>
::std::pair<V,V> confidence_interval(accumulator_set<V> const& acc, V level)
{
	V m = mean(acc);
	V s = standard_deviation(acc);
	V c = count(acc);

//	V q(0);
//	if (c >= 30)
//	{
//		// Use Standardized Normal distribution
//		normal<V> dist;
//		q = dist.quantile(level/2);
//	}
//	else
//	{
//		// Use Student's t distribution
//		student_t<V> dist(c-1);
//		q = dist.quantile(level/2);
//	}

	// Use Student's t distribution
	::dcs::math::stats::students_t<V> dist(c-1);
	V q = dist.quantile(level/V(2));

	V hl = q*s/::std::sqrt(c);

	return ::std::make_pair(m-hl, m+hl);
}


template <typename V>
::std::pair<V,V> prediction_interval(accumulator_set<V> const& acc, V level)
{
	V m = mean(acc);
	V s = standard_deviation(acc);
	V c = count(acc);

	// Use Student's t distribution
	::dcs::math::stats::students_t<V> dist(c-1);
	V q = dist.quantile(level/V(2));

	V hl = q*s*::std::sqrt(V(1)+V(1)/c);

	return ::std::make_pair(m-hl, m+hl);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_ACCUMULATORS_ACCUMULATOR_SET_HPP
