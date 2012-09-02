#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/students_t.hpp>
#include <dcs/test.hpp>


static const double TOL(1.0e-5);


DCS_TEST_DEF( test_students_t )
{
	DCS_DEBUG_TRACE("TEST STUDENT'S t Distribution");

	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::students_t_distribution<real_type> distribution_type;

	// Create an students_t distribution with shape=1.0 and scale=2.5
	distribution_type dist(4);

	DCS_DEBUG_TRACE("degrees of freedom: " << dist.degrees_of_freedom());
	DCS_TEST_CHECK(std::abs(dist.degrees_of_freedom() - 4.0) <= TOL);

	// Create a random number generator
	engine_type rng(5489u);
	real_type x(0);

	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.993059) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - -2.40937) <= TOL);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.94658) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_students_t );

	DCS_TEST_END();
}
