/**
 * \file dcs/math/stats/distribution/distribution_adaptor.hpp
 *
 * \brief Adapt a given class to the base_distribution interface.
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
