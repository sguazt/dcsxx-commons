
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

#include <dcs/math/function/bind.hpp>
#include <dcs/test.hpp>


namespace detail { namespace /*<unnamed>*/ {

template <typename T>
struct bind_test_case_data
{
	T val_inrange;
	T val_lb;
	T val_ub;
	T val_outrange_lo;
	T val_outrange_hi;
}; // bind_test_cast_data

}} // Namespace detail::<unnamed>


DCS_TEST_DEF( bind )
{
	DCS_TEST_CASE( "bind" );

	detail::bind_test_case_data<float> fdata = {0.5,0,1,-1.e-5,1+1.e+5};
	detail::bind_test_case_data<double> ddata = {0.5,0,1,-1.e-5,1+1.e+5};

	// Check bounds (without binding)

	// -- Float values

	DCS_TEST_CHECK( dcs::math::bound_lower(fdata.val_inrange, float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(fdata.val_inrange, float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(fdata.val_inrange, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(fdata.val_lb, float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(fdata.val_lb, float(0)) );
	DCS_TEST_CHECK( dcs::math::bound(fdata.val_lb, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(fdata.val_ub, float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(fdata.val_ub, float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(fdata.val_ub, float(0), float(1)) );

	DCS_TEST_CHECK( !dcs::math::bound_lower(fdata.val_outrange_lo, float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(fdata.val_outrange_lo, float(1)) );
	DCS_TEST_CHECK( !dcs::math::bound(fdata.val_outrange_lo, float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(fdata.val_outrange_hi, float(0)) );
	DCS_TEST_CHECK( !dcs::math::bound_upper(fdata.val_outrange_hi, float(1)) );
	DCS_TEST_CHECK( !dcs::math::bound(fdata.val_outrange_hi, float(0), float(1)) );

	// -- Double values

	DCS_TEST_CHECK( dcs::math::bound_lower(ddata.val_inrange, double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(ddata.val_inrange, double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(ddata.val_inrange, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(ddata.val_lb, double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(ddata.val_lb, double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(ddata.val_lb, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(ddata.val_ub, double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(ddata.val_ub, double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(ddata.val_ub, double(0), double(1)) );

	DCS_TEST_CHECK( !dcs::math::bound_lower(ddata.val_outrange_lo, double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(ddata.val_outrange_lo, double(1)) );
	DCS_TEST_CHECK( !dcs::math::bound(ddata.val_outrange_lo, double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(ddata.val_outrange_hi, double(0)) );
	DCS_TEST_CHECK( !dcs::math::bound_upper(ddata.val_outrange_hi, double(1)) );
	DCS_TEST_CHECK( !dcs::math::bound(ddata.val_outrange_hi, double(0), double(1)) );

	// Check bounds (with binding)

	// -- Float values

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(fdata.val_inrange, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(fdata.val_inrange, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(fdata.val_inrange, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(fdata.val_lb, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(fdata.val_lb, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(fdata.val_lb, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(fdata.val_ub, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(fdata.val_ub, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(fdata.val_ub, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(fdata.val_outrange_lo, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(fdata.val_outrange_lo, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(fdata.val_outrange_lo, float(0), float(1)), float(0), float(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(fdata.val_outrange_hi, float(0), float(1)), float(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(fdata.val_outrange_hi, float(0), float(1)), float(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(fdata.val_outrange_hi, float(0), float(1)), float(0), float(1)) );

	// -- Double values

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(ddata.val_inrange, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(ddata.val_inrange, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(ddata.val_inrange, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(ddata.val_lb, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(ddata.val_lb, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(ddata.val_lb, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(ddata.val_ub, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(ddata.val_ub, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(ddata.val_ub, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(ddata.val_outrange_lo, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(ddata.val_outrange_lo, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(ddata.val_outrange_lo, double(0), double(1)), double(0), double(1)) );

	DCS_TEST_CHECK( dcs::math::bound_lower(dcs::math::bind(ddata.val_outrange_hi, double(0), double(1)), double(0)) );
	DCS_TEST_CHECK( dcs::math::bound_upper(dcs::math::bind(ddata.val_outrange_hi, double(0), double(1)), double(1)) );
	DCS_TEST_CHECK( dcs::math::bound(dcs::math::bind(ddata.val_outrange_hi, double(0), double(1)), double(0), double(1)) );
}

int main()
{
	DCS_TEST_SUITE( "Math Functions" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( bind );
	DCS_TEST_END();
}
