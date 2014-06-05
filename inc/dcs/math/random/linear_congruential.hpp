/**
 * \file dcs/math/random/linear_congruential.hpp
 *
 * \brief Linear Congruential Random Number Engine.
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

#ifndef DCS_MATH_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define DCS_MATH_RANDOM_LINEAR_CONGRUENTIAL_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost libraries version >= 1.15."
#endif


#include <boost/random/linear_congruential.hpp>
#include <cstddef>
#include <dcs/math/random/base_generator.hpp>
#include <stdint.h>


namespace dcs { namespace math { namespace random {

//using ::std::size_t;

/*
template <typename IntT, IntT a, IntT c, IntT m>
class linear_congruential
{
	public: typedef IntT result_type;
	public: static const result_type min_value = (c == 0 ? 1 : 0);
	public: static const result_type max_value = m-1;
	public: static const result_type multiplier = a;
	public: static const result_type increment = c;
	public: static const result_type modulus = m;

	public: explicit linear_congruential(IntT x0=1)
	{
		seed(x0);
	}

	public: void seed(IntT x0=1)
	{
		x_ = ((modulus != 0) ? (x0 % modulus) : x0);

		// handle negative seeds
		if (x_ < 0)
		{
			x_ += modulus;
		}
		// adjust to the correct range
		if (increment == 0 && x_ == 0)
		{
			x_ = 1;
		}

		// post-conditions
		DCS_ASSERT(
			x_ >= min_value,
			throw std::domain_error("Seed less than min value")
		);
		DCS_ASSERT(
			x_ <= max_value,
			throw std::domain_error("Seed greater than max value")
		);
	}

	public: result_type operator()()
	{
		return next();
	}


	public: friend bool operator==(linear_congruential const& l1, linear_congruential const& l2)
	{
		return l1.x_ == l2.x_;
	}


	public: friend bool operator!=(linear_congruential const& l1, linear_congruential const& l2)
	{
		return !(l1 == l2);
	}


	// Perform: (a*x+c) mod m
	private: IntT next()
	{
		IntT max_d_a = std::numeric_limits<IntT>::max()/multiplier;

		if(modulus <= (max_d_a - increment/multiplier))   // i.e. a*m+c <= max
		{
			x_= (multiplier * x_ + increment) % modulus;
		}
		else
		{
			// increment and multiplier are big

			// Perform the product
			if (multiplier != 1)
			{
				if (modulus <= max_d_a) // i.e. a*m <= max
				{
					// small product
					x_ = (multiplier * x_) % modulus;
				}
				else if (std::numeric_limits<IntT>::is_signed && (modulus % multiplier) < (modulus / multiplier))
				{
					// Use the Schrage's Algorithm:
					//   an algorithm for multiplying two 32-bit integers modulo
					//   a 32-bit constant without using any intermediates
					//   larger than 32 bits. 

					const IntT q = modulus / multiplier;
					const IntT r = modulus % multiplier;

					assert(r < q);        // check that overflow cannot happen

					x_ = multiplier*(x_%q) - r*(x_/q);
					while (x_ <= 0)
					{
						x_ += modulus;
					}
				}
				else
				{
//					DCS_ASSERT("multiplier is too large");
					x_ = 0;
				}
			}

			// Perform the sum
			if (increment != 0)
			{
				if (increment <= (std::numeric_limits<IntT>::max()-modulus)) // i.e. m+x < max
				{
					// small sum
					x_ += increment;
					if (x_ >= modulus)
					{
						x_ -= modulus;
					}
				}
				else if (std::numeric_limits<IntT>::is_signed)
				{
					IntT m_sub_c(modulus-increment);

					if (x_ < m_sub_c)
					{
						x_ += increment;
					}
					else
					{
						x_ -= m_sub_c;
					}
				}
				else
				{
//					DCS_ASSERT("increment is too large°);
					x_ = 0;
				}
			}
		}

		return x_;
	}


	private: IntT x_;
};
*/


