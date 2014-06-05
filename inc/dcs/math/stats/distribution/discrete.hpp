/**
 * \file dcs/math/stats/distribution/discrete.hpp
 *
 * \brief Empirical discrete probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_DISCRETE_HPP
#define DCS_MATH_STATS_DISTRIBUTION_DISCRETE_HPP


#include <algorithm>
#include <cstddef>
#include <dcs/algorithm/order.hpp>
#include <dcs/assert.hpp>
#include <dcs/functional/bind.hpp>
//#include <dcs/iterator/any_forward_iterator.hpp>
//#include <dcs/iterator/iterator_range.hpp>
#include <dcs/math/policies.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <functional>
#include <iostream>
#include <vector>


#if __cplusplus > 201103L
// C++0x has its own implementation
#   include <random>
#	define DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
#   define DCS_MATH_STATS_DISTRIBUTION_DISCRETE_NS_ ::std
#elif DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(104500)
// Use Boost implementation
#	include <dcs/detail/config/boost.hpp>
#	include <boost/random/discrete_distribution.hpp>
#	define DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
#	define DCS_MATH_STATS_DISTRIBUTION_DISCRETE_NS_ ::boost::random
#endif // __cplusplus


namespace dcs { namespace math { namespace stats {

/**
 * \c Empirical discrete probability distribution.
 *
 * An empirical discrete distribution is an observed relative frequency
 * distribution that one intends to use to approximate the probabilities of a
 * random variable [1].
 * A discrete_distribution is modeled as a set of events \f$i\f$,
 * \f$0 \le i < n\f$, distributed according to the discrete probability function
 * \f[
 *   \Pr(i | p_0, \ldots , p_{n-1}) = p_i
 * \f]
 * Unless specified otherwise, the distribution parameters are calculated as:
 * \f[
 *   p_k = \frac{w_k}{S}, \quad for k = 0,\ldots, n-1
 * \f]
 * in which the values \f$w_k\f$ , commonly known as the \e weights, shall be
 * non-negative, non-NaN, and non-infinity.
 * Moreover, the following relation shall hold:
 * \f[
 *   0 < S = w_0 + \cdots + w_{n-1}
 * \f]
 *
 * References:
 * - [1] Carver et al. "Doing data analysis with SPSS version 16",
 *       Brooks/Cole, 4th edition, 2009
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <
	typename RealT=double,
	typename PolicyT=::dcs::math::policies::policy<>
>
class discrete_distribution
{

	public: typedef PolicyT policy_type;
	public: typedef RealT value_type;
	public: typedef value_type support_type;
	public: typedef ::std::size_t int_type;
	//private: typedef ::std::vector<value_type> events_container;
	private: typedef ::std::vector<value_type> probs_container;


	/**
 	 * \brief Constructs a discrete distribution object with \f$n = 1\f$ and
 	 * \f$p_0 = 1\f$.
 	 */
	public: discrete_distribution()
#ifdef DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	: impl_(),
	  probs_(impl_.probabilities()),
	  cum_probs_(probs_)
	{
	}
#else // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	{
		probs_.push_back(1);
		cum_probs_.push_back(1);
	}
#endif // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_


	/// A constructor.
	public: template <typename WeightIteratorT>
		discrete_distribution(WeightIteratorT first_weight, WeightIteratorT last_weight)
#ifdef DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	: impl_(first_weight, last_weight),
	  probs_(impl_.probabilities())
	{
		// Compute CDF
		typedef typename probs_container::const_iterator iterator;
		value_type cum_probs_sum(0);
		iterator it_end = probs_.end();
		for (iterator it = probs_.begin(); it != it_end; ++it)
		{
			cum_probs_sum += *it;
			cum_probs_.push_back(cum_probs_sum);
		}
	}
