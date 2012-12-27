#include <cstddef>
#include <dcs/math/type/matrix.hpp>
#include <dcs/test.hpp>


const double tol(1e-5); ///< Tolerance for floating-point equality comparison


DCS_TEST_DEF( real_row_major_create_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Empty Matrix Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A;

	DCS_TEST_CHECK_EQ(    0, A.num_rows() );
	DCS_TEST_CHECK_EQ(    0, A.num_columns() );
	DCS_TEST_CHECK_EQ(    0, A.num_elements() );
	DCS_TEST_CHECK_EQ(    0, A.leading_dimension() );
	DCS_TEST_CHECK_EQ( true, A.empty() );
}

DCS_TEST_DEF( real_row_major_create )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A(nr,nc);

	DCS_TEST_CHECK_EQ(    nr, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nc, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_EQ(    nc, A.leading_dimension() );
	DCS_TEST_CHECK_EQ( false, A.empty() );
}

DCS_TEST_DEF( real_row_major_get )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Getters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type val(5);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A(nr,nc,val);

	DCS_TEST_CHECK_CLOSE( val, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( val, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(2,1), tol );
}

DCS_TEST_DEF( real_row_major_set )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Setters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type val(5);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A(nr,nc,val);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	DCS_TEST_CHECK_CLOSE( 0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( 0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A.at(2,1), tol );
}

DCS_TEST_DEF( real_row_major_resize )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Resize");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type zero(0);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A(nr,nc);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	A.resize(nc,nr);

	DCS_TEST_CHECK_EQ(    nc, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nr, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_CLOSE(    0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE(    1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A(0,2), tol );
	DCS_TEST_CHECK_CLOSE(    2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE(    3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A(1,2), tol );

	DCS_TEST_CHECK_CLOSE(    0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE(    1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A.at(0,2), tol );
	DCS_TEST_CHECK_CLOSE(    2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE(    3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A.at(1,2), tol );
}

DCS_TEST_DEF( real_row_major_resize_from_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Resize from Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A;

	A.resize(nr,nc);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	DCS_TEST_CHECK_EQ(    nr, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nc, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_CLOSE( 0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( 0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A.at(2,1), tol );
}

DCS_TEST_DEF( real_row_major_resize_to_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Row-Major Storage Layout - Matrix Resize to Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::row_major_storage_layout> > A(nr,nc);

	A.resize(0,0);

	DCS_TEST_CHECK_EQ( 0, A.num_rows() );
	DCS_TEST_CHECK_EQ( 0, A.num_columns() );
	DCS_TEST_CHECK_EQ( 0, A.num_elements() );
}

DCS_TEST_DEF( real_col_major_create_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Empty Matrix Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A;

	DCS_TEST_CHECK_EQ(    0, A.num_rows() );
	DCS_TEST_CHECK_EQ(    0, A.num_columns() );
	DCS_TEST_CHECK_EQ(    0, A.num_elements() );
	DCS_TEST_CHECK_EQ(    0, A.leading_dimension() );
	DCS_TEST_CHECK_EQ( true, A.empty() );
}

DCS_TEST_DEF( real_col_major_create )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Creation");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A(nr,nc);

	DCS_TEST_CHECK_EQ(    nr, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nc, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_EQ(    nr, A.leading_dimension() );
	DCS_TEST_CHECK_EQ( false, A.empty() );
}

DCS_TEST_DEF( real_col_major_get )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Getters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type val(5);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A(nr,nc,val);

	DCS_TEST_CHECK_CLOSE( val, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( val, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( val, A.at(2,1), tol );
}

DCS_TEST_DEF( real_col_major_set )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Setters");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type val(5);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A(nr,nc,val);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	DCS_TEST_CHECK_CLOSE( 0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( 0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A.at(2,1), tol );
}

DCS_TEST_DEF( real_col_major_resize )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Resize");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);
	const value_type zero(0);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A(nr,nc);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	A.resize(nc,nr);

	DCS_TEST_CHECK_EQ(    nc, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nr, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_CLOSE(    0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE(    1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A(0,2), tol );
	DCS_TEST_CHECK_CLOSE(    2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE(    3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A(1,2), tol );

	DCS_TEST_CHECK_CLOSE(    0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE(    1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A.at(0,2), tol );
	DCS_TEST_CHECK_CLOSE(    2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE(    3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( zero, A.at(1,2), tol );
}

DCS_TEST_DEF( real_col_major_resize_from_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Resize from Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A;

	A.resize(nr,nc);
	A(0,0) = 0; A(0,1) = 1;
	A(1,0) = 2; A(1,1) = 3;
	A(2,0) = 4; A(2,1) = 5;

	DCS_TEST_CHECK_EQ(    nr, A.num_rows() );
	DCS_TEST_CHECK_EQ(    nc, A.num_columns() );
	DCS_TEST_CHECK_EQ( nr*nc, A.num_elements() );
	DCS_TEST_CHECK_CLOSE( 0, A(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A(2,1), tol );

	DCS_TEST_CHECK_CLOSE( 0, A.at(0,0), tol );
	DCS_TEST_CHECK_CLOSE( 1, A.at(0,1), tol );
	DCS_TEST_CHECK_CLOSE( 2, A.at(1,0), tol );
	DCS_TEST_CHECK_CLOSE( 3, A.at(1,1), tol );
	DCS_TEST_CHECK_CLOSE( 4, A.at(2,0), tol );
	DCS_TEST_CHECK_CLOSE( 5, A.at(2,1), tol );
}

DCS_TEST_DEF( real_col_major_resize_to_empty )
{
	DCS_TEST_CASE("Dense Matrix - Real Type - Column-Major Storage Layout - Matrix Resize to Empty");

	namespace math = ::dcs::math;

	typedef double value_type;

	const std::size_t nr(3);
	const std::size_t nc(2);

	math::matrix< value_type, math::matrix_properties<math::column_major_storage_layout> > A(nr,nc);

	A.resize(0,0);

	DCS_TEST_CHECK_EQ( 0, A.num_rows() );
	DCS_TEST_CHECK_EQ( 0, A.num_columns() );
	DCS_TEST_CHECK_EQ( 0, A.num_elements() );
}


int main()
{
	DCS_TEST_SUITE("Matrix Test Suite");

	DCS_TEST_BEGIN();
		DCS_TEST_DO( real_row_major_create_empty );
		DCS_TEST_DO( real_row_major_create );
		DCS_TEST_DO( real_row_major_get );
		DCS_TEST_DO( real_row_major_set );
		DCS_TEST_DO( real_row_major_resize );
		DCS_TEST_DO( real_row_major_resize_from_empty );
		DCS_TEST_DO( real_row_major_resize_to_empty );
		DCS_TEST_DO( real_col_major_create_empty );
		DCS_TEST_DO( real_col_major_create );
		DCS_TEST_DO( real_col_major_get );
		DCS_TEST_DO( real_col_major_set );
		DCS_TEST_DO( real_col_major_resize );
		DCS_TEST_DO( real_col_major_resize_from_empty );
		DCS_TEST_DO( real_col_major_resize_to_empty );
	DCS_TEST_END();
}
