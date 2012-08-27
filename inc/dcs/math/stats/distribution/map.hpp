/**
 * \file dcs/math/stats/distribution/map.hpp
 *
 * \brief Markov Arrival Process (MAP).
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_MAP_HPP
#define DCS_MATH_STATS_DISTRIBUTION_MAP_HPP


#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublasx/operation/abs.hpp>
#include <boost/numeric/ublasx/operation/cumsum.hpp>
#include <boost/numeric/ublasx/operation/diag.hpp>
#include <boost/numeric/ublasx/operation/inv.hpp>
#include <boost/numeric/ublasx/operation/lu.hpp>
#include <boost/numeric/ublasx/operation/max.hpp>
#include <boost/numeric/ublasx/operation/num_columns.hpp>
#include <boost/numeric/ublasx/operation/num_rows.hpp>
#include <boost/numeric/ublasx/operation/sum.hpp>
#include <boost/numeric/ublasx/operation/which.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/math/policies/policy.hpp>
#include <dcs/math/stats/distribution/base_distribution.hpp>
#include <dcs/math/stats/distribution/exponential.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
//#include <dcs/math/random/uniform_int_adaptor.hpp>
#include <functional>
#include <iostream>
#include <vector>
#include <stdexcept>


namespace dcs { namespace math { namespace stats {

namespace detail { namespace /*<unnamed>*/ {

/**
 * \brief Equilibrium distribution of a continuous-time Markov chain (CTMC).
 * \param Q Infinitesimal generator of the CTMC.
 * \return The equilibrium distribution of the CTMC.
 *
 * Solve the following system:
 * \f{align}
 * \mathbf{\pi}\mathbf{Q}=\mathbf{0} \\
 * \mathbf{\pi}\mathbf{1}^T=1
 * \f}
 * where:
 * - the first equation is the <em>global balance equation</em>,
 * - the * second one is the <em>normalization condition</em>,
 * - and \f$\mathbf{\pi}\f$ is the <em>steady state probabilities</em> vector
 *   (expressed as a row vector).
 * .
 *
 * \note
 *  Actually, we solve the CTMC by means of the <em>direct method</em> (see
 *  [1,2,3] for possible issues and other existing methods).
 *  From the point of view of implementation, there are two main problems:
 *  -# Maths routing usually assumes that vectors are expressed as column
 *     vector.
 *     So, the global balance equation comes in the &quot;wrong&quot; form: the
 *     unknowns are given as a row vector not a column vector.
 *     This problem is resolved by transposing the equation, i.e.
 *     \f[
 *      \mathbf{Q}^T\mathbf{\pi}^T = \mathbf{0}^T
 *     \f]
 *     where the right hand side is now a column vector of zeros, rather than a
 *     row vector.
 *  -# The redundancy amongst the global balance equations.
 *     To solve this problem we need the additional information of the
 *     normalization condition.
 *     This problem is resolved by replacing one of the global balance equations
 *     by the normalization condition.
 *     In the transposed matrix this corresponds to replacing one row by a row
 *     of 1's.
 *     We usually choose the last row and denote the modified matrix Q_n^T .
 *     Similarly we change the constant terms vector, which was all zeros to be
 *     a column vector with 1 in the last row, and zeros everywhere else.
 *     We denote such a vector, \f$e_n^T\f$.
 *  .
 *
 * References:
 * -# W.J. Stewart.
 *    "Introduction to the Numerical Solution of Markov Chains",
 *    Princeton University Press, 1994.
 * -# W.J. Stewart.
 *    "Performance Modeling and Markov Chains",
 *    Formal Methods of Performance Evaluation, Springer, 2007.
 * -# W.J. Stewart.
 *    "Probability, Markov Chains, Queues, and Simulation",
 *    Princeton University Press, 2009.
 * .
 */
template <typename MatrixExprT>
::boost::numeric::ublas::vector<
	typename ::boost::numeric::ublas::matrix_traits<MatrixExprT>::value_type
> ctmc_solve(::boost::numeric::ublas::matrix_expression<MatrixExprT> const& Q)
{
	namespace ublas = ::boost::numeric::ublas;
	namespace ublasx = ::boost::numeric::ublasx;

	typedef typename ublas::matrix_traits<MatrixExprT>::value_type value_type;
	typedef typename ublas::matrix_traits<MatrixExprT>::size_type size_type;
	typedef ublas::vector<size_type> size_vector_type;
	typedef ublas::vector<value_type> vector_type;

	size_type nr = ublasx::num_rows(Q);
	//size_type nc = ublasx::num_columns(Q);

	size_vector_type z;

	// Is the CTMC irreducible?

	z = ublasx::which(
		ublasx::sum<1>(
			ublasx::abs(Q)
		),
		::std::bind2nd(
			::std::equal_to<value_type>(),
			value_type(0)
		)
	);

	size_type nz;
	nz = ublasx::size(z);

	if (nz > 1)
	{
		DCS_DEBUG_TRACE("Warning: Q is a reducible infinitesimal generator.");
//		b = ublas::zero_vector<value_type>(nr);
	}
	else if (nz == 0)
	{
		z.resize(1, false);
		z(0) = nr-1;
		nz = 1;
	}

	// Create the constant terms vecotr b=e_n^T such that Q_n^T\pi^T=e_n^T
	vector_type b;
	b = ublas::zero_vector<value_type>(nr);

	ublas::matrix<value_type> tmp_Q(Q);

	// normalization condition
	for (size_type j = 0; j < nz; ++j)
	{
		size_type k(z(j));

		b(k) = 1;

		for (size_type i = 0; i < nr; ++i)
		{
			tmp_Q(i,k) = value_type(1);
		}
	}

	ublasx::lu_solve_inplace(ublas::trans(tmp_Q), b);

	return ublas::trans(b);
}


/**
 * \brief Equilibrium distribution of a discrete-time Markov chain (DTMC).
 * \param P Stochastic transition matrix of the DTMC.
 * \return The equilibrium distribution of the DTMC.
 */
template <typename MatrixExprT>
::boost::numeric::ublas::vector<
	typename ::boost::numeric::ublas::matrix_traits<MatrixExprT>::value_type
> dtmc_solve(::boost::numeric::ublas::matrix_expression<MatrixExprT> const& P)
{
	namespace ublas = ::boost::numeric::ublas;
	namespace ublasx = ::boost::numeric::ublasx;

	typedef MatrixExprT matrix_type;
	typedef typename ublas::matrix_traits<matrix_type>::size_type size_type;
	typedef typename ublas::matrix_traits<matrix_type>::value_type value_type;

	size_type nr = ublasx::num_rows(P);
	size_type nc = ublasx::num_columns(P);

	ublas::identity_matrix<value_type> I(nr,nc);

	return ctmc_solve(P-I);
}


/**
 * \brief Embedded discrete-time process of the given MAP.
 *
 * \param D0 The \f$D_0\f$ matrix of the MAP.
 * \param D1 The \f$D_1\f$ matrix of the MAP.
 * \return The probability transition matrix of the embedded process.
 *
 * Compute the stochastic transition matrix \f$P\f$ of the embedded phase
 * process at arrival instants.
 * Specifically, \f$P_{ij} is the probability that the MAP restarts in phase
 * \f$j\f$ if the last absorption occurred in phase \f$i\f$.
 *
 * \note If the MAP is feasible, then the probability transition matrix must be
 *  an irreducible stochastic matrix.
 *  In this case, the stationary distribution at arrival instants denoted by
 *  \f$\pi\f$ is given by \f$\piP=\pi$ and \f$\pie^T=1\f$.
 *  After an event has been generated, the distribution of the MAP is given by
 *  \f$\pi\f$.
 */
template <typename D0MatrixExprT, typename D1MatrixExprT>
::boost::numeric::ublas::matrix<
	typename ::boost::numeric::ublas::promote_traits<
		typename ::boost::numeric::ublas::matrix_traits<D0MatrixExprT>::value_type,
		typename ::boost::numeric::ublas::matrix_traits<D1MatrixExprT>::value_type
	>::promote_type
> embedded_dtmc(::boost::numeric::ublas::matrix_expression<D0MatrixExprT> const& D0,
				::boost::numeric::ublas::matrix_expression<D1MatrixExprT> const& D1)
{

//	typedef typename ::boost::numeric::ublas::promote_traits<
//				typename ::boost::numeric::ublas::matrix_traits<D0MatrixExprT>::value_type,
//				typename ::boost::numeric::ublas::matrix_traits<D1MatrixExprT>::value_type
//			>::promote_type value_type;
//	typedef ::boost::numeric::ublas::matrix<value_type> matrix_type;

	// Compute P=(-D0)^{-1})*D1
	return ::boost::numeric::ublas::prod(
				::boost::numeric::ublasx::inv(-D0),
				D1
			);
}


/// Compute the equilibrium distribution of the embedded discrete-time process.
template <typename D0MatrixExprT, typename D1MatrixExprT>
::boost::numeric::ublas::vector<
	typename ::boost::numeric::ublas::promote_traits<
		typename ::boost::numeric::ublas::matrix_traits<D0MatrixExprT>::value_type,
		typename ::boost::numeric::ublas::matrix_traits<D1MatrixExprT>::value_type
	>::promote_type
> equilibrium_distribution(::boost::numeric::ublas::matrix_expression<D0MatrixExprT> const& D0,
						   ::boost::numeric::ublas::matrix_expression<D1MatrixExprT> const& D1)
{
	return dtmc_solve(embedded_dtmc(D0, D1));
}


template <typename ValueT, typename URNG>
inline
ValueT generate_probability(URNG& rng)
{
	::dcs::math::random::uniform_01_adaptor<URNG&,ValueT> u01_rng(rng);

	return u01_rng();
}


template <typename VectorExprT, typename URNG>
typename ::boost::numeric::ublas::vector_traits<VectorExprT>::size_type generate_initial_state(::boost::numeric::ublas::vector_expression<VectorExprT> const& pi, URNG& rng)
{
	namespace ublas = ::boost::numeric::ublas;
	namespace ublasx = ::boost::numeric::ublasx;

	typedef typename ublas::vector_traits<VectorExprT>::size_type size_type;
	typedef typename ublas::vector_traits<VectorExprT>::value_type value_type;

	size_type n = ublasx::size(pi);

	value_type p = generate_probability<value_type>(rng);

	size_type ret(n); //default to last state

	//NOTE: states start from 1!

	ublas::vector<value_type> cdf = ublasx::cumsum(pi);
	for (size_type i = 0; i < n; ++i)
	{
		if (p <= cdf(i))
		{
			ret = i+1;
			break;
		}
	}
// Alternative (but possibly more time-consuming)
//	ret = ublasx::min(
//			ublasx::which(
//				ublasx::cumsum(pi),
//				::std::bind1st(
//					::std::less_equal<value_type>(),
//					p
//				)
//			)
//		);

	return ret;
}


template <typename VectorExprT, typename URNG>
typename ::boost::numeric::ublas::vector_traits<VectorExprT>::size_type generate_next_state(::boost::numeric::ublas::vector_expression<VectorExprT> const& cdf, URNG& rng)
{
	namespace ublas = ::boost::numeric::ublas;
	namespace ublasx = ::boost::numeric::ublasx;

	typedef typename ublas::vector_traits<VectorExprT>::size_type size_type;
	typedef typename ublas::vector_traits<VectorExprT>::value_type value_type;

	value_type p = generate_probability<value_type>(rng);

	ublas::vector<size_type> ix;

	ix = ublasx::which(
			cdf,
			::std::bind2nd(::std::greater_equal<value_type>(), p)
		);

	if (ix.size() == 0)
	{
		//TODO
		throw ::std::runtime_error("Unexpected failure");
	}

	return ix(0);
}


template <typename ValueT, typename URNG>
ValueT generate_sojourn_time(ValueT rate, URNG& rng)
{
	::dcs::math::stats::exponential_distribution<ValueT> exp(rate);

	return ::dcs::math::stats::rand(exp, rng);
}

}} // Namespace detail::<unnamed>


