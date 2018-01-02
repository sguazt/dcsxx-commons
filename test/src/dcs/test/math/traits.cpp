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


//static const double tol = 1e-10;
static const double pi = 3.14159265358979323846;


template <typename T>
inline
static void do_definitely_greater_checks(DCS_TEST_CONTEXT_FUNC_PARAM)
{
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -1e-1) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -1e-2) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -1e-3) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -1e-6) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -1e-12) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(0, -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::max(), 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::max(), std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(-std::numeric_limits<T>::min(), -std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::infinity(), 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(0, 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(0, std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::quiet_NaN(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::quiet_NaN(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_greater(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::quiet_NaN()) );
}

template <typename T>
inline
static void do_definitely_less_checks(DCS_TEST_CONTEXT_FUNC_PARAM)
{
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, 1e-1) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, 1e-2) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, 1e-3) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, 1e-6) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, 1e-12) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(0, std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::max(), 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::infinity(), 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(0, 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(0, std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::quiet_NaN(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::quiet_NaN(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::definitely_less(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::quiet_NaN()) );
}

template <typename T>
inline
static void do_essentially_equal_checks(DCS_TEST_CONTEXT_FUNC_PARAM)
{
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(0, 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(0, -0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(-0, 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::epsilon(), std::numeric_limits<T>::epsilon()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::min(), std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::max(), std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::denorm_min(), std::numeric_limits<T>::denorm_min()) );
#if __cplusplus >= 201103L
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest()) );
#endif // __cplusplus
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::min(), -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::denorm_min(), -std::numeric_limits<T>::denorm_min()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, 1e-1) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, 1e-2) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, 1e-3) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, 1e-6) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, 1e-12) )
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::max(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::infinity(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(0, std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::quiet_NaN(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::quiet_NaN(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::quiet_NaN()) );

	{
		const T x = pi;			// == 3.14159265358979...
		const T y = 22.0/7.0; 	// == 3.14285714285714...
		for (int i = 0; i < 10; ++i)
		{
			const T tol = std::pow(10, -i);
			if (i >= 4)
			{
				DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(x, y, tol) );
				DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(y, x, tol) );
			}
			else
			{
				DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(x, y, tol) );
				DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(y, x, tol) );
			}
		}
	}
}

template <typename T>
inline
static void do_approximately_equal_checks(DCS_TEST_CONTEXT_FUNC_PARAM)
{
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(0, 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(0, -0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(-0, 0) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::epsilon(), std::numeric_limits<T>::epsilon()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::min(), std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::max(), std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::denorm_min(), std::numeric_limits<T>::denorm_min()) );
#if __cplusplus >= 201103L
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest()) );
#endif // __cplusplus
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::min(), -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, 1e-1) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, 1e-2) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, 1e-3) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, 1e-6) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, 1e-12) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::max(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::max(), -std::numeric_limits<T>::min()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::infinity(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(0, std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::quiet_NaN(), 0) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::quiet_NaN(), -std::numeric_limits<T>::infinity()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::quiet_NaN()) );
	DCS_TEST_CHECK( !dcs::math::float_traits<T>::approximately_equal(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::quiet_NaN()) );

	{
		const T x = pi;			// == 3.14159265358979...
		const T y = 22.0/7.0; 	// == 3.14285714285714...
		for (int i = 0; i < 10; ++i)
		{
			const T tol = std::pow(10, -i);
			if (i >= 4)
			{
				DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(x, y, tol) );
				DCS_TEST_CHECK( !dcs::math::float_traits<T>::essentially_equal(y, x, tol) );
			}
			else
			{
				DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(x, y, tol) );
				DCS_TEST_CHECK( dcs::math::float_traits<T>::essentially_equal(y, x, tol) );
			}
		}
	}
}


DCS_TEST_DEF( float_definitely_greater )
{
	DCS_TEST_CASE( "float_defintely_greater" );

	do_definitely_greater_checks<float>(DCS_TEST_CONTEXT_FUNC_ARG);
	do_definitely_greater_checks<double>(DCS_TEST_CONTEXT_FUNC_ARG);
}

DCS_TEST_DEF( float_definitely_less )
{
	DCS_TEST_CASE( "float_defintely_less" );

	do_definitely_less_checks<float>(DCS_TEST_CONTEXT_FUNC_ARG);
	do_definitely_less_checks<double>(DCS_TEST_CONTEXT_FUNC_ARG);
}

DCS_TEST_DEF( float_essentially_equal )
{
	DCS_TEST_CASE( "float_essentially_equal" );

	// float
	do_essentially_equal_checks<float>(DCS_TEST_CONTEXT_FUNC_ARG);
	{
		const float x = 0.02759999999999999F;
		const float y = 0.0276F;
		DCS_TEST_CHECK( dcs::math::float_traits<float>::definitely_less(x, y) );
		DCS_TEST_CHECK( dcs::math::float_traits<float>::definitely_less(x, y, std::numeric_limits<float>::epsilon()) );
		for (int i = 0; i < 5; ++i)
		{
			const float tol = std::pow(10, -i);
			DCS_TEST_CHECK( !dcs::math::float_traits<float>::definitely_less(x, y, tol) );
		}
	}

	do_essentially_equal_checks<double>(DCS_TEST_CONTEXT_FUNC_ARG);

}

DCS_TEST_DEF( float_approximately_equal )
{
	DCS_TEST_CASE( "float_approximately_equal" );

	do_approximately_equal_checks<float>(DCS_TEST_CONTEXT_FUNC_ARG);
	do_approximately_equal_checks<double>(DCS_TEST_CONTEXT_FUNC_ARG);
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
