/**
 * \file dcs/math/stats/distribution/distribution_traits.hpp
 *
 * \brief Traits class for probability distributions.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_TRAITS_HPP
#define DCS_MATH_STATS_DISTRIBUTION_DISTRIBUTION_TRAITS_HPP


#include <dcs/type_traits/remove_reference.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Traits class for statistical distributions.
 *
 * \tparam DistributionT The probability distribution type.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
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
