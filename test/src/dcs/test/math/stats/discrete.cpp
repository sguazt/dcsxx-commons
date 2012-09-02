#include <algorithm>
#include <cmath>
#include <cstddef>
#include <dcs/debug.hpp>
#include <dcs/functional/bind.hpp>
//#include <dcs/iterator/any_forward_iterator.hpp>
#include <dcs/iterator/counting_iterator.hpp>
//#include <dcs/iterator/iterator_range.hpp>
#include <dcs/math/function/sum.hpp>
#include <dcs/math/random/mersenne_twister.hpp>
#include <dcs/math/stats/function/cdf.hpp>
#include <dcs/math/stats/function/pdf.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <dcs/math/stats/distribution/discrete.hpp>
#include <dcs/test.hpp>
#include <functional>
#include <string>


static const double tol = 1e-5;

static const unsigned long seed = 5698u;


namespace detail {

template <typename T>
struct close_to: std::binary_function<T,T,bool>
{
	bool operator()(T const& x, T const& y, T const& tol) const
	{
		return std::abs(x-y) <= tol;
	}
};

} // Namespace detail


//DCS_TEST_DEF( test_discrete_get_probs_range )
//{
//	DCS_DEBUG_TRACE( "TEST discrete distribution -- probabilities getter" );
//
//	typedef double real_type;
//	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;
//
//	std::vector<std::string> events;
//	events.push_back("apple");
//	events.push_back("pear");
//	events.push_back("peach");
//	events.push_back("banana");
//
//	std::vector<real_type> freqs;
//	freqs.push_back(0.5);
//	freqs.push_back(0.2);
//	freqs.push_back(0.8);
//	freqs.push_back(0.6);
//
//	distribution_type dist(freqs.begin(), freqs.end());
//	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());
//
//	dcs::iterator::iterator_range< dcs::iterator::any_forward_iterator<real_type> > probs_range = dist.probabilities();
//
//	std::size_t i = 0;
//	for (
//		dcs::iterator::any_forward_iterator<real_type> it = probs_range.begin();
//		it != probs_range.end();
//		++it, ++i
//	) {
//		DCS_DEBUG_TRACE("P(X==" << events[i] << ")=" << *it << " ==> " << (freqs[i]/freqs_sum));
//		DCS_TEST_CHECK_CLOSE(*it, freqs[i]/freqs_sum, tol);
//	}
//}


DCS_TEST_DEF( test_discrete_get_probs_vector )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- probabilities getter" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.5);
	freqs.push_back(0.2);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());
	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());

		std::vector<real_type> probs = dist.probabilities();

		std::size_t i = 0;
		for (
			std::vector<real_type>::const_iterator it = probs.begin();
			it != probs.end();
			++it, ++i
		) {
			DCS_DEBUG_TRACE("P(X==" << events[i] << ")=" << *it << " ==> " << (freqs[i]/freqs_sum));
			DCS_TEST_CHECK_CLOSE(*it, freqs[i]/freqs_sum, tol);
		}
}


DCS_TEST_DEF( test_discrete_pdf )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- PDF" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.5);
	freqs.push_back(0.2);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());
	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());

	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		DCS_DEBUG_TRACE("P(X==" << events[i] << ")=" << dist.pdf(i) << " ==> " << (freqs[i]/freqs_sum));
		DCS_TEST_CHECK_CLOSE(dist.pdf(i), freqs[i]/freqs_sum, tol);
	}
}


DCS_TEST_DEF( test_discrete_pdf_free )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- PDF -- free function" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.5);
	freqs.push_back(0.2);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());
	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());

	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		DCS_DEBUG_TRACE("P(X==" << events[i] << ")=" << dcs::math::stats::pdf(dist, i) << " ==> " << (freqs[i]/freqs_sum));
	DCS_TEST_CHECK_CLOSE(dcs::math::stats::pdf(dist, i), freqs[i]/freqs_sum, tol);
	}
}


