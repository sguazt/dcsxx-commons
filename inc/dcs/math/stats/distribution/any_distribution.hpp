/**
 * \file dcs/math/stats/distribution/any_distribution.hpp
 *
 * \brief Generic class for probability distributions with runtime polymorphism
 * support.
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

#ifndef DCS_MATH_STATS_DISTRIBUTION_ANY_DISTRIBUTION_HPP
#define DCS_MATH_STATS_DISTRIBUTION_ANY_DISTRIBUTION_HPP


#include <boost/smart_ptr.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <dcs/debug.hpp>
#include <dcs/math/random/any_generator.hpp>
#include <dcs/math/random/base_generator.hpp>
#include <dcs/math/random/generator_traits.hpp>
#include <dcs/math/random/uniform_01_adaptor.hpp>
#include <dcs/math/stats/distribution/base_distribution.hpp>
#include <dcs/math/stats/distribution/distribution_adaptor.hpp>
#include <dcs/math/stats/distribution/distribution_traits.hpp>
#include <dcs/type_traits/add_reference.hpp>
#include <dcs/type_traits/remove_reference.hpp>
#include <dcs/util/holder.hpp>
//#include <iosfwd>


namespace dcs { namespace math { namespace stats {

//namespace detail {
//
///**
// * \brief Interface for the \c ProbabilityDistribution concept.
// *
// * \tparam RealT The type used for real numbers.
// *
// * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
// */
//template <typename ValueT>
//class concept_distribution
//{
//	public: typedef ValueT value_type;
//
//	//virtual value_type rand(::dcs::math::random::any_generator<value_type>& rng) const = 0;
//
//	//[TODO]
//	public: template <typename UniformRandomGeneratorT>
//		value_type rand(UniformRandomGeneratorT& rng) const
//	{
//		return do_rand(
//			::dcs::math::random::make_any_generator<UniformRandomGeneratorT&>(rng)
//		);
//	}
//	//[/TODO]
//
//
//	public: virtual ::std::ostream& print(::std::ostream& os) const = 0;
//
//
//	//virtual ::std::pair<any_iterator,any_iterator> params() = 0;
//	//virtual ::std::pair<any_iterator const,any_iterator const> params() const = 0;
//	virtual ~concept_distribution() { }
//
//
//	//[TODO]
//	private: virtual value_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const = 0;
//	//private: virtual ::std::ostream& print(::std::ostream& os) const = 0;
//	//[/TODO]
//};


//template < typename DistributionT, typename DistributionTraitsT=distribution_traits<DistributionT> >
//class model_distribution: public concept_distribution<typename DistributionTraitsT::value_type>
//{
//	private: typedef DistributionT distribution_type;
//	public: typedef typename ::dcs::type_traits::add_reference<distribution_type>::type reference_distribution_type;
//	public: typedef typename ::dcs::type_traits::add_reference<typename ::dcs::type_traits::add_const<distribution_type>::type>::type const_reference_distribution_type;
//	public: typedef typename DistributionTraitsT::value_type value_type;
//
//
//	public: model_distribution(const_reference_distribution_type dist)
//		: dist_(dist)
//	{
//		// empty
//	}
//
//
//	public: ::std::ostream& print(::std::ostream& os) const
//	{
//		os << dist_;
//		return os;
//	}
//
//
//	private: value_type do_rand(::dcs::math::random::any_generator<value_type>& rng) const
//	{
//		return dist_.rand(rng);
//	}
//
//
//	public: distribution_type dist_;
//};
//
//} // Namespace detail


