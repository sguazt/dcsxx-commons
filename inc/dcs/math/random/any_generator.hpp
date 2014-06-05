/**
 * \file dcs/math/random/any_generator.hpp
 *
 * \brief Generic random number generator.
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

#ifndef DCS_MATH_RANDOM_ANY_GENERATOR_HPP
#define DCS_MATH_RANDOM_ANY_GENERATOR_HPP


#include <boost/smart_ptr.hpp>
//#include <dcs/debug.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_adaptor.hpp>
#include <dcs/math/random/generator_traits.hpp>
//#include <dcs/type_traits/add_reference.hpp>
//#include <dcs/type_traits/reference.hpp>
#include <dcs/type_traits/remove_reference.hpp>
#include <dcs/util/holder.hpp>


namespace dcs { namespace math { namespace random {

/**
 * \brief Generic random number generator.
 * \tparam ResultT The type of randomly generated numbers.
 *
 * This class is useful when one does not know at compile-time the type of
 * the random number generator that is to be used or when one needs to create
 * a container of non-homogeneous randon number generators.
 * Thus, this class realizes a runtime version of the \c RandomNumberGenerator
 * concept; this is accomplished by using the <em>type-erasure</em> technique,
 * which adds a one more level of indirection.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ResultT>
class any_generator
{
	public: typedef ResultT result_type;


	// Default constructor (useful when any_generator is used as a member data).
	public: any_generator()
	{
		// empty
	}


	public: template <typename GeneratorT>
		any_generator(GeneratorT const& rng)
		: ptr_rng_(new generator_adaptor<GeneratorT>(rng))
	{
		// empty
	}


	public: template <typename GeneratorT>
		any_generator(::dcs::util::holder<GeneratorT> const& wrap_rng)
		: ptr_rng_(new generator_adaptor<GeneratorT>(wrap_rng.get()))
	{
		// empty
	}


	// Compiler-generator copy-constructor and assignment are fine


	public: template <typename GeneratorT>
		void generator(GeneratorT const& rng)
	{
		ptr_rng_ = new generator_adaptor<GeneratorT>(rng);
	}


	//@{ RandomNumberEngine concept implementation

	public: result_type operator()()
	{
		return (*ptr_rng_)();
	}


	public: result_type min() const
	{
		return ptr_rng_->min();
	}


	public: result_type max() const
	{
		return ptr_rng_->max();
	}

	public: void seed()
	{
		ptr_rng_->seed();
	}

	public: void seed(result_type s)
	{
		ptr_rng_->seed(s);
	}

	public: void discard(unsigned long z)
	{
		ptr_rng_->discard(z);
	}

	//@} RandomNumberEngine concept implementation


	private: ::boost::shared_ptr< base_generator<result_type> > ptr_rng_; // shared_ptr needed in order to keep alive the pointer during object copying
};


template <
	typename GeneratorT,
	typename GeneratorTraitsT = generator_traits<typename ::dcs::type_traits::remove_reference<GeneratorT>::type >
>
struct make_any_generator_type
{
	typedef any_generator<typename GeneratorTraitsT::result_type> type;
};


namespace detail {

//template <
//	typename GeneratorT,
//	typename GeneratorTraitsT = generator_traits<GeneratorT>
//>
//struct make_any_generator_impl;


template <
	typename GeneratorT,
	typename GeneratorTraitsT = generator_traits<GeneratorT>
>
struct make_any_generator_impl
{
	typedef typename make_any_generator_type<GeneratorT,GeneratorTraitsT>::type any_generator_type;

	static any_generator_type apply(GeneratorT& rng)
	{
		//return any_generator<typename GeneratorT::result_type>(rng);
		return any_generator_type(rng);
	}
};


template <typename GeneratorT, typename GeneratorTraitsT>
struct make_any_generator_impl<GeneratorT&,GeneratorTraitsT>
{
	typedef typename make_any_generator_type<GeneratorT,GeneratorTraitsT>::type any_generator_type;

	static any_generator_type apply(GeneratorT& rng)
	{
		::dcs::util::holder<GeneratorT&> wrap_generator(rng);
		return any_generator_type(wrap_generator);
	}
};

} // Namespace detail


template <typename GeneratorT>
typename make_any_generator_type<GeneratorT>::type make_any_generator(GeneratorT rng)
{
	return detail::make_any_generator_impl<GeneratorT>::apply(rng);
}

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_ANY_GENERATOR_HPP
