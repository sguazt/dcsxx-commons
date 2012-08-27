/**
 * \file dcs/math/stats/function/rand.hpp
 *
 * \brief Generate a random number according to a given probability distribution
 *  and with a given uniform random number generator.
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

#ifndef DCS_MATH_STATS_FUNCTION_RAND_HPP
#define DCS_MATH_STATS_FUNCTION_RAND_HPP


#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_traits.hpp>
#include <dcs/math/stats/distribution/distribution_traits.hpp>


namespace dcs { namespace math { namespace stats {

//template <typename DistributionT, typename ValueT>
//typename distribution_traits<DistributionT>::value_type rand(DistributionT const& dist, ::dcs::math::random::base_generator<ValueT>& rng)
//{
//	return dist.rand(rng);
//}


//template <typename DistributionT, typename UniformRandomGeneratorT>
//typename ::boost::disable_if<
//	::boost::is_base_of< ::dcs::math::random::base_generator<typename ::dcs::math::random::generator_traits<UniformRandomGeneratorT>::result_type>, UniformRandomGeneratorT >,
//	typename distribution_traits<DistributionT>::value_type
//>::type rand(DistributionT const& dist, UniformRandomGeneratorT& rng)
//{
//	return dist.rand(rng);
//}


///**
// * \brief Generate a random number according to a given probability distribution
// *  and with a given uniform random number generator.
// *
// * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
// */
//template <typename DistributionT, typename DistributionTraitsT, typename UniformRandomGeneratorT>
//typename DistributionTraitsT::value_type rand(DistributionT const& dist, UniformRandomGeneratorT& rng)
//{
//	return dist.rand(rng);
//}


/**
 * \brief Generate a random number according to a given probability distribution
 *  and with a given uniform random number generator.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename DistributionT, typename UniformRandomGeneratorT>
typename distribution_traits<DistributionT>::value_type rand(DistributionT const& dist, UniformRandomGeneratorT& rng)
{
    return dist.rand(rng);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_RAND_HPP
