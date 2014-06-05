/**
 * \file dcs/math/stats/distribution/distribution_traits.hpp
 *
 * \brief Traits class for probability distributions.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_TRAITS_HPP
#define DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_TRAITS_HPP


#include <dcs/type_traits/remove_reference.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Traits class for statistical distributions.
 *
 * \tparam DistributionT The probability distribution type.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename DistributionT>
struct distribution_traits
{
	private: typedef typename ::dcs::type_traits::remove_reference<DistributionT>::type distribution_type;
	public: typedef typename distribution_type::value_type value_type;
	public: typedef typename distribution_type::value_type support_type;
//	public: typedef typename distribution_type::policy_type policy_type;
};

}}} // Namespace dcs::math::stats

#endif // DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_TRAITS_HPP
