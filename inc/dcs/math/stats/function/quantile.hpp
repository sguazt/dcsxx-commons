/**
 * \file dcs/math/stats/function/quantile.hpp
 *
 * \brief Quantile function.
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

#ifndef DCS_MATH_STATS_FUNCTION_QUANTILE_HPP
#define DCS_MATH_STATS_FUNCTION_QUANTILE_HPP


namespace dcs { namespace math { namespace stats {

// If uncomment this one the compiler claims that calls to quantile are
// ambiguous
//template <typename DistributionT>
//typename DistributionT::support_type quantile(DistributionT const& dist, typename DistributionT::value_type x)
//{
//	return dist.quantile(x);
//}

template <typename DistributionT, typename RealT>
typename DistributionT::support_type quantile(DistributionT const& dist, RealT x)
{
	typedef typename DistributionT::value_type value_type;
//	return pdf(dist, static_cast<value_type>(x));
	return dist.quantile(static_cast<value_type>(x));
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_QUANTILE_HPP
