/**
 * \file dcs/math/stats/distribution/weibull.hpp
 *
 * \brief The Weibull probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_WEIBULL_HPP
#define DCS_MATH_STATS_DISTRIBUTION_WEIBULL_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/weibull.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The Weibull distribution with shape parameter \f$k\f$ and scale
 *  parameter \f$\lambda\f$.
 *
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|k,\lambda)=\begin{cases} \frac{k}{\lambda}\left(\frac{x}{\lambda}\right)^{k-1}e^{-(x/\lambda)^{k}} & x\geq0\\ 0 & x<0\end{cases}
 * \f]
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class weibull_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit weibull_distribution(support_type shape, support_type scale=1)
		: dist_(shape, scale)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * weibull distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this weibull
	 * distribution.
	 *
	 * A \c weibull random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|k,\lambda)=\begin{cases} \frac{k}{\lambda}\left(\frac{x}{\lambda}\right)^{k-1}e^{-(x/\lambda)^{k}} & x\geq0\\ 0 & x<0\end{cases}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, support_type> eng(rng);

		return dist_.scale()*(::std::pow(-::std::log(eng()),value_type(1)/dist_.shape()));
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * weibull distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * weibull distribution.
	 *
	 * A \c weibull random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\lambda) = \lambda e^{-\lambda x}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, ::std::size_t n)
	{
		::std::vector<support_type> rnds(n);

        for ( ; n > 0; --n)
		{
			rnds.push_back(rand(rng));
		}

		return rnds;
	}


	public: support_type shape() const
	{
		return dist_.shape();
	}


	public: support_type scale() const
	{
		return dist_.scale();
	}


	public: support_type location() const
	{
		return support_type(0);
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


	private: ::boost::math::weibull_distribution<value_type,policy_type> dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, weibull_distribution<RealT,PolicyT> const& dist)
{
	return os << "Weibull("
			  << "shape=" <<  dist.shape()
			  << ", scale=" <<  dist.scale()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_WEIBULL_HPP
