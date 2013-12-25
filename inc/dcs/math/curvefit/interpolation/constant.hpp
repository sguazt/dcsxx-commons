/**
 * \file dcs/math/curvefit/interpolation/constant.hpp
 *
 * \brief Piecewise constant (i.e, step-like) interpolation.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2013       Marco Guazzone (marco.guazzone@gmail.com)
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons (below referred to as "this program").
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP
#define DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP


#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <cstddef>
//#include <dcs/algorithm/order.hpp>


namespace dcs { namespace math { namespace curvefit {

template <typename RealT>
class constant_interpolator: public base_1d_interpolator<RealT>
{
	public: typedef RealT real_type;
	private: typedef base_1d_interpolator<real_type> base_type;


	public: constant_interpolator()
	{
	}

	public: template <typename XIterT, typename YIterT>
			constant_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y)
	: base_type(first_x, last_x, first_y, last_y, 0, 2)
	{
	}

	private: real_type do_interpolate(real_type x) const
	{
		const ::std::size_t j(this->find(x));

		return this->value(j);
	}
}; // constant_interpolator

}}} // Namespace dcs::math::curvefit


#endif // DCS_MATH_CURVEFIT_INTERPOLATION_CONSTANT_HPP
