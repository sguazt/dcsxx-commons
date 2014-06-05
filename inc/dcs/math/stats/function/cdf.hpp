/**
 * \file dcs/math/stats/function/cdf.hpp
 *
 * \brief Cumulative distribution function.
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

#ifndef DCS_MATH_STATS_FUNCTION_CDF_HPP
#define DCS_MATH_STATS_FUNCTION_CDF_HPP


namespace dcs { namespace math { namespace stats {

//template <typename DistributionT>
//typename DistributionT::value_type cdf(DistributionT const& dist, typename DistributionT::value_type x);


template <typename DistributionT>
typename DistributionT::value_type cdf(DistributionT const& dist, typename DistributionT::support_type x)
{
	return dist.cdf(x);
}


template <typename DistributionT, typename RealT>
typename DistributionT::value_type cdf(DistributionT const& dist, RealT x)
{
	typedef typename DistributionT::support_type support_type;
	return dist.cdf(static_cast<support_type>(x));
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_CDF_HPP
