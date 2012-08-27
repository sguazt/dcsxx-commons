#include <algorithm>
#include <cstddef>
#include <dcs/algorithm/order.hpp>
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

	::std::vector<int> sorted_v(v.begin(), v.end());
	::std::sort(sorted_v.begin(), sorted_v.end());

	::std::vector< ::std::size_t > indices(v.size());
	::dcs::algorithm::order(v.begin(), v.end(), indices.begin());

	::std::size_t i = 0;
	for (
		::std::vector< ::std::size_t >::const_iterator it = indices.begin();
		it != indices.end();
		++it, ++i
	) {
		DCS_DEBUG_TRACE("v[" << *it << "]=" << v[*it] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK(v[*it] == sorted_v[i]);
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
	::dcs::algorithm::order(&v[0], &v[N], &indices[0]);

	::std::size_t i = 0;
	for (
		::std::size_t* it = &indices[0];
		it != &indices[N];
		++it, ++i
	) {
		DCS_DEBUG_TRACE("v[" << *it << "]=" << v[*it] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK(v[*it] == sorted_v[i]);
	}
}


DCS_TEST_DEF( test_vector_comparator )
{
	DCS_DEBUG_TRACE("Test case: string");

	::std::vector< ::std::string > v;

	v.push_back("lorem");
	v.push_back("ipsum");
	v.push_back("dolor");
	v.push_back("sit");
	v.push_back("amet");
	v.push_back("consectetur");
	v.push_back("adipisicing");
	v.push_back("elit");
	v.push_back("sed");
	v.push_back("do");
	v.push_back("eiusmod");
	v.push_back("tempor");
	v.push_back("incididunt");
	v.push_back("ut");
	v.push_back("labores");
	v.push_back("et");
	v.push_back("dolore");
	v.push_back("magna");
	v.push_back("aliqua");

	::std::vector< ::std::string > sorted_v(v.begin(), v.end());
	::std::sort(sorted_v.begin(), sorted_v.end(), ::std::less< ::std::string >());

	::std::vector< ::std::size_t > indices(v.size());
	::dcs::algorithm::order(v.begin(), v.end(), indices.begin(), ::std::less< ::std::string >());

	::std::size_t i = 0;
	for (
		::std::vector< ::std::size_t >::const_iterator it = indices.begin();
		it != indices.end();
		++it, ++i
	) {
		DCS_DEBUG_TRACE("v[" << *it << "]=" << v[*it] << " vs. sorted_v[" << i << "]=" << sorted_v[i]);

		DCS_TEST_CHECK(v[*it] == sorted_v[i]);
	}
}


int main()
{
	DCS_TEST_SUITE( "Algorithms test suite: 'order' function" );

	DCS_TEST_BEGIN();

	DCS_TEST_DO(test_vector);
	DCS_TEST_DO(test_carray);
	DCS_TEST_DO(test_vector_comparator);

	DCS_TEST_END();
}
