#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <dcs/math/stats/distribution/any_distribution.hpp>
#include <dcs/math/stats/distribution/exponential.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_rand )
{
	DCS_DEBUG_TRACE("TEST Random Variate Generation");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,real_type> u01_engine_type;
	typedef dcs::math::random::any_generator<real_type> any_engine_type;
	typedef dcs::math::stats::exponential_distribution<real_type> distribution_type;
	typedef dcs::math::stats::any_distribution<real_type> any_distribution_type;

	// Create an exponential distribution with lambda=2.5
	distribution_type dist(2.5);
	any_distribution_type any_dist(dist);

	//DCS_DEBUG_TRACE("lambda: " << dist.lambda());
	//DCS_TEST_CHECK(std::abs(dist.lambda() - 2.5) <= TOL);

	// Create a random number generator
	u01_engine_type rng(5489u);
	any_engine_type any_rng(rng);

	real_type x(0);

	x = any_dist.rand(any_rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.09064) <= TOL);
	x = any_dist.rand(any_rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.230234) <= TOL);
	x = any_dist.rand(any_rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.77332) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_rand );

	DCS_TEST_END();
}
