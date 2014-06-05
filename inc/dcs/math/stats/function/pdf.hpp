/**
 * \file dcs/math/stats/function/pdf.hpp
 *
 * \brief Probability distribution function.
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

#ifndef DCS_MATH_STATS_FUNCTION_PDF_HPP
#define DCS_MATH_STATS_FUNCTION_PDF_HPP


namespace dcs { namespace math { namespace stats {

template <typename DistributionT>
typename DistributionT::value_type pdf(DistributionT const& dist, typename DistributionT::support_type x)
{
	return dist.pdf(x);
}

template <typename DistributionT, typename RealT>
typename DistributionT::value_type pdf(DistributionT const& dist, RealT x)
{
	typedef typename DistributionT::support_type support_type;
//	return pdf(dist, static_cast<value_type>(x));
	return dist.pdf(static_cast<support_type>(x));
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_PDF_HPP
