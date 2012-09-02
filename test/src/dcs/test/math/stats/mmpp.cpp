#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/mmpp.hpp>
#include <dcs/test.hpp>


static const double tol(1.0e-5);


DCS_TEST_DEF( rand )
{
	DCS_DEBUG_TRACE("Test Case: Random Variate Generation");

	typedef double real_type;
	typedef ::boost::numeric::ublas::matrix<real_type> matrix_type;
	typedef ::boost::numeric::ublas::vector<real_type> vector_type;
	typedef ::std::size_t size_type;

	const size_type n(2);
	const unsigned long seed(5489UL);

	vector_type lambda(n);
	lambda(0) = 20;
	lambda(1) = 2;

	matrix_type Q(n,n);
	Q(0,0) = -2; Q(0,1) =  2;
	Q(1,0) =  1; Q(1,1) = -1;

	::dcs::math::stats::mmpp_distribution<real_type> mmpp(lambda, Q);
	DCS_DEBUG_TRACE("Q: " << mmpp.Q());
	DCS_DEBUG_TRACE("lambda: " << mmpp.lambda());

	::dcs::math::random::mt19937 rng(seed);

	real_type res;
	real_type expect;

	res = ::dcs::math::stats::rand(mmpp, rng);
	expect = 0.107375;
	DCS_DEBUG_TRACE("x[1] " << ::std::fixed << res);
	DCS_TEST_CHECK_CLOSE( res, expect, tol );
}

int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( rand );

	DCS_TEST_END();
}
