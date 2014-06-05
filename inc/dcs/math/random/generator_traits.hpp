/**
 * \file dcs/math/random/generator_traits.hpp
 *
 * \brief Traits type for random number generators.
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

#ifndef DCS_MATH_RANDOM_GENERATOR_TRAITS_HPP
#define DCS_MATH_RANDOM_GENERATOR_TRAITS_HPP


#include <dcs/type_traits/remove_const.hpp>
#include <dcs/type_traits/remove_reference.hpp>


namespace dcs { namespace math { namespace random {

template <typename GeneratorT>
struct generator_traits
{
	//typedef GeneratorT generator_type;
	typedef typename ::dcs::type_traits::remove_reference<typename ::dcs::type_traits::remove_const<GeneratorT>::type>::type generator_type;
	typedef typename generator_type::result_type result_type;


	static result_type generate(generator_type& rng)
	{
		return rng();
	}


//	static result_type min()
//	{
//		return generator_type::min();
//	}


//	static result_type max()
//	{
//		return generator_type::max();
//	}


	static result_type min(generator_type const& rng)
	{
		return rng.min();
	}


	static result_type max(generator_type const& rng)
	{
		return rng.max();
	}


	static void seed(generator_type& rng)
	{
		rng.seed();
	}


	static void seed(generator_type& rng, result_type s)
	{
		rng.seed(s);
	}


	static void discard(generator_type& rng, unsigned long z)
	{
		rng.discard(z);
	}
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_GENERATOR_TRAITS_HPP
