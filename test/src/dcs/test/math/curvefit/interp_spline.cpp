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

	/*
	 * To test with MATLAB/Octave
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 1.5]
	 * > cs = spline(x,[0.2 y -1])
	 * > ppval(cs,0.5)
	 *
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 1.5]
	 * > cs = csape(x,y, 'complete', [0.2 -1])
	 * > ppval(cs,0.5)
	 */

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
	expected_coeffs[0][0] =  0.00;
	expected_coeffs[0][1] =  0.20;
	expected_coeffs[0][2] = -0.18;
	expected_coeffs[0][3] =  0.48;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.50;
	expected_coeffs[1][1] =  1.28;
	expected_coeffs[1][2] =  1.26;
	expected_coeffs[1][3] = -1.04;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.00;
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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("Node x = " << x[i] << " ==> " << yy );
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( clamped_cubic_spline_2 )
{
	DCS_TEST_TRACE("Clamped cubic spline #2");

	typedef double real_type;

	/*
	 * To test with MATLAB/Octave
	 * > x = [-1 0 3]
	 * > y = [0.5 0 3]
	 * > cs = spline(x,[0.2 y -1])
	 * > ppval(cs,0.5)
	 *
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3]
	 * > y = [0.5 0 3]
	 * > cs = csape(x,y, 'complete', [0.2 -1])
	 * > ppval(cs,0.5)
	 */

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
	expected_coeffs[0][0] =  0.5000;
	expected_coeffs[0][1] =  0.2000;
	expected_coeffs[0][2] = -1.7625;
	expected_coeffs[0][3] =  1.0625;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.00000;
	expected_coeffs[1][1] = -0.13750;
	expected_coeffs[1][2] =  1.42500;
	expected_coeffs[1][3] = -0.34861;
	real_type x_test(0.5);
	real_type y_test(0.24392361);

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( clamped_cubic_spline_3 )
{
	DCS_TEST_TRACE("Clamped cubic spline #3");

	typedef double real_type;

	/*
	 * To test with MATLAB/Octave
	 * > x = [-1 0 3 6 10]
	 * > y = [0.5 0 3 4 -1]
	 * > cs = spline(x,[0.2 y -1])
	 * > ppval(cs,0.5)
	 *
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3 6 10]
	 * > y = [0.5 0 3 4 -1]
	 * > cs = csape(x,y, 'complete', [0.2 -1])
	 * > ppval(cs,0.5)
	 */

	const std::size_t n(5);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	x[3] = 6;
	x[4] = 10;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	y[3] = 4;
	y[4] = -1;
	real_type lb(0.2);
	real_type ub(-2);
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.500000000000000;
	expected_coeffs[0][1] =  0.199999999999999;
	expected_coeffs[0][2] = -1.485945273631838;
	expected_coeffs[0][3] =  0.785945273631840;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.000000000000000;
	expected_coeffs[1][1] = -0.414054726368159;
	expected_coeffs[1][2] =  0.871890547263681;
	expected_coeffs[1][3] = -0.133512990602543;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  3.000000000000000;
	expected_coeffs[2][1] =  1.212437810945274;
	expected_coeffs[2][2] = -0.329726368159204;
	expected_coeffs[2][3] =  0.012230514096186;
	expected_coeffs[3] = std::vector<real_type>(4);
	expected_coeffs[3][0] =  4.000000000000000;
	expected_coeffs[3][1] = -0.435696517412935;
	expected_coeffs[3][2] = -0.219651741293532;
	expected_coeffs[3][3] =  0.004018967661692;
	real_type x_test(0.5);
	real_type y_test(-0.005743850193477);

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( natural_cubic_spline_1 )
{
	DCS_TEST_TRACE("Natural cubic spline #1");

	/*
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 1.5]
	 * > cs = csape(x,y, 'variational')
	 * > ppval(cs,0.5)
	 */

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("Node x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( natural_cubic_spline_2 )
{
	DCS_TEST_TRACE("Natural cubic spline #2");

	/*
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3]
	 * > y = [0.5 0 3]
	 * > cs = csape(x,y, 'variational')
	 * > ppval(cs,0.5)
	 */

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
	expected_coeffs[0][0] =  0.5000;
	expected_coeffs[0][1] = -0.6875;
	expected_coeffs[0][2] = -0.0000;
	expected_coeffs[0][3] =  0.1875;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.0000;
	expected_coeffs[1][1] = -0.1250;
	expected_coeffs[1][2] =  0.5625;
	expected_coeffs[1][3] = -0.0625;
	real_type x_test(0.5);
	real_type y_test(0.0703125);


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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( natural_cubic_spline_3 )
{
	DCS_TEST_TRACE("Natural cubic spline #3");

	/*
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3 6 10]
	 * > y = [0.5 0 3 4 -1]
	 * > cs = csape(x,y, 'variational')
	 * > ppval(cs,0.5)
	 */

	typedef double real_type;

	const std::size_t n(5);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] = 0;
	x[2] = 3;
	x[3] = 6;
	x[4] = 10;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0;
	y[2] = 3;
	y[3] = 4;
	y[4] = -1;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.500000000000000;
	expected_coeffs[0][1] = -0.720113438045375;
	expected_coeffs[0][2] = -0.000000000000000;
	expected_coeffs[0][3] =  0.220113438045375;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.000000000000000;
	expected_coeffs[1][1] = -0.059773123909250;
	expected_coeffs[1][2] =  0.660340314136126;
	expected_coeffs[1][3] = -0.102360868722125;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  3.000000000000000;
	expected_coeffs[2][1] =  1.138525305410122;
	expected_coeffs[2][2] = -0.260907504363002;
	expected_coeffs[2][3] = -0.002496606554198;
	expected_coeffs[3] = std::vector<real_type>(4);
	expected_coeffs[3][0] =  4.000000000000000;
	expected_coeffs[3][1] = -0.494328097731239;
	expected_coeffs[3][2] = -0.283376963350785;
	expected_coeffs[3][3] =  0.023614746945899;
	real_type x_test(0.5);
	real_type y_test(0.122403407989141);

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( notaknot_cubic_spline_1 )
{
	DCS_TEST_TRACE("Not-a-knot cubic spline #1");

	/*
	 * To test with MATLAB/Octave
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 1.5]
	 * > cs = spline(x,y])
	 * > ppval(cs,0.5)
	 *
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 1.5]
	 * > cs = csape(x,y, 'not-a-knot')
	 * > ppval(cs,0.5)
	 */

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( notaknot_cubic_spline_2 )
{
	DCS_TEST_TRACE("Not-a-knot cubic spline #2");

	/*
	 * To test with MATLAB/Octave
	 * > x = [-1 0 3]
	 * > y = [0.5 0 3]
	 * > cs = spline(x,y])
	 * > ppval(cs,0.5)
	 *
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3]
	 * > y = [0.5 0 3]
	 * > cs = csape(x,y, 'not-a-knot')
	 * > ppval(cs,0.5)
	 */

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
	expected_coeffs[0][1] = -0.69643;
	expected_coeffs[0][2] =  0.21429;
	expected_coeffs[0][3] = -0.01786;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0;
	expected_coeffs[1][1] =  0.67857;
	expected_coeffs[1][2] =  0.16071;
	expected_coeffs[1][3] = -0.01786;
	real_type x_test(0.5);
	real_type y_test(0.37723);

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

/*
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
*/

DCS_TEST_DEF( periodic_cubic_spline_1 )
{
	DCS_TEST_TRACE("Periodic cubic spline #1");

	/*
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [0 1 2 3]
	 * > y = [0 0.5 2 0]
	 * > cs = csape(x,y, 'periodic')
	 * > ppval(cs,0.5)
	 */

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
	y[3] = 0.0;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.0;
	expected_coeffs[0][1] = -1.5;
	expected_coeffs[0][2] =  2.5;
	expected_coeffs[0][3] = -0.5;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.5;
	expected_coeffs[1][1] =  2.0;
	expected_coeffs[1][2] =  1.0;
	expected_coeffs[1][3] = -1.5;
	expected_coeffs[2] = std::vector<real_type>(4);
	expected_coeffs[2][0] =  2.0;
	expected_coeffs[2][1] = -0.5;
	expected_coeffs[2][2] = -3.5;
	expected_coeffs[2][3] =  2.0;
	real_type x_test(0.5);
	real_type y_test(-0.1875);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::periodic_spline_boundary_condition);

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
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

DCS_TEST_DEF( periodic_cubic_spline_2 )
{
	DCS_TEST_TRACE("Periodic cubic spline #2");

	/*
	 * To test with MATLAB curvefit toolbox or with Octave splines package
	 * > pkg load splines  % Octave only
	 * > x = [-1 0 3]
	 * > y = [0.5 0 0.5]
	 * > cs = csape(x,y, 'periodic')
	 * > ppval(cs,0.5)
	 */

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = -1;
	x[1] =  0;
	x[2] =  3;
	std::vector<real_type> y(n);
	y[0] = 0.5;
	y[1] = 0.0;
	y[2] = 0.5;
	std::vector< std::vector<real_type> > expected_coeffs(n-1);
	expected_coeffs[0] = std::vector<real_type>(4);
	expected_coeffs[0][0] =  0.50;
	expected_coeffs[0][1] = -0.33;
	expected_coeffs[0][2] = -0.50;
	expected_coeffs[0][3] =  0.33;
	expected_coeffs[1] = std::vector<real_type>(4);
	expected_coeffs[1][0] =  0.00;
	expected_coeffs[1][1] = -0.33;
	expected_coeffs[1][2] =  0.50;
	expected_coeffs[1][3] = -0.11;
	real_type x_test(0.5);
	//real_type y_test(0.03125);
	real_type y_test(-0.055555555555556);

	dmc::cubic_spline_interpolator<real_type> interp(x.begin(),
													 x.end(),
													 y.begin(),
													 y.end(),
													 dmc::periodic_spline_boundary_condition);

	// Check spline coefficients
//	for (std::size_t k = 0; k < (n-1); ++k)
//	{
//		std::vector<real_type> coeffs = interp.coefficients(k);
//
//		for (std::size_t i = 0; i < 4; ++i)
//		{
//			DCS_DEBUG_TRACE("k = " << k << ", i = " << i << " ==> s_{" << k << "," << i << "} = " << coeffs[i]);
//			DCS_TEST_CHECK_CLOSE(coeffs[i], expected_coeffs[k][i], tol);
//		}
//	}
	// Check interpolation at nodes
	for (std::size_t i = 0; i < n; ++i)
	{
		const real_type yy = interp(x[i]);

		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << yy);
		DCS_TEST_CHECK_CLOSE(yy, y[i], tol);
	}
	// Check interpolation at a given point
	const real_type yy_test = interp(x_test);
	DCS_DEBUG_TRACE("Test x = " << x_test << " ==> " << yy_test);
	DCS_TEST_CHECK_CLOSE(yy_test, y_test, tol);
}

/*
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
*/

int main()
{
	DCS_TEST_SUITE("Spline interpolation");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( clamped_cubic_spline_1 );
		DCS_TEST_DO( clamped_cubic_spline_2 );
		DCS_TEST_DO( clamped_cubic_spline_3 );
		DCS_TEST_DO( natural_cubic_spline_1 );
		DCS_TEST_DO( natural_cubic_spline_2 );
		DCS_TEST_DO( natural_cubic_spline_3 );
		DCS_TEST_DO( notaknot_cubic_spline_1 );
		DCS_TEST_DO( notaknot_cubic_spline_2 );
////		DCS_TEST_DO( parabolic_cubic_spline_1 );
////		DCS_TEST_DO( parabolic_cubic_spline_2 );
		DCS_TEST_DO( periodic_cubic_spline_1 );
		DCS_TEST_DO( periodic_cubic_spline_2 );
////		DCS_TEST_DO( curvature_adjusted_cubic_spline_1 );
////		DCS_TEST_DO( curvature_adjusted_cubic_spline_2 );
	DCS_TEST_END();
}
