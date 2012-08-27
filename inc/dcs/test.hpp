/**
 * \file dcs/test.hpp
 *
 * \brief Minimal framework for test suites.
 *
 * Basic usage:
 * <pre>
 * DCS_TEST_DEF( test_case_1 )
 * {
 *   // do your test stuff
 * }
 *
 * DCS_TEST_DEF( test_case_2 )
 * {
 *   // do your test stuff
 * }
 *
 * // ...
 *
 * DCS_TEST_DEF( test_case_n )
 * {
 *   // do your test stuff
 * }
 *
 * int main()
 * {
 *   DCS_TEST_SUITE("My Test Suite"); // optional
 *   DCS_TEST_BEGIN()
 *
 *   DCS_TEST_DO( test_case_1 );
 *   DCS_TEST_DO( test_case_2 );
 *   // ...
 *   DCS_TEST_DO( test_case_n );
 *
 *   DCS_TEST_END()
 * }
 * </pre>
 *
 * To compile, make sure to add to the linker the standard math library.
 *
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_TEST_HPP
#define DCS_TEST_HPP


#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>


namespace dcs { namespace test { namespace detail { namespace /*<unnamed>*/ {

template <typename T1, typename T2, typename T3>
inline
bool close_to(T1 x, T2 y, T3 tol)
{
	if (::std::isnan(x) || ::std::isnan(y))
	{
		// According to IEEE, NaN are different event by itself
		return false;
	}
	return ::std::abs(x-y) <= (::std::max(::std::abs(x), ::std::abs(y))*tol);
}

}}}} // Namespace dcs::test::detail::<unnamed>


/// Expand the given argument.
#define DCS_TEST_PARAM_EXPAND_(x) x


/// Stringify the given argument.
#define DCS_TEST_STRINGIFY_(x) #x


/// Concatenate the given arguments.
#define DCS_TEST_STR_JOIN_(x,y) x ## y


/// Define the name of the entire test suite.
#define DCS_TEST_SUITE(m) ::std::cerr << "--- Test Suite: " << m << " ---" << ::std::endl;


/// Init procedure.
#define DCS_TEST_INIT() static void dcs_test_init__()


/// Define the beginning of the test suite.
#define DCS_TEST_BEGIN()	/* [DCS_TEST_BEGIN] */ \
							{ \
								/* Begin of Test Suite */ \
								unsigned int test_fails__(0); \
							/* [/DCS_TEST_BEGIN] */


/// Define a new test case.
#define DCS_TEST_DEF(x) static void DCS_TEST_PARAM_EXPAND_(x)(unsigned int& test_fails__)


/// Call the previously defined init function.
#define DCS_TEST_DO_INIT()  dcs_test_init__()


/// Call a previously defined test case.
#define DCS_TEST_DO(x)	/* [DCS_TEST_DO] */ \
						try \
						{ \
							DCS_TEST_PARAM_EXPAND_(x)(test_fails__); \
						} \
						catch (::std::exception& e) \
						{ \
							++test_fails__; \
							DCS_TEST_ERROR( e.what() ); \
						} \
						catch (...) \
						{ \
							++test_fails__; \
						} \
						/* [/DCS_TEST_DO] */


/// Define the end of the test suite.
#define DCS_TEST_END()	/* [DCS_TEST_END] */ \
							if (test_fails__ > 0) \
							{ \
								::std::cerr << "Number of failed tests: " << test_fails__ << ::std::endl; \
							} \
							else \
							{ \
								::std::cerr << "No failed test" << ::std::endl; \
							} \
							/* End of Test Suite */ \
						} \
						/* [/DCS_TEST_END] */


/// Check for the truth of the given assertion \a x.
#define DCS_TEST_CHECK(x)	/* [DCS_TEST_CHECK] */ \
							if (!(DCS_TEST_PARAM_EXPAND_(x))) \
							{ \
								DCS_TEST_ERROR( "Failed assertion: " << DCS_TEST_STRINGIFY_(x) ); \
								++test_fails__; \
							} \
							/* [/DCS_TEST_CHECK] */


/// Check for the equality of \a x against \a y.
#define DCS_TEST_CHECK_EQUAL(x,y)	/* [DCS_TEST_CHECK_EQUAL] */ \
									if (!(DCS_TEST_PARAM_EXPAND_(x) == DCS_TEST_PARAM_EXPAND_(y))) \
									{ \
										DCS_TEST_ERROR( "Failed assertion: (" << DCS_TEST_STRINGIFY_(x) << " == " << DCS_TEST_STRINGIFY_(y) << ")" ); \
										++test_fails__; \
									} \
									/* [/DCS_TEST_CHECK_EQUAL] */


