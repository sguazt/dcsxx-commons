/**
 * \file dcs/math/stats/distribution/distribution_adaptor.hpp
 *
 * \brief Adapt a given class to the base_distribution interface.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_ADAPTOR_HPP
#define DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_ADAPTOR_HPP


#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/stats/distribution/base_distribution.hpp>
#include <dcs/math/stats/distribution/distribution_traits.hpp>
#include <dcs/math/stats/function/rand.hpp>
#include <dcs/type_traits/add_const.hpp>
#include <dcs/type_traits/add_reference.hpp>
//#include <iosfwd>


namespace dcs { namespace math { namespace stats {

template <
	typename DistributionT,
	//typename DistributionTraitsT=::dcs::type_traits::remove_reference<DistributionT>::type
	typename DistributionTraitsT=distribution_traits<DistributionT>
>
class distribution_adaptor: public base_distribution<typename DistributionTraitsT::value_type>
{
	public: typedef DistributionT adaptee_type;
	public: typedef typename DistributionTraitsT::value_type value_type;
	public: typedef typename ::dcs::type_traits::add_reference<DistributionT>::type adaptee_reference;
	public: typedef typename ::dcs::type_traits::add_reference<
								typename ::dcs::type_traits::add_const<DistributionT>::type
							>::type adaptee_const_reference;


	public: distribution_adaptor(adaptee_const_reference dist)
		: adaptee_(dist)
	{
		// Empty
	}


//	private: value_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const
//	{
//		return ::dcs::math::stats::rand(adaptee_, rng);
//	}


	private: value_type do_rand(::dcs::math::random::base_generator<value_type>& rng) const
	{
		return ::dcs::math::stats::rand(adaptee_, rng);
	}


//	private: ::std::ostream& do_print(::std::ostream& os) const
//	{
//		return os << adaptee_;
//	}


	private: adaptee_type adaptee_;
};

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_ADAPTOR_HPP
