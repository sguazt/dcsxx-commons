#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/chi_squared.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_chi_squared )
{
	DCS_DEBUG_TRACE("TEST Chi Squared Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::chi_squared_distribution<real_type> distribution_type;

	// Create an chi_squared distribution with shape=1.0 and scale=2.5
	distribution_type dist(4);

	DCS_DEBUG_TRACE("degrees of freedom: " << dist.degrees_of_freedom());
	DCS_TEST_CHECK(std::abs(dist.degrees_of_freedom() - 4.0) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.78815) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 3.92334) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.78057) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_chi_squared );

	DCS_TEST_END();
}
