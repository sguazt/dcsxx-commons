/**
 * \file test/src/dcs/test/math/functions.hpp
 *
 * \brief Test suite for mathematical functions.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012-2014  Marco Guazzone
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

#include <dcs/math/function/bell.hpp>
#include <dcs/math/function/clamp.hpp>
#include <dcs/math/function/round.hpp>
#include <dcs/test.hpp>


static const double tol = 1e-10;

namespace detail { namespace /*<unnamed>*/ {

template <typename T>
struct clamp_test_case_data
{
	T val_inrange;
	T val_lb;
	T val_ub;
	T val_outrange_lo;
	T val_outrange_hi;
}; // clamp_test_cast_data

}} // Namespace detail::<unnamed>


DCS_TEST_DEF( clamp )
{
	DCS_TEST_CASE( "clamp" );

	detail::clamp_test_case_data<float> fdata = {0.5,0,1,-1.e-5,1+1.e+5};
	detail::clamp_test_case_data<double> ddata = {0.5,0,1,-1.e-5,1+1.e+5};

	// Check bounds (without clamping)

	// -- Float values

	DCS_TEST_CHECK( dcs::math::clamped_down(fdata.val_inrange, float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(fdata.val_inrange, float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(fdata.val_inrange, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(fdata.val_lb, float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(fdata.val_lb, float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped(fdata.val_lb, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(fdata.val_ub, float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(fdata.val_ub, float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(fdata.val_ub, float(0), float(1)) );

	DCS_TEST_CHECK( !dcs::math::clamped_down(fdata.val_outrange_lo, float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(fdata.val_outrange_lo, float(1)) );
	DCS_TEST_CHECK( !dcs::math::clamped(fdata.val_outrange_lo, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(fdata.val_outrange_hi, float(0)) );
	DCS_TEST_CHECK( !dcs::math::clamped_up(fdata.val_outrange_hi, float(1)) );
	DCS_TEST_CHECK( !dcs::math::clamped(fdata.val_outrange_hi, float(0), float(1)) );

	// -- Double values

	DCS_TEST_CHECK( dcs::math::clamped_down(ddata.val_inrange, double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(ddata.val_inrange, double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(ddata.val_inrange, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(ddata.val_lb, double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(ddata.val_lb, double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(ddata.val_lb, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(ddata.val_ub, double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(ddata.val_ub, double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(ddata.val_ub, double(0), double(1)) );

	DCS_TEST_CHECK( !dcs::math::clamped_down(ddata.val_outrange_lo, double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(ddata.val_outrange_lo, double(1)) );
	DCS_TEST_CHECK( !dcs::math::clamped(ddata.val_outrange_lo, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(ddata.val_outrange_hi, double(0)) );
	DCS_TEST_CHECK( !dcs::math::clamped_up(ddata.val_outrange_hi, double(1)) );
	DCS_TEST_CHECK( !dcs::math::clamped(ddata.val_outrange_hi, double(0), double(1)) );

	// Check bounds (with clamping)

	// -- Float values

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(fdata.val_inrange, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(fdata.val_inrange, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(fdata.val_inrange, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(fdata.val_lb, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(fdata.val_lb, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(fdata.val_lb, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(fdata.val_ub, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(fdata.val_ub, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(fdata.val_ub, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(fdata.val_outrange_lo, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(fdata.val_outrange_lo, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(fdata.val_outrange_lo, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(fdata.val_outrange_hi, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(fdata.val_outrange_hi, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(fdata.val_outrange_hi, float(0), float(1)), float(0), float(1)) );

	// -- Double values

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(ddata.val_inrange, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(ddata.val_inrange, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(ddata.val_inrange, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(ddata.val_lb, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(ddata.val_lb, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(ddata.val_lb, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(ddata.val_ub, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(ddata.val_ub, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(ddata.val_ub, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(ddata.val_outrange_lo, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(ddata.val_outrange_lo, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(ddata.val_outrange_lo, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::clamped_down(dcs::math::clamp(ddata.val_outrange_hi, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::clamped_up(dcs::math::clamp(ddata.val_outrange_hi, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::clamped(dcs::math::clamp(ddata.val_outrange_hi, double(0), double(1)), double(0), double(1)) );
}

DCS_TEST_DEF( bell )
{
	DCS_TEST_CASE( "bell" );

	// See: http://oeis.org/A000110
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(0), 1.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(1), 1.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(2), 2.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(3), 5.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(4), 15.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(5), 52.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(6), 203.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(7), 877.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(8), 4140.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(9), 21147.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(10), 115975.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(11), 678570.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(12), 4213597.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(13), 27644437.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(14), 190899322.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(15), 1382958545.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(16), 10480142147.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(17), 82864869804.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(18), 682076806159.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(19), 5832742205057.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(20), 51724158235372.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(21), 474869816156751.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(22), 4506715738447323.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(23), 44152005855084346.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(24), 445958869294805289.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(25), 4638590332229999353.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::bell<double>(26), 49631246523618756274.0, tol );
}

DCS_TEST_DEF( round )
{
	DCS_TEST_CASE( "round" );

	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 0), 0.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 1), 0.1, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 2), 0.12, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 3), 0.123, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 4), 0.1235, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 5), 0.12346, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 6), 0.123457, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 7), 0.1234568, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 8), 0.12345679, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 9), 0.123456789, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(0.123456789, 10), 0.123456789, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(123.456789,  0), 123.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(123.456789, -1), 120.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(123.456789, -2), 100.0, tol );
	DCS_TEST_CHECK_REL_CLOSE( dcs::math::roundp(123.456789, -3), 0.0, tol );
}


int main()
{
	DCS_TEST_SUITE( "Math Functions" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( clamp );
		DCS_TEST_DO( bell );
		DCS_TEST_DO( round );
	DCS_TEST_END();
}
