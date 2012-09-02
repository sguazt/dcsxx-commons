#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/gamma.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_gamma )
{
	DCS_DEBUG_TRACE("TEST GAMMA Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::gamma_distribution<real_type> distribution_type;

	// Create an gamma distribution with shape=1.0 and scale=2.5
	distribution_type dist(1.0, 2.5);

	DCS_DEBUG_TRACE("shape: " << dist.shape());
	DCS_TEST_CHECK(std::abs(dist.shape() - 1.0) <= TOL);

	DCS_DEBUG_TRACE("scale: " << dist.scale());
	DCS_TEST_CHECK(std::abs(dist.scale() - 2.5) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.169202) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.065990) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.390669) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_gamma );

	DCS_TEST_END();
}