template <
	typename RealT = double,
	typename PolicyT = ::dcs::math::policies::policy<>
>
class map_distribution//: public base_distribution<RealT>
{
//	private: typedef base_distribution<RealT> base_type;
//	public: typedef typename base_type::value_type value_type;
//	public: typedef typename base_type::support_type support_type;
	public: typedef RealT value_type;
	public: typedef value_type support_type;
	public: typedef ::boost::numeric::ublas::matrix<support_type> matrix_type;
	public: typedef ::std::size_t size_type;
	private: typedef ::boost::numeric::ublas::vector<support_type> value_vector_type;
	private: typedef ::boost::numeric::ublas::vector<size_type> index_vector_type;


	public: template <typename D0MatrixExprT, typename D1MatrixExprT>
		map_distribution(::boost::numeric::ublas::matrix_expression<D0MatrixExprT> const& D0,
						 ::boost::numeric::ublas::matrix_expression<D1MatrixExprT> const& D1)
	: //base_type(),
	  D0_(D0),
	  D1_(D1)
	{
		// pre: num_rows(D0) == num_rows(D1)
		DCS_ASSERT(
			::boost::numeric::ublasx::num_rows(D0) == ::boost::numeric::ublasx::num_rows(D1),
			throw ::std::invalid_argument("[dcs::math::stats::map_distribution::ctor] Matrices D0 and D1 have different number of rows.")
		);
		// pre: num_cols(D0) == num_cols(D1)
		DCS_ASSERT(
			::boost::numeric::ublasx::num_columns(D0) == ::boost::numeric::ublasx::num_columns(D1),
			throw ::std::invalid_argument("[dcs::math::stats::map_distribution::ctor] Matrices D0 and D1 have different number of columns.")
		);
	}


