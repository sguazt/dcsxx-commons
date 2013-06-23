#include <algorithm>
#include <cstddef>
#include <dcs/algorithm/reorder.hpp>
#include <dcs/debug.hpp>
#include <dcs/test.hpp>
#include <string>
#include <vector>


DCS_TEST_DEF( test_vector )
{
	DCS_DEBUG_TRACE("Test case: STL vector");

	::std::vector<int> v;

	v.push_back(8);
	v.push_back(7);
	v.push_back(5);
	v.push_back(9);
	v.push_back(10);
	v.push_back(-10);
	v.push_back(11);

	std::vector<std::size_t> indices;
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(6);

	std::vector<int> sorted_v(v.begin(), v.end());
	std::sort(sorted_v.begin(), sorted_v.end());

	dcs::algorithm::reorder(indices.begin(), indices.end(), v.begin());

	for (std::size_t i = 0; i != v.size(); ++i)
	{
		DCS_DEBUG_TRACE("v[" << i << "]=" << v[i] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK_EQ(v[i], sorted_v[i]);
	}
}

DCS_TEST_DEF( test_carray )
{
	DCS_DEBUG_TRACE("Test case: C-array");

	const ::std::size_t N = 7;

	int v[] = {8, 7, 5, 9, 10, -10, 11};

	int sorted_v[N];
	::std::copy(&v[0], &v[N], &sorted_v[0]);
	::std::sort(&sorted_v[0], &sorted_v[N]);

	::std::size_t indices[N];
	indices[0] = 5;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 4;
	indices[6] = 6;

	::dcs::algorithm::reorder(&indices[0], &indices[N], &v[0]);

	for (std::size_t i = 0; i != N; ++i)
	{
		DCS_DEBUG_TRACE("v[" << i << "]=" << v[i] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK(v[i] == sorted_v[i]);
	}
}


DCS_TEST_DEF( test_vector_copy )
{
	DCS_DEBUG_TRACE("Test case: STL vector - Copy");

	::std::vector<int> v;

	v.push_back(8);
	v.push_back(7);
	v.push_back(5);
	v.push_back(9);
	v.push_back(10);
	v.push_back(-10);
	v.push_back(11);

	std::vector<std::size_t> indices;
	indices.push_back(5);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(6);

	std::vector<int> sorted_v(v.begin(), v.end());
	std::sort(sorted_v.begin(), sorted_v.end());

	std::vector<int> out(v.size());
	dcs::algorithm::reorder_copy(indices.begin(), indices.end(), v.begin(), out.begin());

	for (std::size_t i = 0; i != out.size(); ++i)
	{
		DCS_DEBUG_TRACE("out[" << i << "]=" << v[i] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK_EQ(out[i], sorted_v[i]);
	}
}

DCS_TEST_DEF( test_carray_copy )
{
	DCS_DEBUG_TRACE("Test case: C-array - Copy");

	const ::std::size_t N = 7;

	int v[] = {8, 7, 5, 9, 10, -10, 11};

	int sorted_v[N];
	::std::copy(&v[0], &v[N], &sorted_v[0]);
	::std::sort(&sorted_v[0], &sorted_v[N]);

	::std::size_t indices[N];
	indices[0] = 5;
	indices[1] = 2;
	indices[2] = 1;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 4;
	indices[6] = 6;

	int out[N];
	::dcs::algorithm::reorder_copy(&indices[0], &indices[N], &v[0], &out[0]);

	for (std::size_t i = 0; i != N; ++i)
	{
		DCS_DEBUG_TRACE("out[" << i << "]=" << out[i] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK(out[i] == sorted_v[i]);
	}
}


int main()
{
	DCS_TEST_SUITE( "Algorithms test suite: 'reorder' function" );

	DCS_TEST_BEGIN();

	DCS_TEST_DO(test_vector);
	DCS_TEST_DO(test_carray);
	DCS_TEST_DO(test_vector_copy);
	DCS_TEST_DO(test_carray_copy);

	DCS_TEST_END();
}
