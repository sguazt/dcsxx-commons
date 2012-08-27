/**
 * \file dcs/math/random/generator_traits.hpp
 *
 * \brief Traits type for random number generators.
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
