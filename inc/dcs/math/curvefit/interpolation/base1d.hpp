/**
 * \file dcs/math/curvefit/interpolation/base1d.hpp
 *
 * \brief Base class for one-dimensional interpolation.
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

#ifndef DCS_MATH_CURVEFIT_INTERPOLATION_BASE1D_HPP
#define DCS_MATH_CURVEFIT_INTERPOLATION_BASE1D_HPP


#include <algorithm>
#include <cstddef>
#include <cmath>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/math/traits/float.hpp>
#include <stdexcept>
#include <vector>


namespace dcs { namespace math { namespace curvefit {

template <typename RealT>
class base_1d_interpolator
{
	public: typedef RealT real_type;


	public: base_1d_interpolator()
	: xx_(),
	  yy_(),
	  n_(0)
	{
	}

	public: template <typename XIterT, typename YIterT>
			base_1d_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y)
	: xx_(first_x, last_x),
	  yy_(first_y, last_y),
	  n_(xx_.size())
	{
		DCS_ASSERT(n_ >= 1,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid number of interpolating points"));
	}

	public: real_type operator()(real_type x) const
	{
		return do_interpolate(x);
	}

	public: ::std::size_t num_nodes() const
	{
		return xx_.size();
	}

	public: ::std::size_t num_values() const
	{
		return yy_.size();
	}

	public: ::std::vector<real_type> nodes() const
	{
		return xx_;
	}

	public: ::std::vector<real_type> values() const
	{
		return yy_();
	}

	public: real_type node(::std::size_t i) const
	{
		return xx_[i];
	}

	public: real_type value(::std::size_t i) const
	{
		return yy_[i];
	}

	/**
	 * Locates a given value inside the interpolation interval.
	 *
	 * Given a set of nodes \f$\{x_0,\ldots,x_{n-1}\}\f$ and a point \f$x\f$,
	 * finds the position \f$0 \le k < n-1\f$ of the interval
	 * \f$[x_0,x_{n-1}]\f$ where \f$x\f$ falls such that:
	 * \f{equation}
	 * \begin{cases}
	 * 0, & x \le x_0,\\
	 * k, & x_k \le x < x_{k+1},\\
	 * n-2, & x \ge x_{n-1},\\
	 * \end{cases}
	 * \f}
	 */
	protected: ::std::size_t find(real_type x) const
	{
		//return sequential_find(x);
		return bsearch_find(x);
	}

	/// Locate a given value using a sequential search
	protected: ::std::size_t sequential_find(real_type x) const
	{
		if (::dcs::math::float_traits<real_type>::approximately_less_equal(x, xx_[0]))
		{
			return 0;
		}

		for (::std::size_t i = 1; i < n_; ++i)
		{
			if (::dcs::math::float_traits<real_type>::definitely_less(x, xx_[i]))
			{
				return i-1;
			}
		}

		return n_-2;
	}

	/// Locate a given value by binary search
	protected: ::std::size_t bsearch_find(real_type x) const
	{
		// Handle out-of-domain points
		if (::dcs::math::float_traits<real_type>::approximately_less_equal(x, xx_[0]))
		{
			return 0;
		}
		if (::dcs::math::float_traits<real_type>::approximately_greater_equal(x, xx_[n_-1]))
		{
			return n_-2;
		}

		::std::size_t lo(0);
		::std::size_t hi(n_-1);

		while (lo < (hi-1))
		{
			const ::std::size_t mid((hi+lo) >> 1);
			if (::dcs::math::float_traits<real_type>::definitely_less(x, xx_[mid]))
			{
				hi = mid;
			}
			else
			{
				lo = mid;
			}
		}

		//post: the returned index is >= 0 and < (n-1)
		DCS_DEBUG_ASSERT( lo >= 0 && lo < (n_-1) );

		return lo;
	}

	private: virtual real_type do_interpolate(real_type x) const = 0;


	private: const ::std::vector<real_type> xx_; ///< Data points
	private: const ::std::vector<real_type> yy_; ///< Data values
	private: const long n_; ///< The number of interpolating points
}; // base_1d_interpolator

}}} // Namespace dcs::math::curvefit

#endif // DCS_MATH_CURVEFIT_INTERPOLATION_BASE1D_HPP
