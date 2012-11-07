
/**
 * \file dcs/test/math/functions.hpp
 *
 * \brief Test suite for mathematical functions.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons.
 *
 * dcsxx-commons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcsxx-commons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcsxx-commons. If not, see <http://www.gnu.org/licenses/>.
 */

#include <dcs/math/function/clamp.hpp>
#include <dcs/test.hpp>


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

int main()
{
	DCS_TEST_SUITE( "Math Functions" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( clamp );
	DCS_TEST_END();
}
