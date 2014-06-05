/**
 * \file dcs/math/stats/utility.hpp
 *
 * \brief Statistics utilities.
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

#ifndef DCS_MATH_STATS_UTILITY_HPP
#define DCS_MATH_STATS_UTILITY_HPP


//#include <boost/smart_ptr.hpp>
//#include <dcs/math/stats/base_distribution.hpp>
//#include <dcs/math/stats/distribution_adaptor.hpp>


namespace dcs { namespace math { namespace stats {

//template <typename DistributionT>
//distribution_adaptor<DistributionT> wrap_distribution(DistributionT const& dist)
//{
//	return distribution_adaptor<DistributionT>(dist);
//}

//template <typename DistributionT, typename UIntType>
//::boost::shared_ptr< base_distribution<typename DistributionT::real_type, UIntType> > make_distribution(DistributionT const& dist)
//{
//	return ::boost::shared_ptr< base_distribution<typename DistributionT::real_type, UIntType> >(
//					new distribution_adaptor<DistributionT,UIntType>(dist)
//	);
//}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_UTILITY_HPP
