/**
 * \file dcs/math/curvefit/interpolation/linear.hpp
 *
 * \brief Piecewise linear interpolation.
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

#ifndef DCS_MATH_CURVEFIT_INTERPOLATION_LINEAR_HPP
#define DCS_MATH_CURVEFIT_INTERPOLATION_LINEAR_HPP


#include <dcs/math/curvefit/interpolation/base1d.hpp>
#include <cstddef>
//#include <dcs/algorithm/order.hpp>


namespace dcs { namespace math { namespace curvefit {

template <typename RealT>
class linear_interpolator: public base_1d_interpolator<RealT>
{
	public: typedef RealT real_type;
	private: typedef base_1d_interpolator<real_type> base_type;


	public: linear_interpolator()
	{
	}

	public: template <typename XIterT, typename YIterT>
			linear_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y)
	: base_type(first_x, last_x, first_y, last_y, 1, 2)
	{
	}

	private: real_type do_interpolate(real_type x) const
	{
		// To eval a point x we use the equation of the line passing by two points
		//
		//    y - y_1 = \frac{y_2 - y_1}{x_2 - x_1} (x - x_1),\,
		//

		::std::size_t j(this->find(x));
		if (this->node(j) == this->node(j+1))
		{
			return this->value(j);
		}

		return this->value(j) + ((x-this->node(j))/(this->node(j+1)-this->node(j)))*(this->value(j+1)-this->value(j));
	}

/*
	public: template <typename XIterT, typename YIterT>
			linear_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y)
	: xx_(first_x, last_x),
	  yy_(first_y, last_y)
	{
		DCS_ASSERT(xx_.size() == yy_.size(),
				   DCS_EXCEPTION_THROW(::std::invalid_argument, "Size of data points and data values mismatches"));

		::std::vector< ::std::size_t > ixx(xx_.size());
		::dcs::algorithm::order(xx_.begin(), xx_.end(), ixx.begin());

		::std::size_t n(ixx.size());
		for (::std::size_t i = 0; i < n; ++i)
		{
			::std::swap(yy_[i], yy_[ixx[i]]);
		}
	}

	private: real_type do_interpolate(real_type x) const
	{
		// To eval a point x we use the equation of the line passing by two points
		//
		//    y - y_1 = \frac{y_2 - y_1}{x_2 - x_1} (x - x_1),\,
		//

		::std::size_t n(xx_.size());

		if (n == 0)
		{
			return ::std::numeric_limits<real_type>::quiet_NaN();
		}
		if (n == 1)
		{
			return yy_[0];
		}

		::std::size_t ix1(0);
		::std::size_t ix2(0);

		typedef typename ::std::vector<real_type>::const_iterator iterator;
		iterator it = ::std::upper_bound(xx_.begin(), xx_.end(), x);
		if (it == xx_.begin())
		{
			// Use the line equation of the first part
			ix2 = 1;
		}
		else if (it == xx_.end())
		{
			// Use the line equation of the last part
			ix2 = n-1;
		}
		else
		{
			ix2 = static_cast< ::std::size_t >(::std::distance(xx_.begin(), it));
		}
		ix1 = ix2-1;

		return (x-xx_[ix1])*(yy_[ix2]-yy_[ix1])/(xx_[ix2]-xx_[ix1])+yy_[ix1];
	}

	private: ::std::vector<real_type> do_data_points() const
	{
		return xx_;
	}

	private: ::std::vector<real_type> do_data_values() const
	{
		return yy_;
	}


	private: ::std::vector<real_type> xx_; ///< Data points
	private: ::std::vector<real_type> yy_; ///< Data values
*/
}; // linear_interpolator

}}} // Namespace dcs::math::curvefit


#endif // DCS_MATH_CURVEFIT_INTERPOLATION_LINEAR_HPP