/**
 * \brief Generic random number generator.
 * \tparam ValueT The type of real numbers.
 *
 * This class is useful when one does not know at compile-time the type of
 * the random probability distribution that is to be used or when one needs to
 * create a container of non-homogeneous randon probability distributions.
 * Thus, this class realizes a runtime version of the \c ProbabilityDistribution
 * concept; this is accomplished by using the <em>type-erasure</em> technique,
 * which adds a one more level of indirection.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
template <typename ValueT>
class any_distribution
{
	public: typedef ValueT value_type;


	public: any_distribution() { }


	public: template <typename DistributionT>
		any_distribution(DistributionT const& dist)
		: ptr_dist_(new distribution_adaptor<DistributionT>(dist))
	{
		// empty
	}


	public: template <typename DistributionT>
		any_distribution(::dcs::util::holder<DistributionT> const& wrap_dist)
		: ptr_dist_(new distribution_adaptor<DistributionT>(wrap_dist.get()))
	{
		// empty
	}


	// Compiler-generated copy ctor and copy assignement are fine.


	public: template <typename DistributionT>
		void distribution(DistributionT dist)
	{
		ptr_dist_ = ::boost::make_shared< distribution_adaptor<DistributionT> >(dist);
	}


	//@{ ProbabilityDistribution concept implementation

//	public: value_type rand(::dcs::math::random::any_generator<value_type>& rng) const
//	{
//		return ptr_dist_->rand(rng);
//	}


	public: template <typename UniformRandomGeneratorT>
		value_type rand(UniformRandomGeneratorT& rng) const
	{
		// pre: distribution pointer must be a valid pointer
		DCS_DEBUG_ASSERT( ptr_dist_ );

//		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type> u01_rng = ::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type>(rng);
//		return ptr_dist_->rand(u01_rng);
		return ptr_dist_->rand(rng);
		//return ptr_dist_->rand(rng);
//			::dcs::math::random::make_any_generator<UniformRandomGeneratorT&>(rng)
//		);
	}


//	public: template <typename UniformRandomGeneratorT>
//		typename ::boost::disable_if<
//			::boost::is_base_of<
//				::dcs::math::random::base_generator<
//					typename ::dcs::math::random::generator_traits<UniformRandomGeneratorT>::result_type
//				>,
//				UniformRandomGeneratorT
//			>,
//			value_type
//		>::type rand(UniformRandomGeneratorT& rng) const
//	{
////		::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type> u01_rng = ::dcs::math::random::uniform_01_adaptor<UniformRandomGeneratorT&,value_type>(rng);
////		return ptr_dist_->rand(u01_rng);
//		return ptr_dist_->rand(rng);
//		//return ptr_dist_->rand(rng);
////			::dcs::math::random::make_any_generator<UniformRandomGeneratorT&>(rng)
////		);
//	}


//	public: value_type rand(::dcs::math::random::base_generator<value_type>& rng) const
//	{
//		::dcs::math::random::uniform_01_adaptor< ::dcs::math::random::base_generator<value_type>&,value_type > u01_rng = ::dcs::math::random::uniform_01_adaptor< ::dcs::math::random::base_generator<value_type>&,value_type >(rng);
//		return ptr_dist_->rand(u01_rng);
//	}


//	public: template <typename T>
//		value_type rand(::dcs::math::random::base_generator<T>& rng) const
//	{
////		//::dcs::math::random::uniform_01_adaptor< ::dcs::math::random::base_generator<T>&,value_type > u01_rng = ::dcs::math::random::uniform_01_adaptor< ::dcs::math::random::base_generator<T>&,value_type >(rng);
////		typedef ::dcs::math::random::base_generator<T> base_generator_type;
////		typedef ::dcs::math::random::uniform_01_adaptor<base_generator_type&, valua_type> adapted_generator_type;
////		adapted_generator_type u01_rng(rng);
////
////		return ptr_dist_->rand(u01_rng);
//		return ptr_dist_->rand(rng);
//	}


//	public: template <
//				typename CharT,
//				typename CharTraits
//			>
//		::std::basic_ostream<CharT,CharTraits>& print(::std::basic_ostream<CharT,CharTraits>& os) const
//	{
////		return ptr_dist_->print(os);
//		os << *ptr_dist_;
//		return os;
//	}

	//@} ProbabilityDistribution concept implementation


	private: ::boost::shared_ptr< base_distribution<value_type> > ptr_dist_; // shared_ptr needed in order to keep alive the pointer during object copying
};


template <
	typename DistributionT,
	typename DistributionTraitsT=distribution_traits<DistributionT>
>
struct make_any_distribution_type
{
	typedef any_distribution<typename DistributionTraitsT::value_type> type;
};


namespace detail {

template <
	typename DistributionT,
	typename DistributionTraitsT=distribution_traits<DistributionT>
>
struct make_any_distribution_impl;


template <typename DistributionT, typename DistributionTraitsT>
struct make_any_distribution_impl
{
	typedef typename make_any_distribution_type<DistributionT,DistributionTraitsT>::type any_distribution_type;

	static any_distribution_type apply(DistributionT& dist)
	{
		return any_distribution_type(dist);
	}
};


template <typename DistributionT, typename DistributionTraitsT>
struct make_any_distribution_impl<DistributionT&,DistributionTraitsT>
{
	typedef typename make_any_distribution_type<DistributionT,DistributionTraitsT>::type any_distribution_type;

	static any_distribution_type apply(DistributionT& dist)
	{
		::dcs::util::holder<DistributionT&> wrap_distribution(dist);
		return any_distribution_type(wrap_distribution);
	}
};


template <typename RealT>
struct make_any_distribution_impl< any_distribution<RealT> >
{
	typedef any_distribution<RealT> any_distribution_type;

//	static any_distribution_type& apply(any_distribution_type& dist)
//	{
//		return dist;
//	}
//
//	static any_distribution_type const& apply(any_distribution_type const& dist)
//	{
//		return dist;
//	}

	static any_distribution_type apply(any_distribution_type const& dist)
	{
		return dist;
	}
};


template <typename RealT>
struct make_any_distribution_impl< any_distribution<RealT>& >
{
	typedef any_distribution<RealT> any_distribution_type;

	static any_distribution_type& apply(any_distribution_type& dist)
	{
		return dist;
	}
};

} // Namespace detail


template <typename DistributionT>
inline typename make_any_distribution_type<DistributionT>::type make_any_distribution(DistributionT dist)
{
	return detail::make_any_distribution_impl<DistributionT>::apply(dist);
}
 

//template <typename RealT, typename UniformRandomGeneratorT>
//inline RealT rand(any_distribution<RealT> const& dist, UniformRandomGeneratorT& rng)
//{
//	return dist.rand(rng);
//}

}}} // Namespace dcs::math::stats


#endif // DCS_MATH_STATS_DISTRIBUTION_ANY_DISTRIBUTION_HPP
