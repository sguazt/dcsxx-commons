/**
 * \file dcs/math/stats/distribution/gamma.hpp
 *
 * \brief The Gamma probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_GAMMA_HPP
#define DCS_MATH_STATS_DISTRIBUTION_GAMMA_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/gamma.hpp>
//#include <boost/random/gamma_distribution.hpp>
//#include <boost/random/variate_generator.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
//#include <dcs/math/stats/distribution/detail/rgamma.cpp>
//#include <dcs/math/constants.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

namespace detail {

} // Namespace detail


/**
 * \brief The Gamma distribution with shape parameter \f$k\f$ and scale
 *  parameter \f$\theta\f$.
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|k,\theta) = x^{k-1} \frac{\exp{\left(-x/\theta\right)}}{\Gamma(k)\,\theta^k}
 * \f]
 *
 * \author Cosimo Anglano, &lt;cosimo.anglano@mfn.unipmn.it&gt;
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class gamma_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit gamma_distribution(support_type shape, support_type scale=1)
		: dist_(shape, scale)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * gamma distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this gamma
	 * distribution.
	 *
	 * A \c gamma random number distribution produces random numbers
	 * \f$x \ge 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|k,\theta) = x^{k-1} \frac{\exp{\left(-x/\theta\right)}}{\Gamma(k)\,\theta^k}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
/* Don't work: Actually (2010-01-21), Boost uses Gamma with only the parameter
 * shape. In principle this wouldn't be a problem since we may use the scaling
 * property gamma_rand(a,b)==b*gamma_rand(a); but for shape==1, it uses
 * Exp(rng()) which is wrong when b!=1 since Gamma(1,b) ~ Exp(1/b)
 *
		typedef ::boost::gamma_distribution<support_type> rdist_type;
		typedef ::boost::variate_generator<UniformRandomGeneratorT&, rdist_type> variate_type;

		return dist_.scale() * variate_type(rng, rdist_type(dist_.shape()))();
*/
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, support_type> eng(rng);
		value_type r(0);
		//value_type ishape = static_cast<unsigned long>(dist_.shape()); // Not safe
		value_type ishape = ::std::floor(dist_.shape());

		if (dist_.shape() >= value_type(1))
		{
			value_type acc(0);
			for (::std::size_t i = 0; i < ishape; ++i)
			{
				acc += ::std::log(eng());
			}
			r += -acc;
		}
		value_type diff = dist_.shape()-ishape;
		if (diff > 0)
		{
/*
			// Acceptance-rejection method (see: http://en.wikipedia.org/wiki/Gamma_distribution#Generating_gamma-distributed_random_variables)

			value_type v0 = ::dcs::math::constants::e<value_type>::value/(::dcs::math::constants::e<value_type>::value + diff);

			value_type csi;
			value_type eta;

			do
			{
				value_type u1 = eng();
				value_type u2 = eng();
				value_type u3 = eng();

				if (u1 <= v0)
				{
					csi = ::std::pow(u2, value_type(1)/diff);
					eta = u3*::std::pow(csi, diff-value_type(1));
				}
				else
				{
					csi = value_type(1)-::std::log(u2);
					eta = u3*::std::exp(-csi);
				}

			}
			while (eta > (::std::pow(eta, diff-value_type(1))*::std::exp(-csi)));
				
			r = (csi - r);
*/

			// this is the original code taken from rnd.cc (Anglano, 2005).
			value_type x;
			value_type y;

			do {
				value_type u1 = eng();
				value_type u2 = eng();
				x = ::std::pow(u1, value_type(1)/diff);
				y = ::std::pow(u2, value_type(1)/dist_.scale());
			} while ((x+y)>1);

			x = (x/(x+y));
			y = -::std::log(eng());

			r += x*y;
		}
		return dist_.scale()*r;

/*
		// This uses a function coming from R
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, support_type> eng(rng);
		return detail::rgamma(dist_.shape(), dist_.scale(), eng);
*/
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * gamma distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * gamma distribution.
	 *
	 * A \c gamma random number distribution produces random numbers
	 * \f$x \ge 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|k,\theta) = x^{k-1} \frac{\exp{\left(-x/\theta\right)}}{\Gamma(k)\,\theta^k}
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


	private: ::boost::math::gamma_distribution<value_type,policy_type> dist_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, gamma_distribution<RealT,PolicyT> const& dist)
{
	return os << "Gamma("
			  << "shape=" <<  dist.shape()
			  << ", scale=" <<  dist.scale()
			  << ")";
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_GAMMA_HPP
