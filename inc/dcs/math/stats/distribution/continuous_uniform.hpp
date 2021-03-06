/**
 * \file dcs/math/stats/distribution/continuous_uniform.hpp
 *
 * \brief The \c continuous_uniform distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_CONTINUOUS_UNIFORM_HPP
#define DCS_MATH_STATS_DISTRIBUTION_CONTINUOUS_UNIFORM_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost libraries version >= 1.15."
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION

#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

using ::std::size_t;


/**
 * \brief The continuous uniform distribution with parameter \f$a\f$ (the
 * minimum value) and \f$b\f$ (the maximum value).
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class continuous_uniform_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit continuous_uniform_distribution(support_type a=0.0, support_type b=1.0)
		: a_(a),
		  b_(b)
	{
		// empty
	}


//	public: void reset()
//	{
//		impl_.reset();
//	}


    /**
	 * \brief Generate a random number distributed according to this continuous
	 * uniform distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this continuous uniform
	 * distribution.
	 *
	 * A \c continuous_uniform random number distribution produces random
	 * numbers * \f$x\f$, \f$a \le x \le b\f$, distributed according to the
	 * constant probability density function:
	 * \f[
	 *   \Pr(x|a,b) = \frac{1}{(b - a)}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
        typedef ::boost::uniform_real<support_type> rdist_type;
        typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

        return variate_type(rng, rdist_type(a_, b_))();
	}


    /**
	 * \brief Generate a vector of random numbers distributed according to this
	 * continuous uniform distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * continuous uniform distribution.
	 *
	 * A \c continuous_uniform random number distribution produces random
	 * numbers * \f$x\f$, \f$a \le x \le b\f$, distributed according to the
	 * constant probability density function:
	 * \f[
	 *   \Pr(x|a,b) = \frac{1}{(b - a)}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		::std::vector<support_type> rand(UniformRandomGeneratorT& rng, size_t n)
	{
        typedef ::boost::uniform_real<support_type> rdist_type;
        typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

		::std::vector<support_type> rnds(n);

        for ( ; n > 0; --n)
		{
			rnds.push_back(variate_type(rng, rdist_type(a_, b_))());
		}

		return rnds;
	}


	public: support_type min() const
	{
		return a_;
	}


	public: support_type max() const
	{
		return b_;
	}


	public: support_type scale() const
	{
		return (b_-a_);
	}


	public: support_type location() const
	{
		return a_;
	}


	private: support_type a_;
	private: support_type b_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, continuous_uniform_distribution<RealT,PolicyT> const& dist)
{
	return os << "CUniform("
			  << "min=" <<  dist.min()
			  << ", max=" <<  dist.max()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_CONTINUOUS_UNIFORM_HPP
