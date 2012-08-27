#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/continuous_uniform.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_continuous_uniform )
{
	DCS_DEBUG_TRACE("TEST Continuous Uniform Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::continuous_uniform_distribution<real_type> distribution_type;

	// Create a continuous uniform distribution in [2.5,9.5]
	distribution_type u(2.5, 9.5);

	DCS_DEBUG_TRACE("a: " << u.min());
	DCS_TEST_CHECK(std::abs(u.min() - 2.5) <= TOL);

	DCS_DEBUG_TRACE("b: " << u.max());
	DCS_TEST_CHECK(std::abs(u.max() - 9.5) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = u.rand(rng);
	DCS_DEBUG_TRACE("random variate #1: " << x);
	DCS_TEST_CHECK(std::abs(x - 9.04191) <= TOL);
	x = u.rand(rng);
	DCS_DEBUG_TRACE("random variate #2: " << x);
	DCS_TEST_CHECK(std::abs(x - 5.56337) <= TOL);
	x = u.rand(rng);
	DCS_DEBUG_TRACE("random variate #3: " << x);
	DCS_TEST_CHECK(std::abs(x - 8.48731) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_continuous_uniform );

	DCS_TEST_END();
}
