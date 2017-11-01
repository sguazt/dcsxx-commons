#include <boost/shared_ptr.hpp>
#include <cstddef>
#include <dcs/algorithm/combinatorics.hpp>
#include <dcs/debug.hpp>
#include <dcs/test.hpp>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace /*<unnamed>*/ {

template <typename CharT, typename CharTraitsT, typename ElemT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os,
                                                    ::std::vector<ElemT> const& v)
{
    os << '(';

	for (::std::size_t i = 0; i < v.size(); ++i)
	{
		if (i > 0)
		{
			os << ' ';
		}
		os << '\'' << v[i] << '\'';
	}

 	os << ')';

    return os;
}

template <typename CharT, typename CharTraitsT, typename ElemT>
::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os,
                                                    ::std::vector< ::std::vector<ElemT> > const& vv)
{
    os << '(';

	for (::std::size_t i = 0; i < vv.size(); ++i)
	{
		if (i > 0)
		{
			os << ' ';
		}
		os << '\'' << vv[i] << '\'';
	}
    os << ')';

    return os;
}

} // Namespace <unnamed>

DCS_TEST_DEF( test_partition_class )
{
	DCS_TEST_TRACE( "Test case: Partition - Class" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_partition part(sz);

	DCS_TEST_TRACE( "Test case: Partition - Class - increment" );

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		++part;
	}

	DCS_TEST_TRACE( "Test case: Partition - Class - decrement" );

	while (part.has_prev())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		--part;
	}

	DCS_TEST_TRACE( "Test case: Partition - Class - subsetting" );

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << '(';
		for (typename dcs::algorithm::partition_traits<value_type>::subset_container::const_iterator it = subs.begin();
			 it != subs.end();
			 ++it)
		{
			if (it != subs.begin())
			{
				DCS_DEBUG_STREAM << ',';
			}

			const dcs::algorithm::partition_traits<value_type>::element_container& subset = *it;

			DCS_DEBUG_STREAM << '(';
			for (typename dcs::algorithm::partition_traits<value_type>::element_const_iterator sub_it = subset.begin();
				 sub_it != subset.end();
				 ++sub_it)
			{
				if (sub_it != subset.begin())
				{
					DCS_DEBUG_STREAM << ',';
				}
				DCS_DEBUG_STREAM << *sub_it;
			}
			DCS_DEBUG_STREAM << ')';
		}
		DCS_DEBUG_STREAM << ')' << ::std::endl;

		++part;
	}
}

