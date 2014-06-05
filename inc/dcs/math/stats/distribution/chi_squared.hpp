/**
 * \file dcs/math/stats/distribution/chi_squared.hpp
 *
 * \brief The (Negative) Chi Squared probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_CHI_SQUARED_HPP
#define DCS_MATH_STATS_DISTRIBUTION_CHI_SQUARED_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/chi_squared.hpp>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/stats/distribution/gamma.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The Chi Squared distribution with degrees of freedom parameter
 * \f$\nu\f$.
 *
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|\nu) = \frac{1}{2^{k/2}\Gamma(k/2)}\; x^{k/2-1} e^{-x/2}
 * \f]
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class chi_squared_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit chi_squared_distribution(support_type df)
		: dist_(df)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * chi_squared distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this chi_squared
	 * distribution.
	 *
	 * A \c chi_squared random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\nu) = \frac{1}{2^{k/2}\Gamma(k/2)}\; x^{k/2-1} e^{-x/2}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		return ::dcs::math::stats::rand(
			gamma_distribution<value_type>(
				dist_.degrees_of_freedom()/value_type(2),
				value_type(2)
			),
			rng
		);
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * chi_squared distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * chi_squared distribution.
	 *
	 * A \c chi_squared random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\nu) = \frac{1}{2^{k/2}\Gamma(k/2)}\; x^{k/2-1} e^{-x/2}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, ::std::size_t n) const
	{
		::std::vector<support_type> rnds(n);

        for ( ; n > 0; --n)
		{
			rnds.push_back(
				::dcs::math::stats::rand(
					gamma_distribution<value_type>(
						dist_.degrees_of_freedom()/value_type(2),
						value_type(2)
					),
					rng
				)
			);
		}

		return rnds;
	}


	public: support_type degrees_of_freedom() const
	{
		return dist_.degrees_of_freedom();
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


	private: ::boost::math::chi_squared_distribution<value_type,policy_type> dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, chi_squared_distribution<RealT,PolicyT> const& dist)
{
	return os << "ChiSquared("
			  << "df=" <<  dist.degrees_of_freedom()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_CHI_SQUARED_HPP
