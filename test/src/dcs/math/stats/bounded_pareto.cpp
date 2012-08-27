#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/bounded_pareto.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_bounded_pareto )
{
	DCS_DEBUG_TRACE("TEST BOUNDED PARETO Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::bounded_pareto_distribution<real_type> distribution_type;

	// Create an bounded_pareto distribution with shape=2.5, min=2, max=40
	distribution_type dist(2.5, 2, 40);

	DCS_DEBUG_TRACE("shape: " << dist.shape());
	DCS_TEST_CHECK(std::abs(dist.shape() - 2.5) <= TOL);

	DCS_DEBUG_TRACE("min: " << dist.min());
	DCS_TEST_CHECK(std::abs(dist.min() - real_type(2)) <= TOL);

	DCS_DEBUG_TRACE("max: " << dist.max());
	DCS_TEST_CHECK(std::abs(dist.max() - real_type(40)) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 5.93346) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.51735) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 4.32818) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_bounded_pareto );

	DCS_TEST_END();
}
