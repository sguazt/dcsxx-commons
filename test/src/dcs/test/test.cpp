/**
 * \file dcs/test/test.cpp
 *
 * \brief Test suite for the minimal test framework \c dcs::test.
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
 * along with dcsxx-commons.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <complex>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/test.hpp>


namespace ublas = boost::numeric::ublas;


static const double tol(1e-6);
static const double mul(tol*10);


DCS_TEST_DEF( check )
{
	DCS_TEST_TRACE( "Test case: 'check'" );

	DCS_TEST_CHECK( true );
}

DCS_TEST_DEF( check_eq )
{
	DCS_TEST_TRACE( "Test case: 'check_eq'" );

	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_EQ( short(1), short(1) );
	DCS_TEST_CHECK_EQ( int(1), int(1) );
	DCS_TEST_CHECK_EQ( long(1), long(1) );
	DCS_TEST_CHECK_EQ( unsigned(1), unsigned(1) );

	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_EQ( short(1), int(1) );
	DCS_TEST_CHECK_EQ( short(1), int(1) );
	DCS_TEST_CHECK_EQ( int(1), long(1) );
	DCS_TEST_CHECK_EQ( long(1), int(1) );

	DCS_DEBUG_TRACE( "-- Test aliases." );
	DCS_TEST_CHECK_EQUAL( int(1), int(1) );
}

DCS_TEST_DEF( check_close )
{
	DCS_TEST_TRACE( "Test case: 'check_close'" );

	const double c1(1*mul);
	const double c2(2*mul);

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_CLOSE( float(c1), float(c1), tol );
	DCS_TEST_CHECK_CLOSE( double(c1), double(c1), tol );
	DCS_TEST_CHECK_CLOSE( ::std::complex<float>(c1,c2), ::std::complex<float>(c1,c2), tol );
	DCS_TEST_CHECK_CLOSE( ::std::complex<double>(c1,c2), ::std::complex<double>(c1,c2), tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_CLOSE( float(c1), double(c1), tol );
	DCS_TEST_CHECK_CLOSE( double(c1), float(c1), tol );
	DCS_TEST_CHECK_CLOSE( ::std::complex<float>(c1,c2), ::std::complex<double>(c1,c2), tol );
	DCS_TEST_CHECK_CLOSE( ::std::complex<double>(c1,c2), ::std::complex<float>(c1,c2), tol );
}

DCS_TEST_DEF( check_rel_close )
{
	DCS_TEST_TRACE( "Test case: 'check_rel_close'" );

	const double c1(1*mul);
	const double c2(2*mul);

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_REL_CLOSE( float(c1), float(c1), tol );
	DCS_TEST_CHECK_REL_CLOSE( double(c1), double(c1), tol );
	DCS_TEST_CHECK_REL_CLOSE( ::std::complex<float>(c1,c2), ::std::complex<float>(c1,c2), tol );
	DCS_TEST_CHECK_REL_CLOSE( ::std::complex<double>(c1,c2), ::std::complex<double>(c1,c2), tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_REL_CLOSE( float(c1), double(c1), tol );
	DCS_TEST_CHECK_REL_CLOSE( double(c1), float(c1), tol );
	DCS_TEST_CHECK_REL_CLOSE( ::std::complex<float>(c1,c2), ::std::complex<double>(c1,c2), tol );
	DCS_TEST_CHECK_REL_CLOSE( ::std::complex<double>(c1,c2), ::std::complex<float>(c1,c2), tol );
}

DCS_TEST_DEF( check_vector_eq )
{
	DCS_TEST_TRACE( "Test case: 'check_vector_eq'" );

	const ::std::size_t n(5);

	ublas::vector<short> sv = ublas::scalar_vector<short>(n, 1);
	ublas::vector<int> iv = ublas::scalar_vector<int>(n, 1);
	ublas::vector<long> lv = ublas::scalar_vector<long>(n, 1L);
	ublas::vector<unsigned> uv = ublas::scalar_vector<unsigned>(n, 1u);

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_VECTOR_EQ( sv, sv, n );
	DCS_TEST_CHECK_VECTOR_EQ( iv, iv, n );
	DCS_TEST_CHECK_VECTOR_EQ( lv, lv, n );
	DCS_TEST_CHECK_VECTOR_EQ( uv, uv, n );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_VECTOR_EQ( sv, iv, n );
	DCS_TEST_CHECK_VECTOR_EQ( iv, sv, n );
	DCS_TEST_CHECK_VECTOR_EQ( iv, lv, n );
	DCS_TEST_CHECK_VECTOR_EQ( lv, iv, n );
}

DCS_TEST_DEF( check_vector_close )
{
	DCS_TEST_TRACE( "Test case: 'check_vector_close'" );

	const ::std::size_t n(5);

	ublas::vector<float> fv = ublas::scalar_vector<float>(n, 1);
	ublas::vector<float> dv = ublas::scalar_vector<float>(n, 1);
	ublas::vector< ::std::complex<float> > cfv = ublas::scalar_vector< ::std::complex<float> >(n, ::std::complex<float>(1,2));
	ublas::vector< ::std::complex<double> > cdv = ublas::scalar_vector< ::std::complex<double> >(n, ::std::complex<double>(1,2));

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_VECTOR_CLOSE( fv, fv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( dv, dv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( cfv, cfv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( cdv, cdv, n, tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_VECTOR_CLOSE( fv, dv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( dv, fv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( cfv, cdv, n, tol );
	DCS_TEST_CHECK_VECTOR_CLOSE( cdv, cfv, n, tol );
}

DCS_TEST_DEF( check_vector_rel_close )
{
	DCS_TEST_TRACE( "Test case: 'check_vector_rel_close'" );

	const ::std::size_t n(5);
	const double c1(1*mul);
	const double c2(2*mul);

	ublas::vector<float> fv = ublas::scalar_vector<float>(n, c1);
	ublas::vector<double> dv = ublas::scalar_vector<double>(n, c1);
	ublas::vector< ::std::complex<float> > cfv = ublas::scalar_vector< ::std::complex<float> >(n, ::std::complex<float>(c1,c2));
	ublas::vector< ::std::complex<double> > cdv = ublas::scalar_vector< ::std::complex<double> >(n, ::std::complex<double>(c1,c2));

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( fv, fv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( dv, dv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( cfv, cfv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( cdv, cdv, n, tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( fv, dv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( dv, fv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( cfv, cdv, n, tol );
	DCS_TEST_CHECK_VECTOR_REL_CLOSE( cdv, cfv, n, tol );
}

DCS_TEST_DEF( check_matrix_eq )
{
	DCS_TEST_TRACE( "Test case: 'check_matrix_eq'" );

	const ::std::size_t nr(3);
	const ::std::size_t nc(4);

	ublas::matrix<short> sv = ublas::scalar_matrix<short>(nr, nc, 1);
	ublas::matrix<int> iv = ublas::scalar_matrix<int>(nr, nc, 1);
	ublas::matrix<long> lv = ublas::scalar_matrix<long>(nr, nc, 1L);
	ublas::matrix<unsigned> uv = ublas::scalar_matrix<unsigned>(nr, nc, 1u);

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_MATRIX_EQ( sv, sv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( iv, iv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( lv, lv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( uv, uv, nr, nc );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_MATRIX_EQ( sv, iv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( iv, sv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( iv, lv, nr, nc );
	DCS_TEST_CHECK_MATRIX_EQ( lv, iv, nr, nc );
}

DCS_TEST_DEF( check_matrix_close )
{
	DCS_TEST_TRACE( "Test case: 'check_matrix_close'" );

	const ::std::size_t nr(3);
	const ::std::size_t nc(4);
	const double c1(1*mul);
	const double c2(2*mul);

	ublas::matrix<float> fA = ublas::scalar_matrix<float>(nr, nc, c1);
	ublas::matrix<double> dA = ublas::scalar_matrix<double>(nr, nc, c1);
	ublas::matrix< ::std::complex<float> > cfA = ublas::scalar_matrix< ::std::complex<float> >(nr, nc, ::std::complex<float>(c1,c2));
	ublas::matrix< ::std::complex<double> > cdA = ublas::scalar_matrix< ::std::complex<double> >(nr, nc, ::std::complex<double>(c1,c2));

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_MATRIX_CLOSE( fA, fA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( dA, dA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( cfA, cfA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( cdA, cdA, nr, nc, tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_MATRIX_CLOSE( fA, dA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( dA, fA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( cfA, cdA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_CLOSE( cdA, cfA, nr, nc, tol );
}


DCS_TEST_DEF( check_matrix_rel_close )
{
	DCS_TEST_TRACE( "Test case: 'check_matrix_rel_close'" );

	const ::std::size_t nr(3);
	const ::std::size_t nc(4);
	const double c1(1*mul);
	const double c2(2*mul);

	ublas::matrix<float> fA = ublas::scalar_matrix<float>(nr, nc, c1);
	ublas::matrix<double> dA = ublas::scalar_matrix<double>(nr, nc, c1);
	ublas::matrix< ::std::complex<float> > cfA = ublas::scalar_matrix< ::std::complex<float> >(nr, nc, ::std::complex<float>(c1,c2));
	ublas::matrix< ::std::complex<double> > cdA = ublas::scalar_matrix< ::std::complex<double> >(nr, nc, ::std::complex<double>(c1,c2));

	// Check T vs. T
	DCS_DEBUG_TRACE( "-- Test against same types." );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( fA, fA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( dA, dA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( cfA, cfA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( cdA, cdA, nr, nc, tol );

	// Check T1 vs. T2
	DCS_DEBUG_TRACE( "-- Test against different types." );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( fA, dA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( dA, fA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( cfA, cdA, nr, nc, tol );
	DCS_TEST_CHECK_MATRIX_REL_CLOSE( cdA, cfA, nr, nc, tol );
}


int main()
{
	DCS_TEST_SUITE( "Test 'utils.hpp' functionalities" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO( check );
		DCS_TEST_DO( check_eq );
		DCS_TEST_DO( check_close );
		DCS_TEST_DO( check_rel_close );
		DCS_TEST_DO( check_vector_eq );
		DCS_TEST_DO( check_vector_close );
		DCS_TEST_DO( check_vector_rel_close );
		DCS_TEST_DO( check_matrix_eq );
		DCS_TEST_DO( check_matrix_close );
		DCS_TEST_DO( check_matrix_rel_close );
	DCS_TEST_END();
}
