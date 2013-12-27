/**
 * \file test/src/dcs/test/math/curvefit/nearest.cpp
 *
 * \brief Test suite for nearest-neighbor interpolation.
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
#include <dcs/math/curvefit/interpolation/nearest.hpp>
#include <dcs/test.hpp>


namespace dmc = dcs::math::curvefit;


const double tol = 1e-5;

DCS_TEST_DEF( nearest_1 )
{
	DCS_TEST_TRACE("Nearest #1");

	typedef double real_type;

	const std::size_t n(10);

	std::vector<real_type> x(n);
	x[0] = 0;
	x[1] = 0.63;
	x[2] = 1.26;
	x[3] = 1.89;
	x[4] = 2.51;
	x[5] = 3.14;
	x[6] = 3.77;
	x[7] = 4.40;
	x[8] = 5.03;
	x[9] = 5.65;
	std::vector<real_type> y(n);
	y[0] = 0;
	y[1] = 0.59;
	y[2] = 0.95;
	y[3] = 0.95;
	y[4] = 0.59;
	y[5] = 0.00;
	y[6] = -0.59;
	y[7] = -0.95;
	y[8] = -0.95;
	y[9] = -0.59;

	//x = arange( 0.0, 5.65, 5.65/50)

	dmc::nearest_neighbor_interpolator<real_type> interp(x.begin(),
												 x.end(),
												 y.begin(),
												 y.end());

	for (std::size_t i = 0; i < n; ++i)
	{
		DCS_DEBUG_TRACE("x = " << x[i] << " ==> " << interp(x[i]) );
		DCS_TEST_CHECK_CLOSE(interp(x[i]), y[i], tol);
	}
}

int main()
{
	DCS_TEST_SUITE("Nearest-neighbor interpolation");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( nearest_1 );
	DCS_TEST_END();
}
