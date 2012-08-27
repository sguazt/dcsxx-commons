/**
 * \file dcs/math/random/any_variate_generator.hpp
 *
 * \brief Generic (type-erased) random variate generators.
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
