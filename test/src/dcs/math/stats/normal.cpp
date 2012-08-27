#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/normal.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_normal )
{
	DCS_DEBUG_TRACE("TEST Normal Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::normal_distribution<real_type> distribution_type;

	// Create an normal distribution with lambda=2.5
	distribution_type dist(1.0, 2.5);

	DCS_DEBUG_TRACE("mean: " << dist.mean());
	DCS_TEST_CHECK(std::abs(dist.mean() - 1.0) <= TOL);

	DCS_DEBUG_TRACE("stddev: " << dist.stddev());
	DCS_TEST_CHECK(std::abs(dist.stddev() - 2.5) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 3.45874) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.92083) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - -1.30954) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_normal );

	DCS_TEST_END();
}
