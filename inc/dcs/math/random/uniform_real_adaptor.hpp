/**
 * \file dcs/math/random/uniform_real_adaptor.hpp
 *
 * \brief Adaptor for generating random numbers in [0,1] from a base generator.
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

#ifndef DCS_MATH_RANDOM_UNIFORM_REAL_ADAPTOR_HPP
#define DCS_MATH_RANDOM_UNIFORM_REAL_ADAPTOR_HPP


#include <dcs/detail/config/boost.hpp>


#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost library version >= 1.15"
#endif // DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION


#include <boost/random/uniform_real_distribution.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/type_traits/remove_reference.hpp>
#include <dcs/util/holder.hpp>
#include <limits>


namespace dcs { namespace math { namespace random {

/**
 * \brief Adaptor for generating random numbers uniformly distributed in a real
 *  interval from a base random number generator.
 *
 * \tparam BaseRandomGeneratorT The base random number generator type.
 * \tparam RealT The result type.
 *
 * Wraps a random number generator of type \a BaseGeneratorT for generating
 * random numbers uniformly distributed in real interval.
 * Random numbers are generated according the algorithm provided by
 * \a BaseRandomGeneratorT.
 *
 * \todo Make it a derived class of base_generator.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename BaseRandomGeneratorT, typename RealT>
class uniform_real_adaptor: public base_generator<RealT>
{
	private: typedef base_generator<RealT> base_type;
    public: typedef BaseRandomGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<BaseRandomGeneratorT>::type::result_type input_type;
    public: typedef typename base_type::result_type result_type;
    public: typedef typename base_type::ulonglong_type ulonglong_type;
    private: typedef ::boost::random::uniform_real_distribution<result_type> adaptor_impl_type;


    public: explicit uniform_real_adaptor(result_type min_arg = 0.0, result_type max_arg = 1.0)
        : base_type(),
		  rng_(),
		  impl_(min_arg, max_arg)
//		  min_(min_arg),
//		  max_(max_arg)
    {
		// empty
    }


	/// Seed constructor.
    public: uniform_real_adaptor(input_type seed, result_type min_arg, result_type max_arg)
        : base_type(),
		  rng_(seed),
		  impl_(min_arg, max_arg)
//		  min_(min_arg),
//		  max_(max_arg)
    {
		// empty
    }


	/// Seed constructor.
    public: uniform_real_adaptor(input_type seed)
        : base_type(),
		  rng_(seed),
		  impl_()
    {
//		min_ = static_cast<result_type>((rng_.min)());
//		max_ = static_cast<result_type>((rng_.max)());
    }


	/// Copy constructor.
    public: uniform_real_adaptor(uniform_real_adaptor const& that)
        : base_type(that),
		  rng_(that.rng_),
		  impl_(that.impl_)
//		  min_(that.min_),
//		  max_(that.max_)
    {
		// empty
    }


	/// A Constructor: copy the base generator.
	public: uniform_real_adaptor(base_engine_type rng, result_type min_arg, result_type max_arg)
		: base_type(),
		  rng_(rng),
		  impl_(min_arg, max_arg)
//		  min_(min_arg),
//		  max_(max_arg)
	{
		// empty
	}


	/// A Constructor: copy the base generator.
	public: uniform_real_adaptor(base_engine_type rng)
		: base_type(),
		  rng_(rng),
		  impl_()
//		  min_((rng.min)()),
//		  max_((rng.max)())
	{
		// empty
	}


// Support of reference-to-refernce qualifier is only available from C++0x.
#if __cplusplus >= 201103L

	/// A constructor: move the base generator.
    //public: uniform_real_adaptor(base_engine_type&& rng)
    public: uniform_real_adaptor(base_engine_type& rng, result_type min_arg, result_type max_arg)
        : base_type(),
		  rng_(rng),
		  impl_(min_arg, max_arg)
//		  min_(min_arg),
//		  max_(max_arg)
    {
		// empty
    }


	/// A constructor: move the base generator.
    //public: uniform_real_adaptor(base_engine_type&& rng)
    public: uniform_real_adaptor(base_engine_type& rng)
        : base_type(),
		  rng_(rng),
		  impl_()
//		  min_((rng.min)()),
//		  max_((rng.max)())
    {
		// empty
    }

#else

	/// A constructor: move the base generator.
    public: uniform_real_adaptor(::dcs::util::holder<base_engine_type>& rng, result_type min_arg, result_type max_arg)
        : base_type(),
		  rng_(rng),
		  impl_(min_arg, max_arg)
//		  min_(min_arg),
//		  max_(max_arg)
    {
		// empty
    }


	/// A constructor: move the base generator.
    public: uniform_real_adaptor(::dcs::util::holder<base_engine_type>& rng)
        : base_type(),
		  rng_(rng),
		  impl_()
//		  min_((rng.min)()),
//		  max_((rng.max)())
    {
		// empty
    }

#endif

	public: base_engine_type base() const
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
//			factor = (max_-min_)
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
//			result = static_cast<result_type>(rng_()-(rng_.min)()) * factor + min_;
//		}
//		while (result >= max_);
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
// generator is itself a uniform_real_adaptor)
template <typename RandomNumberGeneratorT, typename RealT>
class uniform_real_adaptor< uniform_real_adaptor<RandomNumberGeneratorT,RealT>, RealT >: public uniform_real_adaptor<RandomNumberGeneratorT,RealT>
{
    public: typedef RandomNumberGeneratorT base_engine_type;
    public: typedef typename ::dcs::type_traits::remove_reference<RandomNumberGeneratorT>::type::result_type input_type;
    public: typedef RealT result_type;
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_UNIFORM_REAL_ADAPTOR_HPP
