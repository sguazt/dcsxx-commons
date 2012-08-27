#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/linear_congruential.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <dcs/test.hpp>

static const double TOL = 1.0e-5;

DCS_TEST_DEF( test_create )
{
	DCS_DEBUG_TRACE("Test Case: create");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type u01_rng(x0);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.9662120) <= TOL);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.1291730) <= TOL);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.0106569) <= TOL);
}


// In this test the wrapped generator is a copy of the original generator.
// So the two generators (i.e., the original and wrapped one) have a separate
// state; if one of them changes its internal state, the other remains
// unchanged.
DCS_TEST_DEF( test_wrapped_copy )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	u01_engine_type u01_rng(rng);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.9662120) <= TOL);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 2074924992);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.1291730) <= TOL);
}


// In this test the wrapped generator is a reference to the original generator.
// So the two generators (i.e., the original and wrapped one) have a common
// state; if one of them changes its internal state, the change is also seen by
// the other one.
DCS_TEST_DEF( test_wrapped_ref )
{
	DCS_DEBUG_TRACE("Test Case: Wrapped Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type&,value_type> u01_engine_type;

	value_type x(0);
	seed_type x0(123456);
	engine_type rng(x0);
	u01_engine_type u01_rng(rng);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.9662120) <= TOL);

	x0 = rng();
	DCS_DEBUG_TRACE("x[2]: " << x0);
	DCS_TEST_CHECK(x0 == 277396911);

	x = u01_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::abs(x - 0.0106569) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_create );
	DCS_TEST_DO( test_wrapped_copy );
	DCS_TEST_DO( test_wrapped_ref );

	DCS_TEST_END();
}
