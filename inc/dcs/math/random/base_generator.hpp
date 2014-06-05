/**
 * \file dcs/math/random/base_generator.hpp
 *
 * \brief Base random number generator.
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

#ifndef DCS_MATH_RANDOM_BASE_GENERATOR_HPP
#define DCS_MATH_RANDOM_BASE_GENERATOR_HPP


#include <boost/cstdint.hpp>


namespace dcs { namespace math { namespace random {

/**
 * \brief Interface for the \c RandomNumberEngine concept.
 *
 * \tparam ResultT The type of randomly generated numbers.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ResultT>
class base_generator
{
	public: typedef ResultT result_type;
	public: typedef ::boost::ulong_long_type ulonglong_type;


	public: virtual ~base_generator() { }


	public: result_type operator()()
	{
		return do_generate();
	}


//	public: static result_type min() ;


//	public: static result_type max();


	public: result_type min() const
	{
		return do_min();
	}


	public: result_type max() const
	{
		return do_max();
	}


	public: void seed()
	{
		this->do_seed();
	}


	public: void seed(result_type s)
	{
		do_seed(s);
	}


	public: void discard(ulonglong_type z)
	{
		do_discard(z);
	}


	private: virtual result_type do_generate() = 0;

	private: virtual result_type do_min() const = 0;

	private: virtual result_type do_max() const = 0;

	private: virtual void do_seed() = 0;

	private: virtual void do_seed(result_type s) = 0;

	private: virtual void do_discard(ulonglong_type z) = 0;
};

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_BASE_GENERATOR_HPP
