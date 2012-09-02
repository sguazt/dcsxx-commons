#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/discrete_uniform.hpp>
#include <dcs/test.hpp>


DCS_TEST_DEF( test_discrete_uniform )
{
	DCS_DEBUG_TRACE("TEST Discrete Uniform Distribution");

	typedef int support_type;
	typedef double value_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_uniform_distribution<support_type,value_type> distribution_type;

	// Create a continuous uniform distribution in [2.5,9.5]
	distribution_type dist(2, 10);

	DCS_DEBUG_TRACE("a: " << dist.min());
	DCS_TEST_CHECK(dist.min() == 2);

	DCS_DEBUG_TRACE("b: " << dist.max());
	DCS_TEST_CHECK(dist.max() == 10);

	// Create a random number generator
	engine_type rng(5489u);
	value_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate #1: " << x);
	DCS_TEST_CHECK(x == 10);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate #2: " << x);
	DCS_TEST_CHECK(x == 5);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate #3: " << x);
	DCS_TEST_CHECK(x == 9);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_discrete_uniform );

	DCS_TEST_END();
}