/**
 * \brief Linear Congruential Random Number Engine.
 *
 * \tparam UIntT The type of randomly generated numbers.
 * \tparam a The multiplier.
 * \tparam c The increment.
 * \tparam m The modulus.
 *
 * The Linear Congruential random number generator has the following form:
 * \f[
 *   X_{i+1} = a X_{i} + c \quad (\operatorname{mod} m)
 * \f]
 * where:
 * - \f$a\f$ is the \e multiplier.
 * - \f$c\f$ is the \e increment.
 * - \f$m\f$ is the \e modulus.
 * .
 * This class implements the \c RandomNumberEngine concept.
 *
 * \see "Numerical Recipes in C: The Art of Scientific Computing" (William H. Press, Brian P. Flannery, Saul A. Teukolsky, William T. Vetterling).
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */
template <typename UIntT, UIntT a, UIntT c, UIntT m>
class linear_congruential: public base_generator<UIntT>
{
	private: typedef base_generator<UIntT> base_type;
	public: typedef UIntT result_type;
	private: typedef ::boost::random::linear_congruential<UIntT,a,c,m,0> impl_type;
	public: typedef typename base_type::ulonglong_type ulonglong_type;
//	public: typedef long long ulonglong_type;


	public: static const result_type multiplier = a;
	public: static const result_type increment = c;
	public: static const result_type modulus = m;
	public: static const result_type default_seed = impl_type::default_seed;


	public: linear_congruential()
		: impl_()
	{
		// empty
	}


	public: explicit linear_congruential(result_type s)
		: impl_(s)
	{
		// empty
	}


//	public: template <typename ItT>
//		linear_congruential(ItT& first, ItT& last)
//		: impl_(first,last)
//	{
//		// empty
//	}


//	public: template <typename ItT>
//		void seed(ItT& first, ItT& last)
//	{
//		impl_.seed(first, last);
//	}


	public: static result_type min()
	{
		return (increment == 0u ? 1u : 0u);
	}


	public: static result_type max()
	{
		return (modulus - 1);
	}


	private: result_type do_min() const
	{
		return impl_.min();
	}


	private: result_type do_max() const
	{
		return impl_.max();
	}


	private: void do_seed()
	{
		impl_.seed();
	}


	private: void do_seed(result_type s)
	{
		impl_.seed(s);
	}


	private: result_type do_generate()
	{
		return impl_();
	}


	//FIXME: actually cannot use impl_.discard since it is defined only when
	//       BOOST_NO_LONG_LONG is undefined.
	private: void do_discard(ulonglong_type z)
	{
		for ( ; z != 0; --z)
		{
			this->operator()();
		}
//		impl_.discard(z);
	}


	public: friend bool operator==(linear_congruential const& l1, linear_congruential const& l2)
	{
		return l1.impl_ == l2.impl_;
	}


	public: friend bool operator!=(linear_congruential const& l1, linear_congruential const& l2)
	{
		return !(l1 == l2);
	}


	private: impl_type impl_;
};

// Some standard LCG (see http://random.mat.sbg.ac.at/~charly/server/node3.html)

typedef linear_congruential<int32_t, 16807, 0, 2147483647> minstd_rand0;
typedef linear_congruential<int32_t, 48271, 0, 2147483647> minstd_rand1;
typedef linear_congruential<int32_t, 69621, 0, 2147483647> minstd_rand2;
//FIXME: the declaration below requires a true 64 bit integer in order to
// store the two integral constants.
// For the moment use the boost::rand48 class (which emulates drand48
// without requiring true 64bit support) until we find a way the underlying
// architecture type.
#if true
typedef linear_congruential<uint64_t, 25214903917, 11, 281474976710656> rand48;
#else
class rand48
{
	public: typedef ::boost::rand48::result_type result_type;
	public: static const result_type default_seed = 1u;


	public: rand48()
		: impl_(default_seed)
	{
		// empty
	}


	public: explicit rand48(result_type s)
		: impl_(s)
	{
		// empty
	}


	public: template <typename ItT>
		rand48(ItT& first, ItT& last)
		: impl_(first,last)
	{
		// empty
	}


	public: void seed(result_type s=default_seed)
	{
		impl_.seed(s);
	}


	public: template <typename ItT>
		void seed(ItT& first, ItT& last)
	{
		impl_.seed(first, last);
	}


	public: static result_type min()
	{
		return 0;
	}


	public: static result_type max()
	{
		return ::std::numeric_limits<int32_t>::max();
	}


	public: result_type operator()()
	{
		return impl_();
	}


	public: void discard(size_t z)
	{
		for ( ; z != 0; --z)
		{
			operator()();
		}
	}


	public: friend bool operator==(rand48 const& lhs, rand48 const& rhs)
	{
		return lhs.impl_ == rhs.impl_;
	}


	public: friend bool operator!=(rand48 const& lhs, rand48 const& rhs)
	{
		return !(lhs == rhs);
	}


	private: ::boost::rand48 impl_;
};
#endif // false

}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_LINEAR_CONGRUENTIAL_HPP
