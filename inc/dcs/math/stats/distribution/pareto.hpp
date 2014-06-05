/**
 * \file dcs/math/stats/distribution/pareto.hpp
 *
 * \brief The Pareto probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_PARETO_HPP
#define DCS_MATH_STATS_DISTRIBUTION_PARETO_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/pareto.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The Pareto distribution with shape parameter \f$\alpha\f$ and scale
 *  parameter \f$\beta\f$.
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|\lambda) = \frac{\alpha\,\beta^\alpha}{x^{\alpha+1}}, \quad
 *                    \text{ for }x>\beta
 * \f]
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class pareto_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit pareto_distribution(support_type shape=1, support_type scale=1)
		: dist_(shape, scale)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * pareto distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this pareto
	 * distribution.
	 *
	 * A \c pareto random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\alpha) = \frac{\alpha\,k^\alpha}{x^{\alpha+1}}, \quad
	 *                   \text{ for }x>k
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, support_type> eng(rng);

		// Use the inversion method:
    	//    x=\frac{k}{(1-p)^{1/\alpha}}
    	// => x=k(1-p)^{-1/\alpha}
    	// => x=ku^{-1/\alpha}, where u is a uniform random number in [0,1)

#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(104000)
		return dist_.scale()*::std::pow(value_type(1)-eng(), -value_type(1)/dist_.shape());
//		return dist_.scale()*::std::pow(eng(), -value_type(1)/dist_.shape());
#else
		return dist_.location()*::std::pow(value_type(1)-eng(), -value_type(1)/dist_.shape());
//		return dist_.location()*::std::pow(eng(), -value_type(1)/dist_.shape());
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * pareto distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * pareto distribution.
	 *
	 * A \c pareto random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\lambda) = \frac{\alpha\,\beta^\alpha}{x^{\alpha+1}}, \quad
	 *                    \text{ for }x>\beta
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, ::std::size_t n)
	{
		::std::vector<support_type> rnds(n);

        for ( ; n > 0; --n)
		{
			rnds.push_back(rand());
		}

		return rnds;
	}


	public: support_type shape() const
	{
		return dist_.shape();
	}


	public: support_type scale() const
	{
#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(104000)
		return dist_.scale();
#else
		return dist_.location();
#endif // DCS_DETAIL_CONFIG_BOOST_VERSION
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


	public: value_type mean() const
	{
#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(104000)
		return dist_.scale()*dist_.shape()/(dist_.shape()-1);
#else
		return dist_.location()*dist_.shape()/(dist_.shape()-1);
#endif // DCS_DETAIL_CONFIG_BOOST_VERSION
	}


	public: value_type variance() const
	{
#if DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(104000)
		return dist_.scale()*dist_.scale()*dist_.shape()/((dist_.shape()-1)*(dist_.shape()-2));
#else
		return dist_.location()*dist_.location()*dist_.shape()/((dist_.shape()-1)*(dist_.shape()-2));
#endif // DCS_DETAIL_CONFIG_BOOST_VERSION
	}


	private: ::boost::math::pareto_distribution<value_type,policy_type> dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, pareto_distribution<RealT,PolicyT> const& dist)
{
	return os << "Pareto("
			  << "shape=" <<  dist.shape()
			  << ", scale=" <<  dist.scale()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_PARETO_HPP
