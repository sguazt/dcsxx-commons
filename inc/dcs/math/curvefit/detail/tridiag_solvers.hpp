/**
 * \file dcs/math/curvefit/detail/tridiag_solvers.hpp
 *
 * \brief Solvers for tridiagonal and quasi-tridiagonal linear systems.
 *
 * Most of the code comes from [1,2].
 *
 * References:
 * -# W.H. Press, S.A Teukolsky, W.T. Vetterling and B.P Flannery,
 *    "Numerical Recipies: The Art of Scientific Computing, 3rd Edition",
 *    Cambridge University Press, 2007
 * -# G. Engeln-Muellges and F. Uhlig,
 *    "Numerical Algorithm with C",
 *    Springer-Verlag, 1996
 * .
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone (marco.guazzone@gmail.com)
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons (below referred to as "this program").
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_MATH_CURVEFIT_DETAIL_TRIDIAG_HPP
#define DCS_MATH_CURVEFIT_DETAIL_TRIDIAG_HPP


#include <cmath>
#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <limits>
#include <stdexcept>
#include <vector>


namespace dcs { namespace math { namespace curvefit { namespace detail { namespace /*<unnamed>*/ {

template <typename RealT>
inline
bool is_zero(RealT v)
{
	return ::std::fabs(v) < ::std::numeric_limits<RealT>::epsilon();
}

/**
 * \brief Solve a tridiagonal linear system with the Thomas algorithm.
 *
 * Solve the generic tridiagonal linear system \f$Ax=b\f$ where:
 * \f{align}
 *  A &= \begin{pmatrix}
 *        d_1 & c_1 &        &        & 0       \newline
 *        a_2 & d_2 & c_2    &        &         \newline
 *            & a_3 & d_3    & \ddots &         \newline
 *            &     & \ddots & \ddots & c_{n-1} \newline
 *        0   &     &        & a_n    & d_n
 *       \end{pmatrix} \newline
 *  b &= \begin{pmatrix}
 *        b_1 \newline b_2 \newline \vdots \newline b_n
 *       \end{pmatrix} \newline
 *  x &= \begin{pmatrix}
 *        x_1 \newline x_2 \newline \vdots \newline x_n
 *       \end{pmatrix}
 * \f}
 * using the Thomas algorithm.
 *
 * The Thomas algorithm consists in the following steps:
 * \f{align}
 *  c'_i &= \begin{cases}
 *           \frac{c_i}{d_i} & i = 1, \newline
 *           \frac{c_i}{d_i - c'_{i - 1} a_i} & i = 2, 3, \ldots, n-1
 *          \end{cases} \newline
 *  b'_i &= \begin{cases}
 *           \frac{b_i}{d_i} & i = 1, \newline
 *           \frac{b_i - b'_{i - 1} a_i}{d_i - c'_{i - 1} a_i} & i = 2, 3, \ldots, n.
 *          \end{cases}
 * \f}
 * The solution is then obtained by back substitution:
 * \f[
 *  x_i = \begin{cases}
 *         b'_i, & i=n,\newline
 *         b'_i - c'_i x_{i + 1} & i = n - 1, n - 2, \ldots, 1. 
 *        \end{cases}
 * \f]
 *
 * \param subdiag The sub-diagonal of matrix \f$A\f$
 * \param diag The main diagonal of matrix \f$A\f$
 * \param supdiag The super-diagonal of matrix \f$A\f$
 * \param x On input, the vector of coefficients \f$b\f$.
 *  On output, the vector of unknowns \f$x\f$.
 * \param n The size of the system
 *
 * References:
 * -# W.H. Press, S.A Teukolsky, W.T. Vetterling and B.P Flannery,
 *    "Numerical Recipies: The Art of Scientific Computing, 3rd Edition",
 *    Cambridge University Press, 2007
 * .
 */
template <typename RealT, typename VectorT>
void tridiagonal_solver_inplace(VectorT const& subdiag, VectorT const& diag, VectorT const& superdiag, VectorT& x, ::std::size_t n)
{
	if (is_zero(diag[0]))
	{
		DCS_EXCEPTION_THROW(::std::domain_error,
							"Matrix must be positive definite");
	}

	::std::vector<RealT> aux_vec(n-1); // The vector of c'_i

	aux_vec[0] = superdiag[0]/diag[0];
	x[0] /= diag[0];

	for (::std::size_t i = 1; i < (n-1); ++i)
	{
		if (is_zero(diag[i]))
		{
			DCS_EXCEPTION_THROW(::std::domain_error,
								"Matrix must be positive definite");
		}

		const RealT m = 1.0/(diag[i] - subdiag[i-1]*aux_vec[i-1]);
		aux_vec[i] = superdiag[i]*m;
		x[i] = (x[i] - subdiag[i-1]*x[i-1])*m;
	}

	if (n > 1)
	{
		x[n-1] = (x[n-1] - subdiag[n-2]*x[n-2])/(diag[n-1] - subdiag[n-2]*aux_vec[n-2]);
	}

	for (::std::ptrdiff_t i = n-2; i >= 0; --i)
	{
		x[i] -= aux_vec[i]*x[i+1];
	}
}

///**
// * Solve a asymmetric tridiagonal linear system.
// *
// * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is an asymmetric tridiagonal
// * positive definite n-by-n matrix, by using the plain Gauss elimination (only
// * not bothering with the zeros off the tri-diagonals).
// * 
// *  The matrix \f$A\f$ has the form:
// *  \f{pmatrix}
// *   d_0 & b_0 &     &     &     &         &         \newline
// *   a_0 & d_1 & b_1 &     &     &         &         \newline
// *       & a_1 & d_2 &  .  &     &         &         \newline
// *       &     &  .  &  .  &  .  &         &         \newline
// *       &     &     &  .  &  .  &  .      &         \newline
// *       &     &     &     &  .  &  .      & b_{n-2} \newline
// *       &     &     &     &     & a_{n-2} & d_{n-1} \newline
// *  \f}
// * The super-diagonal and sub-diagonal vectors must be one element shorter than
// * the diagonal vector.
// *
// * \param diag On input, a vector representing the diagonal of \f$A\f$.
// * \param subdiag On input, a vector representing the sub-diagonal of \f$A\f$.
// * \param supdiag On input, a vector representing the super-diagonal of \f$A\f$.
// * \param x On input, a vector representing the vector \f$b\f$.
// *  On output, a vector representing the vector \f$x\f$ (i.e., the
// *  solution to the system).
// * \param n The length of vector \f$x\f$.
// * \param start The initial position from which start reading.
// */
//template <typename RealT, typename VectorT>
//void tridiagonal_solver_inplace(VectorT const& diag, VectorT const& subdiag, VectorT const& supdiag, VectorT& x, ::std::size_t n, ::std::size_t start = 0)
//{
//	// Bidiagonalization 
//
//	::std::vector<RealT> alpha(n, 0);
//
//	alpha[0] = diag[0];
//
//	if (alpha[0] == 0)
//	{
//		throw new ::std::domain_error("Matrix must be positive definite");
//	}
//
//	for (::std::size_t i = 1; i < n; ++i)
//	{
//		const RealT t = subdiag[i-1]/alpha[i-1];
//		alpha[i] = diag[i]-t*supdiag[i-1];
//		x[i] = x[i]-t*x[i-1];
//		if (alpha[i] == 0)
//		{
//			throw new ::std::domain_error("Matrix must be positive definite");
//		}
//	}
//
//	/* backsubstitution */
//	x[n-1] = x[n-1]/alpha[n-1];
//	if (n >= 2)
//	{
//		for (::std::ptrdiff_t i = n-2; i >= 0; --i)
//		{
//			x[i] = (x[i]-supdiag[i]*x[i+1])/alpha[i];
//		}
//	}
//}

/**
 * Solve a symmetric tridiagonal linear system using LDL' factorization.
 *
 * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is a symmetric tridiagonal
 * positive definite matrix using the \f$LDL^T\f$ factorization.
 * 
 *  The matrix \f$A\f$ has the form:
 *  \f{pmatrix}
 *   d_0 & a_0 &     &     &     &         &         \newline
 *   a_0 & d_1 & a_1 &     &     &         &         \newline
 *       & a_1 & d_2 &  .  &     &         &         \newline
 *       &     &  .  &  .  &  .  &         &         \newline
 *       &     &     &  .  &  .  &  .      &         \newline
 *       &     &     &     &  .  &  .      & a_{n-2} \newline
 *       &     &     &     &     & a_{n-2} & d_{n-1} \newline
 *  \f}
 * The super-diagonal and sub-diagonal vectors must be one element shorter than
 * the diagonal vector.
 *
 * \param diag A vector representing the diagonal of \f$A\f$.
 * \param offdiag A vector representing either the sub-diagonal or
 *  super-diagonal of \f$A\f$.
 * \param x On input, a vector representing the vector \f$b\f$.
 *  On output, a vector representing the vector \f$x\f$ (i.e., the
 *  solution to the system).
 * \param n The length of vector \f$x\f$.
 */
template <typename RealT, typename VectorT>
void symmetric_tridiagonal_solver_inplace(VectorT& diag, VectorT& offdiag, VectorT& x, ::std::size_t n)
{
	::std::vector<RealT> L_subdiag(n);
	::std::vector<RealT> D_diag(n);

	D_diag[0] = diag[0];
	for (::std::size_t i = 1; i < n; ++i)
	{
		if (is_zero(D_diag[i-1]))
		{
			DCS_EXCEPTION_THROW(::std::domain_error,
								"Matrix must be positive definite");
		}
		L_subdiag[i-1] = offdiag[i-1]/D_diag[i-1];
		D_diag[i] = diag[i]-offdiag[i-1]*L_subdiag[i-1];
		x[i] -= L_subdiag[i-1]*x[i-1];
	}

	x[n-1] /= D_diag[n-1];
	for (::std::ptrdiff_t i = n-2; i >= 0; --i)
	{
		x[i] = x[i]/D_diag[i] - L_subdiag[i]*x[i+1];
	}
}

/**
 * Solve an asymmetric nearly tridiagonal linear system.
 *
 * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is a asymmetric nearly
 * tridiagonal positive definite matrix by first solving the system without
 * the corner elements and then using the Sherma-Morrison formula to
 * compensate for them.
 *
 *  The matrix \f$A\f$ has the form:
 *  \f{pmatrix}
 *   d_0     & b_0 &     &     &     &         & b_{n-1} \newline
 *   a_0     & d_1 & b_1 &     &     &         &         \newline
 *           & a_1 & d_2 &  .  &     &         &         \newline
 *           &     &  .  &  .  &  .  &         &         \newline
 *           &     &     &  .  &  .  &  .      &         \newline
 *           &     &     &     &  .  &  .      & b_{n-2} \newline
 *   a_{n-1} &     &     &     &     & a_{n-2} & d_{n-1} \newline
 *  \f}
 * The super-diagonal and sub-diagonal vectors must have the same number of
 * elements as the the diagonal vector.
 *
 * \param diag On input, a vector representing the diagonal of \f$A\f$.
 *  On output, a vector representing the diagonal of the
 *  (diagonal) matrix \f$D\f$ of the\f$LDL^T\f$ factorization.
 * \param subdiag On input, a vector representing the subdiagonal of \f$A\f$.
 * \param supdiag On input, a vector representing the supdiagonal of \f$A\f$.
 * \param x On input, a vector representing the vector \f$b\f$.
 *  On output, a vector representing the vector \f$x\f$ (i.e., the
 *  solution to the system).
 * \param n The length of vector \f$x\f$.
 * \param start The initial position from which start reading.
 *
 * References:
 * -# Numerical Recipies in C++
 * .
 */
template <typename RealT, typename VectorT>
void cyclic_tridiagonal_solver_inplace(VectorT& diag, VectorT& subdiag, VectorT& supdiag, VectorT& x, ::std::size_t n)
{
	// pre: n > 2
	DCS_ASSERT(n > 2,
			   DCS_EXCEPTION_THROW(::std::invalid_argument,
								   "The size of the cyclic linear system must be > 2"));

	const RealT gamma(-diag[0]);
	const RealT alpha(subdiag[n-1]);
	const RealT beta(supdiag[n-1]);

	// We use the Sherman-Morrison formula, treating the original system as a
	// tridiagonal system plus a correction

	// 1. Setup and solve a new tridiagonal system $A'x=b$
	// where $A'$ has the form:
	// \begin{pmatrix}
	//  d_0-\gamma & b_0 &     &     &     &         &         \newline
	//  a_0        & d_1 & b_1 &     &     &         &         \newline
	//             & a_1 & d_2 &  .  &     &         &         \newline
	//             &     &  .  &  .  &  .  &         &         \newline
	//             &     &     &  .  &  .  &  .      &         \newline
	//             &     &     &     &  .  &  .      & b_{n-2} \newline
	//             &     &     &     &     & a_{n-2} & d_{n-1}-\frac{\alpha\beta}{gamma} \newline
	// \end{pmatrix}
	// where $\alpha=a_{n-1}$, $\beta==b_{n-1}$ and $\gamma=-d_0$

	::std::vector<RealT> newdiag(n, 0);
    newdiag[0] = diag[0]-gamma;
    newdiag[n-1] = diag[n-1]-alpha*beta/gamma;
    for (::std::size_t i = 1; i < (n-1); ++i)
	{
		newdiag[i] = diag[i];
	}
    tridiagonal_solver_inplace<RealT>(subdiag, newdiag, supdiag, x, n);

	// 2. Setup and solve a new tridiagonal system $A'z=u$, where
	// $u$ has the following form:
	// \begin{pmatrix}
	//  \gamma \newline
	//  0 \newline
	//  \vdots \newline
	//  0 \newline
	//  \alpha
	// \end{pmatrix}
	::std::vector<RealT> z(n, 0);
    z[0] = gamma;
    z[n-1] = alpha;
    tridiagonal_solver_inplace<RealT>(subdiag, newdiag, supdiag, z, n);

	// 3. Form $vx/(1+vz)$ and compute the solution $x$ for the original system,
	// where $v$ has the form:
	// \begin{pmatrix}
	//  1 \newline
	//  0 \newline
	//  \vdots \newline
	//  \frac{\beta}{\gamma}
	// \end{pmatrix}
    const RealT fact((x[0]+beta*x[n-1]/gamma)/(1.0+z[0]+beta*z[n-1]/gamma));
    for (::std::size_t i = 0; i < n; ++i)
	{
		x[i] -= fact*z[i];
	}
}

/**
 * Solve a symmetric nearly tridiagonal linear system using LDL' factorization.
 *
 * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is a symmetric nearly
 * tridiagonal positive definite matrix using the \f$LDL^T\f$ factorization.
 *  The matrix \f$A\f$ has the form:
 *  \f{pmatrix}
 *   x & x &   &   &   &   & x \newline
 *   x & x & x &   &   &   &   \newline
 *     & x & x & x &   &   &   \newline
 *     &   & x & x & x &   &   \newline
 *     &   &   & x & x & x &   \newline
 *     &   &   &   & x & x & x \newline
 *   x &   &   &   &   & x & x \newline
 *  \f}
 *  and thus the matrix \f$L\f$ is like:
 *  \f{pmatrix}
 *   1 &   &   &   &   &   &   \newline
 *   x & 1 &   &   &   &   &   \newline
 *     & x & 1 &   &   &   &   \newline
 *     &   & x & 1 &   &   &   \newline
 *     &   &   & x & 1 &   &   \newline
 *     &   &   &   & x & 1 &   \newline
 *   x & x & x & x & x & x & 1 \newline
 *  \f}
 * The super-diagonal and sub-diagonal vectors must have the same number of
 * elements as the the diagonal vector.
 *
 * \param diag On input, a vector representing the diagonal of \f$A\f$.
 *  On output, a vector representing the diagonal of the
 *  (diagonal) matrix \f$D\f$ of the\f$LDL^T\f$ factorization.
 * \param subdiag On input, a vector representing the subdiagonal of \f$A\f$.
 *  On output, a vector representing the subdiagonal of \f$L\f$
 *  of the \f$LDL^T\f$ factorization.
 * \param x On input, a vector representing the vector \f$b\f$.
 *  On output, a vector representing the vector \f$x\f$ (i.e., the
 *  solution to the system).
 * \param n The length of vector \f$x\f$.
 * \param start The initial position from which start reading.
 */
template <typename RealT, typename VectorT>
void symmetric_cyclic_tridiagonal_solver_inplace(VectorT& diag, VectorT& offdiag, VectorT& x, ::std::size_t n)
{
#if 0
	// Compute the LDL' factorization

	const RealT gamma(-diag[0]);
	const RealT alpha(offdiag[n-1]);
	const RealT beta(alpha);

	// We use the Sherman-Morrison formula, treating the original system as a
	// tridiagonal system plus a correction

	// 1. Setup and solve a new tridiagonal system $A'x=b$
	// where $A'$ has the form:
	// \begin{pmatrix}
	//  d_0-\gamma & a_0 &     &     &     &         &         \newline
	//  a_0        & d_1 & a_1 &     &     &         &         \newline
	//             & a_1 & d_2 &  .  &     &         &         \newline
	//             &     &  .  &  .  &  .  &         &         \newline
	//             &     &     &  .  &  .  &  .      &         \newline
	//             &     &     &     &  .  &  .      & a_{n-2} \newline
	//             &     &     &     &     & a_{n-2} & d_{n-1}-\frac{\alpha\beta}{gamma} \newline
	// \end{pmatrix}
	// where $\alpha=a_{n-1}$, $\beta==b_{n-1}$ and $\gamma=-d_0$

	::std::vector<RealT> newdiag(n, 0);
    newdiag[0] = diag[0]-gamma;
    newdiag[n-1] = diag[n-1]-alpha*beta/gamma;
    for (::std::size_t i = 1; i < (n-1); ++i)
	{
		newdiag[i] = diag[i];
	}
    symmetric_tridiagonal_solver_inplace<RealT>(newdiag, offdiag, x, n);

	// 2. Setup and solve a new tridiagonal system $A'z=u$, where
	// $u$ has the following form:
	// \begin{pmatrix}
	//  \gamma \newline
	//  0 \newline
	//  \vdots \newline
	//  0 \newline
	//  \alpha
	// \end{pmatrix}
	::std::vector<RealT> z(n, 0);
    z[0] = gamma;
    z[n-1] = alpha;
    symmetric_tridiagonal_solver_inplace<RealT>(newdiag, offdiag, z, n);

	// 3. Form $vx/(1+vz)$ and compute the solution $x$ for the original system,
	// where $v$ has the form:
	// \begin{pmatrix}
	//  1 \newline
	//  0 \newline
	//  \vdots \newline
	//  \frac{\beta}{\gamma}
	// \end{pmatrix}
    const RealT fact((x[0]+beta*x[n-1]/gamma)/(1.0+z[0]+beta*z[n-1]/gamma));
    for (::std::size_t i = 0; i < n; ++i)
	{
		x[i] -= fact*z[i];
	}
#else // 0
	if (is_zero(diag[0]))
	{
		DCS_EXCEPTION_THROW(::std::domain_error,
							"Matrix must be positive definite");
	}

	if (n == 1)
	{
		x[0] /= diag[0];
		return;
	}

	::std::vector<RealT> delta(n, 0);
	::std::vector<RealT> gamma(n, 0);
	::std::vector<RealT> alpha(n, 0);

	alpha[0] = diag[0];
	gamma[0] = offdiag[0]/alpha[0];
	delta[0] = offdiag[n-1]/alpha[0];

	for (::std::size_t i = 1; i < (n-2); ++i)
	{
		alpha[i] = diag[i]-offdiag[i-1]*gamma[i-1];
		if (is_zero(alpha[i]))
		{
			DCS_EXCEPTION_THROW(::std::domain_error,
								"Matrix must be positive definite");
		}

		gamma[i] = offdiag[i]/alpha[i];
		delta[i] = -delta[i-1]*offdiag[i-1]/alpha[i];
	}

	RealT sum(0);
	for (::std::size_t i = 0; i < (n-2); ++i)
	{
		sum += alpha[i]*delta[i]*delta[i];
	}

	alpha[n-2] = diag[n-2]-offdiag[n-3]*gamma[n-3];
	gamma[n-2] = (offdiag[n-2]-offdiag[n-3]*delta[n-3])/alpha[n-2];
	alpha[n-1] = diag[n-1]-sum-alpha[n-2]*gamma[n-2]*gamma[n-2];

	/* update */
	::std::vector<RealT> c(n, 0);
	::std::vector<RealT> z(n, 0);
	z[0] = x[0];
	for (::std::size_t i = 1; i < (n-1); ++i)
	{
		z[i] = x[i]-z[i-1]*gamma[i-1];
	}
	sum = 0;
	for (::std::size_t i = 0; i < (n-2); ++i)
	{
		sum += delta[i]*z[i];
	}
	z[n-1] = x[n-1]-sum-gamma[n-2]*z[n-2];
	for (::std::size_t i = 0; i < n; ++i)
	{
		c[i] = z[i]/alpha[i];
	}

	/* backsubstitution */
	x[n-1] = c[n-1];
	x[n-2] = c[n-2]-gamma[n-2]*x[n-1];
	if (n >= 3)
	{
		for (::std::ptrdiff_t i = n-3; i >= 0; --i)
		{
			x[i] = c[i]-gamma[i]*x[i+1]-delta[i]*x[n-1];
		}
	}
#endif
}

}}}}} // Namespace dcs::math::curvefit::detail::<unnamed>

#endif // DCS_MATH_CURVEFIT_DETAIL_TRIDIAG_HPP
