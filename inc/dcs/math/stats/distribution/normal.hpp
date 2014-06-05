/**
 * \file dcs/math/stats/distribution/normal.hpp
 *
 * \brief The Normal probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_NORMAL_HPP
#define DCS_MATH_STATS_DISTRIBUTION_NORMAL_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/normal.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

using ::std::size_t;


/**
 * The Normal distribution with parameter \f$\mu\f$ (the mean) and \f$\sigma\f$
 * (the standard deviation).
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class normal_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit normal_distribution(support_type mean=0, support_type stddev=1)
		: dist_(mean,stddev)
//		: mean_(mean),
//		  stddev_(stddev)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * normal distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A random number distributed according to this normal
	 * distribution.
	 *
	 * A \c normal random number distribution produces random numbers * \f$x\f$
	 * distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\mu,\sigma) = \frac{1}{\sigma\sqrt{2\pi}}\exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		typedef ::boost::normal_distribution<support_type> rdist_type;
		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

		return variate_type(rng, rdist_type(dist_.mean(), dist_.standard_deviation()))();
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * normal distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * normal distribution.
	 *
	 * A \c normal random number distribution produces random numbers * \f$x\f$
	 * distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\mu,\sigma) = \frac{1}{\sigma\sqrt{2\pi}}\exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, size_t n)
	{
		typedef ::boost::normal_distribution<support_type> rdist_type;
        typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

		::std::vector<support_type> rnds(n);

        for ( ; n > 0; --n)
		{
			rnds.push_back(variate_type(rng, rdist_type(dist_.mean(), dist_.standard_deviation()))());
		}

		return rnds;
	}


	public: support_type mean() const
	{
		return dist_.mean();
	}


	public: support_type stddev() const
	{
		return dist_.standard_deviation();
	}


	public: support_type location() const
	{
		return dist_.location();
	}


	public: support_type scale() const
	{
		return dist_.scale();
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


	//private: support_type mean_;
	//private: support_type stddev_;
	private: ::boost::math::normal_distribution<value_type,policy_type> dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, normal_distribution<RealT,PolicyT> const& dist)
{
	return os << "Normal("
			  << "mean=" <<  dist.mean()
			  << ", stddev=" <<  dist.stddev()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_NORMAL_HPP
