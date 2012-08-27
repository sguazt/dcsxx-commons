/**
 * \file dcs/math/stats/distribution/bounded_pareto.hpp
 *
 * \brief The Bounded Pareto probability distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_BOUNDED_PARETO_HPP
#define DCS_MATH_STATS_DISTRIBUTION_BOUNDED_PARETO_HPP


#include <cmath>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

/**
 * \brief The Bounded Pareto distribution with shape parameter \f$\alpha\f$, and
 *  location parameters \f$L\f$ and \f$H\f$.
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * The bounded Pareto distribution has three parameters \f$\alpha\f$, \f$L\f$
 * and \f$H\f$.
 * As in the standard Pareto distribution \f$\alpha\f$ determines the shape.
 * \f$L\f$ denotes the minimal value, and \f$H\f$ denotes the maximal value.
 *
 * The probability density function (pdf):
 * \f[
 *   \Pr(x|\alpha,L,H) = \frac{\alpha L^\alpha x^{-\alpha - 1}}{1-\left(\frac{L}{H}\right)^\alpha}
 * \f]
 *
 * \author Cosimo Anglano, &lt;cosimo.anglano@mfn.unipmn.it&gt;
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class bounded_pareto_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit bounded_pareto_distribution(support_type shape, support_type min, support_type max)
		: shape_(shape),
		  min_(min),
		  max_(max)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a random number distributed according to this
	 * bounded_pareto distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \return A random number distributed according to this bounded_pareto
	 * distribution.
	 *
	 * A \c bounded_pareto random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\alpha,L,H) = \frac{\alpha L^\alpha x^{-\alpha - 1}}{1-\left(\frac{L}{H}\right)^\alpha}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&, support_type> eng(rng);

		// Use the inversion method:
		//   x=\frac{L}{\sqrt[\alpha]{1-u\left(1-\left(\frac{L}{H}\right)^{\alpha}\right)}}

		return min_ / ::std::pow(value_type(1) - eng()*(value_type(1)-::std::pow(min_/max_, shape_)), value_type(1)/shape_);
	}


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * bounded_pareto distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A vector of random numbers distributed according to this
	 * bounded_pareto distribution.
	 *
	 * A \c bounded_pareto random number distribution produces random numbers
	 * \f$x > 0\f$ distributed according to the probability density function:
	 * \f[
	 *   \Pr(x|\alpha,L,H) = \frac{\alpha L^\alpha x^{-\alpha - 1}}{1-\left(\frac{L}{H}\right)^\alpha}
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
		return shape_;
	}


	public: support_type min() const
	{
		return min_;
	}


	public: support_type max() const
	{
		return max_;
	}


	public: support_type location() const
	{
		return support_type(min_);
	}


//	public: support_type quantile(value_type p) const
//	{
//		return ::boost::math::quantile(dist_, p);
//	}


	private: support_type shape_;
	private: support_type min_;
	private: support_type max_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, bounded_pareto_distribution<RealT,PolicyT> const& dist)
{
	return os << "BoundedPareto("
			  << "shape=" <<  dist.shape()
			  << ", min=" << dist.min()
			  << ", max=" << dist.max()
			  << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_BOUNDED_PARETO_HPP
