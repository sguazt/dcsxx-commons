/**
 * \file dcs/math/stats/distribution/base_distribution.hpp
 *
 * \brief Base class for probability distributions.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_BASE_DISTRIBUTION_HPP
#define DCS_MATH_STATS_DISTRIBUTION_BASE_DISTRIBUTION_HPP


#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>
//#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
//#include <iosfwd>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Interface for the \c ProbabilityDistribution concept.
 *
 * \tparam ValueT The type used for real numbers.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename ValueT>
class base_distribution
{
	public: typedef ValueT value_type;
	public: typedef value_type support_type;


	public: virtual ~base_distribution() { }


//	public: template <typename UniformRandomGeneratorT>
//		typename ::boost::disable_if<
//			::boost::is_base_of< ::dcs::math::random::base_generator<typename UniformRandomGeneratorT::result_type>, UniformRandomGeneratorT>,
//			support_type
//		>::type rand(UniformRandomGeneratorT& rng) const
//	{
//		::dcs::math::random::any_generator<value_type> any_rng;
//
//		any_rng = ::dcs::math::random::make_any_generator<UniformRandomGeneratorT&>(rng);
//
//		return do_rand(any_rng);
//	}


	public: template <typename UniformRandomGeneratorT>
		support_type rand(UniformRandomGeneratorT& rng) const
	{
		typedef UniformRandomGeneratorT base_generator_type;
		typedef ::dcs::math::random::uniform_01_adaptor<base_generator_type&, value_type> adapted_generator_type;
		//::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type> u01_rng = ::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type>(rng)
		adapted_generator_type u01_rng(rng);

		return do_rand(u01_rng);
	}


	public: support_type rand(::dcs::math::random::base_generator<value_type>& rng) const
	{
		return do_rand(rng);
	}


//	public: void print(::std::ostream& os) const
//	{
//		do_print(os);
//	}


	private: virtual support_type do_rand(::dcs::math::random::base_generator<value_type>& rng) const = 0;


//	private: virtual support_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const = 0;


//	private: virtual ::std::ostream& do_print(::std::ostream& os) const
//	{
//		return os;
//	}


//	friend template <
//				typename CharT,
//				typename CharTraitsT
//			>
//		::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, base_distribution const& distr)
//	{
//		return distr.do_print(os);
//	}
};


//template <
//	typename CharT,
//	typename CharTraitsT,
//	typename ValueT
//>
//::std::basic_ostream<CharT,CharTraitsT>& operator<<(::std::basic_ostream<CharT,CharTraitsT>& os, base_distribution<ValueT> const& dist)
//{
//	return dist.print(os);
//}


}}} // Namaespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_BASE_DISTRIBUTION_HPP
