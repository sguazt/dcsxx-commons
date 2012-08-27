/**
 * \file dcs/math/random/generator_adaptor.hpp
 *
 * \brief Adapt a given class to the generator_adaptor interface.
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
