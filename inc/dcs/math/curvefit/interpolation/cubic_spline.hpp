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
#include <dcs/math/curvefit/detail/tridiag_solvers.hpp>
#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <dcs/math/traits/float.hpp>
#include <limits>


namespace dcs { namespace math { namespace curvefit {

enum spline_boundary_condition_category
{
	clamped_spline_boundary_condition, ///< Clamped cubic spline boundary condition
	natural_spline_boundary_condition, ///< Natural cubic spline boundary condition
	not_a_knot_spline_boundary_condition, ///< Not-a-knot boundary condition
//	parabolic_spline_boundary_condition, ///< Parabolically terminated spline boundary condition
	periodic_spline_boundary_condition, ///< Periodic cubic spline boundary condition
//	curvature_adjusted_spline_boundary_condition ///< Endpoint curvature-adjusted spline boundary condition
	generalized_natural_spline_boundary_condition ///< Generalized natural spline boundary condition
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
 *  h_{k-1}s_{k-1}+2(h_{k-1}+h_{k})s_{k}+h_ks_{k+1} = u_k, \quad k=1,2,\ldots,n-1
 * \f]
 * where \f$s_k\f$, for \f$k=0,1,\ldots,n\f$ are the unknowns and:
 * \f{align}
 *  h_k &= x_{k+1}-x_k,\\
 *  d_k &= \frac{y_{k+1}-y_k}{h_k},\\
 *  u_k &= 6(d_k-d_{k-1}),\\
 * \f}
 * for \f$k=1,2,\ldots,n-1\f$.
 *
 * This is a tridiagonal linear system with $n-1$ linear equations involving
 * \f$n+1\f$ unknowns.
 * Thus two additional equations are needed in order to eliminate \f$s_0\f$ from
 * the first equation and \f$s_n\f$ from the \f$(n-1)\f$-st equation.
 * This is obtained by fixing the so called <em>boundary conditions</em>.
 *
 * The currently supported boundary conditions are:
 * - <b>Clamped (or complete)) spline condition</b>: it consists in specifying
 *   both \f$S'(x_0)\f$ and \f$S'(x_n)\f$, thus resulting in:
 *   \f{align}
 *    s_0 &= \frac{3}{h_0}(d_0-S'(x_0))-\frac{s_1}{2},\\
 *    s_n &= \frac{3}{h_{n-1}}(S'(x_n)-d_{n-1})-\frac{s_{n-1}}{2}.
 *   \f}
 * - <b>Generalized natural spline condition</b>: it consists in setting
 *   \f$S''(x_0)=\alpha and S''(x_n)=\beta\f$, thus resulting in the following
 *   two additional equations (the first and the in the system, respectively):
 *   \f{align}
 *    2s_0+s_1 &= 3\frac{y_1-y_0}{h_0}+h_0\frac{\alpha}{2},\\
 *    s_{n-1}+2s_n &= 3\frac{y_n-y_{n-1}}{h_{n-1}}+h_{n-1}\frac{\beta}{2}.
 *   \f}
 *   It is sometimes referred to as <em>second derivative matching boundary condition</em>.
 * - <b>Natural (or free) spline condition</b>: it consists in setting
 *   \f$S''(x_0)=S''(x_n)=0\f$, thus resulting in:
 *   \f{align}
 *    s_0 &= 0,\\
 *    s_n &= 0.
 *   \f}
 *   It is sometimes referred to as <em>zero curvature boundary condition</em>.
 *   Note: this is a special case of the <em>generalized natural spline
 *   condition</em>, by setting \f$\alpha=\beta=0\f$.
 * - <b>Not-a-Knot spline condition</b>: it consists in extrapolating
 *   \f$S''(x)\f$ to the endpoints,(i.e., it extrapolates S''(x_0) from the
 *   interior nodes at \f$x_1$ and \f$x_2\f$, and \f$S''(x_n)$ from the interior
 *   nodes at \f$x_{n-1}\f$ and \f$x_{n-2}\f$), thus resulting in:
 *   \f{align}
 *    s_0 &= s_1-\frac{h_0(s_2-s_1)}{h_1},\\
 *    s_n &= s_{n-1}+\frac{h_{n-1}(s_{n-1}-s_{n-2})}{h_{n-2}}.
 *   \f}
 *   It is sometimes referred to as <em>third derivative matching boundary condition</em>
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
 *    s_0 &= s_1,\\
 *    s_n &= s_{n-1}.
 *   \f}
 * - <b>Periodic spline</b>: it consists in requiring that
 *   \f{align}
 *    S(x_0) &= S(x_n),
 *    S'(x_0) &= S'(x_n),
 *    S''(x_0) &= S''(x_n),
 *   \f}
 *   The distance \f$p=(x_n-x_0)\f$ is called <em>period</em> and the spline
 *   \f$S(x)\f$ is such that \f$S(x)=S(x+kp)\f$ for \f$k\in\mathbb{Z}\f$.
 * - <b>Endpoint curvature-adjusted spline</b>: it consists in specifying
 *   \f$S''(x)\f$ at each endpoint, thus resulting in:
 *   \f{align}
 *    s_0 &= S''(x_0),\\
 *    s_n &= S''(x_n).
 *   \f}
 * .
 *
 * Maths for splines are mostly taken from (de Boor,2001) and (Englen-Muellges,1996).
 *
 * References:
 * -# <em>Carl de Boor.</em>
 *    <b>A Practical Guide to Splines, Revised Edition.</b>
 *    Spinger-Verlag New York, Inc., 2001.
 * -# <em>Gisela Engeln-Muellges and Frank Uhlig.</em>
 *    <b>Numerical Algorithms with C.</b>
 *    Spinger-Verlag, Inc., 1996.
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
	  s_(this->num_nodes())
	{
		this->init();
	}

	public: ::std::vector<real_type> coefficients(::std::size_t k) const
	{
		// pre: k < n
		DCS_ASSERT( k < this->num_nodes(),
					DCS_EXCEPTION_THROW( ::std::invalid_argument,
										 "Spline coefficients are defined for k=0,...,N-1, where N is the number of nodes" ));

		::std::vector<real_type> coeffs(4);

		const real_type hk(this->node(k+1)-this->node(k));
		const real_type dk((this->value(k+1)-this->value(k))/hk);
		coeffs[0] = this->value(k);
		coeffs[1] = dk - hk*(s_[k+1]+2.0*s_[k])/3.0;
		coeffs[2] = s_[k];
		coeffs[3] = (s_[k+1]-s_[k])/(3.0*hk);

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

	private: void init()
	{
		// pre: check that bounds are present when they are needed
		DCS_ASSERT( (bound_cond_ != clamped_spline_boundary_condition /*&& bound_cond_ != curvature_adjusted_spline_boundary_condition*/)
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
		 * - \f$d_k=\frac{y_{k+1}-y_k}{h_k}\f$
		 * Furthermore, for \f$k=1,\ldots,n-2\f$, let \f$b_k=3(h_{k}d_{k-1}+h_{k-1}d_{k})\f$.
		 * We now solve the following tridiagonal linear system:
		 * \f[
		 *  Hs = b \quad \text{subject to boundary conditions to fix $s_0$ and $s_{n-1}$}
		 * \f]
		 * where:
		 * \f[
		 *  H=\begin{pmatrix}
		 *     ?   & \ldots     & \ldots     & \ldots  & \ldots             & ?       \\
		 *     h_1 & 2(h_1+h_0) & h_0        & 0       & \ldots             & 0       \\
		 *     0   & h_2        & 2(h_2+h_1) & h_1     & \ddots             & 0       \\
		 *     0   & \ddots     & \ddots     & \ddots  & \ddots             & 0       \\
		 *     0   & \ddots     & \ddots     & h_{n-2} & 2(h_{n-2}+h_{n-3}) & h_{n-3} \\
		 *     ?   & \ldots     & l\dots     & ?       & ?                  & ?
		 *    \end{pmatrix}
		 * \f]
		 * \f[
		 *  s=\begin{pmatrix}
		 *     s_0 \\ s_1 \\ s_2 \\ \vdots \\ s_{n-1}
		 *    \end{pmatrix}
		 * \f]
		 * \f[
		 *  b=\begin{pmatrix}
		 *     b_0 \\ b_2 \\ u_3 \\ \vdots \\ b_{n-1}
		 *    \end{pmatrix}
		 * \f]
		 * This system can be efficiently solved in linear time with the Thomas algorithm
		 */

		// Fast computations for small n
		if (n == 3)
		{
			switch (bound_cond_)
			{
				case clamped_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT d0 = (this->value(1)-this->value(0))/h0;
						const RealT h1 = this->node(2)-this->node(1);
						const RealT d1 = (this->value(2)-this->value(1))/h1;
						s_[1] = (3.0*(d1-d0)+lb_-ub_)/(h0+h1);
						s_[0] = 1.5*(d0-lb_)/h0-s_[1]/2.0;
						s_[2] = 1.5*(ub_-d1)/h1-s_[1]/2.0;
					}
					return;
				case natural_spline_boundary_condition:
					lb_ = ub_ = 0;
				case generalized_natural_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT d0 = (this->value(1)-this->value(0))/h0;
						const RealT h1 = this->node(2)-this->node(1);
						const RealT d1 = (this->value(2)-this->value(1))/h1;
						s_[0] = lb_/2.0;
						s_[2] = ub_/2.0;
						s_[1] = (3.0*(d1-d0)-(h0*lb_+h1*ub_)/2.0)/(2.0*(h0+h1));
					}
					return;
				case periodic_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT d0 = (this->value(1)-this->value(0))/h0;
						const RealT h1 = this->node(2)-this->node(1);
						const RealT d1 = (this->value(2)-this->value(1))/h1;
						const RealT g0 = 3.0*(d1-d0);
						const RealT g1 = 3.0*((this->value(1)-this->value(2))/h0-d1);
						const RealT a = 2.0*(h0+h1);
						const RealT b = h0+h1;
						const RealT det = 3.0*(h0+h1)*(h0+h1);
						s_[1] = (a*g0-b*g1)/det;
						s_[0] = s_[2] = (-b*g0+a*g1)/det;
					}
					return;
				case not_a_knot_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT h1 = this->node(2)-this->node(1);
						const RealT u0 = this->value(1)-this->value(0);
						const RealT u1 = this->value(2)-this->value(1);
						//const RealT d0 = (this->value(1)-this->value(0))/h0;
						//s_[1] = (3.0/(h0+h1))*(u1-h1*d0)/(h0+2.0*h1);
						s_[1] = (3.0/(h1+h0))*((h0/h1)*u1-u0)/(h0+2.0*h1);
						s_[0] = s_[1]+h0/h1*s_[1];
						s_[2] = s_[1]+h1/h0*(s_[1]-s_[0]);
					}
					return;
				default:
					// Nothing special
					break;
			}
		}
		else if (n == 4 && bound_cond_ == not_a_knot_spline_boundary_condition)
		{
			// The case for n=4 must be treated separately since the H matrix is not symmetric

			const RealT h0 = this->node(1)-this->node(0);
			const RealT h1 = this->node(2)-this->node(1);
			const RealT h2 = this->node(3)-this->node(2);
			const RealT d0 = (this->value(1)-this->value(0))/h0;
			const RealT d1 = (this->value(2)-this->value(1))/h1;
			const RealT u1 = this->value(2)-this->value(1);
			const RealT u2 = this->value(3)-this->value(2);

			::std::vector<real_type> H_diag(2, 0);
			::std::vector<real_type> H_subdiag(1, 0);
			::std::vector<real_type> H_supdiag(1, 0);
			::std::vector<real_type> b(2, 0);

			H_diag[0] = h0+2.0*h1;
			H_diag[1] = 2.0*h1+h2;
			H_subdiag[0] = h1-h2;
			H_supdiag[0] = h1-h0;
			b[0] = (3.0/(h0+h1))*(u1-h1*d0);
			//b[1] = (3.0/(h1+h2))*(u2-h2*d1);
			b[1] = (3.0/(h1+h2))*((h1/h2)*u2-u1);
			detail::tridiagonal_solver_inplace<real_type>(H_subdiag, H_diag, H_supdiag, b, 2);
			s_[1] = b[0];
			s_[2] = b[1];
			s_[0] = s_[1]+h0/h1*(s_[1]-s_[2]);
			s_[3] = s_[2]+h2/h1*(s_[2]-s_[1]);
			return;
		}

		::std::vector<real_type> H_diag(n-1, 0);
		::std::vector<real_type> H_subdiag(n-2, 0);
		//::std::vector<real_type> H_supdiag; //(n-1, 0);

		// Fill the parts of matrix H and of vector s_ that are common to all splines.
		// That is, H[1:(n-2),1:(n-2)]:
		//     2(h_1+h_0) & h_1        &         &                    & 0                  \newline
		//     h_1        & 2(h_2+h_1) & h_2     &                    & 0                  \newline
		//                & \ddots     & \ddots  & \ddots             & 0                  \newline
		//                &            & h_{n-4} & 2(h_{n-3}+h_{n-4}) & h_{n-3}            \newline
		//                &            &         & h_{n-3}            & 2(h_{n-3}+h_{n-2}) \newline
		// and s_[1:(n-2)]:
		//     3(d_1-d_0)\f$.
		for (::std::size_t k = 0; k < (n-2); ++k)
		{
			const real_type kp1 = k+1;
			const real_type kp2 = k+2;
			const real_type hk = this->node(kp1)-this->node(k); // h_k
			const real_type hkp1 = this->node(kp2)-this->node(kp1); // h_{k+1}
			const real_type dk = (this->value(kp1)-this->value(k))/hk; // d_k
			const real_type dkp1 = (this->value(kp2)-this->value(kp1))/hkp1; // d_{k+1}

			H_subdiag[k] = hkp1;
			H_diag[k] = 2.0*(hk+hkp1);
			s_[kp1] = 3.0*(dkp1-dk); // NOTE: s_[0] is never filled since it is part of the boundary conditions
		}

		// Compute first and last equation (dependent by spline type)
		switch (bound_cond_)
		{
			case clamped_spline_boundary_condition:
				// S'(x_0) and S'(x_{n-1}) are already known
				{
					const RealT h0 = this->node(1)-this->node(0);
					const RealT h1 = this->node(2)-this->node(1);
					const RealT d0 = (this->value(1)-this->value(0))/h0;
					const RealT d1 = (this->value(2)-this->value(1))/h1;
					const RealT hnm2 = this->node(n-1)-this->node(n-2);
					const RealT hnm3 = this->node(n-2)-this->node(n-3);
					const RealT dnm2 = (this->value(n-1)-this->value(n-2))/hnm2;
					const RealT dnm3 = (this->value(n-2)-this->value(n-3))/hnm3;
					H_diag[0] = (1.5*h0+2.0*h1);
					H_subdiag[0] = h1;
					s_[1] = 3.0*(d1-0.5*(3.0*d0-lb_));
					H_diag[n-3] = 2.0*hnm3+1.5*hnm2;
					H_subdiag[n-3] = hnm3;
					s_[n-2] = 3.0*(0.5*(3.0*dnm2-ub_)-dnm3);
				}
				break;
			case natural_spline_boundary_condition:
				// S''(x_0) = 0 and S''(x_{n-1})=0
				lb_ = ub_ = 0;
			case generalized_natural_spline_boundary_condition:
				// S''(x_0) and S''(x_{n-1}) are known
				{
					const RealT h0 = this->node(1)-this->node(0);
					const RealT h1 = this->node(2)-this->node(1);
					const RealT d0 = (this->value(1)-this->value(0))/h0;
					const RealT d1 = (this->value(2)-this->value(1))/h1;
					s_[0] = lb_/2.0;
					H_diag[0] = 2.0*(h0+h1);
					H_subdiag[0] = h1;
					s_[1] = 3.0*(d1-d0)-h0*s_[0];
					const RealT hnm3 = this->node(n-2)-this->node(n-3);
					const RealT hnm2 = this->node(n-1)-this->node(n-2);
					const RealT dnm3 = (this->value(n-2)-this->value(n-3))/hnm3;
					const RealT dnm2 = (this->value(n-1)-this->value(n-2))/hnm2;
					s_[n-1] = ub_/2.0;
					H_subdiag[n-3] = hnm3;
					H_diag[n-3] = 2.0*(hnm3+hnm2);
					s_[n-2] = 3.0*(dnm2-dnm3)-hnm2*s_[n-1];
				}
				break;
			case not_a_knot_spline_boundary_condition:
				{
					const RealT h0 = this->node(1)-this->node(0);
					const RealT h1 = this->node(2)-this->node(1);
					const RealT d0 = (this->value(1)-this->value(0))/h0;
					const RealT u1 = this->value(2)-this->value(1);
					H_diag[0] = h0+2.0*h1;
					H_subdiag[0] = h1-h0;
					s_[1] = (3.0/(h1+h0))*(u1-h1*d0);
					const RealT hnm3 = this->node(n-2)-this->node(n-3);
					const RealT hnm2 = this->node(n-1)-this->node(n-2);
					const RealT unm3 = this->value(n-2)-this->value(n-3);
					const RealT dnm2 = (this->value(n-1)-this->value(n-2))/hnm2;
					H_diag[n-3] = hnm3-hnm2;
					H_subdiag[n-3] = 2.0*hnm3+hnm2;
					s_[n-2] = (3.0/(hnm2+hnm3))*(hnm3*dnm2-unm3);
				}
				break;
//			case parabolic_spline_boundary_condition:
//				//break;
//				throw ::std::runtime_error("TODO");
			case periodic_spline_boundary_condition:
				{
					H_diag.push_back(0);
					H_subdiag.push_back(0);

					const ::std::size_t k = n-2;
					const RealT hk = this->node(k+1)-this->node(k);
					const RealT h0 = this->node(1)-this->node(0);
					const RealT dk = (!detail::is_zero(hk) ? (this->value(k+1)-this->value(k))/hk : 0);
					const RealT d0 = (!detail::is_zero(h0) ? (this->value(1)-this->value(0))/h0 : 0);
					H_subdiag[k] = h0;
					H_diag[k] = 2.0*(h0+hk);
					s_[k+1] = 3.0*(d0-dk);
				}
				break;
//			case curvature_adjusted_spline_boundary_condition:
//				throw ::std::runtime_error("TODO");
//				//break;
		}

		if (bound_cond_ != periodic_spline_boundary_condition)
		{
			::std::vector<RealT> aux_s(s_.begin()+1, s_.end()-1);

			detail::symmetric_tridiagonal_solver_inplace<real_type>(H_diag,
																	H_subdiag,
																	aux_s,
																	n-2);
			::std::copy(aux_s.begin(), aux_s.end(), s_.begin()+1);

			switch (bound_cond_)
			{
 				case clamped_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT d0 = (this->value(1)-this->value(0))/h0;
						const RealT hnm2 = this->node(n-1)-this->node(n-2);
						const RealT dnm2 = (this->value(n-1)-this->value(n-2))/hnm2;
						s_[0] = (1.0/(2.0*h0))*(3.0*(d0-lb_)-s_[1]*h0);
						s_[n-1] = -(1.0/(2.0*hnm2))*(3.0*(dnm2-ub_)+s_[n-2]*hnm2);
					}
					break;
 				case not_a_knot_spline_boundary_condition:
					{
						const RealT h0 = this->node(1)-this->node(0);
						const RealT h1 = this->node(2)-this->node(1);
						const RealT hnm3 = this->node(n-2)-this->node(n-3);
						const RealT hnm2 = this->node(n-1)-this->node(n-2);
						s_[0] = s_[1]+h0/h1*(s_[1]-s_[2]);
						s_[n-1] = s_[n-2]+hnm2/hnm3*(s_[n-2]-s_[n-3]);
					}
					break;
				default:
					break;
			}
		}
		else
		{
			::std::vector<RealT> aux_s(s_.begin()+1, s_.end());

			detail::symmetric_cyclic_tridiagonal_solver_inplace<real_type>(H_diag,
																		   H_subdiag,
																		   aux_s,
																		   n-1);

			::std::copy(aux_s.begin(), aux_s.end(), s_.begin()+1);
			s_[0] = s_[n-1];
		}
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
	private: ::std::vector<real_type> s_; ///< Vector of second derivatives
}; // cubic_spline_interpolator

}}} // Namespace dcs::math::curvefit


#endif // DCS_MATH_CURVEFIT_INTERPOLATION_CUBIC_SPLINE_HPP
