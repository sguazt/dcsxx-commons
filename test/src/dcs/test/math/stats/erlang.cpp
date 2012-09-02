#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/erlang.hpp>
#include <dcs/test.hpp>


static const double tol(1.0e-5);


DCS_TEST_DEF( test_erlang )
{
	DCS_DEBUG_TRACE("TEST erlang Distribution");

	typedef double real_type;
	typedef ::std::size_t uint_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::erlang_distribution<real_type> distribution_type;

	const uint_type seed(5489);
	const uint_type k(3);
	const real_type lambda(2.5);

	// Create an Erlang(k,lambda) distribution
	distribution_type dist(k, lambda);

	DCS_DEBUG_TRACE("k: " << dist.k());
	DCS_TEST_CHECK(std::abs(dist.k() - k) <= tol);
	DCS_DEBUG_TRACE("lambda: " << dist.lambda());
	DCS_TEST_CHECK(std::abs(dist.lambda() - lambda) <= tol);

	// Create a random number generator
	engine_type rng(seed);

/*
	real_type x(0);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 1.09064) <= tol);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.230234) <= tol);
	x = dist.rand(rng);
	DCS_DEBUG_TRACE("random variate: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.77332) <= tol);
*/
	for (::std::size_t i=0; i<1000; ++i)
	{
		::std::cout << dist.rand(rng) << ::std::endl;
	}
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_erlang );

	DCS_TEST_END();
}
