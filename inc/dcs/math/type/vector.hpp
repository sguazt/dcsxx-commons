/**
 * \file dcs/math/type/vector.hpp
 *
 * \brief A numerical dense vector class.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2012 Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_MATH_TYPE_VECTOR_HPP
#define DCS_MATH_TYPE_VECTOR_HPP


#include <algorithm>
#include <cstddef>
#include <dcs/assert.hpp>
#include <dcs/assert.hpp>
#include <dcs/exception.hpp>
#include <stdexcept>


namespace dcs { namespace math {


struct default_vector_properties { };


template <typename ValueT, typename PropsT = default_vector_properties>
class vector: public base_array<ValueT>
{
	public: typedef ValueT value_type;
	public: typedef PropsT properties_type;
	public: typedef ::std::size_t size_type;


	public: vector()
	: n_(0),
	  data_(0)
	{
	}

	public: explicit vector(::std::size_t n, value_type const& v = value_type/*zero*/())
	: n_(n),
	  data_((n > 0) ? new value_type[n] : 0)
	{
		if (data_)
		{
			::std::fill(data_, data_+n_, v);
		}
	}

	public: vector(vector<value_type> const& v)
	: n_(v.n_),
	  data_((n_ > 0) ? new value_type[n_] : 0)
	{
		if (data_)
		{
			::std::copy(v.begin_data(), v.end_data(), data_);
		}
	}

	public: template <typename IterT>
			vector(IterT first, IterT last)
	: n_(::std::distance(first, last)),
	  data_((n_ > 0) ? new value_type[n_] : 0)
	{
		if (data_)
		{
			::std::copy(first, last, data_);
		}
	}

	public: ~vector()
	{
		if (data_)
		{
			delete[] data_;
		}
	}

	public: vector<value_type> operator=(vector<value_type> const& that)
	{
		if (this != &that)
		{
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

	public: value_type& operator()(size_type i)
	{
		// pre: data_ != null
		DCS_ASSERT(data_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Zero-length vector"));
		// pre: i < n_
		DCS_ASSERT(i < n_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Index out-of-bound"));

		// Retrieve value in column-major order
		return data_[i];
	}

	public: value_type const& operator()(size_type i) const
	{
		// pre: data_ != null
		DCS_ASSERT(data_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Zero-length vector"));
		// pre: i < n_
		DCS_ASSERT(i < n_,
				   DCS_EXCEPTION_THROW(::std::logic_error,
									   "Index out-of-bound"));

		// Retrieve value in column-major order
		return data_[i];
	}

	public: value_type& at(size_type i)
	{
		return operator()(i);
	}

	public: value_type const& at(size_type i) const
	{
		return operator()(i);
	}

	public: value_type& operator[](size_type i)
	{
		return operator()(i);
	}

	public: value_type const& operator[](size_type i) const
	{
		return operator()(i);
	}

	public: size_type length() const
	{
		return n_;
	}

	public: void resize(size_type n, bool preserve = true)
	{
		if (!preserve || !n_ || !n)
		{
			if (data_)
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
			const size_type mn(::std::min(n_, n));

			value_type* tmp_data = new value_type[mn];

			// Back-up old data
			::std::copy(data_, data_+mn, tmp_data);

			delete[] data_;

			data_ = new value_type[n];

			// Restore old data
			::std::copy(tmp_data, tmp_data+mn, data_);

			// If the new dimension is bigger than the older one, fill the gap with zeros
			if (n > n_)
			{
				::std::fill(data_+n_, data_+n, value_type/*zero*/());
			}

			delete[] tmp_data;
		}

		n_ = n;
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


	private: ::std::size_t n_; ///< Number of elements
	private: value_type* data_; ///< The raw storage
}; // vector

}} // Namespace dcs::math

#endif // DCS_MATH_TYPE_VECTOR_HPP
