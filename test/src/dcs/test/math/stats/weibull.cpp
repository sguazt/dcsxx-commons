#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/weibull.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_weibull )
{
	DCS_DEBUG_TRACE("TEST BOUNDED PARETO Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::weibull_distribution<real_type> distribution_type;

	// Create an weibull distribution with shape=2.5, scale=3
	distribution_type dist(2.5, 3);

	DCS_DEBUG_TRACE("shape: " << dist.shape());
	DCS_TEST_CHECK(std::abs(dist.shape() - 2.5) <= TOL);

	DCS_DEBUG_TRACE("min: " << dist.scale());
	DCS_TEST_CHECK(std::abs(dist.scale() - real_type(3)) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.02166) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.77969) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.42781) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_weibull );

	DCS_TEST_END();
}
