#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/distribution/pmpp.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <dcs/test.hpp>


static const double tol(1.0e-5);


DCS_TEST_DEF( rand )
{
	DCS_DEBUG_TRACE("Test Case: Random Variate Generation");

	typedef double real_type;

	const unsigned long seed(5489UL);

	const real_type regular_rate(0.15);
	const real_type bursty_rate(0.60);
	const real_type phase_shape(3-2*0.75); // => Hurst = 0.75
	const real_type min_phase_duration(1);


	::dcs::math::stats::pmpp_distribution<real_type> pmpp(regular_rate,
														  bursty_rate,
														  phase_shape,
														  min_phase_duration);

	::dcs::math::random::mt19937 rng(seed);

	real_type res;
	real_type expect;

	res = ::dcs::math::stats::rand(pmpp, rng);
	expect = 0.242629;
	DCS_DEBUG_TRACE("x[1] " << ::std::fixed << res);
	DCS_TEST_CHECK_CLOSE( res, expect, tol );
}


void randn()
{
	typedef double real_type;

	const unsigned long seed(5489UL);

	const real_type regular_rate(0.15);
	const real_type bursty_rate(0.60);
	const real_type phase_shape(3-2*0.75); // => Hurst = 0.75
	const real_type min_phase_duration(1);


	::dcs::math::stats::pmpp_distribution<real_type> pmpp(regular_rate,
														  bursty_rate,
														  phase_shape,
														  min_phase_duration);

	::dcs::math::random::mt19937 rng(seed);

	::std::vector<real_type> res;

	res = pmpp.rand(rng,1e+6);
	for (std::size_t i=0; i < 1e+6; ++i)
	{
		std::cout << res[i] << std::endl;
	}
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( rand );

	DCS_TEST_END();

//	randn();
}
