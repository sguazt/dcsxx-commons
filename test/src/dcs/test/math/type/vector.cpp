#include <cstddef>
#include <dcs/math/type/vector.hpp>
#include <dcs/test.hpp>


const double tol(1e-5); ///< Tolerance for floating-point equality comparison


DCS_TEST_DEF( real_create_empty )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Empty Vector Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	math::vector<value_type> v;

	DCS_TEST_CHECK_EQ(    0, v.length() );
	DCS_TEST_CHECK_EQ( true, v.empty() );
}

DCS_TEST_DEF( real_create )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n(3);

	math::vector<value_type> v(n);

	DCS_TEST_CHECK_EQ(     n, v.length() );
	DCS_TEST_CHECK_EQ( false, v.empty() );
}

DCS_TEST_DEF( real_get )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Getters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n(3);
	const value_type val(5);

	math::vector<value_type> v(n,val);

	DCS_TEST_CHECK_CLOSE( val, v(0), tol );
	DCS_TEST_CHECK_CLOSE( val, v(1), tol );
	DCS_TEST_CHECK_CLOSE( val, v(2), tol );

	DCS_TEST_CHECK_CLOSE( val, v.at(0), tol );
	DCS_TEST_CHECK_CLOSE( val, v.at(1), tol );
	DCS_TEST_CHECK_CLOSE( val, v.at(2), tol );
}

DCS_TEST_DEF( real_set )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Setters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n(3);
	const value_type val(5);

	math::vector<value_type> v(n,val);
	v(0) = 0;
	v(1) = 1;
	v(2) = 2;

	DCS_TEST_CHECK_CLOSE( 0, v(0), tol );
	DCS_TEST_CHECK_CLOSE( 1, v(1), tol );
	DCS_TEST_CHECK_CLOSE( 2, v(2), tol );

	DCS_TEST_CHECK_CLOSE( 0, v.at(0), tol );
	DCS_TEST_CHECK_CLOSE( 1, v.at(1), tol );
	DCS_TEST_CHECK_CLOSE( 2, v.at(2), tol );
}

DCS_TEST_DEF( real_resize )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Resize");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n1(3);
	const std::size_t n2(5);
	const value_type zero(0);

	math::vector<value_type> v(n1);
	v(0) = 0;
	v(1) = 1;
	v(2) = 2;

	v.resize(n2);

	DCS_TEST_CHECK_CLOSE(    0, v(0), tol );
	DCS_TEST_CHECK_CLOSE(    1, v(1), tol );
	DCS_TEST_CHECK_CLOSE(    2, v(2), tol );
	DCS_TEST_CHECK_CLOSE( zero, v(3), tol );
	DCS_TEST_CHECK_CLOSE( zero, v(4), tol );

	DCS_TEST_CHECK_CLOSE(    0, v.at(0), tol );
	DCS_TEST_CHECK_CLOSE(    1, v.at(1), tol );
	DCS_TEST_CHECK_CLOSE(    2, v.at(2), tol );
	DCS_TEST_CHECK_CLOSE( zero, v.at(3), tol );
	DCS_TEST_CHECK_CLOSE( zero, v.at(4), tol );
}

DCS_TEST_DEF( real_resize_from_empty )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Resize from Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n(3);

	math::vector<value_type> v;

	v.resize(n);

	v(0) = 0;
	v(1) = 1;
	v(2) = 2;

	DCS_TEST_CHECK_CLOSE( 0, v(0), tol );
	DCS_TEST_CHECK_CLOSE( 1, v(1), tol );
	DCS_TEST_CHECK_CLOSE( 2, v(2), tol );

	DCS_TEST_CHECK_CLOSE( 0, v.at(0), tol );
	DCS_TEST_CHECK_CLOSE( 1, v.at(1), tol );
	DCS_TEST_CHECK_CLOSE( 2, v.at(2), tol );
}

DCS_TEST_DEF( real_resize_to_empty )
{
	DCS_TEST_CASE("Dense Vector - Real Type - Vector Resize to Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t n(3);

	math::vector<value_type> v(n);
	v(0) = 0;
	v(1) = 1;
	v(2) = 2;

	v.resize(0);

	DCS_TEST_CHECK_EQ( 0, v.length() );
}


int main()
{
	DCS_TEST_SUITE("Vector Test Suite");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( real_create_empty );
		DCS_TEST_DO( real_create );
		DCS_TEST_DO( real_get );
		DCS_TEST_DO( real_set );
		DCS_TEST_DO( real_resize );
		DCS_TEST_DO( real_resize_from_empty );
		DCS_TEST_DO( real_resize_to_empty );
	DCS_TEST_END();
}
