/**
 * \file dcs/math/stats/function/rand.hpp
 *
 * \brief Generate a random number according to a given probability distribution
 *  and with a given uniform random number generator.
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
// * \author Marco Guazzone (marco.guazzone@gmail.com)
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
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename DistributionT, typename UniformRandomGeneratorT>
typename distribution_traits<DistributionT>::value_type rand(DistributionT const& dist, UniformRandomGeneratorT& rng)
{
    return dist.rand(rng);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_RAND_HPP
