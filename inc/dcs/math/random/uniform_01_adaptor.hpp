/**
 * \file dcs/math/random/uniform_01_adaptor.hpp
 *
 * \brief Adaptor for generating random numbers in [0,1] from a base generator.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2009 Marco Guazzone (marco.guazzone@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DCS_MATH_RANDOM_UNIFORM_01_ADAPTOR_HPP
#define DCS_MATH_RANDOM_UNIFORM_01_ADAPTOR_HPP


#include <dcs/detail/config/boost.hpp>


#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost library version >= 1.15"
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <boost/random/uniform_01.hpp>
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename BaseRandomGeneratorT, typename RealT>
class uniform_01_adaptor: public base_generator<RealT>
{
	private: typedef base_generator<RealT> base_type;
    public: typedef BaseRandomGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<BaseRandomGeneratorT>::type::result_type input_type;
    public: typedef typename base_type::result_type result_type;
    public: typedef typename base_type::ulonglong_type ulonglong_type;
	private: typedef ::boost::random::uniform_01<result_type> adaptor_impl_type;


	/// Default constructor.
    public: uniform_01_adaptor()
        : base_type(),
		  rng_(),
		  impl_()
    {
		// empty
    }


	/// Seed constructor.
    public: uniform_01_adaptor(input_type seed)
        : base_type(),
		  rng_(seed),
		  impl_()
    {
		// empty
    }


	/// Copy constructor.
    public: uniform_01_adaptor(uniform_01_adaptor const& that)
        : base_type(that),
		  rng_(that.rng_),
		  impl_(that.impl_)
    {
		// empty
    }


	/// A Constructor: copy the base generator.
	public: uniform_01_adaptor(base_engine_type rng)
		: base_type(),
		  rng_(rng),
		  impl_()
	{
		// empty
	}


// Support of reference-to-refernce qualifier is only available from C++0x.
#if __cplusplus > 201103L

	/// A constructor: move the base generator.
    //public: uniform_01_adaptor(base_engine_type&& rng)
    public: uniform_01_adaptor(base_engine_type& rng)
        : base_type(),
		  rng_(rng),
		  impl_()
    {
		// empty
    }

#else

	/// A constructor: move the base generator.
    public: uniform_01_adaptor(::dcs::util::holder<base_engine_type>& rng)
        : base_type(),
		  rng_(rng),
		  impl_()
    {
		// empty
    }

#endif


	public: const base_engine_type base() const
	{
		return rng_;
	}


    private: result_type do_generate()
    {
//		result_type factor;
//		result_type result;
//
//		do
//		{
//			factor = result_type(1)
//					 / (
//							static_cast<result_type>(
//							(rng_.max)()-(rng_.min)()
//						)
//						+ static_cast<result_type>(
//							::std::numeric_limits<input_type>::is_integer
//							? 1
//							: 0
//						)
//			);
//			result = static_cast<result_type>(rng_()-(rng_.min)()) * factor;
//		}
//		while (result >= result_type(1));
//
//		return result;

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
		return result_type(0);
	}


	private: result_type do_max() const
	{
		return result_type(1);
	}


	private: base_engine_type rng_;
	private: adaptor_impl_type impl_;
};


// Template specialization for avoid auto-wrapping (i.e., when the base
// generator is itself a uniform_01_adaptor)
template <typename RandomNumberGeneratorT, typename RealT>
class uniform_01_adaptor< uniform_01_adaptor<RandomNumberGeneratorT,RealT>, RealT >: public uniform_01_adaptor<RandomNumberGeneratorT,RealT>
{
    public: typedef RandomNumberGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<RandomNumberGeneratorT>::type::result_type input_type;
    public: typedef RealT result_type;
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_UNIFORM_01_ADAPTOR_HPP
