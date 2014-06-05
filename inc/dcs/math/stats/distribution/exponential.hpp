/**
 * \file dcs/math/stats/distribution/exponential.hpp
 *
 * \brief The (Negative) Exponential probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_EXPONENTIAL_HPP
#define DCS_MATH_STATS_DISTRIBUTION_EXPONENTIAL_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/exponential.hpp>
#include <boost/random/exponential_distribution.hpp>
//#include <boost/random/variate_generator.hpp>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
//TODO
//#include <dcs/math/random/any_generator.hpp>
//#include <dcs/math/random/base_generator.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The (Negative) Exponential distribution with rate parameter
 * \f$\lambda\f$.
 *
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|\lambda) = \lambda e^{-\lambda x}
 * \f]
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class exponential_distribution//TODO>>: public base_distribution<RealT>
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit exponential_distribution(support_type lambda=1)
		: dist_(lambda)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * exponential distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this exponential
	 * distribution.
	 *
	 * A \c exponential random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\lambda) = \lambda e^{-\lambda x}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		typedef ::boost::exponential_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;
//
//		return variate_type(rng, rdist_type(dist_.lambda()))();
		return rdist_type(dist_.lambda())(rng);
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * exponential distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * exponential distribution.
	 *
	 * A \c exponential random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\lambda) = \lambda e^{-\lambda x}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, ::std::size_t n)
	{
		typedef ::boost::exponential_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

		::std::vector<support_type> rnds(n);
		rdist_type rvg(dist_.lambda());

		for (; n > 0; --n)
		{
//			rnds.push_back(variate_type(rng, rdist_type(dist_.lambda()))());
			rnds.push_back(rvg(rng));
		}

		return rnds;
	}


	public: support_type lambda() const
	{
		return dist_.lambda();
	}


	public: support_type scale() const
	{
		return support_type(1)/dist_.lambda();
	}


	public: support_type location() const
	{
		return support_type(0);
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


//TODO
//	private: support_type do_rand(::dcs::math::random::base_generator<value_type>& rng) const
//	{
//		typedef ::boost::exponential_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;
//
//		return variate_type(rng, rdist_type(dist_.lambda()))();
//	}


//TODO
//	private: support_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const
//	{
//		typedef ::boost::exponential_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;
//
//		return variate_type(rng, rdist_type(dist_.lambda()))();
//	}


	private: ::boost::math::exponential_distribution<value_type,policy_type> dist_;
};


template <
    typename CharT,
    typename CharTraitsT,
    typename RealT,
    typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, exponential_distribution<RealT,PolicyT> const& dist)
{
	return os << "Exp("
			  << "lambda=" <<  dist.lambda()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_EXPONENTIAL_HPP
