#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/map.hpp>
#include <dcs/test.hpp>


static const double tol(1.0e-5);


DCS_TEST_DEF( rand )
{
	DCS_DEBUG_TRACE("Test Case: Random Variate Generation");

	typedef double real_type;
	typedef ::boost::numeric::ublas::matrix<real_type> matrix_type;
	typedef ::std::size_t size_type;

	const size_type n(3);
	const unsigned long seed(5489UL);

	matrix_type D0(n,n);
	D0(0,0) = -0.01; D0(0,1) =  0.01; D0(0,2) =  0.00;
	D0(1,0) =  0.00; D0(1,1) = -0.51; D0(1,2) =  0.01;
	D0(2,0) =  0.00; D0(2,1) =  0.00; D0(2,2) = -0.50;

	matrix_type D1(n,n);
	D1(0,0) =  0.00; D1(0,1) =  0.00; D1(0,2) =  0.00;
	D1(1,0) =  0.50; D1(1,1) =  0.00; D1(1,2) =  0.00;
	D1(2,0) =  0.00; D1(2,1) =  0.50; D1(2,2) =  0.00;

	::dcs::math::stats::map_distribution<real_type> map(D0, D1);

	::dcs::math::random::mt19937 rng(seed);

	real_type res;
	real_type expect;

	res = ::dcs::math::stats::rand(map, rng);
	expect = 180.452470;
	DCS_DEBUG_TRACE("x[1] " << ::std::fixed << res);
	DCS_TEST_CHECK_CLOSE( res, expect, tol );
}

int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( rand );

	DCS_TEST_END();
}
