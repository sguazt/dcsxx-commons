/**
 * \file dcs/math/random/utility.hpp
 *
 * \brief Make a new random number generator object by wrapping the given
 *  random number generator into the \c base_generator hierarchy.
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
