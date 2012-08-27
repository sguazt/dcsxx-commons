/**
 * \file dcs/math/stats/distribution/mmpp.hpp
 *
 * \brief Markov-modulated Poisson Process (MMPP).
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_MMPP_HPP
#define DCS_MATH_STATS_DISTRIBUTION_MMPP_HPP


#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublasx/operation/diag.hpp>
#include <cstddef>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/stats/distribution/base_distribution.hpp>
#include <dcs/math/stats/distribution/map.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <iostream>
#include <vector>


namespace dcs { namespace math { namespace stats {

template <
	typename RealT = double,
	typename PolicyT = ::dcs::math::policies::policy<>
>
class mmpp_distribution//: public base_distribution<RealT>
{
	public: typedef RealT value_type;
	public: typedef value_type support_type;
	public: typedef ::boost::numeric::ublas::matrix<support_type> matrix_type;
	public: typedef ::boost::numeric::ublas::vector<support_type> vector_type;
	public: typedef ::std::size_t size_type;
	private: typedef map_distribution<RealT,PolicyT> map_distribution_type;


	public: template <typename VectorExprT, typename MatrixExprT>
		mmpp_distribution(::boost::numeric::ublas::vector_expression<VectorExprT> const& lambda,
						 ::boost::numeric::ublas::matrix_expression<MatrixExprT> const& Q)
	: //base_type(),
	  map_(Q-::boost::numeric::ublasx::diag(lambda), ::boost::numeric::ublasx::diag(lambda))
	{
	}


	// Compiler-generated copy-constructor, copy-assignment, and destructor
	// are fine.


	public: vector_type lambda() const
	{
		return ::boost::numeric::ublasx::diag(map_.D1());
	}


	public: matrix_type Q() const
	{
		return map_.D0()+map_.D1();
	}


/*
	private: value_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const
	{
		return rand_sample(rng);
	}

	private: value_type do_rand(::dcs::math::random::base_generator<value_type>& rng) const
	{
		return rand_sample(rng);
	}
*/

	public: template <typename URNG>
		value_type rand(URNG& rng) const
	{
		return map_.rand(rng);
	}


	/**
	 * The following algorithm is an adaptation of the one found in the MMPP-QN
	 * toolbox (by G. Casale et al, http://www.cs.wm.edu/MMPPQN/).
	 */
	public: template <typename URNG>
		::std::vector<value_type> rand(URNG& rng, size_type n) const
	{
		return map_.rand(rng, n);
	}


	private: map_distribution_type map_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, mmpp_distribution<RealT,PolicyT> const& dist)
{
	return os << "MMPP("
			  << "lambda=" <<  dist.lambda()
			  << ",Q=" <<  dist.Q()
			  << ")";
}

}}} // Namespace dcs:math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_MMPP_HPP