DCS_TEST_DEF( test_partition_iter )
{
	DCS_TEST_TRACE( "Test case: Partition - Iter" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - iteration" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::iterator it = part.begin();
				 it != part.end();
				 ++it)
			{
				if (it != part.begin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - const iteration" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::const_iterator it = part.begin();
				 it != part.end();
				 ++it)
			{
				if (it != part.begin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - const iteration (alt)" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::const_iterator it = part.cbegin();
				 it != part.cend();
				 ++it)
			{
				if (it != part.cbegin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - reverse iteration" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::reverse_iterator it = part.rbegin();
				 it != part.rend();
				 ++it)
			{
				if (it != part.rbegin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - const reverse iteration" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::const_reverse_iterator it = part.rbegin();
				 it != part.rend();
				 ++it)
			{
				if (it != part.rbegin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}

	DCS_TEST_TRACE( "Test case: Partition - Iter - const reverse iteration (alt)" );
	{
		dcs::algorithm::lexicographic_partition part(sz);

		while (part.has_next())
		{
			DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

			for (dcs::algorithm::lexicographic_partition::const_reverse_iterator it = part.crbegin();
				 it != part.crend();
				 ++it)
			{
				if (it != part.crbegin())
				{
					DCS_DEBUG_STREAM << ",";
				}
				DCS_DEBUG_STREAM << *it;
			}
			DCS_DEBUG_STREAM << std::endl;

			++part;
		}
	}
}

DCS_TEST_DEF( test_next_partition )
{
	DCS_TEST_TRACE( "Test case: Partition - next_partition function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_partition part(sz);

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::next_partition(v.begin(), v.end(), part);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_prev_partition )
{
	DCS_TEST_TRACE( "Test case: Partition - prev_partition function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_partition part(sz, false);

	while (part.has_prev())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::prev_partition(v.begin(), v.end(), part);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_reverse_partition_class )
{
	DCS_TEST_TRACE( "Test case: Reverse partition - Class" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::reverse_lexicographic_partition part(sz);

	DCS_TEST_TRACE( "Test case: Reverse partition - Class - increment" );

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		++part;
	}

	DCS_TEST_TRACE( "Test case: Reverse partition - Class - decrement" );

	while (part.has_prev())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		--part;
	}

	DCS_TEST_TRACE( "Test case: Reverse partition - Class - subsetting" );

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << '(';
		for (typename dcs::algorithm::partition_traits<value_type>::subset_container::const_iterator it = subs.begin();
			 it != subs.end();
			 ++it)
		{
			if (it != subs.begin())
			{
				DCS_DEBUG_STREAM << ',';
			}

			const dcs::algorithm::partition_traits<value_type>::element_container& subset = *it;

			DCS_DEBUG_STREAM << '(';
			for (typename dcs::algorithm::partition_traits<value_type>::element_const_iterator sub_it = subset.begin();
				 sub_it != subset.end();
				 ++sub_it)
			{
				if (sub_it != subset.begin())
				{
					DCS_DEBUG_STREAM << ',';
				}
				DCS_DEBUG_STREAM << *sub_it;
			}
			DCS_DEBUG_STREAM << ')';
		}
		DCS_DEBUG_STREAM << ')' << ::std::endl;

		++part;
	}
}

DCS_TEST_DEF( test_k_partition_class )
{
	DCS_TEST_TRACE( "Test case: k-Partition - Class" );

	typedef char value_type;

	const ::std::size_t sz(4);
	const ::std::size_t k(2);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_k_partition part(sz,k);

	DCS_TEST_TRACE( "Test case: k-Partition - Class - increment" );

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		++part;
	}

	DCS_TEST_TRACE( "Test case: k-Partition - Class - decrement" );

	while (part.has_prev())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs = part(v.begin(), v.end());

		DCS_DEBUG_STREAM << subs << ::std::endl;

		--part;
	}
}

DCS_TEST_DEF( test_next_k_partition )
{
	DCS_TEST_TRACE( "Test case: k-Partition - next_partition function" );

	typedef char value_type;

	const ::std::size_t sz(4);
	const ::std::size_t k(2);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_k_partition part(sz,k);

	while (part.has_next())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::next_partition(v.begin(), v.end(), part);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_prev_k_partition )
{
	DCS_TEST_TRACE( "Test case: k-Partition - prev_partition function" );

	typedef char value_type;

	const ::std::size_t sz(4);
	const ::std::size_t k(2);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_k_partition part(sz, k, false);

	while (part.has_prev())
	{
		DCS_DEBUG_STREAM << part << " : " << part.num_subsets() << " : ";

		dcs::algorithm::partition_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::prev_partition(v.begin(), v.end(), part);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_subset_class_with_empty )
{
	DCS_TEST_TRACE( "Test case: Subset Class with Empty Set" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz, true);

	DCS_TEST_TRACE( "Test case: Subset - Class - increment" );

	while (subset.has_next())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		++subset;
	}

	DCS_TEST_TRACE( "Test case: Subset - Class - decrement" );

	while (subset.has_prev())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		--subset;
	}
}

DCS_TEST_DEF( test_subset_class_without_empty )
{
	DCS_TEST_TRACE( "Test case: Subset Class without Empty Set" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz, false);

	DCS_TEST_TRACE( "Test case: Subset - Class - increment" );

	while (subset.has_next())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		++subset;
	}

	DCS_TEST_TRACE( "Test case: Subset - Class - decrement" );

	while (subset.has_prev())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		--subset;
	}
}

