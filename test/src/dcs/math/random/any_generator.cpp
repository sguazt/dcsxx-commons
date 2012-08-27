#include <cmath>
#include <dcs/debug.hpp>
#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/linear_congruential.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <dcs/test.hpp>
#include <dcs/util/holder.hpp>

static const double TOL = 1.0e-5;

DCS_TEST_DEF( test_create )
{
	DCS_DEBUG_TRACE("TEST Creation");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::any_generator<value_type> any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	any_engine_type any_rng(rng);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = any_rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_copy )
{
	DCS_DEBUG_TRACE("TEST Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::any_generator<value_type> any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	any_engine_type any_rng(rng);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 22885540);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_reference )
{
	DCS_DEBUG_TRACE("TEST Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::any_generator<value_type> any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	dcs::util::holder<engine_type&> wrap_rng(rng);
	any_engine_type any_rng(
		wrap_rng
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_meta_functor_copy )
{
	DCS_DEBUG_TRACE("TEST Meta Functor Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::make_any_generator_type<engine_type>::type any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	any_engine_type any_rng(rng);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 22885540);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_meta_functor_reference )
{
	DCS_DEBUG_TRACE("TEST Meta Functor Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::make_any_generator_type<engine_type&>::type any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	dcs::util::holder<engine_type&> wrap_rng(rng);
	any_engine_type any_rng(
		wrap_rng
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_functor_copy )
{
	DCS_DEBUG_TRACE("TEST Functor Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::make_any_generator_type<engine_type>::type any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	any_engine_type any_rng(
		dcs::math::random::make_any_generator(rng)
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(x == 22885540);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_functor_reference )
{
	DCS_DEBUG_TRACE("TEST Functor Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type value_type;
	typedef dcs::math::random::make_any_generator_type<engine_type&>::type any_engine_type;

	value_type x(123456);
	engine_type rng(x);

	DCS_DEBUG_TRACE("x[0]: " << x);
	DCS_TEST_CHECK(x == 123456);

	any_engine_type any_rng(
		dcs::math::random::make_any_generator<engine_type&>(rng)
	);


	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(x == 2074924992);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(x == 277396911);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(x == 22885540);
}


DCS_TEST_DEF( test_u01_wrap_copy )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::any_generator<value_type> any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	any_engine_type any_rng(rng);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


DCS_TEST_DEF( test_u01_wrap_reference )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::any_generator<value_type> any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	dcs::util::holder<u01_engine_type&> wrap_rng(rng);
	any_engine_type any_rng(
		wrap_rng
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


DCS_TEST_DEF( test_u01_wrap_meta_functor_copy )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Meta Functor Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::make_any_generator_type<u01_engine_type>::type any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	any_engine_type any_rng(rng);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


DCS_TEST_DEF( test_u01_wrap_meta_functor_reference )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Meta Functor Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::make_any_generator_type<u01_engine_type&>::type any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	dcs::util::holder<u01_engine_type&> wrap_rng(rng);
	any_engine_type any_rng(
		wrap_rng
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


DCS_TEST_DEF( test_u01_wrap_functor_copy )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Functor Copy");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::make_any_generator_type<u01_engine_type>::type any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	any_engine_type any_rng(
		dcs::math::random::make_any_generator(rng)
	);

	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[2]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);

	x = rng();
	DCS_DEBUG_TRACE("x[6]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


DCS_TEST_DEF( test_u01_wrap_functor_reference )
{
	DCS_DEBUG_TRACE("TEST Uniform [0,1] Wrapped Functor Reference");

	typedef dcs::math::random::minstd_rand0 engine_type;
	typedef engine_type::result_type seed_type;
	typedef double value_type;
	typedef dcs::math::random::uniform_01_adaptor<engine_type,value_type> u01_engine_type;
	typedef dcs::math::random::make_any_generator_type<u01_engine_type&>::type any_engine_type;

	value_type x(0);
	seed_type x0(123456);
	u01_engine_type rng(x0);

	DCS_DEBUG_TRACE("x[0]: " << x0);
	DCS_TEST_CHECK(x0 == 123456);

	any_engine_type any_rng(
		dcs::math::random::make_any_generator<u01_engine_type&>(rng)
	);


	x = any_rng();
	DCS_DEBUG_TRACE("x[1]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.9662120) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[3]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.1291730) <= TOL);

	x = any_rng();
	DCS_DEBUG_TRACE("x[4]: " << x);
	DCS_TEST_CHECK(std::fabs(x - 0.0106569) <= TOL);
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_create );
	DCS_TEST_DO( test_copy );
	DCS_TEST_DO( test_reference );
	DCS_TEST_DO( test_meta_functor_copy );
	DCS_TEST_DO( test_meta_functor_reference );
	DCS_TEST_DO( test_functor_copy );
	DCS_TEST_DO( test_functor_reference );
	DCS_TEST_DO( test_u01_wrap_copy );
	DCS_TEST_DO( test_u01_wrap_reference );
	DCS_TEST_DO( test_u01_wrap_meta_functor_copy );
	DCS_TEST_DO( test_u01_wrap_meta_functor_reference );
	DCS_TEST_DO( test_u01_wrap_functor_copy );
	DCS_TEST_DO( test_u01_wrap_functor_reference );

	DCS_TEST_END();
}
