#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/iterator/any_forward_iterator.hpp>
#include <dcs/test.hpp>
#include <set>
#include <list>
#include <vector>
//#include <boost/iterator.hpp>
#include <iterator>


DCS_TEST_DEF( test_list_iteration )
{
	std::list<int> list_of_ints;
	list_of_ints.push_back(42);
	list_of_ints.push_back(43);
	list_of_ints.push_back(44);

	typedef std::list<int>::iterator iterator_type;
	typedef dcs::iterator::make_any_forward_iterator_type<iterator_type>::type any_number_iterator_type;
	any_number_iterator_type it_end(list_of_ints.end());

	any_number_iterator_type it(list_of_ints.begin());
	iterator_type real_it(list_of_ints.begin());

	for (
		it = list_of_ints.begin();
		it != it_end;
		++it, ++real_it
	) {
		DCS_DEBUG_TRACE( "it: " << (*it) );
		DCS_TEST_CHECK( *it == *real_it );
	}
}


DCS_TEST_DEF( test_vector_iteration )
{
	std::vector<int> vector_of_ints;
	vector_of_ints.push_back(42);
	vector_of_ints.push_back(43);
	vector_of_ints.push_back(44);

	typedef std::vector<int>::iterator iterator_type;
	typedef dcs::iterator::make_any_forward_iterator_type<iterator_type>::type any_number_iterator_type;
	any_number_iterator_type it_end(vector_of_ints.end());

	any_number_iterator_type it(vector_of_ints.begin());
	iterator_type real_it(vector_of_ints.begin());

	for (
		;//it = vector_of_ints.begin();
		it != it_end;
		++it, ++real_it
	) {
		DCS_DEBUG_TRACE( "it: " << (*it) );
		DCS_TEST_CHECK( *it == *real_it );
	}
}


/*
DCS_TEST_DEF( test_set_iteration )
{
	std::set<int> set_of_ints;
	set_of_ints.insert(1);
	set_of_ints.insert(2);
	set_of_ints.insert(3);
	set_of_ints.insert(4);

	typedef std::set<int>::iterator iterator_type;
	typedef dcs::iterator::make_any_forward_iterator_type<iterator_type>::type any_number_iterator_type;
	any_number_iterator_type it_end(set_of_ints.end());

	any_number_iterator_type it;

	iterator_type set_it = set_of_ints.begin();
	for (
		it = set_of_ints.begin();
		it != it_end;
		++it
	) {
		DCS_DEBUG_TRACE( "it: " << (*it) );
		DCS_TEST_CHECK( *it == *set_it );
		++set_it;
	}
}


DCS_TEST_DEF( test_vector_list_iteration_mix )
{
	std::vector<int> vector_of_ints(42, 43);
	typedef std::vector<int>::iterator iterator_type;
	//typedef dcs::iterator::make_any_iterator_type<std::vector<int>::iterator>::type any_number_iterator_type; // Don't work since iterators to vector are random_access while iterators to list are not!
	//any_number_iterator_type number_iter;
	typedef dcs::iterator::any_forward_iterator<
		  std::iterator_traits<iterator_type>::value_type,
		  //std::iterator_traits<iterator_type>::iterator_category, // Don't work since iterators to vector are random_access while iterators to list are not!
		  std::bidirectional_iterator_tag,
		  std::iterator_traits<iterator_type>::reference,
		  std::iterator_traits<iterator_type>::difference_type
		> any_number_iterator_type;
	any_number_iterator_type it;


	it = vector_of_ints.begin();
	++it;
	DCS_DEBUG_TRACE( "*(++it) vs vector[1]: " << *it );
	DCS_TEST_CHECK( *it == vector_of_ints[1] );

	std::list<int> list_of_ints(41, 44);
	it = list_of_ints.begin();
	++it;
	DCS_DEBUG_TRACE( "*(++it) vs list.back(): " << *it );
	DCS_TEST_CHECK( *it == list_of_ints.back() );
}
*/


int main()
{
	DCS_TEST_BEGIN();

	DCS_TEST_DO( test_list_iteration );
	DCS_TEST_DO( test_vector_iteration );
//	DCS_TEST_DO( test_set_iteration );
//	DCS_TEST_DO( test_vector_list_iteration_mix );

	DCS_TEST_END();
}
