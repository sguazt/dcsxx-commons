/**
 * \file dcs/math/random/utility.hpp
 *
 * \brief Make a new random number generator object by wrapping the given
 *  random number generator into the \c base_generator hierarchy.
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

#ifndef DCS_MATH_RANDOM_UTILITY_HPP
#define DCS_MATH_RANDOM_UTILITY_HPP


#include <boost/smart_ptr.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_adaptor.hpp>


namespace dcs { namespace math { namespace random {

/**
 * \brief Make a new random number generator object by wrapping the given
 *  random number generator into the \c base_generator hierarchy.
 */
template <typename GeneratorT>
::boost::shared_ptr<base_generator> make_generator(GeneratorT const& rng)
{
	return ::boost::shared_ptr(new generator_adaptor<GeneratorT>(rng));
}

}}}

#endif // DCS_MATH_RANDOM_UTILITY_HPP
