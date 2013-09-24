/**
 * \file dcs/math/curvefit/interpolation/cubic_spline.hpp
 *
 * \brief Cubic spline data interpolation.
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

#ifndef DCS_MATH_CURVEFIT_INTERPOLATION_CUBIC_SPLINE_HPP
#define DCS_MATH_CURVEFIT_INTERPOLATION_CUBIC_SPLINE_HPP


#include <algorithm>
#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <dcs/math/traits/float.hpp>
#include <limits>


namespace dcs { namespace math { namespace curvefit {

namespace detail { namespace /*<unnamed>*/ {

/**
 * \brief Solve a tridiagonal linear system with the Thomas algorithm.
 *
 * Given a linear system \f$Ax=b\f$ where:
 * \f{align}
 *  A &= \begin{pmatrix}
 *        d_1 & c_1 &        &        & 0       \\
 *        a_2 & d_2 & c_2    &        &         \\
 *            & a_3 & d_3    & \ddots &         \\
 *            &     & \ddots & \ddots & c_{n-1} \\
 *        0   &     &        & a_n    & d_n
 *       \end{pmatrix} \\
 *  b &= \begin{pmatrix}
 *        b_1 \\ b_2 \\ \vdots \\ b_n
 *       \end{pmatrix} \\
 *  x &= \begin{pmatrix}
 *        x_1 \\ x_2 \\ \vdots \\ x_n
 *       \end{pmatrix}
 * \f}
 * the Thomas algorithm consists in the following steps:
 * \f{align}
 *  c'_i &= \begin{cases}
 *           \frac{c_i}{d_i} & i = 1, \\
 *           \frac{c_i}{d_i - c'_{i - 1} a_i} & i = 2, 3, \ldots, n-1
 *          \end{cases} \\
 *  b'_i &= \begin{cases}
 *           \frac{b_i}{d_i} & i = 1, \\
 *           \frac{b_i - b'_{i - 1} a_i}{d_i - c'_{i - 1} a_i} & i = 2, 3, \ldots, n.
 *          \end{cases}
 * \f}
 * The solution is then obtained by back substitution:
 * \f[
 *  x_i = \begin{cases}
 *         b'_i, & i=n,\\
 *         b'_i - c'_i x_{i + 1} & i = n - 1, n - 2, \ldots, 1. 
 *        \end{cases}
 * \f]
 */
template <typename RealT, typename InIterT, typename OutIterT>
void tridiagonal_solver_inplace(InIterT subdiag_first, InIterT subdiag_last, InIterT diag_first, InIterT superdiag_first, OutIterT x_first)
{
	const ::std::size_t n(::std::distance(subdiag_first, subdiag_last));

	::std::vector<RealT> aux_vec(n);

	aux_vec[0] = *superdiag_first / *diag_first;
	*x_first /= *diag_first;

	OutIterT x_it;

	x_it = x_first;
	for (::std::size_t i = 1; i < n; ++i)
	{
		const RealT x_prev(*x_it);

		++subdiag_first;
		++diag_first;
		++superdiag_first;
		++x_it;

		const RealT m = 1.0/(*diag_first - *subdiag_first*aux_vec[i-1]);
		aux_vec[i] = *superdiag_first * m;
		*x_it = (*x_it - *subdiag_first * x_prev) * m;
	}

	++x_it;
	for (::std::ptrdiff_t i = n-1; i >= 0; --i)
	{
		const RealT x_succ(*x_it);

		--x_it;

		*x_it -= aux_vec[i]*x_succ;
	}
}

/*
template <typename RealT, typename InIterT, typename OutIterT>
void tridiagonal_solver_inplace(InIterT subdiag_first, InIterT subdiag_last, InIterT diag_first, InIterT supdiag_first, OutIterT x_first)
{
    std::size_t in;

	const std::size_t N = std::distance(subdiag_first, subdiag_last);

	std::vector<RealT> a(subdiag_first, subdiag_first+N);
	std::vector<RealT> b(diag_first, diag_first+N);
	std::vector<RealT> c(supdiag_first, supdiag_first+N);
	std::vector<RealT> x(x_first, x_first+N);

    // Allocate scratch space.
    double * cprime = new double[N];

    if (!cprime) {
        // do something to handle error
    }

    cprime[0] = c[0] / b[0];
    x[0] = x[0] / b[0];

    // loop from 1 to N - 1 inclusive
    for (in = 1; in < N; in++) {
        double m = 1.0 / (b[in] - a[in] * cprime[in - 1]);
        cprime[in] = c[in] * m;
        x[in] = (x[in] - a[in] * x[in - 1]) * m;
    }

    // loop from N - 2 to 0 inclusive, safely testing loop end condition
    for (in = N - 1; in-- > 0; )
    {
        x[in] = x[in] - cprime[in] * x[in + 1];
    }

    // free scratch space 
    delete[] cprime;

	for (in = 0; in < N; ++in)
	{
		*x_first = x[in];
		++x_first;
	}
}
*/

/**
 * Solve a symmetric tridiagonal linear system using LDL' factorization.
 *
 * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is a symmetric tridiagonal
 * positive definite matrix using the \f$LDL^T\f$ factorization.
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
void tridiagonal_ldl_solver_inplace(VectorT& diag, VectorT& subdiag, VectorT& x, ::std::size_t n, ::std::size_t start = 0)
{
	for (::std::size_t i = start+1; i < n; ++i)
	{
		const RealT sdm1(subdiag[i-1]);
		subdiag[i-1] = sdm1/diag[i-1];
		diag[i] -= sdm1*subdiag[i-1];
		x[i] -= subdiag[i-1]*x[i-1];
	}

	x[n-1] /= diag[n-1];
	//NOTE: static_cast is needed to avoid possible bad behaviors (experienced with GCC 4.8)
	for (::std::ptrdiff_t i = n-2; i >= static_cast< ::std::ptrdiff_t >(start); --i)
	{
		x[i] = x[i]/diag[i] - subdiag[i]*x[i+1];
	}
}

/**
 * Solve a symmetric nearly tridiagonal linear system using LDL' factorization.
 *
 * Solve the linear system \f$Ax=b\f$ where \f$A\f$ is a symmetric nearly
 * tridiagonal positive definite matrix using the \f$LDL^T\f$ factorization.
 *  The matrix \f$A\f$ has the form:
 *  \f{pmatrix}
 *   x & x &   &   &   &   & x \\
 *   x & x & x &   &   &   &   \\
 *     & x & x & x &   &   &   \\
 *     &   & x & x & x &   &   \\
 *     &   &   & x & x & x &   \\
 *     &   &   &   & x & x & x \\
 *   x &   &   &   &   & x & x \\
 *  \f}
 *  and thus the matrix \f$L\f$ is like:
 *  \f{pmatrix}
 *   1 &   &   &   &   &   &   \\
 *   x & 1 &   &   &   &   &   \\
 *     & x & 1 &   &   &   &   \\
 *     &   & x & 1 &   &   &   \\
 *     &   &   & x & 1 &   &   \\
 *     &   &   &   & x & 1 &   \\
 *   x & x & x & x & x & x & 1 \\
 *  \f}
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
void cyclic_tridiagonal_ldl_solver_inplace(VectorT& diag, VectorT& subdiag, VectorT& lastrow, VectorT& x, ::std::size_t n, ::std::size_t start = 0)
{
	// Compute the LDL' factorization
	for (::std::size_t i = start; i < (n-2); ++i)
	{
		const RealT sd(subdiag[i]);
		const RealT lr(lastrow[i]);
		subdiag[i] /= diag[i]; // elimination of coefficient L(i,i-1)
		lastrow[i] /= diag[i]; // elimination of coefficient L(n,i-1)

		diag[i+1] -= sd*subdiag[i]; // elimination on line i+1
		lastrow[i+1] -= sd*lastrow[i]; // elimination on line n
		diag[n-1] -= lr*lastrow[i]; // Ditto
	}

	const RealT lr(lastrow[n-2]);
	lastrow[n-2] /= diag[n-2];
	diag[n-1] -= lr*lastrow[n-2];

	// Solve LDL'x=b
	for (::std::size_t i = start+1; i < (n-1); ++i)
	{
		x[i] -= subdiag[i-1]*x[i-1];
		//x[n-1] -= lastrow[i-1]*x[i-1];
	}
	for (::std::size_t i = start; i < (n-1); ++i)
	{
		x[n-1] -= lastrow[i]*x[i];
	}

	for (::std::size_t i = start; i < n; ++i)
	{
		x[i] /= diag[i];
	}

	x[n-2] -= lastrow[n-2]*x[n-1];
	//NOTE: static_cast is needed to avoid possible bad behaviors (experienced with GCC 4.8)
	for (::std::ptrdiff_t i = n-3; i >= static_cast< ::std::ptrdiff_t >(start); --i)
	{
		x[i] -= subdiag[i]*x[i+1] + lastrow[i]*x[n-1];
	}
}

}} // Namespace detail::<unnamed>


enum spline_boundary_condition_category
{
	clamped_spline_boundary_condition, ///< Clamped cubic spline boundary condition
	natural_spline_boundary_condition, ///< Natural cubic spline boundary condition
	not_a_knot_spline_boundary_condition, ///< Not-a-knot boundary condition
	parabolic_spline_boundary_condition, ///< Parabolically terminated spline boundary condition
	periodic_spline_boundary_condition, ///< Periodic cubic spline boundary condition
	curvature_adjusted_spline_boundary_condition ///< Endpoint curvature-adjusted spline boundary condition
};

/**
 * \brief Cubic spline interpolation.
 *
 * Suppose that \f$\{(xk , yk)\}_{k=0}^n\f$ are \f$n+1\f$ points, where
 * \f$x_0<x_1<\cdots<x_n\f$.
 * The function \f$S(x)\f$ is called a <b>cubic spline</b> if there exist
 * \f$n\f$ cubic polynomials \f$S_k(x)\f$ with coefficients \f$s_{k,0}\f$,
 * \f$s_{k,1}\f$, \f$s_{k,2}\f$, and \f$s_k,3\f$ that satisfy the following
 * properties:
 * -# \f$S(x)=S_k(x)=s_{k,0}+s_{k,1}(x-x_k)+s_{k,2}(x-x_k)^2+s_{k,3}(x-x_k)^3\f$
 *  for \f$x\in[x_k,x_{k+1}]\f$ and \f$k=0,1,\ldots,n-1\f$
 * -# \f$S(x_k)=y_k\f$, for \f$k=0,1,\ldots,n\f$,
 * -# \f$S_k(x_{k+1})=S_{k+1}(x_{k+1})\f$, for \f$k=0,1,\ldots,n-2\f$,
 * -# \f$S_k'(x_{k+1})=S_{k+1}'(x_{k+1})\f$, for \f$k=0,1,\ldots,n-2\f$,
 * -# \f$S_k''(x_{k+1})=S_{k+1}''(x_{k+1})\f$, for \f$k=0,1,\ldots,n-2\f$.
 * .
 *
 * To construct a cubic spline, we need to solve the following linear system:
 * \f[
 *  h_{k-1}m_{k-1}+2(h_{k-1}+h_{k})m_{k}+h_km_{k+1} = u_k, \quad k=1,2,\ldots,n-1
 * \f]
 * where \f$m_k\f$, for \f$k=0,1,\ldots,n\f$ are the unknowns and:
 * \f{align}
 *  h_k &= x_{k+1}-x_k,\\
 *  d_k &= \frac{y_{k+1}-y_k}{h_k},\\
 *  u_k &= 6(d_k-d_{k-1}),\\
 * \f}
 * for \f$k=1,2,\ldots,n-1\f$.
 *
 * This is a tridiagonal linear system with $n-1$ linear equations involving
 * \f$n+1\f$ unknowns.
 * Thus two additional equations are needed in order to eliminate \f$m_0\f$ from
 * the first equation and \f$m_n\f$ from the \f$(n-1)\f$-st equation.
 * This is obtained by fixing the so called <em>boundary conditions</em>.
 *
 * The currently supported boundary conditions are:
 * - <b>Clamped (or complete)) spline condition</b>: it consists in specifying
 *   both \f$S'(x_0)\f$ and \f$S'(x_n)\f$, thus resulting in:
 *   \f{align}
 *    m_0 &= \frac{3}{h_0}(d_0-S'(x_0))-\frac{m_1}{2},\\
 *    m_n &= \frac{3}{h_{n-1}}(S'(x_n)-d_{n-1})-\frac{m_{n-1}}{2}.
 *   \f}
 * - <b>Natural (or free) spline condition</b>: it consists in setting
 *   \f$S''(x_0)=S''(x_n)=0\f$, thus resulting in:
 *   \f{align}
 *    m_0 &= 0,\\
 *    m_n &= 0.
 *   \f}
 *   It is sometimes referred to as zero curvature boundary condition.
 * - <b>Not-a-Knot spline condition</b>: it consists in extrapolating
 *   \f$S''(x)\f$ to the endpoints,(i.e., it extrapolates S''(x_0) from the
 *   interior nodes at \f$x_1$ and \f$x_2\f$, and \f$S''(x_n)$ from the interior
 *   nodes at \f$x_{n-1}\f$ and \f$x_{n-2}\f$), thus resulting in:
 *   \f{align}
 *    m_0 &= m_1-\frac{h_0(m_2-m_1)}{h_1},\\
 *    m_n &= m_{n-1}+\frac{h_{n-1}(m_{n-1}-m_{n-2})}{h_{n-2}}.
 *   \f}
 *   It is sometimes referred to as third derivative matching boundary condition
 *   since it is equivalent to require that:
 *   \f{align}
 *    S_0'''(x_1) &= S_1'''(x_1),\\
 *    S_{n-2}'''(x_{n-1}) &= S_{n-1}'''(x_{n-1}).
 *   \f}
 *   where \f$S_i'''(x)=6d_i$.
 * - <b>Parabolically terminated spline</b>: it consists in requiring that
 *   \f$S''(x)\f$ is constant near the endpoints (i.e., that \f$S'''(x)=0\f$
 *   both on the interval \f$[x_0,x_1]\f$ and on \f$[x_{n-1},x_n]\f$), thus
 *   resulting in:
 *   \f{align}
 *    m_0 &= m_1,\\
 *    m_n &= m_{n-1}.
 *   \f}
 * - <b>Endpoint curvature-adjusted spline</b>: it consists in specifying
 *   \f$S''(x)\f$ at each endpoint, thus resulting in:
 *   \f{align}
 *    m_0 &= S''(x_0),\\
 *    m_n &= S''(x_n).
 *   \f}
 * .
 *
 * References:
 * -# <em>Carl de Boor.</em>
 *    <b>A Practical Guide to Splines, Revised Edition.</b>
 *    Spinger-Verlag New York, Inc., 2001.
 * -# <em>John H. Mathews and Kurtis K. Fink.</em>
 *    <b>Numerical Methods Using MATLAB, 4th Edition.</b>
 *    Pearson, 2004.
 * .
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename RealT>
class cubic_spline_interpolator: public base_1d_interpolator<RealT>
{
	public: typedef RealT real_type;
	private: typedef base_1d_interpolator<real_type> base_type;


	public: cubic_spline_interpolator()
	{
	}

	public: template <typename XIterT, typename YIterT>
			cubic_spline_interpolator(XIterT first_x,
									  XIterT last_x,
									  YIterT first_y,
									  YIterT last_y,
									  spline_boundary_condition_category boundary_condition,
									  real_type lb = -::std::numeric_limits<real_type>::infinity(),
									  real_type ub = ::std::numeric_limits<real_type>::infinity())
	: base_type(first_x, last_x, first_y, last_y, 3, 2),
	  bound_cond_(boundary_condition),
	  lb_(lb),
	  ub_(ub),
	  m_(this->num_nodes())
	{
		this->init();
	}

	public: ::std::vector<real_type> coefficients(::std::size_t k) const
	{
		// pre: k < n
		DCS_ASSERT( k < (this->num_nodes()-1),
					DCS_EXCEPTION_THROW( ::std::invalid_argument,
										 "Spline coefficients are defined for k=0,...,N-2, where N is the number of nodes" ));

/*
		const real_type h(this->hk(k));
		const real_type d(this->dk(k));

		::std::vector<real_type> coeffs(4);
		coeffs[0] = this->value(k);
		coeffs[1] = d - h*(2.0*m_[k]+m_[k+1])/6.0;
		coeffs[2] = m_[k]/2.0;
		coeffs[3] = (m_[k+1]-m_[k])/(6.0*h);
*/
		::std::vector<real_type> coeffs(4);
		const real_type dy(this->value(k+1)-this->value(k));
		const real_type dx(this->node(k+1)-this->node(k));
		const real_type dxy(dy/dx);
		const real_type a((dxy - m_[k])/dx);
		const real_type b((m_[k+1] -dxy)/dx);
		coeffs[0] = this->value(k);
		coeffs[1] = m_[k];
		coeffs[2] = 2.0*a - b;
		coeffs[3] = (b - a)/dx;

