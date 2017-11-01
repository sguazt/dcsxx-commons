/**
 * \file test/src/dcs/test/math/traits.hpp
 *
 * \brief Test suite for mathematical traits type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2017 Marco Guazzone (marco.guazzone@gmail.com)
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

#include <dcs/math/traits/float.hpp>
#include <dcs/test.hpp>
#include <limits>


static const double tol = 1e-10;

DCS_TEST_DEF( float_definitely_greater )
{
	DCS_TEST_CASE( "float_defintely_greater" );

#ifdef DO_CHECKS
# undef DO_CHECKS
#endif
#define DO_CHECKS(REAL_T)	DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -1e-1) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -1e-2) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -1e-3) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -1e-6) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -1e-12) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(0, -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::max(), 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::max(), std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(-std::numeric_limits<REAL_T>::min(), -std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::infinity(), 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(0, 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(0, std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::quiet_NaN(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(-std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::quiet_NaN(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::quiet_NaN(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_greater(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::quiet_NaN()) );

	// -- Float values

	DO_CHECKS( float );

	// -- Double values

	DO_CHECKS( double );
}

DCS_TEST_DEF( float_definitely_less )
{
	DCS_TEST_CASE( "float_defintely_less" );

#ifdef DO_CHECKS
# undef DO_CHECKS
#endif
#define DO_CHECKS(REAL_T)	DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, 1e-1) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, 1e-2) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, 1e-3) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, 1e-6) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, 1e-12) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(0, std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::max(), 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::min(), std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::max(), -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::infinity(), 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(0, 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(0, std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::quiet_NaN(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::quiet_NaN(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::quiet_NaN(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::definitely_less(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::quiet_NaN()) );

	// -- Float values

	DO_CHECKS( float );

	// -- Double values

	DO_CHECKS( double );
}

DCS_TEST_DEF( float_essentially_equal )
{
	DCS_TEST_CASE( "float_essentially_equal" );

#ifdef DO_CHECKS
# undef DO_CHECKS
#endif
#define DO_CHECKS(REAL_T)	DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(0, 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::epsilon(), std::numeric_limits<REAL_T>::epsilon()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::min(), std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::max(), std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::min(), -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::max(), -std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, 1e-1) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, 1e-2) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, 1e-3) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, 1e-6) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, 1e-12) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::max(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::min(), std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::max(), -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::infinity(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(0, std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::quiet_NaN(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::quiet_NaN(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::quiet_NaN(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::essentially_equal(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::quiet_NaN()) );

	// -- Float values

	DO_CHECKS( float );

	// -- Double values

	DO_CHECKS( double );
}

DCS_TEST_DEF( float_approximately_equal )
{
	DCS_TEST_CASE( "float_approximately_equal" );

#ifdef DO_CHECKS
# undef DO_CHECKS
#endif
#define DO_CHECKS(REAL_T)	DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(0, 0) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::epsilon(), std::numeric_limits<REAL_T>::epsilon()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::min(), std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::max(), std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::min(), -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::max(), -std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, 1e-1) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, 1e-2) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, 1e-3) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, 1e-6) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, 1e-12) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::max(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::min(), std::numeric_limits<REAL_T>::max()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::max(), -std::numeric_limits<REAL_T>::min()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::infinity(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(0, std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::quiet_NaN(), 0) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::quiet_NaN(), std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::quiet_NaN(), -std::numeric_limits<REAL_T>::infinity()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(std::numeric_limits<REAL_T>::infinity(), std::numeric_limits<REAL_T>::quiet_NaN()) ); \
							DCS_TEST_CHECK( !dcs::math::float_traits<REAL_T>::approximately_equal(-std::numeric_limits<REAL_T>::infinity(), -std::numeric_limits<REAL_T>::quiet_NaN()) );

	// -- Float values

	DO_CHECKS( float );

	// -- Double values

	DO_CHECKS( double );
}


int main()
{
	DCS_TEST_SUITE( "Traits" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( float_definitely_greater );
		DCS_TEST_DO( float_definitely_less );
		DCS_TEST_DO( float_essentially_equal );
		DCS_TEST_DO( float_approximately_equal );
	DCS_TEST_END();
}
