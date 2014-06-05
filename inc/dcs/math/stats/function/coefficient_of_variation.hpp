/**
 * \file dcs/math/stats/function/coefficient_of_variation.hpp
 *
 * \brief Compute the coefficient-of-variation for various statistics.
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

#ifndef DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP
#define DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP


#include <dcs/math/stats/function/mean.hpp>
#include <dcs/math/stats/function/standard_deviation.hpp>


namespace dcs { namespace math { namespace stats {

/**
 * \brief Compute the coefficient-of-variation for various statistics.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename SampleT, typename ValueT>
ValueT coefficient_of_variation(SampleT const& sample)
{
	return standard_deviation(sample)/mean(sample);
}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_FUNCTION_COEFFICIENT_OF_VARIATION_HPP
