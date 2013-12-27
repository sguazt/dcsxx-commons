/**
 * \file test/src/dcs/test/math/curvefit/constant.cpp
 *
 * \brief Test suite for constant interpolation.
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
#include <dcs/math/curvefit/interpolation/constant.hpp>
#include <dcs/test.hpp>


namespace dmc = dcs::math::curvefit;


const double tol = 1e-5;

DCS_TEST_DEF( constant_1 )
{
	DCS_TEST_TRACE("Constant #1");

	typedef double real_type;

	const std::size_t n(3);

	std::vector<real_type> x(n);
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	std::vector<real_type> y(n);
	y[0] = 2;
	y[1] = 3;
	y[2] = 4;

	dmc::constant_interpolator<real_type> interp(x.begin(),
												 x.end(),
												 y.begin(),
												 y.end());

	for (std::size_t i = 0; i < n; ++i)
	{
		real_type yy = interp(x[i]);
		DCS_TEST_TRACE("x = " << x[i] << " ==> " << yy );
		DCS_TEST_CHECK_CLOSE(yy, i < (n-1) ? y[i] : y[n-2], tol);
	}
}

int main()
{
	DCS_TEST_SUITE("Constant interpolation");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( constant_1 );
	DCS_TEST_END();
}
