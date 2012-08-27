/**
 * \file dcs/math/stats/distribution/erlang.hpp
 *
 * \brief The Erlang probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_ERLANG_HPP
#define DCS_MATH_STATS_DISTRIBUTION_ERLANG_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/gamma.hpp>
//#include <boost/random/gamma_distribution.hpp>
#include <cstddef>
#include <dcs/math/function/round.hpp>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/stats/distribution/continuous_uniform.hpp>
//TODO
//#include <dcs/math/random/any_generator.hpp>
//#include <dcs/math/random/base_generator.hpp>
#include <iosfwd>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The Erlang distribution with shape parameter \f$k\f$ and rate
 * parameter \f$\lambda\f$.
 *
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The Erlang distribution is a special case of the Gamma distribution where
 * the shape parameter \f$k\f$ is an integer and the scale parameter is the
 * inverse rate \f$1/\lambda\f$.
 * In the Gamma distribution, this parameter is not restricted to the integers.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|k,\lambda) = \lambda^k x^{k-1} e^{-\lambda x} \over (k-1)!, \quad\text{for }x,\lambda\ge 0. 
 * \f]
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class erlang_distribution//TODO>>: public base_distribution<RealT>
{
	private: typedef erlang_distribution<RealT,PolicyT> self_type;
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;
	private: typedef ::boost::math::gamma_distribution<value_type, policy_type> distribution_type;
//	private: typedef ::boost::random::gamma_distribution<support_type> variate_generator_type;


	public: explicit erlang_distribution(support_type k, support_type lambda=1)
		: dist_(::dcs::math::round(k), 1.0/lambda)
//		  variate_(::dcs::math::round(k), 1.0/lambda)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * erlang distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this erlang
	 * distribution.
	 *
	 * A \c erlang random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|k,\lambda) = \lambda^k x^{k-1} e^{-\lambda x} \over (k-1)!
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
//		// Alt #1: use Gamma
//		return const_cast<self_type*>(this)->variate_(rng);
//
//		// Alt #2 Erlang is the sum of 'stages' independent Exp(myrate)
//		// ALt #2.1: Naive implementation
//		value_type s(0);
//		value_type invrate(scale());
//		::std::size_t nstages(static_cast< ::std::size_t >(shape()));
//		continuous_uniform_distribution<value_type,policy_type> runif;
//
//		for (int i = 0; i < nstages; ++i)
//		{
//			s += -invrate*std::log(runif.rand(rng));
//		}
		// ALt #2.2: Possibly optimized implementation (\sum\log{x_i} == \log\prod{x_i})
		value_type r(1);
		continuous_uniform_distribution<value_type,policy_type> runif;

		for (int i = 0; i < shape(); ++i)
		{
			r *= 1-runif.rand(rng);
		}
		return -scale()*::std::log(r);
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * erlang distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * erlang distribution.
	 *
	 * A \c erlang random number distribution produces random numbers
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


	public: support_type k() const
	{
		return dist_.shape();
	}


	public: support_type lambda() const
	{
		return 1.0/dist_.scale();
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


//TODO
//	private: support_type do_rand(::dcs::math::random::base_generator<value_type>& rng) const
//	{
//		typedef ::boost::erlang_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;
//
//		return variate_type(rng, rdist_type(dist_.lambda()))();
//	}


//TODO
//	private: support_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const
//	{
//		typedef ::boost::erlang_distribution<support_type> rdist_type;
//		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;
//
//		return variate_type(rng, rdist_type(dist_.lambda()))();
//	}


	private: distribution_type dist_;
//	private: variate_generator_type variate_;
};


template <
    typename CharT,
    typename CharTraitsT,
    typename RealT,
    typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, erlang_distribution<RealT,PolicyT> const& dist)
{
	return os << "Erlang("
			  << "k=" <<  dist.k()
			  << "lambda=" <<  dist.lambda()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_ERLANG_HPP
