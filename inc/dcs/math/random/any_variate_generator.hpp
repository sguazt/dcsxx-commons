/**
 * \file dcs/math/random/any_variate_generator.hpp
 *
 * \brief Generic (type-erased) random variate generators.
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

#ifndef DCS_MATH_RANDOM_ANY_VARIATE_GENERATOR_HPP
#define DCS_MATH_RANDOM_ANY_VARIATE_GENERATOR_HPP


#include <boost/smart_ptr.hpp>
#include <dcs/debug.hpp>
#include <dcs/type_traits/add_reference.hpp>
#include <dcs/type_traits/remove_reference.hpp>


namespace dcs { namespace math { namespace random {

namespace detail {

template <typename ResultT>
struct concept_variate_generator
{
	typedef ResultT result_type;
	virtual result_type operator()() = 0;
	virtual result_type min() const = 0;
	virtual result_type max() const = 0;
};


template <typename VariateGeneratorT>
class model_variate_generator: public concept_variate_generator<typename ::dcs::type_traits::remove_reference<VariateGeneratorT>::type::result_type>
{
	private: typedef GeneratorT generator_type;
	private: typedef typename ::dcs::type_traits::remove_reference<generator_type>::type value_generator_type;
	public: typedef typename ::dcs::type_traits::add_reference<generator_type>::type ref_generator_type;
	public: typedef typename value_generator_type::result_type result_type;


//	public: model_variate_generator(GeneratorT const& rng)
//		: rng_(rng)
//	{
//	}


	public: model_variate_generator(ref_generator_type rng)
		: rng_(rng)
	{
		// empty
	}


	public: result_type operator()()
	{
		return rng_();
	}


	public: result_type min() const
	{
		return rng_.min();
	}


	public: result_type max() const
	{
		return rng_.max();
	}


	private: ref_generator_type rng_;
};

} // Namespace detail


/**
 * \brief Generic (type-erased) random variate generators.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ResultT>
class any_variate_generator
{
	public: typedef ResultT result_type;

	public: template <typename GeneratorT>
		any_variate_generator(GeneratorT& rng)
		: ptr_rng_(new detail::model_variate_generator<GeneratorT>(rng))
	{
		// empty
	}


	public: result_type operator()()
	{
		return (*ptr_rng_)();
	}


	public: result_type min() const
	{
		return ptr_rng_.min();
	}


	public: result_type max() const
	{
		return ptr_rng_.max();
	}


	private: ::boost::weak_ptr< detail::concept_variate_generator<result_type> > ptr_rng_;
};


template <typename GeneratorT>
any_variate_generator<typename GeneratorT::result_type> make_any_variate_generator(GeneratorT& rng)
{
	return any_variate_generator<typename GeneratorT::result_type>(rng);
}

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_ANY_VARIATE_GENERATOR_HPP
