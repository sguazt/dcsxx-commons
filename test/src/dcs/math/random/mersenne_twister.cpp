#include <dcs/debug.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/test.hpp>


DCS_TEST_DEF( test_mt11213b )
{
	DCS_DEBUG_TRACE("TEST Mersenne Twister (MT11213B)");

	typedef dcs::math::random::mt11213b engine_type;
	typedef engine_type::result_type value_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	x = rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 3258421267);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 1846212635);

	x = rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 1619973732);
}


DCS_TEST_DEF( test_mt19937 )
{
	DCS_DEBUG_TRACE("TEST Mersenne Twister (MT19937)");

	typedef dcs::math::random::mt19937 engine_type;
	typedef engine_type::result_type value_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	x = rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 545331265);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 2211535594);

	x = rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 4152021490);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_mt11213b );
	DCS_TEST_DO( test_mt19937 );

	DCS_TEST_END();
}
