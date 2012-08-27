#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/degenerate.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_degenerate )
{
	DCS_DEBUG_TRACE("TEST Degenerate Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::degenerate_distribution<real_type> distribution_type;

	// Create a degenerate distribution with constant value=2.5
	const real_type k0(2.5);
	distribution_type dist(k0);

	DCS_DEBUG_TRACE("stddev: " << dcs::math::stats::mean(dist));
	DCS_TEST_CHECK(std::abs(dcs::math::stats::mean(dist) - k0) <= TOL);

	DCS_DEBUG_TRACE("stddev: " << dcs::math::stats::standard_deviation(dist));
	DCS_TEST_CHECK(std::abs(dcs::math::stats::standard_deviation(dist) - 0) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - k0) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - k0) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - k0) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_degenerate );

	DCS_TEST_END();
}
