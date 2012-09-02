#include <dcs/debug.hpp>
#include <dcs/math/random/linear_congruential.hpp>
#include <dcs/test.hpp>


DCS_TEST_DEF( test_minstd_rand0 )
{
	DCS_DEBUG_TRACE("TEST MINSTD -- rand0");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	x = rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_minstd_rand1 )
{
	DCS_DEBUG_TRACE("TEST MINSTD -- rand1");

	typedef dcs::math::random::minstd_rand1 engine_type;
	typedef engine_type::result_type value_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	x = rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 1664377282);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 1645061505);

	x = rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 1261092736);
}


DCS_TEST_DEF( test_minstd_rand2 )
{
	DCS_DEBUG_TRACE("TEST MINSTD -- rand2");

	typedef dcs::math::random::minstd_rand2 engine_type;
	typedef engine_type::result_type value_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	x = rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 5195588);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 944779452);

	x = rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 1213603729);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_minstd_rand0 );
	DCS_TEST_DO( test_minstd_rand1 );
	DCS_TEST_DO( test_minstd_rand2 );

	DCS_TEST_END();
}
