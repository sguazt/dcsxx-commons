/**
 * \file src/dcs/math/stats/distribution/pmpp.hpp
 *
 * \brief Pareto Modulated Poisson Process.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_PMPP_HPP
#define DCS_MATH_STATS_DISTRIBUTION_PMPP_HPP


#include <dcs/detail/config/boost.hpp>

// Boost >= 1.15 for Boost.Random
// Boost >= 1.23 for Boost.SmartPtr
#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(102300) // 1.23
#	error "Required Boost libraries version >= 1.23."
#endif


#include <cmath>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/math/stats/distribution/exponential.hpp>
#include <dcs/math/stats/distribution/pareto.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Pareto Modulated Poisson Process (PMPP).
 *
 * A Pareto Modulated Poisson Process (PMPP) [1] is a doubly stochastic Poisson
 * process (i.e., a time-dependent Poisson process where the intensity function
 * or the mean rate of occurrence of events is a stochastic process) in which a
 * Poisson process is switched between two rates by an underlying Pareto
 * distribution.
 * We model data traffic as a switched Poisson process alternating between the
 * two levels \f$\lambda_1\f$ and \f$\lambda_2\f$.
 * The sojourn times in these two states are independent and identically
 * distributed with Pareto distribution with parameter \f$\alpha\f$.
 * The two states of this switched Poisson process would correspond to the long
 * and short burst rates.
 * The sojourn time distribution is chosen to be a thick-tailed one in order to
 * capture the long-term dependencies in the net arrival process.
 *
 * References:
 * - [1] T. Le-Ngoc, S. Subramanian,
 *       A Pareto-Modulated Poisson Process (PMPP) Model for Long-Range
 *       Dependent Traffic.
 *       Computer Communications 23 (2000) 123–132.
 * - [2] H.J. Jeong, J.R. Lee, D. McNickle, K. Pawlikowski,
 *       "Suggestions of efficient self-similar generators"
 *       Simulation Modelling Practice and Theory 15 (2007) 328–353 
 * .
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <
	typename RealT = double,
	typename PolicyT=::dcs::math::policies::policy<>
>
class pmpp_distribution
{
	private: typedef RealT real_type;
	public: typedef real_type support_type;
	public: typedef real_type value_type;
	public: typedef PolicyT policy_type;
	private: typedef exponential_distribution<real_type,policy_type> exponential_distribution_type;
	private: typedef pareto_distribution<real_type,policy_type> pareto_distribution_type;


	public: enum phase_category
	{
		first_phase = 0,
		second_phase = 1
	};


	public: pmpp_distribution(value_type phase1_rate,
							  value_type phase2_rate,
							  value_type phase_duration_shape,
							  value_type min_phase_duration,
							  phase_category initial_phase = first_phase)
	: phase1_rate_(phase1_rate),
	  phase2_rate_(phase2_rate),
	  phase_duration_shape_(phase_duration_shape),
	  min_phase_duration_(min_phase_duration),
	  cur_time_(0),
	  end_phase_time_(0),
	  cur_phase_(initial_phase),
	  phase1_arr_dist_(phase1_rate),
	  phase2_arr_dist_(phase2_rate),
	  phase_len_dist_(phase_duration_shape_,min_phase_duration)
	{
		// pre: phase1 arrival rate > 0
		DCS_ASSERT(
			phase1_rate > 0,
			throw ::std::invalid_argument("[dcs::math::stats::ppmp::ctor] Phase arrival rate must be a positive number.")
		);
		// pre: phase2 arrival rate > 0
		DCS_ASSERT(
			phase2_rate > 0,
			throw ::std::invalid_argument("[dcs::math::stats::ppmp::ctor] Phase arrival rate must be a positive number.")
		);
		// pre: phase duration shape > 0
		DCS_ASSERT(
			phase_duration_shape > 0,
			throw ::std::invalid_argument("[dcs::math::stats::ppmp::ctor] Phase duration shape must be a positive number.")
		);
		// pre: minimum phase duration > 0
		DCS_ASSERT(
			min_phase_duration > 0,
			throw ::std::invalid_argument("[dcs::math::stats::ppmp::ctor] Minimum phase duration must be a positive number.")
		);
	}


	public: value_type phase1_rate() const
	{
		return phase1_rate_;
	}


	public: value_type phase2_rate() const
	{
		return phase2_rate_;
	}


	public: value_type phase_duration_shape() const
	{
		return phase_duration_shape_;
	}


	public: value_type min_phase_duration() const
	{
		return min_phase_duration_;
	}


	/// Generate a randomly PPBP distributed variate.
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		if (cur_time_ >= end_phase_time_)
		{
			// Jump to the other phase.

			switch (cur_phase_)
			{
				case first_phase:
					DCS_DEBUG_TRACE("Changing phase: First -> Second.");
					cur_phase_ = second_phase;
					break;
				case second_phase:
					DCS_DEBUG_TRACE("Changing phase: Second -> First.");
					cur_phase_ = first_phase;
					break;
			}

			// Generate a new phase duration

			value_type duration(0);

			do
			{
				duration = phase_len_dist_.rand(rng);
			}
			while (duration < 0);

			DCS_DEBUG_TRACE("Generated new duration: " << duration);

			end_phase_time_ = duration;
			cur_time_ = value_type/*zero*/();
		}

		// Generate a new arrival inside current phase

