/**
 * \file test/src/dcs/test/math/curvefit/spline.cpp
 *
 * \brief Test suite for spline interpolation.
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


#include <dcs/debug.hpp>
#include <dcs/math/curvefit/interpolation/cubic_spline.hpp>
#include <dcs/test.hpp>


namespace dmc = dcs::math::curvefit;


const double tol = 1e-5;

DCS_TEST_DEF( clamped_cubic_spline_1 )
{
	DCS_TEST_TRACE("Clamped cubic spline #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	std::vector<real_type> y(n);
	y[0] = 0;
	y[1] = 0.5;
	y[2] = 2;
	y[3] = 1.5;
	real_type lb(0.2);
	real_type ub(-1);
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0;
	expected_coeffs[0][1] =  0.2;
	expected_coeffs[0][2] = -0.18;
	expected_coeffs[0][3] =  0.48;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  1.28;
	expected_coeffs[1][2] =  1.26;
	expected_coeffs[1][3] = -1.04;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] =  0.68;
	expected_coeffs[2][2] = -1.86;
	expected_coeffs[2][3] =  0.68;
	real_type x_test(0.5);
	real_type y_test(0.115);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::clamped_spline_boundary_condition,
													 lb,
													 ub);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("Node x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
	// Check interpolation at a given point
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << interp(x_test) );
	DCS_TEST_CHECK_CLOSE(interp(x_test), y_test, tol);
}

DCS_TEST_DEF( clamped_cubic_spline_2 )
{
	DCS_TEST_TRACE("Clamped cubic spline #2");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	real_type lb(0.2);
	real_type ub(-1);
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.5;
	expected_coeffs[0][1] =  0.2;
	expected_coeffs[0][2] = -1.7625;
	expected_coeffs[0][3] =  1.0625;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0;
	expected_coeffs[1][1] = -0.1375;
	expected_coeffs[1][2] =  1.425;
	expected_coeffs[1][3] = -0.348611111111111;

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::clamped_spline_boundary_condition,
													 lb,
													 ub);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

DCS_TEST_DEF( natural_cubic_spline_1 )
{
	DCS_TEST_TRACE("Natural cubic spline #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.0;
	y[1] = 0.5;
	y[2] = 2.0;
	y[3] = 1.5;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] = 0;
	expected_coeffs[0][1] = 0.1;
	expected_coeffs[0][2] = 0;
	expected_coeffs[0][3] = 0.4;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  1.3;
	expected_coeffs[1][2] =  1.2;
	expected_coeffs[1][3] = -1;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] =  0.7;
	expected_coeffs[2][2] = -1.8;
	expected_coeffs[2][3] =  0.6;
	real_type x_test(0.5);
	real_type y_test(0.1);


	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::natural_spline_boundary_condition);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("Node x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
	// Check interpolation at a given point
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << interp(x_test) );
	DCS_TEST_CHECK_CLOSE(interp(x_test), y_test, tol);
}

DCS_TEST_DEF( natural_cubic_spline_2 )
{
	DCS_TEST_TRACE("Natural cubic spline #2");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.5;
	expected_coeffs[0][1] = -0.6875;
	expected_coeffs[0][2] = -0;
	expected_coeffs[0][3] =  0.1875;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0;
	expected_coeffs[1][1] = -0.125;
	expected_coeffs[1][2] =  0.5625;
	expected_coeffs[1][3] = -0.0625;

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::natural_spline_boundary_condition);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

DCS_TEST_DEF( notaknot_cubic_spline_1 )
{
	DCS_TEST_TRACE("Not-a-knot cubic spline #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.0;
	y[1] = 0.5;
	y[2] = 2.0;
	y[3] = 1.5;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.0;
	expected_coeffs[0][1] = -1.0;
	expected_coeffs[0][2] =  2.0;
	expected_coeffs[0][3] = -0.5;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  1.5;
	expected_coeffs[1][2] =  0.5;
	expected_coeffs[1][3] = -0.5;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] =  1.0;
	expected_coeffs[2][2] = -1.0;
	expected_coeffs[2][3] = -0.5;
	real_type x_test(0.5);
	real_type y_test(-0.0625);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::not_a_knot_spline_boundary_condition);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
	// Check interpolation at a given point
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << interp(x_test) );
	DCS_TEST_CHECK_CLOSE(interp(x_test), y_test, tol);
}

DCS_TEST_DEF( notaknot_cubic_spline_2 )
{
	DCS_TEST_TRACE("Not-a-knot cubic spline #2");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.5;
	expected_coeffs[0][1] = -0.875;
	expected_coeffs[0][2] =  0.375;
	expected_coeffs[0][3] =  0;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0;
	expected_coeffs[1][1] = -0.125;
	expected_coeffs[1][2] =  0.375;
	expected_coeffs[1][3] =  0;

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::not_a_knot_spline_boundary_condition);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

DCS_TEST_DEF( parabolic_cubic_spline_1 )
{
	DCS_TEST_TRACE("Parabolically terminated cubic spline #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.0;
	y[1] = 0.5;
	y[2] = 2.0;
	y[3] = 1.5;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.0;
	expected_coeffs[0][1] = -0.375;
	expected_coeffs[0][2] =  0.875;
	expected_coeffs[0][3] =  0.0;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  1.375;
	expected_coeffs[1][2] =  0.875;
	expected_coeffs[1][3] = -0.75;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] =  0.875;
	expected_coeffs[2][2] = -1.375;
	expected_coeffs[2][3] =  0.0;
	real_type x_test(0.5);
	real_type y_test(0.03125);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::parabolic_spline_boundary_condition);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
	// Check interpolation at a given point
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << interp(x_test) );
	DCS_TEST_CHECK_CLOSE(interp(x_test), y_test, tol);
}

DCS_TEST_DEF( parabolic_cubic_spline_2 )
{
	DCS_TEST_TRACE("Parabolically terminated cubic spline #2");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::parabolic_spline_boundary_condition);

	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

DCS_TEST_DEF( curvature_adjusted_cubic_spline_1 )
{
	DCS_TEST_TRACE("Curvature-adjusted cubic spline #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	x[3] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.0;
	y[1] = 0.5;
	y[2] = 2.0;
	y[3] = 1.5;
	real_type lb(-0.3);
	real_type ub(3.3);
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] = 0.0;
	expected_coeffs[0][1] = 0.1;
	expected_coeffs[0][2] = 0.0;
	expected_coeffs[0][3] = 0.4;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  1.3;
	expected_coeffs[1][2] =  1.2;
	expected_coeffs[1][3] = -1.0;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] =  0.7;
	expected_coeffs[2][2] = -1.8;
	expected_coeffs[2][3] =  0.6;
	real_type x_test(0.5);
	real_type y_test(0.1);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::curvature_adjusted_spline_boundary_condition,
													 lb,
													 ub);

	// Check spline coefficients
	for (std::size_t k = 0; k < (n-1); ++k)
	{
		std::vector<real_type> coeffs = interp.coefficients(k);

		for (std::size_t i = 0; i < 4; ++i)
		{
			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
		}
	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
	// Check interpolation at a given point
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << interp(x_test) );
	DCS_TEST_CHECK_CLOSE(interp(x_test), y_test, tol);
}

DCS_TEST_DEF( curvature_adjusted_cubic_spline_2 )
{
	DCS_TEST_TRACE("Curvature-adjusted cubic spline #2");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	real_type lb(0.2);
	real_type ub(-1);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::curvature_adjusted_spline_boundary_condition,
													 lb,
													 ub);

	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

int main()
{
	DCS_TEST_SUITE("Spline interpolation");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( clamped_cubic_spline_1 );
		DCS_TEST_DO( clamped_cubic_spline_2 );
		DCS_TEST_DO( natural_cubic_spline_1 );
		DCS_TEST_DO( natural_cubic_spline_2 );
		DCS_TEST_DO( notaknot_cubic_spline_1 );
		DCS_TEST_DO( notaknot_cubic_spline_2 );
//		DCS_TEST_DO( parabolic_cubic_spline_1 );
//		DCS_TEST_DO( parabolic_cubic_spline_2 );
//		DCS_TEST_DO( curvature_adjusted_cubic_spline_1 );
//		DCS_TEST_DO( curvature_adjusted_cubic_spline_2 );
	DCS_TEST_END();
}
