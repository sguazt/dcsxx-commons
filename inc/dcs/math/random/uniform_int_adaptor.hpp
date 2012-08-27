/**
 * \file dcs/math/random/uniform_int_adaptor.hpp
 *
 * \brief Adaptor for generating uniformly distributed integer random numbers
 *  from a base generator.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_MATH_RANDOM_UNIFORM_INT_ADAPTOR_HPP
#define DCS_MATH_RANDOM_UNIFORM_INT_ADAPTOR_HPP


#include <dcs/detail/config/boost.hpp>


#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost library version >= 1.15"
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <boost/random/uniform_int_distribution.hpp>
#include <dcs/assert.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_traits.hpp>
#include <dcs/type_traits/remove_reference.hpp>
#include <dcs/util/holder.hpp>
#include <limits>


namespace dcs { namespace math { namespace random {

/**
 * \brief Adaptor for generating random numbers in [0,1] from a base random
 *  number generator.
 *
 * \tparam BaseBaseRandomGeneratorT The base random number generator type.
 * \tparam RealT The result type.
 *
 * Wraps a random number generator of type \a BaseGeneratorT for generating
 * random numbers in [0,1].
 * Random numbers are generator according the algorithm provided by
 * \a BaseRandomGeneratorT.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename BaseRandomGeneratorT, typename IntT>
class uniform_int_adaptor: public base_generator<IntT>
{
	private: typedef base_generator<IntT> base_type;
    public: typedef BaseRandomGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<base_engine_type>::type::result_type input_type;
    public: typedef typename base_type::result_type result_type;
    public: typedef typename base_type::ulonglong_type ulonglong_type;
	private: typedef ::boost::random::uniform_int_distribution<result_type> adaptor_impl_type;


	/// Default constructor.
    public: explicit uniform_int_adaptor(result_type a = 0,
										 result_type b = ::std::numeric_limits<result_type>::max())
        : base_type(),
		  rng_(),
		  impl_(a, b)
    {
		// pre: a_ <= b_
		DCS_ASSERT(
			a <= b,
			::std::invalid_argument("[dcs::math::random::uniform_int_adaptor::ctor] Bad range.")
		);
    }


	/// Seed constructor.
    public: uniform_int_adaptor(input_type seed,
								result_type a,
								result_type b)
        : base_type(),
		  rng_(seed),
		  impl_(a, b)
    {
		// pre: a_ <= b_
		DCS_ASSERT(
			a <= b,
			::std::invalid_argument("[dcs::math::random::uniform_int_adaptor::ctor] Bad range.")
		);
    }


	/// Copy constructor.
    public: uniform_int_adaptor(uniform_int_adaptor const& that)
        : base_type(that),
		  rng_(that.rng_),
		  impl_(that.a_, that.b_)
    {
		// empty
    }


	/// A Constructor: copy the base generator.
	public: explicit uniform_int_adaptor(base_engine_type rng,
										 result_type a = 0,
										 result_type b = ::std::numeric_limits<result_type>::max())
		: base_type(),
		  rng_(rng),
		  impl_(a, b)
	{
		// pre: a_ <= b_
		DCS_ASSERT(
			a <= b,
			::std::invalid_argument("[dcs::math::random::uniform_int_adaptor::ctor] Bad range.")
		);
	}


// Support of reference-to-refernce qualifier is only available from C++0x.
#if __cplusplus > 201103L

	/// A constructor: move the base generator.
    //public: uniform_int_adaptor(base_engine_type&& rng)
    public: explicit uniform_int_adaptor(base_engine_type& rng,
										 result_type a = 0,
										 result_type b = ::std::numeric_limits<result_type>::max())
        : base_type(),
		  rng_(rng),
		  impl_(a, b)
    {
		// pre: a_ <= b_
		DCS_ASSERT(
			a <= b,
			::std::invalid_argument("[dcs::math::random::uniform_int_adaptor::ctor] Bad range.")
		);
    }

#else

	/// A constructor: move the base generator.
    public: explicit uniform_int_adaptor(::dcs::util::holder<base_engine_type>& rng,
										 result_type a = 0,
										 result_type b = ::std::numeric_limits<result_type>::max())
        : base_type(),
		  rng_(rng),
		  impl_(a, b)
    {
		// pre: a_ <= b_
		DCS_ASSERT(
			a <= b,
			::std::invalid_argument("[dcs::math::random::uniform_int_adaptor::ctor] Bad range.")
		);
    }

#endif


	public: const base_engine_type base() const
	{
		return rng_;
	}


    private: result_type do_generate()
    {
		return impl_(rng_);
    }


	private: void do_seed()
	{
		this->rng_.seed();
	}


	private: void do_seed(result_type s)
	{
		rng_.seed(s);
		//generator_traits<base_engine_type>::seed(rng_, s);
	}


	private: void do_discard(ulonglong_type z)
	{
		while (z--)
		{
			rng_();
		}
	}


	private: result_type do_min() const
	{
		return impl_.min();
	}


	private: result_type do_max() const
	{
		return impl_.max();
	}


	private: base_engine_type rng_;
	private: adaptor_impl_type impl_;
};


// Template specialization for avoid auto-wrapping (i.e., when the base
// generator is itself a uniform_int_adaptor)
template <typename RandomNumberGeneratorT, typename IntT>
class uniform_int_adaptor< uniform_int_adaptor<RandomNumberGeneratorT,IntT>, IntT >: public uniform_int_adaptor<RandomNumberGeneratorT,IntT>
{
    public: typedef RandomNumberGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<RandomNumberGeneratorT>::type::result_type input_type;
    public: typedef IntT result_type;
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_UNIFORM_INT_ADAPTOR_HPP
