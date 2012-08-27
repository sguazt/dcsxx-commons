#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/linear_congruential.hpp>
#include <dcs/math/random/uniform_real_adaptor.hpp>
#include <dcs/test.hpp>

static const double TOL = 1.0e-5;

DCS_TEST_DEF( test_create_05_25 )
{
	DCS_DEBUG_TRACE("Test Case: Create [0.5, 2.5]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_real_adaptor<engine_type,value_type> ureal_engine_type;

	value_type x(0);
	seed_type x0(123456);
	ureal_engine_type ureal_rng(x0, 0.5, 2.5);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.43242) <= TOL);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.758346) <= TOL);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.521314) <= TOL);
}


// In this test the wrapped generator is a copy of the original generator.
// So the two generators (i.e., the original and wrapped one) have a separate
// state; if one of them changes its internal state, the other remains
// unchanged.
DCS_TEST_DEF( test_wrapped_copy_05_25 )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Copy [0.5, 2.5]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_real_adaptor<engine_type,value_type> ureal_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	ureal_engine_type ureal_rng(rng, 0.5, 2.5);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.43242) <= TOL);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 2074924992);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.758346) <= TOL);
}


// In this test the wrapped generator is a reference to the original generator.
// So the two generators (i.e., the original and wrapped one) have a common
// state; if one of them changes its internal state, the change is also seen by
// the other one.
DCS_TEST_DEF( test_wrapped_ref_05_25 )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Reference [0.5, 2.5]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_real_adaptor<engine_type&,value_type> ureal_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	ureal_engine_type ureal_rng(rng, 0.5, 2.5);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 2.43242) <= TOL);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 277396911);

	x = ureal_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.521314) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_create_05_25 );
	DCS_TEST_DO( test_wrapped_copy_05_25 );
	DCS_TEST_DO( test_wrapped_ref_05_25 );

	DCS_TEST_END();
}
