/**
 * \file test/src/dcs/test/math/curvefit/interp_core.cpp
 *
 * \brief Test suite for interpolation core functionalities.
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


#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <dcs/test.hpp>


namespace dmc = dcs::math::curvefit;


namespace detail { namespace /*<unnamed>*/ {

class fake_interpolator: public dmc::base_1d_interpolator<double>
{
	private: typedef dmc::base_1d_interpolator<double> base_type;


	public: template <typename XIterT, typename YIterT>
			fake_interpolator(XIterT x_first, XIterT x_last, YIterT y_first, YIterT y_last)
	: base_type(x_first, x_last, y_first, y_last)
	{	
	}

	public: std::size_t find(double x) const
	{
		return this->base_type::find(x);
	}

	public: double do_interpolate(double x) const
	{
		// Fake implementation (non sense)
		return x;
	}
};

}} // Namespace detail::<unnamed>

const double tol = 1e-5;

DCS_TEST_DEF( find_1 )
{
	DCS_TEST_TRACE("Find #1");

	typedef double real_type;

	const std::size_t n(4);

	std::vector<real_type> x(n);
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;
	x[3] = 4;
	std::vector<real_type> y(n);
	y[0] = 2;
	y[1] = 3;
	y[2] = 4;
	y[3] = 5;

	detail::fake_interpolator interp(x.begin(),
									 x.end(),
									 y.begin(),
									 y.end());

	DCS_TEST_TRACE("Check nodes...");
	for (std::size_t i = 0; i < n; ++i)
	{
		const std::size_t j = interp.find(x[i]);

		DCS_TEST_TRACE("x = " << x[i] << " ==> " << j);
		DCS_TEST_CHECK_EQUAL(j, i < (n-1) ? i : (n-2));
	}

	DCS_TEST_TRACE("Check inner points...");
	for (std::size_t i = 0; i < (n-1); ++i)
	{
		const double xx((x[i]+x[i+1])/2.0);

		const std::size_t j = interp.find(xx);

		DCS_TEST_TRACE("x = " << xx << " ==> " << j);
		DCS_TEST_CHECK_EQUAL(j, i < (n-1) ? i : (n-2));
	}

	DCS_TEST_TRACE("Check outer points...");
	double xx1(x[0]-0.5);
	std::size_t j1 = interp.find(xx1);
	DCS_TEST_TRACE("x = " << xx1 << " ==> " << j1);
	DCS_TEST_CHECK_EQUAL(j1, 0);
	double xx2(x[n-1]+0.5);
	std::size_t j2 = interp.find(xx2);
	DCS_TEST_TRACE("x = " << xx2 << " ==> " << j2);
	DCS_TEST_CHECK_EQUAL(j2, n-2);
}

int main()
{
	DCS_TEST_SUITE("Interpolation Core Functionalities");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( find_1 );
	DCS_TEST_END();
}
