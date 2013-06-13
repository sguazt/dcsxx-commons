/**
 * \file dcs/math/type/matrix.hpp
 *
 * \brief A numerical 2D dense matrix.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_MATH_TYPE_MATRIX_HPP
#define DCS_MATH_TYPE_MATRIX_HPP


#include <algorithm>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/math/type/base_matrix.hpp>
#include <dcs/math/type/detail/storage.hpp>
#include <dcs/math/type/matrix_properties.hpp>
#include <stdexcept>


namespace dcs { namespace math {

template <typename ValueT, typename PropsT = default_matrix_properties>
class matrix: public base_matrix<ValueT>
{
	private: typedef base_matrix<ValueT> base_type;
	public: typedef ValueT value_type;
	public: typedef ::std::size_t size_type;
	public: typedef PropsT properties_type;


	public: matrix()
	: nr_(0),
	  nc_(0),
	  n_(0),
	  data_(0)
	{
	}

	public: matrix(size_type nr,
				   size_type nc,
				   value_type v = value_type/*zero*/())
	: nr_(nr),
	  nc_(nc),
	  n_(nr*nc),
	  data_((n_ > 0) ? new value_type[n_] : 0)
	{
		if (data_)
		{
			::std::fill(data_, data_+n_, v);
		}
	}

	public: matrix(matrix<value_type,properties_type> const& m)
	: nr_(m.nr_),
	  nc_(m.nc_),
	  n_(m.n_),
	  data_((n_ > 0) ? new value_type[n_] : 0)
	{
		if (data_)
		{
			::std::copy(m.begin_data(), m.end_data(), data_);
		}
	}

	public: ~matrix()
	{
		if (data_)
		{
			delete[] data_;
		}
	}

	public: matrix<value_type>& operator=(matrix<value_type,properties_type> const& that)
	{
		if (this != &that)
		{
			nr_ = that.nr_;
			nc_ = that.nc_;
			n_ = that.n_;
			if (data_)
			{
				delete[] data_;
			}
			if (n_ > 0)
			{
				data_ = new value_type[n_];
				::std::copy(that.begin_data(), that.end_data(), data_);
			}
			else
			{
				data_ = 0;
			}
		}

		return *this;
	}

	public: size_type leading_dimension() const
	{
		return detail::matrix_storage_helper<typename properties_type::storage_layout>::leading_dimension(nr_, nc_);
	}

	public: size_type num_rows() const
	{
		return nr_;
	}

	public: size_type num_columns() const
	{
		return nc_;
	}

	public: size_type num_elements() const
	{
		return n_;
	}

	public: value_type& operator()(size_type r, size_type c)
	{
        // pre: data_ != null
        DCS_ASSERT(n_ > 0,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Zero-length matrix"));
        // pre: r < nr_
        DCS_ASSERT(r < nr_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Row index out-of-bound"));
        // pre: c < nc_
        DCS_ASSERT(c < nc_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Column index out-of-bound"));

		return detail::matrix_storage_helper<typename properties_type::storage_layout>::template at(data_, nr_, nc_, r, c);
	}

	public: value_type const& operator()(size_type r, size_type c) const
	{
        // pre: data_ != null
        DCS_ASSERT(n_ > 0,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Zero-length matrix"));
        // pre: r < nr_
        DCS_ASSERT(r < nr_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Row index out-of-bound"));
        // pre: c < nc_
        DCS_ASSERT(c < nc_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Column index out-of-bound"));

		return detail::matrix_storage_helper<typename properties_type::storage_layout>::template at(data_, nr_, nc_, r, c);
	}

	public: value_type& at(size_type r, size_type c)
	{
		return operator()(r,c);
	}

	public: value_type const& at(size_type r, size_type c) const
	{
		return operator()(r,c);
	}

	public: void resize(size_type nr, size_type nc, bool preserve = true)
	{
		const size_type n(nr*nc);

		if (!preserve || !n || !data_ || !n_)
		{
			// Resize without data preservation

			if (n_ > 0)
			{
				delete[] data_;
			}
			if (n > 0)
			{
				data_ = new value_type[n];

				::std::fill(data_, data_+n, value_type/*zero*/());
			}
			else
			{
				data_ = 0;
			}
		}
		else
		{
			// Resize with data preservation

			const size_type mnr(::std::min(nr_, nr));
			const size_type mnc(::std::min(nc_, nc));
			const size_type mn(mnr*mnc);

			value_type* tmp_data = new value_type[mn];

			// Back-up old data
			//::std::copy(data_, data_+mn, tmp_data);
			detail::matrix_storage_helper<typename properties_type::storage_layout>::template copy(data_, nr_, nc_, tmp_data, nr, nc, mnr, mnc);

			delete[] data_;

			data_ = new value_type[n];

			// If the new dimension covers a larger area than the older one, fill the gap with zeros
			if (n > mn)
			{
				::std::fill(data_, data_+n, value_type/*zero*/());
			}

			// Restore old data
			//::std::copy(tmp_data, tmp_data+mn, data_);
			detail::matrix_storage_helper<typename properties_type::storage_layout>::template copy(tmp_data, nr, nc, data_, nr, nc, mnr, mnc);

			delete[] tmp_data;
		}

		n_ = n;
		nr_ = nr;
		nc_ = nc;
	}

	public: bool empty() const
	{
		return n_ == 0;
	}

	public: value_type* begin_data()
	{
		return data_;
	}

	public: value_type const* begin_data() const
	{
		return data_;
	}

	public: value_type* end_data()
	{
		return data_+n_;
	}

	public: value_type const* end_data() const
	{
		return data_+n_;
	}


	private: size_type nr_; ///< Number of rows
	private: size_type nc_; ///< Number of columns
	private: size_type n_; ///< Number of elements
	private: value_type* data_;
}; // matrix

}} // Namespace dcs::math

#endif // DCS_MATH_TYPE_MATRIX_HPP