/// Check for the floating point equality of \a x against \a y with a tolerance
/// of \a e.
#define DCS_TEST_CHECK_CLOSE(x,y,e)	/* [DCS_TEST_CHECK_CLOSE] */ \
									if (!::dcs::test::detail::close_to(DCS_TEST_PARAM_EXPAND_(x), DCS_TEST_PARAM_EXPAND_(y), DCS_TEST_PARAM_EXPAND_(e))) \
									{ \
										DCS_TEST_ERROR( "Failed assertion: abs(" << DCS_TEST_STRINGIFY_(x) << "-" << DCS_TEST_STRINGIFY_(y) << ") <= " << DCS_TEST_STRINGIFY_(e) << " [with " << DCS_TEST_STRINGIFY_(x) << " == " << DCS_TEST_PARAM_EXPAND_(x) << ", " << DCS_TEST_STRINGIFY_(y) << " == " << DCS_TEST_PARAM_EXPAND_(y) << " and " << DCS_TEST_STRINGIFY_(e) << " == " << DCS_TEST_PARAM_EXPAND_(e) << "]" ); \
										++test_fails__; \
									} \
									/* [/DCS_TEST_CHECK_CLOSE] */


///// Check for the floating point absolute precision of \a x against \a y with a
///// tolerance of \a tol.
//#define DCS_TEST_CHECK_PRECISION(x,y,tol) if (!(::std::fabs((x) - (y)) <= (tol))) { DCS_TEST_ERROR( ">> Failed assertion: (abs(" << DCS_TEST_STRINGIFY_(x) << " - " << DCS_TEST_STRINGIFY_(y) << ") <= " << DCS_TEST_STRINGIFY_(tol) << ")" ); ++test_fails__; }


/// Check for the floating point relative precision of \a x against \a y with a
/// tolerance of \a e.
#define DCS_TEST_CHECK_REL_CLOSE(x,y,e)	/* [DCS_TEST_CHECK_REL_CLOSE] */ \
										if ((DCS_TEST_PARAM_EXPAND_(x) != DCS_TEST_PARAM_EXPAND_(y)) && !(::std::abs((DCS_TEST_PARAM_EXPAND_(x) - DCS_TEST_PARAM_EXPAND_(y))/DCS_TEST_PARAM_EXPAND_(y)) <= DCS_TEST_PARAM_EXPAND_(e))) \
										{ \
											DCS_TEST_ERROR( "Failed assertion: abs((" << DCS_TEST_STRINGIFY_(x) << "-" << DCS_TEST_STRINGIFY_(y) << ")/" << DCS_TEST_STRINGIFY_(y) << ") <= " << DCS_TEST_STRINGIFY_(e)  << " [with " << DCS_TEST_STRINGIFY_(x) << " == " << DCS_TEST_PARAM_EXPAND_(x) << ", " << DCS_TEST_STRINGIFY_(y) << " == " << DCS_TEST_PARAM_EXPAND_(y) << " and " << DCS_TEST_STRINGIFY_(e) << " == " << DCS_TEST_PARAM_EXPAND_(e) << "]" ); \
											++test_fails__; \
										} \
										/* [/DCS_TEST_CHECK_REL_CLOSE] */


/// Check that elements of \a x and \a y are equal.
#define DCS_TEST_CHECK_VECTOR_EQ(x,y,n)	/* [DCS_TEST_CHECK_VECTOR_EQ] */ \
										if (DCS_TEST_PARAM_EXPAND_(n) > 0) \
										{ \
											::std::size_t n__ = DCS_TEST_PARAM_EXPAND_(n); \
											for (::std::size_t i__ = n__; i__ > 0; --i__) \
											{ \
												if (!(DCS_TEST_PARAM_EXPAND_(x)[n__-i__] == DCS_TEST_PARAM_EXPAND_(y)[n__-i__])) \
												{ \
													DCS_TEST_ERROR( "Failed assertion: (" << DCS_TEST_STRINGIFY_(x[i__]) << "==" << DCS_TEST_STRINGIFY_(y[i__]) << ")" << " [with " << DCS_TEST_STRINGIFY_(x[i__]) << " == " << DCS_TEST_PARAM_EXPAND_(x)[n__-i__] << ", " << DCS_TEST_STRINGIFY_(y[i__]) << " == " << DCS_TEST_PARAM_EXPAND_(y)[n__-i__] << ", " << DCS_TEST_STRINGIFY_(i__) << " == " << i__ << " and " << DCS_TEST_STRINGIFY_(n) << " == " << n__ << "]" ); \
													++test_fails__; \
												} \
											} \
										} \
										/* [/DCS_TEST_CHECK_VECTOR_EQ] */


