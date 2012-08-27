/**
 * \file dcs/math/stats/utility.hpp
 *
 * \brief Statistics utilities.
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
