#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/iterator/iterator_range.hpp>
#include <dcs/test.hpp>
#include <set>
#include <list>
#include <vector>
//#include <boost/iterator.hpp>
#include <iterator>


DCS_TEST_DEF( test_vector_iteration )
{
	std::vector<int> vector_of_ints;
	vector_of_ints.push_back(42);
	vector_of_ints.push_back(43);
	vector_of_ints.push_back(44);

	typedef std::vector<int>::iterator iterator_type;
//	typedef dcs::iterator::any_iterator<
//			  std::iterator_traits<iterator_type>::value_type,
//			  std::iterator_traits<iterator_type>::iterator_category,
//			  std::iterator_traits<iterator_type>::reference,
//			  std::iterator_traits<iterator_type>::difference_type
//		> any_number_iterator_type;
	typedef dcs::iterator::iterator_range<iterator_type>::type range_type;
	range_type rng = dcs::iterator::make_iterator_range(
		vector_of_ints.begin(),
		vector_of_ints.end()
	);

	DCS_DEBUG_TRACE( "First iterator in range equals original first iterator: " << (rng.begin() == vector_of_ints.begin()) );
	DCS_TEST_CHECK( rng.begin() == vector_of_ints.begin() );
	DCS_DEBUG_TRACE( "Second iterator in range equals original last iterator: " << (rng.end() == vector_of_ints.end()) );
	DCS_TEST_CHECK( rng.end() == vector_of_ints.end() );
	DCS_DEBUG_TRACE( "Range size equals original vector iterator distance: " << (rng.size() == std::distance(vector_of_ints.begin(), vector_of_ints.end())) );
	DCS_TEST_CHECK( rng.size() == std::distance(vector_of_ints.begin(), vector_of_ints.end()) );
	DCS_DEBUG_TRACE( "First iterator in range points to: " << *(rng.begin()) );
	DCS_TEST_CHECK( *(rng.begin()) == 42 );
	DCS_DEBUG_TRACE( "(it+1) point to: " << *(rng.begin()+1) );
	DCS_TEST_CHECK( *(rng.begin()+1) == 43 );
	DCS_DEBUG_TRACE( "(it+2) point to: " << *(rng.begin()+2) );
	DCS_TEST_CHECK( *(rng.begin()+2) == 44 );

	std::size_t i = 0;
	for (
		iterator_type it = rng.begin();
		it != rng.end();
		++it
	) {
		DCS_DEBUG_TRACE( "it: " << (*it) );
		DCS_TEST_CHECK( *it == vector_of_ints[i] );
		++i;
	}
}


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_vector_iteration );

	DCS_TEST_END();
}