/// Check that elements of \a x and \a y are close with respect to a given
/// precision.
#define DCS_TEST_CHECK_VECTOR_CLOSE(x,y,n,e)	/* [DCS_TEST_CHECK_VECTOR_CLOSE] */ \
												if (DCS_TEST_PARAM_EXPAND_(n) > 0) \
												{ \
													::std::size_t n__ = DCS_TEST_PARAM_EXPAND_(n); \
													for (::std::size_t i__ = n__; i__ > 0; --i__) \
													{ \
														if (!(::std::abs(DCS_TEST_PARAM_EXPAND_(x)[n__-i__]-DCS_TEST_PARAM_EXPAND_(y)[n__-i__]) <= DCS_TEST_PARAM_EXPAND_(e))) \
														{ \
															DCS_TEST_ERROR( "Failed assertion: abs(" << DCS_TEST_STRINGIFY_(x[i__]) << "-" << DCS_TEST_STRINGIFY_(y[i__]) << ") <= " << DCS_TEST_STRINGIFY_(e)  << " [with " << DCS_TEST_STRINGIFY_(x[i__]) << " == " << DCS_TEST_PARAM_EXPAND_(x)[n__-i__] << ", " << DCS_TEST_STRINGIFY_(y[i__]) << " == " << DCS_TEST_PARAM_EXPAND_(y)[n__-i__] << ", " << DCS_TEST_STRINGIFY_(i__) << " == " << i__ << ", " << DCS_TEST_STRINGIFY_(n) << " == " << n__ << " and " << DCS_TEST_STRINGIFY_(e) << " == " << DCS_TEST_PARAM_EXPAND_(e) << "]" ); \
															++test_fails__; \
														} \
													} \
												} \
												/* [/DCS_TEST_CHECK_VECTOR_CLOSE] */


/// Check that elements of matrices \a x and \a y are equal.
#define DCS_TEST_CHECK_MATRIX_EQ(x,y,nr,nc)	/* [DCS_TEST_CHECK_MATRIX_EQ] */ \
											for (::std::size_t i__ = 0; i__ < DCS_TEST_PARAM_EXPAND_(nr); ++i__) \
											{ \
												for (::std::size_t j__ = 0; j__ < DCS_TEST_PARAM_EXPAND_(nc); ++j__) \
												{ \
													if (!(::std::abs(DCS_TEST_PARAM_EXPAND_(x)(i__,j__)-DCS_TEST_PARAM_EXPAND_(y)(i__,j__)) <= DCS_TEST_PARAM_EXPAND_(e))) \
													{ \
														DCS_TEST_ERROR( "Failed assertion: abs(" << DCS_TEST_STRINGIFY_(x(i__,j__)) << "-" << DCS_TEST_STRINGIFY_(y(i__,j__)) << ") <= " << DCS_TEST_STRINGIFY_(e)  << " [with " << DCS_TEST_STRINGIFY_(x(i__,j__)) << " == " << DCS_TEST_PARAM_EXPAND_(x)(i__,j__) << ", " << DCS_TEST_STRINGIFY_(y(i__,j__)) << " == " << DCS_TEST_PARAM_EXPAND_(y)(i__,j__) << ", " << DCS_TEST_STRINGIFY_(i__) << " == " << i__ << ", " << DCS_TEST_STRINGIFY_(j__) << " == " << DCS_TEST_PARAM_EXPAND_(j__) << " and " << DCS_TEST_STRINGIFY_(e) << " == " << DCS_TEST_PARAM_EXPAND_(e) << "]" ); \
														++test_fails__; \
													} \
												} \
											} \
											/* [/DCS_TEST_CHECK_MATRIX_EQ] */


/// Check that elements of matrices \a x and \a y are are with respect to a
/// given precision.
#define DCS_TEST_CHECK_MATRIX_CLOSE(x,y,nr,nc, e)	/* [DCS_TEST_CHECK_MATRIX_CLOSE] */ \
												for (::std::size_t i__ = 0; i__ < DCS_TEST_PARAM_EXPAND_(nr); ++i__) \
												{ \
													for (::std::size_t j__ = 0; j__ < DCS_TEST_PARAM_EXPAND_(nc); ++j__) \
													{ \
														if (!(::std::abs(DCS_TEST_PARAM_EXPAND_(x)(i__,j__)-DCS_TEST_PARAM_EXPAND_(y)(i__,j__)) <= DCS_TEST_PARAM_EXPAND_(e))) \
														{ \
															DCS_TEST_ERROR( "Failed assertion: abs(" << DCS_TEST_STRINGIFY_(x(i__,j__)) << "-" << DCS_TEST_STRINGIFY_(y(i__,j__)) << ") <= " << DCS_TEST_STRINGIFY_(e)  << " [with " << DCS_TEST_STRINGIFY_(x(i__,j__)) << " == " << DCS_TEST_PARAM_EXPAND_(x)(i__,j__) << ", " << DCS_TEST_STRINGIFY_(y(i__,j__)) << " == " << DCS_TEST_PARAM_EXPAND_(y)(i__,j__) << ", " << DCS_TEST_STRINGIFY_(i__) << " == " << i__ << ", " << DCS_TEST_STRINGIFY_(j__) << " == " << DCS_TEST_PARAM_EXPAND_(j__) << " and " << DCS_TEST_STRINGIFY_(e) << " == " << DCS_TEST_PARAM_EXPAND_(e) << "]" ); \
															++test_fails__; \
														} \
													} \
												} \
												/* [/DCS_TEST_CHECK_MATRIX_CLOSE] */


/// Output the error message \a x.
#define DCS_TEST_ERROR(x) std::cerr << "[Error (" << __FILE__ << ":" << __func__ << ":" << __LINE__ << ")>> " << DCS_TEST_PARAM_EXPAND_(x) << std::endl

#endif // DCS_TEST_HPP
