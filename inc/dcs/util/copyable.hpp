/**
 * \file dcs/util/copyable.hpp
 *
 * \brief Copyable concept and model
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

#ifndef DCS_UTIL_COPYABLE_HPP
#define DCS_UTIL_COPYABLE_HPP

#include <cassert>
#include <typeinfo>

// See
//  Peter Pirkelbauer and Sean Parent and Mat Marcus and Bjarne Stroustrup.
//  "Runtime Concepts for the C++ Standard Template Library",
//  In Proc. of the 2008 ACM Symposium on Applied Computing (SAC'08), 2008
//

namespace dcs { namespace util {

namespace detail {

struct concept_copyable
{
	virtual concept_copyable& clone() const = 0;
	//virtual bool operator==(concept_copyable const&) const = 0;
};


template <typename T>
struct model_copyable: concept_copyable
{
	model_copyable(T const& value)
		: value_(value)
	{
		// empty
	}


	model_copyable& clone() const
	{
		return *(new model_copyable(value_));
	}


//	friend bool operator==(concept_copyable const& lhs, concept_copyable const& rhs)
//	{
//		assert(typeid(lhs) == typeid(rhs));
//
//		return dynamic_cast<T>(lhs) == dynamic_cast<T>(rhs);
//	}

//	bool operator==(concept_copyable const& rhs) const
//	{
//		assert(typeid(*this) == typeid(rhs));
//
//		return this->value_ == static_cast<model_copyable>(rhs).value_;
//	}


	T value_;
};

} // Namespace detail


/**
 * \brief Copyable concept and model
 *
 * Based on:
 *  Peter Pirkelbauer and Sean Parent and Mat Marcus and Bjarne Stroustrup.
 *  "Runtime Concepts for the C++ Standard Template Library",
 *  In Proc. of the 2008 ACM Symposium on Applied Computing (SAC'08), 2008
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
struct wrapper_copyable
{
	template <typename T>
	wrapper_copyable(T const& value)
		: c_(new detail::model_copyable<T>(value))
	{
	}

	wrapper_copyable(wrapper_copyable const& rhs)
		: c_(&(rhs.c_->clone()))
	{
	}

	~wrapper_copyable()
	{
		delete c_;
	}

	wrapper_copyable& operator=(wrapper_copyable const& that)
	{
		if (this != &that)
		{
			this->c_ = &(that.c_->clone());
		}

		return *this;
	}

//	friend bool operator==(wrapper_copyable const& x, wrapper_copyable const& y)
//	{
//		return *(x.c_) == *(y.c_);
//	}

	detail::concept_copyable* c_;
};

}} // Namespace dcs::util


#endif // DCS_UTIL_COPYABLE_HPP
