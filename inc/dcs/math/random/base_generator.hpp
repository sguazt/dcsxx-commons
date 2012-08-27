/**
 * \file dcs/math/random/base_generator.hpp
 *
 * \brief Base random number generator.
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

#ifndef DCS_MATH_RANDOM_BASE_GENERATOR_HPP
#define DCS_MATH_RANDOM_BASE_GENERATOR_HPP


#include <boost/cstdint.hpp>


namespace dcs { namespace math { namespace random {

/**
 * \brief Interface for the \c RandomNumberEngine concept.
 *
 * \tparam ResultT The type of randomly generated numbers.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
