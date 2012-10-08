/**
 * \file dcs/system/posix_process.hpp
 *
 * \brief Class to create and manage a process in POSIX-compliant systems.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright (C) 2012       Marco Guazzone
 *                          [Distributed Computing System (DCS) Group,
 *                           Computer Science Institute,
 *                           Department of Science and Technological Innovation,
 *                           University of Piemonte Orientale,
 *                           Alessandria (Italy)]
 *
 * This file is part of dcsxx-commons.
 *
 * dcsxx-commons is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dcsxx-commons is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dcsxx-commons.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_SYSTEM_POSIX_PROCESS_HPP
#define DCS_SYSTEM_POSIX_PROCESS_HPP


//TODO: How to check for a POSIX-compliant system?
//
//FIXME: It seems this is not the best way to check for a POSIX-compliant system
//#if _POSIX_C_SOURCE < 1 && !_XOPEN_SOURCE && !_POSIX_SOURCE
//# error "Unable to find a POSIX compliant system."
//#endif // _POSIX_C_SOURCE


#include <cerrno>
#include <cstddef>
#include <cstring>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/logging.hpp>
#include <dcs/system/process_status_category.hpp>
#include <fcntl.h>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>



namespace dcs { namespace system {

class posix_process
{
	private: static const unsigned int zzz_secs_ = 5;


	public: explicit posix_process(::std::string const& cmd)
	: cmd_(cmd),
//	  args_(),
	  async_(false),
	  pid_(-1),
	  status_(undefined_process_status),
	  sig_(-1),
	  exit_status_(EXIT_SUCCESS)
	{
	}

//	public: template <typename FwdIterT>
//			posix_process(::std::string const& cmd, FwdIterT arg_first, FwdIterT arg_last)
//	: cmd_(cmd),
//	  args_(arg_first, arg_last),
//	  async_(false),
//	  status_(undefined_status),
//	  sig_(-1),
//	  exit_status_(EXIT_SUCCESS)
//	{
//	}

	public: ~posix_process()
	{
		// Wait for child termination to prevent zombies
		try
		{
			this->wait();
		}
		catch (...)
		{
			::std::ostringstream oss;
			oss << "Failed to wait for command '" << cmd_ << "'";
			dcs::log_error(DCS_LOGGING_AT, oss.str());
		}
	}

	public: void asynch(bool val)
	{
		async_ = val;
	}

	public: template <typename FwdIterT>
			void run(FwdIterT arg_first, FwdIterT arg_last)
	{
		::pid_t pid = ::fork();

		if (pid == -1)
		{
			::std::ostringstream oss;
			oss << "Call to fork(2) failed for command '" << cmd_ << "': " << ::strerror(errno);

			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		if (pid == 0)
		{
			// The child

			// Get the maximum number of files this process is allowed to open
#if defined(F_MAXFD)
			int maxdescs = ::fcntl(-1, F_MAXFD, 0);
			if (maxdescs == -1)
			{
# if defined(_SC_OPEN_MAX)
            	maxdescs = ::sysconf(_SC_OPEN_MAX);
# else // _SC_OPEN_MAX
				::rlimit limit;
				if (::getrlimit(RLIMIT_NOFILE, &limit) < 0)
				{
					::std::ostringstream oss;
					oss << "Call to getrlimit(2) failed for command '" << cmd_ << "': " << ::strerror(errno);

					DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
				}
				maxdescs = limit.rlim_cur;
# endif // _SC_OPEN_MAX
			}
#else // F_MAXFD
# if defined(_SC_OPEN_MAX)
			int maxdescs = ::sysconf(_SC_OPEN_MAX);
# else // _SC_OPEN_MAX
			::rlimit limit;
			if (::getrlimit(RLIMIT_NOFILE, &limit) < 0)
			{
				::std::ostringstream oss;
				oss << "Call to getrlimit(2) failed for command '" << cmd_ << "': " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}
			maxdescs = limit.rlim_cur;
# endif // _SC_OPEN_MAX
#endif // F_MAXFD
			if (maxdescs == -1)
			{
				maxdescs = 1024;
			}

			// Check if the command already has path information
			::std::string cmd_path;
			::std::string cmd_name;
			typename ::std::string::size_type pos;
			pos = cmd_.find_last_of('/');
			if (pos != ::std::string::npos)
			{
				cmd_path = cmd_.substr(0, pos);
				cmd_name = cmd_.substr(pos+1);
			}


			// Populate the argument list
			::std::size_t nargs = ::std::distance(arg_first, arg_last)+2;
			char** argv = new char*[nargs];
			argv[0] = new char[cmd_name.size()+1];
			::std::strncpy(argv[0], cmd_name.c_str(), cmd_name.size()+1); // by convention, the first argument is always the command name
			::std::size_t i(1);
			while (arg_first != arg_last)
			{
				argv[i] = new char[arg_first->size()+1];
				::std::strncpy(argv[i], arg_first->c_str(), arg_first->size()+1);
				++arg_first;
				++i;
			}
			argv[i] = 0; // The array of pointers must be terminated by a NULL pointer.

			// Close unused file descriptors
			for (int fd = 0; fd < maxdescs; ++fd)
			{
#ifdef DCS_DEBUG
				// Keep standard error open for debug
				if (fd != STDERR_FILENO)
				{
					::close(fd);
				}
#else // DCS_DEBUG
				::close(fd);
#endif // DCS_DEBUG
			}

			// Run the command
			::execvp(cmd_.c_str(), argv);

			// Actually we should delete argv and envp data. As we must not
			// call any non-async-signal-safe functions though we simply exit.
			::write(STDERR_FILENO, "execvp() failed\n", 17);
			_exit(EXIT_FAILURE);
		}

		// The parent

		pid_ = pid;
		status_ = running_process_status;

		if (!async_)
		{
			this->wait();
		}
	}

	public: void wait()
	{
		int wstatus;

		if (::waitpid(pid_, &wstatus, WUNTRACED | WCONTINUED) == -1)
		{
			::std::ostringstream oss;
			oss << "Call to waitpid(2) failed for command '" << cmd_ << "': " << ::strerror(errno);

			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		if (WIFEXITED(wstatus))
		{
			exit_status_ = WEXITSTATUS(wstatus);
			if (exit_status_ != EXIT_SUCCESS)
			{
				status_ = failed_process_status;

				::std::ostringstream oss;
				oss << "Command '" << cmd_ << "' exited with status: " << exit_status_;
				dcs::log_warn(DCS_LOGGING_AT, oss.str());
			}
			else
			{
				status_ = terminated_process_status;
			}
		}
		else if (WIFSTOPPED(wstatus))
		{
			status_ = stopped_process_status;
			sig_ = WSTOPSIG(wstatus);
		}
		else if (WIFCONTINUED(wstatus))
		{
			status_ = resumed_process_status;
		}
		else if (WIFSIGNALED(wstatus))
		{
			sig_ = WTERMSIG(wstatus);
			status_ = aborted_process_status;

			::std::ostringstream oss;
			oss << "Command '" << cmd_ << "' signaled with signal: " << sig_;
			dcs::log_warn(DCS_LOGGING_AT, oss.str());
		}
		else
		{
			status_ = aborted_process_status;

			::std::ostringstream oss;
			oss << "Command '" << cmd_ << "' failed for an unknown reason";
			dcs::log_error(DCS_LOGGING_AT, oss.str());
		}
	}

	public: process_status_category status() const
	{
		return status_;
	}

	public: void stop()
	{
		// pre: process must be running
		DCS_ASSERT(status_ == running_process_status,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Cannot stop a process that is not running"));

		this->kill(SIGSTOP);
	}

	public: void resume()
	{
		// pre: process must have been stopped
		DCS_ASSERT(status_ == stopped_process_status,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Cannot resume a process that has not been stopped"));

		this->kill(SIGCONT);
	}

	public: void terminate()
	{
		// pre: process must be running
		DCS_ASSERT(status_ == running_process_status,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Cannot stop a process that is not running"));

		this->kill(SIGTERM);
		::sleep(zzz_secs_);
		if (this->alive())
		{
			this->kill(SIGKILL);
		}
		this->wait();
	}

	public: bool alive() const
	{
		if (::kill(pid_, 0) == -1)
		{
			if (errno != ESRCH)
			{
				::std::ostringstream oss;
				oss << "Call to kill(2) failed for command '" << cmd_ << "' and signal 0: " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}

			return false;
		}

		return true;
	}

	public: void kill(int sig)
	{
		// pre: sig >= 0
		DCS_ASSERT(sig >= 0,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid signal number"));

		// signal 0 has a special meaning: it can be used to check if a process
		// exists without actually sending any signal to it.
		// To send such a signal, use method \c exist.
		if (sig == 0)
		{
			return;
		}

		if (::kill(pid_, sig) == -1)
		{
			::std::ostringstream oss;
			oss << "Call to kill(2) failed for command '" << cmd_ << "' and signal " << sig << ": " << ::strerror(errno);

			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		sig_ = sig;
		switch (sig)
		{
			case SIGCONT:
				status_ = resumed_process_status;
				break;
			case SIGSTOP:
				status_ = stopped_process_status;
				break;
			case SIGTERM:
			case SIGKILL:
				status_ = terminated_process_status;
				break;
			case SIGINT:
				status_ = aborted_process_status;
				break;
			default:
				::sleep(zzz_secs_);
				if (!this->alive())
				{
					status_ = aborted_process_status;
				}
				break;
		}
	}


	private: ::std::string cmd_; ///< The command path
//	private: ::std::vector< ::std::string > args_; ///< The list of command arguments
	private: bool async_; ///< A \c true value means that the parent does not block to wait for child termination
	private: ::pid_t pid_; ///< The process identifier
	private: process_status_category status_; ///< The current status of this process
	private: int sig_; ///< The last signal sent to this process
	private: int exit_status_; ///< The exit status of this process
}; // posix_process

}} // Namespace dcs::system


#endif // DCS_SYSTEM_POSIX_PROCESS_HPP
