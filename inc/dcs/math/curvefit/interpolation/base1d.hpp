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


	public: template <typename XIterT, typename YIterT>
			base_1d_interpolator(XIterT first_x, XIterT last_x, YIterT first_y, YIterT last_y, ::std::size_t order, ::std::size_t m)
	: xx_(first_x, last_x),
	  yy_(first_y, last_y),
	  n_(xx_.size()),
	  ord_(order),
	  m_(m),
	  jsav_(0),
	  cor_(0),
	  dj_(::std::max(::std::size_t(1), static_cast< ::std::size_t >(::std::pow(n_, 0.25))))
	{
		DCS_ASSERT(n_ >= 2,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid number of interpolating points"));
		DCS_ASSERT(ord_ >= 1,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid interpolation order"));
		DCS_ASSERT(m_ >= 2,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid number of local points"));
		DCS_ASSERT(m_ >= ord_,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Interpolation order cannot be greater than the number of local points"));
		DCS_ASSERT(m_ <= n_,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Interpolation order cannot be greater than the number of interpolating points"));

	}

	public: real_type operator()(real_type x) const
	{
		return do_interpolate(x);
	}

	public: ::std::size_t order() const
	{
		return ord_;
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

	protected: ::std::size_t find(real_type x) const
	{
		//return cor_ ? hunt(x) : locate(x);
		if (::dcs::math::float_traits<real_type>::approximately_less_equal(x, xx_[0]))
		{
			return 0;
		}
		for (::std::size_t i = 1; i < n_; ++i)
		{
			if (::dcs::math::float_traits<real_type>::approximately_less_equal(x, xx_[i]))
			{
				return i-1;
			}
		}
		return n_-1;
	}

	protected: ::std::size_t locate(real_type x) const
	{
		bool ascnd(xx_[n_-1] >= xx_[0]);
		::std::size_t jl(0);
		::std::size_t ju(n_-1);
		while ((ju-jl) > 1)
		{
			::std::size_t jm((ju+jl) >> 1);
			if ((x >= xx_[jm]) == ascnd)
			{
				jl = jm;
			}
			else
			{
				ju = jm;
			}
		}
		cor_ = ::std::abs(jl-jsav_) > dj_ ? 0 : 1;
		jsav_ = jl;
		return ::std::max(::std::size_t(0), ::std::min(n_-m_,jl-((m_-2) >> 1)));
	}

	protected: ::std::size_t hunt(real_type x) const
	{
		long ju(0);
		::std::size_t inc(1);
		bool ascnd(xx_[n_-1] >= xx_[0]);
		long jl(jsav_);
		if (jl < 0 || jl > static_cast<long>(n_-1))
		{
			jl = 0;
			ju = n_-1;
		}
		else if ((x >= xx_[jl]) == ascnd)
		{
			while (true)
			{
				ju = jl + inc;
				if (ju >= static_cast<long>(n_-1))
				{
					ju = n_-1;
					break;
				}
				else if ((x < xx_[ju]) == ascnd)
				{
					break;
				}
				else
				{
					jl = ju;
					inc *= 2;
				}
			}
		}
		else
		{
			ju = jl;
			while (true)
			{
				jl = jl - inc;
				if (jl <= 0)
				{
					jl = 0;
					break;
				}
				else if ((x >= xx_[jl]) == ascnd)
				{
					break;
				}
				else
				{
					ju = jl;
					inc *= 2;
				}
			}
		}
		while ((ju-jl) > 1)
		{
			long jm((ju+jl) >> 1);
			if ((x >= xx_[jm]) == ascnd)
			{
				jl = jm;
			}
			else
			{
				ju = jm;
			}
		}
		cor_ = ::std::abs(jl-jsav_) > dj_ ? 0 : 1;
		jsav_ = jl;
		return ::std::max(::std::size_t(0), ::std::min(n_-m_,jl-((m_-2)>>1)));
	}

	private: virtual real_type do_interpolate(real_type x) const = 0;


	private: const ::std::vector<real_type> xx_; ///< Data points
	private: const ::std::vector<real_type> yy_; ///< Data values
	private: const ::std::size_t n_; ///< The number of interpolating points
	private: const ::std::size_t ord_; ///< The order of interpolation
	private: const ::std::size_t m_; ///< The number of local points
	private: mutable ::std::size_t jsav_;
	private: mutable ::std::size_t cor_;
	private: const ::std::size_t dj_;
}; // base_1d_interpolator

}}} // Namespace dcs::math::curvefit

#endif // DCS_MATH_CURVEFIT_INTERPOLATION_BASE1D_HPP
