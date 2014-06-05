/**
 * \file dcs/math/random/generator_adaptor.hpp
 *
 * \brief Adapt a given class to the generator_adaptor interface.
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

#ifndef DCS_MATH_RANDOM_GENERATOR_ADAPTOR_HPP
#define DCS_MATH_RANDOM_GENERATOR_ADAPTOR_HPP


#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_traits.hpp>
#include <dcs/type_traits/add_const.hpp>
#include <dcs/type_traits/add_reference.hpp>


namespace dcs { namespace math { namespace random {

/**
 * \brief Adaptor for the base_generator interface.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <
	typename GeneratorT,
	typename GeneratorTraitsT=generator_traits<GeneratorT>
>
class generator_adaptor: public base_generator<typename GeneratorTraitsT::result_type>
{
	private: typedef base_generator<typename GeneratorTraitsT::result_type> base_type;
	public: typedef GeneratorT adaptee_type;
	public: typedef GeneratorTraitsT generator_traits_type;
	public: typedef typename generator_traits_type::result_type result_type;
//	public: typedef typename ::dcs::type_traits::add_reference<GeneratorT>::type adaptee_reference;
//	public: typedef typename ::dcs::type_traits::add_reference<
//						typename ::dcs::type_traits::add_const<GeneratorT>::type
//					>::type adaptee_const_reference;
	public: typedef typename base_type::ulonglong_type ulonglong_type;


	public: generator_adaptor()
		: adaptee_()
	{
		// Empty
	}


//	public: generator_adaptor(adaptee_const_reference gen)
//		: adaptee_(gen)
//	{
//		// Empty
//	}


	public: explicit generator_adaptor(result_type seed)
		: adaptee_(seed)
	{
		// Empty
	}


	public: explicit generator_adaptor(adaptee_type gen)
		: adaptee_(gen)
	{
		// Empty
	}


	private: result_type do_generate()
	{
		return generator_traits_type::generate(adaptee_);
	}


//	public: static result_type min()
//	{
//		return generator_traits_type::min();
//	}


//	public: static result_type max()
//	{
//		return generator_traits_type::max();
//	}


	private: result_type do_min() const
	{
		return generator_traits_type::min(adaptee_);
	}


	private: result_type do_max() const
	{
		return generator_traits_type::max(adaptee_);
	}


	private: void do_seed()
	{
		generator_traits_type::seed(adaptee_);
	}


	private: void do_seed(result_type s)
	{
		generator_traits_type::seed(adaptee_, s);
	}


	private: void do_discard(ulonglong_type z)
	{
		generator_traits_type::discard(adaptee_, z);
	}


	public: friend bool operator==(generator_adaptor const& g1, generator_adaptor const& g2)
	{
		return g1.adaptee_ == g2.adaptee_;
	}


	public: friend bool operator!=(generator_adaptor const& g1, generator_adaptor const& g2)
	{
		return !(g1 == g2);
	}


	private: adaptee_type adaptee_;
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_GENERATOR_ADAPTOR_HPP