DCS_TEST_DEF( test_discrete_cdf )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- CDF" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.5);
	freqs.push_back(0.2);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());
	std::vector<real_type> cum_freqs;
	cum_freqs.push_back(0.5);
	cum_freqs.push_back(0.7);
	cum_freqs.push_back(1.5);
	cum_freqs.push_back(2.1);

	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());

	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		DCS_DEBUG_TRACE("P(X<=" << events[i] << ")=" << dist.cdf(i) << " ==> " << (cum_freqs[i]/freqs_sum));
		DCS_TEST_CHECK_CLOSE(dist.cdf(i), cum_freqs[i]/freqs_sum, tol);
	}
}


DCS_TEST_DEF( test_discrete_cdf_free )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- CDF -- free function" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.5);
	freqs.push_back(0.2);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());
	std::vector<real_type> cum_freqs;
	cum_freqs.push_back(0.5);
	cum_freqs.push_back(0.7);
	cum_freqs.push_back(1.5);
	cum_freqs.push_back(2.1);

	real_type freqs_sum = dcs::math::sum<real_type>(freqs.begin(), freqs.end());

	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		DCS_DEBUG_TRACE("P(X<=" << events[i] << ")=" << dcs::math::stats::cdf(dist, i) << " ==> " << (cum_freqs[i]/freqs_sum));
		DCS_TEST_CHECK_CLOSE(dcs::math::stats::cdf(dist, i), cum_freqs[i]/freqs_sum, tol);
	}
}


DCS_TEST_DEF( test_discrete_rand )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- RAND" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	engine_type rng(seed);

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.2);
	freqs.push_back(0.5);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());


	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		real_type x = dist.rand(rng);

		DCS_DEBUG_TRACE("rand=" << x);
		DCS_TEST_CHECK(
			dcs::iterator::counting_iterator<std::size_t>(events.size())
			!=
			std::find_if(
				dcs::iterator::counting_iterator<std::size_t>(0),
				dcs::iterator::counting_iterator<std::size_t>(events.size()),
				dcs::functional::bind(
					detail::close_to<real_type>(),
					dcs::functional::placeholders::_1,
					x,
					tol
				)
			)
		);
	}
}


DCS_TEST_DEF( test_discrete_rand_free )
{
	DCS_DEBUG_TRACE( "TEST discrete distribution -- RAND -- free function" );

	typedef std::size_t int_type;
	typedef double real_type;
	typedef dcs::math::random::mt11213b engine_type;
	typedef dcs::math::stats::discrete_distribution<real_type> distribution_type;

	engine_type rng(seed);

	std::vector<std::string> events;
	events.push_back("apple");
	events.push_back("pear");
	events.push_back("peach");
	events.push_back("banana");

	std::vector<real_type> freqs;
	freqs.push_back(0.2);
	freqs.push_back(0.5);
	freqs.push_back(0.8);
	freqs.push_back(0.6);

	distribution_type dist(freqs.begin(), freqs.end());


	for (
		std::size_t i = 0;
		i < events.size();
		++i
	) {
		real_type x = dcs::math::stats::rand(dist, rng);

		DCS_DEBUG_TRACE("rand=" << x);
		DCS_TEST_CHECK(
			dcs::iterator::counting_iterator<std::size_t>(events.size())
			!=
			std::find_if(
				dcs::iterator::counting_iterator<std::size_t>(0),
				dcs::iterator::counting_iterator<std::size_t>(events.size()),
				dcs::functional::bind(
					detail::close_to<real_type>(),
					dcs::functional::placeholders::_1,
					x,
					tol
				)
			)
		);
	}
}


int main()
{
	DCS_TEST_SUITE( "Empirical discrete probability distribution" );

	DCS_TEST_BEGIN();

	DCS_TEST_DO(test_discrete_get_probs_vector);
	//DCS_TEST_DO(test_discrete_get_probs_range);
	DCS_TEST_DO(test_discrete_pdf);
	DCS_TEST_DO(test_discrete_pdf_free);
	DCS_TEST_DO(test_discrete_cdf);
	DCS_TEST_DO(test_discrete_cdf_free);
	DCS_TEST_DO(test_discrete_rand);
	DCS_TEST_DO(test_discrete_rand_free);

	DCS_TEST_END();
}