#else // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	{
		// 1. Create the probability table and
		// 2. Make sure the size of events and probabilities container
		//    complains, and
		// 3. Reorder the probability table according to the events (this help
		//    us to compute the CDF), and
		// 4. Make sure probabilities sum t

		value_type weights_sum(0);

		// Create PDF
		for (WeightIteratorT it = first_weight;
			 it != last_weight;
			 ++it)
		{
			probs_.push_back(*it);
			weights_sum += *it;
		}

		// Normalize PDF and compute CDF
		value_type cum_probs_sum(0);
		for (typename probs_container::iterator it = probs_.begin();
			 it != probs_.end();
			 ++it)
		{
			// Normalize probability
			*it /= weights_sum;

			// Compute CDF
			cum_probs_sum += *it;
			cum_probs_.push_back(cum_probs_sum);
		}
	}
#endif // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_


	public: ::std::vector<value_type> probabilities() const
	{
		return probs_;
	}


//	///\todo: Avoid using const_cast.
//	public: ::dcs::iterator::iterator_range< ::dcs::iterator::any_forward_iterator<value_type> > probabilities() const
//	{
//
//		return ::dcs::iterator::make_iterator_range(
//			::dcs::iterator::make_any_forward_iterator(const_cast<discrete_distribution*>(this)->probs_.begin()),
//			::dcs::iterator::make_any_forward_iterator(const_cast<discrete_distribution*>(this)->probs_.end())
//		);
//	}


	/// Return the PDF
	public: ::std::vector<value_type> pdf() const
	{
		return probs_;
	}


	/// Compute the PDF for the given value.
	public: value_type pdf(int_type x) const
	{
		if (x >= probs_.size())
		{
			return 0;
		}

		return probs_[x];
	}


	/// Return the CDF
	public: ::std::vector<value_type> cdf() const
	{
		return cum_probs_;
	}


	/// Compute the CDF for the given value.
	public: value_type cdf(int_type x) const
	{
//		if (x < 0) // this may cause a warning when int_type is an unsigned type
		if ((x+1) < 1) // this is a trick to prevent a warning in case int_type is an unsigned type
		{
			return 0;
		}

		if (x >= cum_probs_.size())
		{
			return 1;
		}

		return cum_probs_[x];
	}


	// Compute the quantile value corresponding to the given probability value.
	public: int_type quantile(value_type p) const
	{
		typename probs_container::const_iterator it;

		it = ::std::find_if(
			cum_probs_.begin(),
			cum_probs_.end(),
			::dcs::functional::bind(
				::std::greater_equal<value_type>(),
				::dcs::functional::placeholders::_1,
				p
			)
		);

		if (it == cum_probs_.end())
		{
			return cum_probs_.size()-1;
		}

		return it-cum_probs_.begin();
	}


	/// Generate a random variate distributed according to this distribution and
	/// generated by means of the given uniform random number generator.
	public: template <typename UniformRandomGeneratorT>
		value_type rand(UniformRandomGeneratorT& rng) const
	{
#ifdef DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
		return impl_(rng);
#else // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, value_type> u01_rng(rng);

		return quantile(u01_rng());
#endif // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	}


//	/// The events container.
#ifdef DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
	/// The implementing object
	private: DCS_MATH_STATS_DISTRIBUTION_DISCRETE_NS_::discrete_distribution<int_type,value_type> impl_;
#endif // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL_
//	private: events_container events_;
	/// The probabilities container.
	private: probs_container probs_;
	/// The cumulative probabilities container.
	private: probs_container cum_probs_;
};


#ifndef DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL

template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, discrete_distribution<RealT,PolicyT> const& dist)
{
	os << "Discrete(";

	::std::vector<RealT> probs = dist.probabilities();
	::std::size_t size = probs.size();
	for (::std::size_t i = 0; i < size; ++i)
	{
		if (i > 0)
		{
			os << ",";
		}
		os << "p_" << i << "=" << probs[i];
	}
	os << ")";

	return os;
}

#endif // DCS_MATH_STATS_DISCRETE_DISTRIBUTION_HAVE_IMPL

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_DISCRETE_HPP
