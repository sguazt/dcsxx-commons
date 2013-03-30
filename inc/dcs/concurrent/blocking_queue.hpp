/**
 * \file dcs/concurrent/blocking_queue.hpp
 *
 * \brief An optionally-bounded blocking queue.
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
#ifndef DCS_CONCURRENT_BLOCKING_QUEUE_HPP
#define DCS_CONCURRENT_BLOCKING_QUEUE_HPP


#include <boost/chrono.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <cstddef>
#include <deque>
#include <queue>


namespace dcs { namespace concurrent {


/**
 * An optionally-bounded blocking queue.
 * 
 * This container orders elements in FIFO (First-In-First-Out) way.
 * The underlying implementation is backed by the template argument Q container.
 */
template<
	typename ValueT,
	typename SequenceT = ::std::deque<ValueT>
>
class blocking_queue
{
	private: static const ::boost::chrono::duration<long> dummy_duration;


	public: typedef SequenceT container_type;
	public: typedef typename container_type::value_type value_type;
	public: typedef typename container_type::reference reference;
	public: typedef typename container_type::const_reference const_reference;
	public: typedef typename container_type::size_type size_type;
	private: typedef ::std::queue<value_type,container_type> queue_impl_type;


	//TODO: concept-check: value_type == container_type::value_type


	public: explicit blocking_queue(container_type seq = container_type())
	: queue_(seq)
	{
	}

	public: explicit blocking_queue(size_type capacity)
	: cap_(capacity)
	{
	}

	public: bool empty() const
	{
		::boost::unique_lock< ::boost::mutex > lock(mutex_);

		return queue_.empty();
	}

	public: size_type size() const
	{
		::boost::unique_lock< ::boost::mutex > lock(mutex_);

		return queue_.size();
	}

	public: bool bounded() const
	{
		return cap_ > 0;
	}

	public: size_type capacity() const
	{
		return cap_;
	}

	public: bool try_push(value_type const& val)
	{
		return push(val, false, dummy_duration);
	}

	public: void push(value_type const& val)
	{
		push(val, true, dummy_duration);
	}

	public: template <typename Rep, typename Period>
			bool push(value_type const& val, ::boost::chrono::duration<Rep, Period> const& wait_time)
	{
		return push(val, true, wait_time);
	}

	public: bool try_front(value_type& val) const
	{
		return peek(val, true, false, dummy_duration);
	}

	public: value_type front() const
	{
		value_type val;

		peek(val, true, true, dummy_duration);

		return val;
	}

	public: bool try_back(value_type& val) const
	{
		return peek(val, false, false, dummy_duration);
	}

	public: value_type back() const
	{
		value_type val;

		peek(val, false, true, dummy_duration);

		return val;
	}

	public: bool try_pop(value_type& val)
	{
		return pop(val, false, dummy_duration);
	}

	public: void pop(value_type& val)
	{
		pop(val, true, dummy_duration);
	}

	public: template <typename Rep, typename Period>
			void pop(value_type& val, ::boost::chrono::duration<Rep,Period> const& wait_time)
	{
		pop(val, true, wait_time);
	}

	private: template <typename Rep, typename Period>
			 bool push(value_type const& val, bool wait, ::boost::chrono::duration<Rep,Period> const& wait_time)
	{
		::boost::unique_lock< ::boost::mutex > lock(mutex_);
		if (wait)
		{
			while (this->bounded() && queue_.size() >= cap_)
			{
				if (dummy_duration == wait_time)
				{
					full_cond_.wait_for(lock, wait_time);
				}
				else
				{
					full_cond_.wait(lock);
				}
			}
		}
		else
		{
			if (this->bounded() && queue_.size() >= cap_)
			{
				return false;
			}
		}
		queue_.push(val);
		lock.unlock();

		empty_cond_.notify_one();

		return true;
	}

	private: template <typename Rep, typename Period>
			 bool pop(value_type& val, bool wait, ::boost::chrono::duration<Rep,Period> const& wait_time)
	{
		::boost::unique_lock< ::boost::mutex > lock(mutex_);
		if (wait)
		{
			while (queue_.empty())
			{
				if (dummy_duration == wait_time)
				{
					empty_cond_.wait_for(lock, wait_time);
				}
				else
				{
					empty_cond_.wait(lock);
				}
			}
		}
		else
		{
			if (queue_.empty())
			{
				return false;
			}
		}
		
		val = queue_.front();
		queue_.pop();
		lock.unlock();

		full_cond_.notify_one();

		return true;
	}

	private: template <typename Rep, typename Period>
			 bool peek(value_type& val, bool front, bool wait, ::boost::chrono::duration<Rep,Period> const& wait_time)
	{
		::boost::unique_lock< ::boost::mutex > lock(mutex_);
		if (wait)
		{
			while (queue_.empty())
			{
				if (dummy_duration == wait_time)
				{
					empty_cond_.wait_for(lock, wait_time);
				}
				else
				{
					empty_cond_.wait(lock);
				}
			}
		}
		else
		{
			if (queue_.empty())
			{
				return false;
			}
		}

		val = front ? queue_.front() : queue_.back();

		return true;
	}

	private: size_type cap_; ///< The maximum capacity of the queue
	private: queue_impl_type queue_; ///< The queue container
	private: mutable ::boost::mutex mutex_; ///< Main lock for guarding all accesses
	private: mutable ::boost::condition_variable empty_cond_; ///< Condition for waiting pops
	private: mutable ::boost::condition_variable full_cond_; ///< Condition for waiting pushes
}; // blocking_queue

template <typename T, typename Q>
const ::boost::chrono::duration<long> blocking_queue<T,Q>::dummy_duration;

}} // Namespace dcs::concurrent

#endif // DCS_CONCURRENT_BLOCKING_QUEUE_HPP