		return coeffs;
	}

	public: real_type leftmost_endpoint() const
	{
		return lb_;
	}

	public: real_type rightmost_endpoint() const
	{
		return ub_;
	}

	public: spline_boundary_condition_category boundary_condition() const
	{
		return bound_cond_;
	}

//	private: real_type hk(::std::size_t k) const
//	{
//		return this->node(k+1)-this->node(k);
//	}
//
//	private: real_type dk(::std::size_t k) const
//	{
//		return (this->value(k+1)-this->value(k))/this->hk(k);
//	}
//
//	private: real_type uk(::std::size_t k) const
//	{
//		return 6.0*(dk(k)-dk(k-1));
//	}

	private: void init()
	{
		// pre: check that bounds are present when they are needed
		DCS_ASSERT( (bound_cond_ != clamped_spline_boundary_condition && bound_cond_ != curvature_adjusted_spline_boundary_condition)
					|| (::std::isfinite(lb_) && ::std::isfinite(ub_)),
					DCS_EXCEPTION_THROW( ::std::invalid_argument,
										 "Endpoints must be finite for the specified boundary conditions" ));
		// pre: check periodicity requirement
		DCS_ASSERT( bound_cond_ != periodic_spline_boundary_condition
					|| ::dcs::math::float_traits<real_type>::essentially_equal(this->value(0), this->value(this->num_nodes()-1)),
					DCS_EXCEPTION_THROW( ::std::invalid_argument,
										 "For periodic splines, the first y-value must be equal to the last one" ));

		const ::std::size_t n(this->num_nodes());

		// check nodes to ensure they are a strictly increasing sequence
		for (::std::size_t i = 1; i < n; ++i)
		{
			if (::dcs::math::float_traits<real_type>::approximately_less_equal(this->node(i), this->node(i-1)))
			{
				DCS_EXCEPTION_THROW(::std::invalid_argument,
									"Node sequence is not a strictly increasing sequence");
			}
		}

		/*
		 * For \f$k=0,\ldots,n-1\f$, let
		 * - \f$h_k=x_{k+1}-x_k\f$
		 * - \f$m_k=S''(x_k)\f$
		 * - \f$d_k=\frac{y_{k+1}-y_k}{h_k}\f$
		 * Furthermore, for \f$k=1,\ldots,n-1\f$, let \f$u_k=6(d_k-d_{k-1})\f$.
		 * We now solve the following tridiagonal linear system:
		 * \f[
		 *  Hm = u \quad \text{subject to boundary conditions to fix $m_0$ and $m_n$}
		 * \f]
		 * where:
		 * \f[
		 *  H=\begin{pmatrix}
		 *     h_1 & 2(h_0+h_1) &            &         & 0                  \\
		 *     h_2 & 2(h_1+h_2) & h_3        &         &                    \\
		 *         & h_3        & 2(h_2+h_3) & \ddots  &                    \\
		 *         &            & \ddots     & \ddots  & h_{n-2}            \\
		 *     0   &            &            & h_{n-2} & 2(h_{n-2}+h_{n-1})
		 *    \end{pmatrix}
		 * \f]
		 * \f[
		 *  m=\begin{pmatrix}
		 *     m_1 \\ m_2 \\ m_3 \\ \vdots \\ m_{n-1}
		 *    \end{pmatrix}
		 * \f]
		 * \f[
		 *  u=\begin{pmatrix}
		 *     u_2 \\ u_3 \\ u_4 \\ \vdots \\ u_{n-2}
		 *    \end{pmatrix}
		 * \f]
		 * This system can be efficiently solved in linear time with the Thomas algorithm
		 */

#if 0
		const ::std::size_t n(this->num_nodes()-1);

		::std::vector<real_type> H_supdiag(n-1, 0);
		::std::vector<real_type> H_diag(n-1, 0);
		::std::vector<real_type> H_subdiag(n-1, 0);

		switch (bound_cond_)
		{
			case clamped_spline_boundary_condition:
				H_diag[0] = 1.5*this->hk(0) + 2.0*this->hk(1); // \frac{3}{2}*h_0 + 2*h_1
				H_supdiag[0] = this->hk(1); // h_1
				m_[1] = this->uk(1) - 3.0*(this->dk(0)-lb_); // u_1 - 3*(d_0-S'(x_0))
				H_subdiag[n-2] = this->hk(n-2); // h_{n-2}
				H_diag[n-2] = 2.0*this->hk(n-2) + 1.5*this->hk(n-1); // 2*h_{n-2} + \frac{3}{2}*h_{n-1}
				m_[n-1] = this->uk(n-1) - 3.0*(ub_-this->dk(n-1)); // u_{n-1} - 3*(S'(x_{n})-d_{n-1})
				break;
			case natural_spline_boundary_condition:
				H_diag[0] = 2.0*(this->hk(0)+this->hk(1)); // 2*(h_0+h_1)
				H_supdiag[0] = this->hk(1); // h_1
				m_[1] = this->uk(1); // u_1
				H_subdiag[n-2] = this->hk(n-2); // h_{n-2}
				H_diag[n-2] = 2.0*(this->hk(n-2)+this->hk(n-1)); // 2*(h_{n-2}+h_{n-1})
				m_[n-1] = this->uk(n-1); // u_{n-1}
				break;
			case not_a_knot_spline_boundary_condition:
				H_diag[0] = 3.0*this->hk(0) + 2.0*this->hk(1) + this->hk(0)*this->hk(0)/this->hk(1); // 3*h_0 + 2*h_1 + \frac{h_0^2}{h_1}
				H_supdiag[0] = this->hk(1) - this->hk(0)*this->hk(0)/this->hk(1); // h_1 - \frac{h_0^2}{h_1}
				m_[1] = this->uk(1); // u_1
				H_subdiag[n-2] = this->hk(n-2) - this->hk(n-1)*this->hk(n-1)/this->hk(n-2); // h_{n-2} - \frac{h_{n-1}^2}{h_{n-2}}
				H_diag[n-2] = 2.0*this->hk(n-2) + 3.0*this->hk(n-1) + this->hk(n-1)*this->hk(n-1)/this->hk(n-2); // 2*h_{n-2} + 3*h_{n-1} + \frac{h_{n-1}^2}{h_{n-2}}
				m_[n-1] = this->uk(n-1); // u_{n-1}
				break;
			case parabolic_spline_boundary_condition:
				H_diag[0] = 3.0*this->hk(0) + 2.0*this->hk(1); // 3*h_0 + 2*h_1
				H_supdiag[0] = this->hk(1); // h_1
				m_[1] = this->uk(1); // u_1
				H_subdiag[n-2] = this->hk(n-2); // h_{n-2}
				H_diag[n-2] = 2.0*this->hk(n-2) + 3.0*this->hk(n-1); // 2*h_{n-2} + 3*h_{n-1}
				m_[n-1] = this->uk(n-1); // u_{n-1}
				break;
			case curvature_adjusted_spline_boundary_condition:
				H_diag[0] = 2.0*(this->hk(0)+this->hk(1)); // 2*(h_0 + h_1)
				H_supdiag[0] = this->hk(1); // h_1
				m_[1] = this->uk(1) - this->hk(0)*lb_; // u_1 - h_0*S''(x_0)
				H_subdiag[n-2] = this->hk(n-2); // h_{n-2}
				H_diag[n-2] = 2.0*(this->hk(n-2)+this->hk(n-1)); // 2*(h_{n-2} + h_{n-1})
				m_[n-1] = this->uk(n-1) - this->hk(n-1)*ub_; // u_{n-1} - h_{n-1}*S''(x_n)
				break;
		}
//DCS_DEBUG_TRACE("1.Subdiagonal: " << dcs::debug::to_string(H_subdiag.begin(), H_subdiag.end()));
//DCS_DEBUG_TRACE("1.Diagonal: " << dcs::debug::to_string(H_diag.begin(), H_diag.end()));
//DCS_DEBUG_TRACE("1.Supdiagonal: " << dcs::debug::to_string(H_supdiag.begin(), H_supdiag.end()));
//DCS_DEBUG_TRACE("1.Coefficients: " << dcs::debug::to_string(m_.begin()+1, m_.end()-1));

		for (::std::size_t k = 1; k < (n-2); ++k)
		{
			H_subdiag[k] = this->hk(k-1); // h_{k-1}
			H_diag[k] = 2.0*(this->hk(k-1)+this->hk(k)); // 2*(h_{k-1}+h_{k})
			H_supdiag[k] = this->hk(k); // h_k
			m_[k+1] = this->uk(k); // u_k
		}

DCS_DEBUG_TRACE("2.Subdiagonal: " << dcs::debug::to_string(H_subdiag.begin(), H_subdiag.end()));
DCS_DEBUG_TRACE("2.Diagonal: " << dcs::debug::to_string(H_diag.begin(), H_diag.end()));
DCS_DEBUG_TRACE("2.Supdiagonal: " << dcs::debug::to_string(H_supdiag.begin(), H_supdiag.end()));
DCS_DEBUG_TRACE("2.Coefficients: " << dcs::debug::to_string(m_.begin()+1, m_.end()-1));
		detail::tridiagonal_solver_inplace<real_type>(H_subdiag.begin(),
													  H_subdiag.end(),
													  H_diag.begin(),
													  H_supdiag.begin(),
													  m_.begin()+1);
DCS_DEBUG_TRACE("3.Unknowns: " << dcs::debug::to_string(m_.begin(), m_.end()));

		// Compute m_0 and m_n
		switch (bound_cond_)
		{
			case clamped_spline_boundary_condition:
				m_[0] = (3.0/this->hk(0))*(this->dk(0)-lb_) - m_[1]/2.0; // \frac{3}{h_0}(d_0-S'(x_0)) - \frac{m_1}{2}
				m_[n] = (3.0/this->hk(n-1))*(ub_-this->dk(n-1)) - m_[n-1]/2.0; // \frac{3}{h_{n-1}}(S'(x_n)-d_{n-1}) - \frac{m_{n-1}}{2}
				break;
			case natural_spline_boundary_condition:
				m_[0] = m_[n] = 0;
				break;
			case not_a_knot_spline_boundary_condition:
				m_[0] = m_[1] - this->hk(0)*(m_[2]-m_[1])/this->hk(1); // m_1 - \frac{h_0(m_2-m_1)}{h_1}
				m_[n] = m_[n-1] + this->hk(n-1)*(m_[n-1]-m_[n-2])/this->hk(n-2); // m_{n-1} + \frac{h_{n-1}(m_{n-1}-m_{n-2})}{h_{n-2}}
				break;
			case parabolic_spline_boundary_condition:
				m_[0] = m_[1]; // m_1
				m_[n] = m_[n-1]; // m_{n-1}
				break;
			case curvature_adjusted_spline_boundary_condition:
				m_[0] = lb_; // S''(x_0)
				m_[n] = ub_; // S''(x_n)
				break;
		}
//DCS_DEBUG_TRACE("4.Unknowns: " << dcs::debug::to_string(m_.begin(), m_.end()));
#else // 0
		if (n == 2)
		{
			if (bound_cond_ != clamped_spline_boundary_condition)
			{
				m_[0] = m_[1] = (this->value(1)-this->value(0))/(this->node(1)-this->node(0));
				return;
			}
		}
		else if (n == 3 && bound_cond_ == not_a_knot_spline_boundary_condition)
		{
			// Fast computation for not-a-knot spline when n==3
			const real_type dx_l = this->node(1)-this->node(0);
			const real_type dy_l = (this->value(1) - this->value(0))/dx_l;
			const real_type dx_r = this->node(2) - this->node(1);
			const real_type dy_r = (this->value(2) - this->value(1))/dx_r;
			const real_type w_l = dx_r/(dx_l + dx_r);
			const real_type w_r = 1 - w_l;
			m_[0] = (1 + w_r)*dy_l - w_r*dy_r;
			m_[1] = w_l*dy_l + w_r*dy_r;
			m_[2] = (1 + w_l)*dy_r - w_l*dy_l;
			return;
		}

		::std::vector<real_type> H_diag(n, 0);
		::std::vector<real_type> H_subdiag(n-1, 0);
		::std::vector<real_type> H_lastrow; // Only used by periodic splines, so it is resized if necessary
		::std::vector<real_type> qdy(n-1, 0);

		for (::std::size_t k = 0; k < (n-1); ++k)
		{
			H_subdiag[k] = 1.0/(this->node(k+1)-this->node(k));
			qdy[k] = (this->value(k+1)-this->value(k))*H_subdiag[k]*H_subdiag[k];
		}
		// Compute the coefficients matrix and the RHS for rows 1:n-2 (independent by spline type)
		for (::std::size_t k = 1; k < (n-1); ++k)
		{
			H_diag[k] = 2.0*(H_subdiag[k-1]+H_subdiag[k]);
			m_[k] = 3.0*(qdy[k-1]+qdy[k]);
		}

		// Compute first and last equation (dependent by spline type)
		::std::size_t loffs(0);
		::std::size_t roffs(0);
		switch (bound_cond_)
		{
			case clamped_spline_boundary_condition:
				// m_[0] and m_[n-1] are already known
				m_[0] = lb_;
				m_[n-1] = ub_;
				m_[1] = m_[1] - m_[0]*H_subdiag[0];
				m_[n-2] = m_[n-2] - m_[n-1]*H_subdiag[n-2];
				loffs = 1;
				roffs = 1;
				break;
			case natural_spline_boundary_condition:
				// S''(x_0) = 0
				H_diag[0] = 2.0*H_subdiag[0];
				m_[0] = 3.0*qdy[0];
				// S''(x_{n-1}) = 0
				H_diag[n-1] = 2.0*H_subdiag[n-2];
				m_[n-1] = 3.0*qdy[n-2];
				break;
			case not_a_knot_spline_boundary_condition:
				{
					// S'''(x_1^-) = S'''(x_1^+)
					real_type r(H_subdiag[1]/H_subdiag[0]);
					real_type rp1sq((1+r)*(1+r));
					H_diag[0] = H_subdiag[0]/(1+r);
					m_[0] = ((3.0*r+2)*qdy[0]+r*qdy[1])/rp1sq;
					// S'''(x_{n-2}^-) = S'''(x_{n-2}^+)
					r = H_subdiag[n-3]/H_subdiag[n-2];
					rp1sq = (1+r)*(1+r);
					H_diag[n-1] = H_subdiag[n-2]/(1+r);
					m_[n-1] = ((3.0*r+2)*qdy[n-2]+r*qdy[n-3])/rp1sq;
				}
				break;
			case parabolic_spline_boundary_condition:
				throw ::std::runtime_error("TODO");
				//break;
			case periodic_spline_boundary_condition:
				H_diag[0] = 2.0*(H_subdiag[0]+H_subdiag[n-2]);
				m_[0] = 3.0*(qdy[0]+qdy[n-2]);
				H_lastrow.resize(n-1);
				H_lastrow[0] = H_subdiag[n-2];
				::std::fill(H_lastrow.begin()+1, H_lastrow.end(), 0.0);
				H_lastrow[n-3] = H_subdiag[n-3];
				roffs = 1;
				break;
			case curvature_adjusted_spline_boundary_condition:
				throw ::std::runtime_error("TODO");
				//break;
		}
//DCS_DEBUG_TRACE("1.Subdiagonal: " << dcs::debug::to_string(H_subdiag.begin(), H_subdiag.end()));
//DCS_DEBUG_TRACE("1.Diagonal: " << dcs::debug::to_string(H_diag.begin(), H_diag.end()));
//DCS_DEBUG_TRACE("1.Supdiagonal: " << dcs::debug::to_string(H_supdiag.begin(), H_supdiag.end()));
//DCS_DEBUG_TRACE("1.Coefficients: " << dcs::debug::to_string(m_.begin()+1, m_.end()-1));

		// check: avoid uint underflow
		DCS_DEBUG_ASSERT( n >= roffs );

DCS_DEBUG_TRACE("2.Subdiagonal: " << dcs::debug::to_string(H_subdiag.begin()+loffs, H_subdiag.end()-roffs));
DCS_DEBUG_TRACE("2.Diagonal: " << dcs::debug::to_string(H_diag.begin()+loffs, H_diag.end()-roffs));
DCS_DEBUG_TRACE("2.Coefficients: " << dcs::debug::to_string(m_.begin()+loffs, m_.end()-roffs));
		if (bound_cond_ != periodic_spline_boundary_condition)
		{
			detail::tridiagonal_ldl_solver_inplace<real_type>(H_diag,
															  H_subdiag,
															  m_,
															  n-roffs,
															  loffs);
		}
		else
		{
			detail::cyclic_tridiagonal_ldl_solver_inplace<real_type>(H_diag,
																	 H_subdiag,
																	 H_lastrow,
																	 m_,
																	 n-roffs,
																	 loffs);
			m_[n-1] = m_[0];
		}
DCS_DEBUG_TRACE("3.Unknowns: " << dcs::debug::to_string(m_.begin(), m_.end()));
#endif //0
	}

	private: real_type do_interpolate(real_type x) const
	{
		const ::std::size_t k = this->find(x);
		const ::std::vector<real_type> coeffs = this->coefficients(k);
		const real_type w = x - this->node(k);

		return	coeffs[0] + w*(coeffs[1] + w*(coeffs[2] + w*coeffs[3]));
	}


	private: spline_boundary_condition_category bound_cond_; ///< The boundary condition category
	private: real_type lb_; ///< Leftmost endpoint for the boundary condition
	private: real_type ub_; ///< Rightmost endpoint for the boundary condition
	private: ::std::vector<real_type> m_; ///< Vector of second derivatives
}; // cubic_spline_interpolator

}}} // Namespace dcs::math::curvefit


#endif // DCS_MATH_CURVEFIT_INTERPOLATION_CUBIC_SPLINE_HPP
