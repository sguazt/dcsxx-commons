#include <dcs/debug.hpp>
#include <dcs/math/random/linear_congruential.hpp>
#include <dcs/math/random/uniform_int_adaptor.hpp>
#include <dcs/test.hpp>


DCS_TEST_DEF( test_create_0_9 )
{
	DCS_DEBUG_TRACE("Test Case: create [0,9]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef int value_type;
	typedef dcs::math::random::uniform_int_adaptor<engine_type,value_type> uint_engine_type;

	value_type x(0);
	seed_type x0(123456);
	uint_engine_type uint_rng(x0, 0, 9);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 9);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 1);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 0);
}


// In this test the wrapped generator is a copy of the original generator.
// So the two generators (i.e., the original and wrapped one) have a separate
// state; if one of them changes its internal state, the other remains
// unchanged.
DCS_TEST_DEF( test_wrapped_copy_0_9 )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Copy [0,9]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef int value_type;
	typedef dcs::math::random::uniform_int_adaptor<engine_type,value_type> uint_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	uint_engine_type uint_rng(rng, 0, 9);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 9);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 2074924992);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 1);
}


// In this test the wrapped generator is a reference to the original generator.
// So the two generators (i.e., the original and wrapped one) have a common
// state; if one of them changes its internal state, the change is also seen by
// the other one.
DCS_TEST_DEF( test_wrapped_ref_0_9 )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Reference [0,9]");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef int value_type;
	typedef dcs::math::random::uniform_int_adaptor<engine_type&,value_type> uint_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	uint_engine_type uint_rng(rng, 0, 9);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 9);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 277396911);

	x = uint_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 0);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_create_0_9 );
	DCS_TEST_DO( test_wrapped_copy_0_9 );
	DCS_TEST_DO( test_wrapped_ref_0_9 );

	DCS_TEST_END();
}
