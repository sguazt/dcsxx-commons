/**
 * \file dcs/math/stats/distribution/students_t.hpp
 *
 * \brief The Student's t distribution.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_STUDENTS_T_HPP
#define DCS_MATH_STATS_DISTRIBUTION_STUDENTS_T_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(103500) // 1.35
# 	error "Required Boost library version >= 1.35"
#endif

#include <boost/math/distributions/students_t.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/stats/distribution/chi_squared.hpp>
#include <dcs/math/stats/distribution/normal.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

using ::std::size_t;


/**
 * \brief The Student's t distribution with parameter \f$\nu\f$ (the degrees of
 *  freedom).
 *
 * \tparam RealT The type used for real numbers.
 * \tparam PolicyT The policy type.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template < typename RealT=double, typename PolicyT=::dcs::math::policies::policy<> >
class students_t_distribution
{
	public: typedef RealT support_type;
	public: typedef RealT value_type;
	public: typedef PolicyT policy_type;

	public: explicit students_t_distribution(support_type df)
		: dist_(df)
	{
		// empty
	}


	// compiler-generated copy ctor and assignment operator are fine


	/**
	 * \brief Generate a vector of random numbers distributed according to this
	 * Student's t distribution.
	 *
	 * \param rng A uniform random number generator.
	 * \param n The number of random numbers to generate.
	 * \return A random number distributed according to this Student's t
	 * distribution.
	 *
	 * A \c Student's t random number distribution produces random numbers * \f$x\f$
	 * distributed according to the probability density function:
	 * \f[
	 *   \frac{\Gamma(\frac{\nu+1}{2})} {\sqrt{\nu\pi}\,\Gamma(\frac{\nu}{2})} \left(1+\frac{x^2}{\nu} \right)^{-(\frac{\nu+1}{2})}
	 * \f]
	 */
	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		normal_distribution<value_type> norm;
		chi_squared_distribution<value_type> chi(dist_.degrees_of_freedom());
		return	::dcs::math::stats::rand(norm, rng)
				/ ::std::sqrt(
						::dcs::math::stats::rand(chi, rng)
						/ dist_.degrees_of_freedom()
					);
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
		::std::vector<support_type> rnds(n);

		for ( ; n > 0; --n)
		{
			rnds.push_back(rand(rng));
		}

		return rnds;
	}
//@}TODO


	public: support_type degrees_of_freedom() const
	{
		return dist_.degrees_of_freedom();
	}


	public: support_type location() const
	{
		return support_type(0);
	}


	public: support_type scale() const
	{
		return support_type(1);
	}


	public: support_type quantile(value_type p) const
	{
		return ::boost::math::quantile(dist_, p);
	}


	private: ::boost::math::students_t_distribution<value_type,policy_type> dist_;
};


template <
    typename CharT,
    typename CharTraitsT,
    typename RealT,
    typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, students_t_distribution<RealT,PolicyT> const& dist)
{
    return os << "StudentT("
              << "df=" <<  dist.degrees_of_freedom()
              << ")";
}

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_STUDENTS_T_HPP