//		value_type rate(0);
		exponential_distribution_type* ptr_phase_arr_dist;

		if (cur_phase_ == first_phase)
		{
//			rate = phase1_rate_;
			ptr_phase_arr_dist = &phase1_arr_dist_;
		}
		else
		{
//			rate = phase2_rate_;
			ptr_phase_arr_dist = &phase2_arr_dist_;
		}

		value_type iatime(0);

		do
		{
			iatime = ptr_phase_arr_dist->rand(rng);
		}
		while (iatime < 0);

		DCS_DEBUG_TRACE("Generated new interarrival time: " << iatime);

		value_type next_time(cur_time_+iatime);

		// Make sure next arrival remains inside this phase.
		if (next_time > end_phase_time_)
		{
			DCS_DEBUG_TRACE("New arrival will be at the end of this phase.");

			iatime = end_phase_time_-cur_time_;
			cur_time_ = end_phase_time_;
		}
		else
		{
			cur_time_ += iatime;
		}

		DCS_DEBUG_TRACE("Next arrival at time: " << iatime << " (phase: " << cur_phase_ << ", duration=" << end_phase_time_ << ", left=" << (end_phase_time_-cur_time_) << ")");

		return iatime;
	}


	/// Generate \a n randomly PPBP distributed variates.
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, ::std::size_t n)
	{
		::std::vector<support_type> sample(n);

		for (::std::size_t i = 0; i < n; ++i)
		{
			sample[i] = rand(rng);
		}

		return sample;
	}


	private: value_type phase1_rate_;
	private: value_type phase2_rate_;
	private: value_type phase_duration_shape_;
	private: value_type min_phase_duration_;
	private: mutable value_type cur_time_;
	private: mutable real_type end_phase_time_;
	private: mutable phase_category cur_phase_;
	private: mutable exponential_distribution_type phase1_arr_dist_;
	private: mutable exponential_distribution_type phase2_arr_dist_;
	private: mutable pareto_distribution_type phase_len_dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, pmpp_distribution<RealT,PolicyT> const& dist)
{
	return os << "PMPP("
			  << "phase1-rate=" <<  dist.phase1_rate()
			  << ", phase2-rate=" <<  dist.phase2_rate()
			  << ", phase-duration-shape=" <<  dist.phase_duration_shape()
			  << ", min-phase-duration=" <<  dist.min_phase_duration()
			  << ")";
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_PMPP_HPP
