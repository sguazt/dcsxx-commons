/**
 * \file dcs/math/curvefit/interpolation/constant.hpp
 *
 * \brief Piecewise constant (i.e, step-like) interpolation.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2013 Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP
#define DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP


#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <cstddef>
#include <stdexcept>


namespace dcs { namespace math { namespace curvefit {

template <typename RealT>
class constant_interpolator: public base_1d_interpolator<RealT>
{
	public: typedef RealT real_type;
	private: typedef base_1d_interpolator<real_type> base_type;


	public: template <typename XIterT, typename YIterT>
			constant_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y)
	: base_type(first_x, last_x, first_y, last_y)
	{
		// pre: n >= 1
		DCS_ASSERT(this->num_nodes() > 0,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Insufficient number of nodes. Required at least 1 node."));
	}

	private: real_type do_interpolate(real_type x) const
	{
		const ::std::size_t j(this->find(x));

		return this->value(j);
	}
}; // constant_interpolator

}}} // Namespace dcs::math::curvefit


#endif // DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP
