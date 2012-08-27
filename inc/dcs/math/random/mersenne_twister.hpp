/**
 * \file dcs/math/random/mersenne_twister.hpp
 *
 * \brief Mersenne Twister Random Number Engine.
 *
 * Copyright (C) 2009-2012  Distributed Computing System (DCS) Group,
 *                          Computer Science Institute,
 *                          Department of Science and Technological Innovation,
 *                          University of Piemonte Orientale,
 *                          Alessandria (Italy).
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 */

#ifndef DCS_MATH_RANDOM_MERSENNE_TWISTER_HPP
#define DCS_MATH_RANDOM_MERSENNE_TWISTER_HPP


#include <dcs/detail/config/boost.hpp>

#if !DCS_DETAIL_CONFIG_BOOST_CHECK_VERSION(101500) // 1.15
#	error "Required Boost libraries version >= 1.15."
#endif


#include <boost/random/mersenne_twister.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <cstddef>
#include <stdint.h>


namespace dcs { namespace math { namespace random {

/**
 * \brief A mersenne_twister random number engine produces unsigned integer
 * random numbers in the closed interval \f$[0, 2^w − 1]\f$.
 *
 * \tparam UIntT The type of randomly generated numbers.
 * \tparam w The word size.
 * \tparam n The state size.
 * \tparam m The shift size.
 * \tparam r The mask bits.
 * \tparam a The XOR mask.
 * \tparam u The tempering.
 * \tparam s The tempering.
 * \tparam b The tempering.
 * \tparam t The tempering.
 * \tparam c The parameter.
 * \tparam l The tempering.
 *
 * A mersenne_twister random number engine produces unsigned integer random
 * numbers in the closed interval \f$[0, 2^{nw-r} − 1]\f$.
 * The state \f$x_i\f$ of a mersenne_twister object \f$x\f$ is of size \f$n\f$
 * and consists of a sequence \f$X\f$ of \f$n\f$ values of the type delivered by
 * \f$x\f$; all subscripts applied * to \f$X\f$ are to be taken modulo \f$n\f$.
 * The transition algorithm employs a twisted generalized feedback shift
 * register defined by shift values \f$n\f$ and \f$m\f$, a twist value \f$r\f$,
 * and a conditional xor-mask \f$a\f$.
 * To improve the uniformity of the result, the bits of the raw shift register
 * are additionally tempered (i.e., scrambled) according to a bit-scrambling
 * matrix defined by values \f$u\f$, \f$s\f$, \f$b\f$, \f$t\f$,
 * \f$c\f$, and \f$l\f$.
 * The state transition is performed as follows:
 * a) Concatenate the upper \f$w-r\f$ bits of \f$X_{i-n}\f$ with the lower
 *    \f$r\f$ bits of \f$X_{i+1-n}\f$ to obtain an unsigned integer value \f$Y\f$.
 * b) With \f$\alpha=a*(Y \wedge 1)\f$, set \f$X_i\f$ to
 *    \f$X_{i+m-n} \oplus (Y >> 1) xor \alpha\f$
 * The generation algorithm determines the unsigned integer values \f$z_1\f$,
 * \f$z_2\f$, \f$z_3\f$, \f$z_4\f$ as follows, then delivers \f$z_4\f$ as its
 * result:
 * a) Let \f$z_1 = X_i \oplus ((X_i >> u)\f$.
 * b) Let \f$z_2 = z_1 \oplus ((z_1 << s) \wedge b)\f$.
 * c) Let \f$z_3 = z_2 \oplus ((z_2 << t) \wedge c)\f$. 
 * d) Let \f$z_4 = z_3 \oplus (z_3 >> l).
 *
 * This class implements the \c RandomNumberEngine concept.
 *
 * \author Marco Guazzone, &gt;marco.guazzone@mfn.unipmn.it&lt;
 */
template <
	typename UIntT,
	::std::size_t w,
	::std::size_t n,
	::std::size_t m,
	::std::size_t r,
	UIntT a,
	::std::size_t u,
	::std::size_t s,
	UIntT b,
	::std::size_t t,
	UIntT c,
	::std::size_t l
>
class mersenne_twister: public base_generator<UIntT>
{
	private: typedef base_generator<UIntT> base_type;
	public: typedef UIntT result_type;
	public: typedef typename base_type::ulonglong_type ulonglong_type;
	private: typedef ::boost::random::mersenne_twister<UIntT,w,n,m,r,a,u,s,b,t,c,l,0> impl_type;


	public: static const ::std::size_t word_size = w;
	public: static const ::std::size_t state_size = n;
	public: static const ::std::size_t shift_size = m;
	public: static const ::std::size_t mask_bits = r;
	public: static const result_type xor_mask = a;
	public: static const ::std::size_t tempering_u = u;
	public: static const ::std::size_t tempering_s = s;
	public: static const result_type tempering_b = b;
	public: static const ::std::size_t tempering_t = t;
	public: static const result_type parameter_c = c;
	public: static const ::std::size_t tempering_l = l;
	public: static const result_type default_seed = impl_type::default_seed;


	public: mersenne_twister()
		: impl_()
	{
		// empty
	}


	public: explicit mersenne_twister(result_type z)
		: impl_(z)
	{
		// empty
	}


//	public: template <typename ItT>
//		mersenne_twister(ItT& first, ItT& last)
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
		//return impl_type::min();//FIXME: has not been implemented yet
		return 0;
	}


	public: static result_type max()
	{
		//return impl_type::max();//FIXME: has not been implemented yet
		// 2^w-1
		result_type res = 0;
		for(size_t i = 0; i < w; ++i)
		{
			res |= (1u << i);
		}
		return res;
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


	private: void do_seed(result_type z)
	{
		impl_.seed(z);
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


	public: friend bool operator==(mersenne_twister const& x, mersenne_twister const& y)
	{
		return x.impl_ == y.impl_;
	}


	public: friend bool operator!=(mersenne_twister const& x, mersenne_twister const& y)
	{
		return !(x == y);
	}


	private: impl_type impl_;
};


typedef mersenne_twister<uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 7, 0x31b6ab00, 15, 0xffe50000, 17> mt11213b;
typedef mersenne_twister<uint32_t, 32, 624, 397, 31, 0x9908b0df, 11, 7, 0x9d2c5680, 15, 0xefc60000, 18> mt19937;


}}} // Namespace dcs::math::random


#endif // DCS_MATH_RANDOM_MERSENNE_TWISTER_HPP