DCS_TEST_DEF( test_next_subset_with_empty )
{
	DCS_TEST_TRACE( "Test case: Subset with Empty Set - next_subset function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz);

	while (subset.has_next())
	{
		DCS_DEBUG_STREAM << subset << " : [size=" << subset.size() << "] : ";

		dcs::algorithm::subset_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::next_subset(v.begin(), v.end(), subset);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_prev_subset_with_empty )
{
	DCS_TEST_TRACE( "Test case: Subset with Empty Set - prev_subset function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz);

	while (subset.has_next())
	{
		++subset;
	}

	while (subset.has_prev())
	{
		DCS_DEBUG_STREAM << subset << " : [size=" << subset.size() << "] : ";

		dcs::algorithm::subset_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::prev_subset(v.begin(), v.end(), subset);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_next_subset_without_empty )
{
	DCS_TEST_TRACE( "Test case: Subset without Empty Set - next_subset function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz, false);

	while (subset.has_next())
	{
		DCS_DEBUG_STREAM << subset << " : [size=" << subset.size() << "] : ";

		dcs::algorithm::subset_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::next_subset(v.begin(), v.end(), subset);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_prev_subset_without_empty )
{
	DCS_TEST_TRACE( "Test case: Subset without Empty Set - prev_subset function" );

	typedef char value_type;

	const ::std::size_t sz(4);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_subset subset(sz, false);

	while (subset.has_next())
	{
		++subset;
	}

	while (subset.has_prev())
	{
		DCS_DEBUG_STREAM << subset << " : [size=" << subset.size() << "] : ";

		dcs::algorithm::subset_traits<value_type>::subset_container subs;

		subs = dcs::algorithm::prev_subset(v.begin(), v.end(), subset);

		DCS_DEBUG_STREAM << subs << ::std::endl;
	}
}

DCS_TEST_DEF( test_k_subset_class )
{
	DCS_TEST_TRACE( "Test case: k-Subset Class" );

	typedef char value_type;

	const ::std::size_t sz(4);
	const ::std::size_t k(2);

	::std::vector<value_type> v(sz);
	for (::std::size_t i = 0; i < sz; ++i)
	{
		v[i] = 'a' + i;
	}

	dcs::algorithm::lexicographic_k_subset subset(sz, k);

	DCS_TEST_TRACE( "Test case: k-Subset - Class - increment" );

	while (subset.has_next())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		++subset;
	}

	DCS_TEST_TRACE( "Test case: k-Subset - Class - decrement" );

	while (subset.has_prev())
	{
		DCS_DEBUG_TRACE( "Subset: " << subset << " [size=" << subset.size() << "]" );

		--subset;
	}
}


int main()
{
	DCS_TEST_SUITE( "Algorithms test suite: Combinatorics functions" );

	DCS_TEST_BEGIN();
		DCS_TEST_DO(test_partition_class);
		DCS_TEST_DO(test_partition_iter);
		DCS_TEST_DO(test_next_partition);
		DCS_TEST_DO(test_prev_partition);
		DCS_TEST_DO(test_reverse_partition_class);
		DCS_TEST_DO(test_k_partition_class);
		DCS_TEST_DO(test_next_k_partition);
		DCS_TEST_DO(test_prev_k_partition);
		DCS_TEST_DO(test_subset_class_with_empty);
		DCS_TEST_DO(test_next_subset_with_empty);
		DCS_TEST_DO(test_prev_subset_with_empty);
		DCS_TEST_DO(test_subset_class_without_empty);
		DCS_TEST_DO(test_next_subset_without_empty);
		DCS_TEST_DO(test_prev_subset_without_empty);
		DCS_TEST_DO(test_k_subset_class);
	DCS_TEST_END();
}