	// Compiler-generated copy-constructor, copy-assignment, and destructor
	// are fine.


	public: matrix_type const& D0() const
	{
		return D0_;
	}


	public: matrix_type const& D1() const
	{
		return D1_;
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
		::std::vector<value_type> samples;
		samples = rand(rng, 1);

		if (samples.size() == 0)
		{
			throw ::std::runtime_error("[dcs::math::stats::map_distribution::rand] Unexpected failure.");
		}

		return samples[0];
	}


	/**
	 * The following algorithm is an adaptation of the one found in the MAP-QN
	 * toolbox (by G. Casale et al, http://www.cs.wm.edu/MAPQN/).
	 */
	public: template <typename URNG>
		::std::vector<value_type> rand(URNG& rng, size_type n) const
	{
		namespace ublas = ::boost::numeric::ublas;
		namespace ublasx = ::boost::numeric::ublasx;

		const size_type max_path_len0(20); // initial max path length
		const size_type path_len_incr(5); // increment in the max path length

		size_type ns(ublasx::num_rows(D0_)); // # stages
		size_type ns2(ns << 1); // 2*ns

		value_vector_type pi;

		pi = detail::equilibrium_distribution(D0_,  D1_);

		size_type s0; // initial stage

		// Randomly generate the initial stage.
		s0 = detail::generate_initial_state(pi, rng);

		matrix_type P(ns,ns2,0);

		for (size_type b=0; b < 2; ++b)
		{
			for (size_type i = 0; i < ns; ++i)
			{
				for (size_type j = 0; j < ns; ++j)
				{
					P(i,b*ns+j) = (b==0 ? D0_(i,j) : D1_(i,j)) / ::std::abs(D0_(i,i));
				}
			}
		}
		for (size_type i=0; i < ns; ++i)
		{
			P(i,i) = 0;
		}

		// Create CDF
		matrix_type C(ns,ns2);
		for (size_type i = 0; i < ns; ++i)
		{
			ublas::row(C, i) = ublasx::cumsum(ublas::row(P, i));
		}
		C = ublasx::abs(C);

		size_type src_s(s0);
		matrix_type V(ublas::zero_matrix<value_type>(n, max_path_len0));
		size_type max_path_len(max_path_len0);
		for (size_type i = 0; i < n; ++i)
		{
			bool arrival(false);
			size_type last(1);
			V(i,0) = src_s;

			while (!arrival)
			{
				size_type dst_s;
				dst_s = detail::generate_next_state(
							ublas::row(C, src_s-1),
							rng
					);
				++dst_s; // make sure that stage id starts from 1
				if (dst_s > ns)
				{
					arrival = true;
					dst_s -= ns;
					src_s = dst_s;
				}
				else
				{
					V(i,last) = dst_s;
					src_s = dst_s;
					++last;
				}
				if (last >= max_path_len)
				{
					max_path_len += path_len_incr;
					V.resize(n, max_path_len, true);
					for (size_type c = last; c < max_path_len; ++c)
					{
						ublas::column(V, c) = ublas::zero_vector<size_type>(n);
					}
				}
			}
		}

//XXX: not used
//		// Create the vector of absorbing stages (for each sample)
//		value_vector_type L(n);
//
//		for (size_type i = 0; i < n; ++i)
//		{
//			size_type ix;
//
//			ix = ublasx::max(
//					ublasx::which(
//						ublas::row(V, i)
//					)
//				);
//			L(i) = V(i,ix);
//		}

//XXX: not used
//		// Create the vector of initial stages (for each sample)
//		value_vector_type F;
//
//		F = ublas::column(V, 1);

		value_vector_type hold_rates(-ublasx::diag(D0_));

		size_type nv = ublasx::num_columns(V);
		matrix_type H(V); // matrix of times to absorptions
		for (size_type i = 0; i < ns; ++i)
		{
			size_type s = i+1;
			for (size_type j = 0; j < n; ++j)
			{
				for (size_type k = 0; k < nv; ++k)
				{
					if (V(j,k) == s)
					{
						H(j,k) = hold_rates(i);
					}
				}
			}
		}

		::std::vector<value_type> samples(n, 0);

		for (size_type i = 0; i < nv; ++i)
		{
			for (size_type k = 0; k < n; ++k)
			{
				if (H(k,i) > 0)
				{
					samples[k] += detail::generate_sojourn_time<value_type>(H(k,i), rng);
				}
			}
		}

		return samples;
	}


	private: matrix_type D0_;
	private: matrix_type D1_;
};


template <
	typename CharT,
	typename CharTraitsT,
	typename RealT,
	typename PolicyT
>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, map_distribution<RealT,PolicyT> const& dist)
{
	return os << "MAP("
			  << "D0=" <<  dist.D0()
			  << ",D1=" <<  dist.D1()
			  << ")";
}

}}} // Namespace dcs:math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_MAP_HPP
