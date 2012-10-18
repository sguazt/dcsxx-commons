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


#include <boost/smart_ptr.hpp>
#include <boost/utility.hpp>
#include <cerrno>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <dcs/assert.hpp>
#include <dcs/debug.hpp>
#include <dcs/exception.hpp>
#include <dcs/logging.hpp>
#include <dcs/system/process_status_category.hpp>
#ifdef __GNUC__
# include <ext/stdio_filebuf.h>
#else // __GNUC__
# include <boost/iostreams/device/file_descriptor.hpp>
# include <boost/iostreams/stream_buffer.hpp>
#endif // __GNUC__
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

class posix_process: private ::boost::noncopyable
{
	private: static const unsigned int zzz_secs_ = 5;
#ifdef __GNUC__
	private: typedef ::__gnu_cxx::stdio_filebuf<char> fd_streambuf_type;
#else // __GNUC__
	private: typedef ::boost::iostreams::file_descriptor_source fd_device_type;
	private: typedef ::boost::iostreams::stream_buffer<fd_device_type> fd_streambuf_type;
#endif // __GNUC__


	public: explicit posix_process()
	: cmd_(),
	  async_(true),
	  pid_(-1),
	  status_(undefined_process_status),
	  sig_(-1),
	  exit_status_(EXIT_SUCCESS)
	{
	}

	public: explicit posix_process(::std::string const& cmd)
	: cmd_(cmd),
//	  args_(),
	  async_(true),
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
			if (this->alive())
			{
				this->wait();
			}
		}
		catch (::std::exception const& e)
		{
			::std::ostringstream oss;
			oss << "Failed to wait for command '" << cmd_ << "': " << e.what();
			dcs::log_error(DCS_LOGGING_AT, oss.str());
		}
		catch (...)
		{
			::std::ostringstream oss;
			oss << "Failed to wait for command '" << cmd_ << "': Unknown reason";
			dcs::log_error(DCS_LOGGING_AT, oss.str());
		}
	}

	public: void command(::std::string const& cmd)
	{
		cmd_ = cmd;
	}

	/// Returns the command name (without arguments).
	public: ::std::string command() const
	{
		return cmd_;
	}

	/**
	 * \brief Allows to set if the execution of this process will block
	 *  (\c false value) or not (\c true value) the parent process.
	 */
	public: void asynch(bool val)
	{
		async_ = val;
	}

	/**
	 * \brief Tells if the execution of this process will block (\c false value)
	 *  or not (\c true value) the parent process.
	 */
	public: bool asynch() const
	{
		return async_;
	}

	/// Returns the stream connected to the standard input of this process. 
	public: ::std::ostream& input_stream()
	{
		// pre: not null
		DCS_ASSERT(p_ios_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to input stream"));

		return *p_ios_;
	}

	/// Returns the stream connected to the standard input of this process. 
	public: ::std::ostream const& input_stream() const
	{
		// pre: not null
		DCS_ASSERT(p_ios_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to input stream"));

		return *p_ios_;
	}

	/// Returns the stream connected to the standard output of this process. 
	public: ::std::istream& output_stream()
	{
		// pre: not null
		DCS_ASSERT(p_ois_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to output stream"));

		return *p_ois_;
	}

	/// Returns the stream connected to the standard output of this process. 
	public: ::std::istream const& output_stream() const
	{
		// pre: not null
		DCS_ASSERT(p_ois_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to output stream"));

		return *p_ois_;
	}

	/// Returns the stream connected to the standard error of this process. 
	public: ::std::istream& error_stream()
	{
		// pre: not null
		DCS_ASSERT(p_eis_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to error stream"));

		return *p_eis_;
	}

	/// Returns the stream connected to the standard error of this process. 
	public: ::std::istream const& error_stream() const
	{
		// pre: not null
		DCS_ASSERT(p_eis_,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Invalid pointer to error stream"));

		return *p_eis_;
	}

	/**
	 * \brief Runs this process (without arguments and without connecting to the
	 *  standard input/output/error).
	 */
	public: void run()
	{
		::std::vector< ::std::string > args;
		run(args.begin(), args.end());
	}

	/**
	 * \brief Runs this process with the given argument and optionally by
	 *  connecting to the standard input/output/error.
	 */
	public: template <typename FwdIterT>
			 void run(FwdIterT arg_first, FwdIterT arg_last, bool pipe_in = false, bool pipe_out = false, bool pipe_err = false)
	{
		const ::std::size_t pipe_in_child_rd(0);
		const ::std::size_t pipe_in_parent_wr(1);
		const ::std::size_t pipe_out_parent_rd(2);
		const ::std::size_t pipe_out_child_wr(3);
		const ::std::size_t pipe_err_parent_rd(4);
		const ::std::size_t pipe_err_child_wr(5);

		// Create two pipes to let to communicate with AMPL.
		// Specifically, we want to write the input into AMPL (through the producer)
		// and to read the output from AMPL (through the consumer).
		// So, the child process read its input from the parent and write its output on
		// the pipe; while the parent write the child's input on the pipe and read its
		// input from the child.
		//
		// pipefd:
		// - [0,1]: Where the parent write to and the child read from (child's stdin).
		// - [2,3]: Where the parent read from and the child write to (child's stdout).
		// - [4,5]: Where the parent read from and the child write to (child's stderr).
		int pipefd[6];

		if (pipe_in)
		{
			if (::pipe(&pipefd[0]) == -1)
			{
				::std::ostringstream oss;
				oss << "Call to pipe(2) failed for command: '" << cmd_ << "' and for input production: " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}
		}
		if (pipe_out)
		{
			if (::pipe(&pipefd[2]) == -1)
			{
				::std::ostringstream oss;
				oss << "Call to pipe(2) failed for command: '" << cmd_ << "' and for output consumption: " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}
		}
		if (pipe_err)
		{
			if (::pipe(&pipefd[4]) == -1)
			{
				::std::ostringstream oss;
				oss << "Call to pipe(2) failed for command: '" << cmd_ << "' and for error consumption: " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}
		}

		// Spawn a new process

		// Between fork() and execve() only async-signal-safe functions
		// must be called if multithreaded applications should be supported.
		// That's why the following code is executed before fork() is called.
 
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

			::std::vector<bool> close_fd(maxdescs, true);

			// Associate the child's stdin/stdout to the pipe read/write fds.
			close_fd[STDIN_FILENO] = false;
			close_fd[STDOUT_FILENO] = false;
#ifdef DCS_DEBUG
			// Keep standard error open for debug
			close_fd[STDERR_FILENO] = false;
#endif // DCS_DEBUG
			if (pipe_in)
			{
				if (pipefd[pipe_in_child_rd] != STDIN_FILENO)
				{
					if (::dup2(pipefd[pipe_in_child_rd], STDIN_FILENO) != STDIN_FILENO)
					{
						::std::ostringstream oss;
						oss << "Call to dup2(2) failed for command '" << cmd_ << "' during connection to standard input: " << ::strerror(errno);

						DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
					}
				}
				else
				{
					if (STDIN_FILENO < maxdescs)
					{
						close_fd[STDIN_FILENO] = false;
					}
					else
					{
						::close(STDIN_FILENO);
					}
				}
			}
			if (pipe_out)
			{
				if (pipefd[pipe_out_child_wr] != STDOUT_FILENO)
				{
					if (::dup2(pipefd[pipe_out_child_wr], STDOUT_FILENO) != STDOUT_FILENO)
					{
						::std::ostringstream oss;
						oss << "Call to dup2(2) failed for command '" << cmd_ << "' during connection to standard output: " << ::strerror(errno);

						DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
					}
				}
				else
				{
					if (STDOUT_FILENO < maxdescs)
					{
						close_fd[STDOUT_FILENO] = false;
					}
					else
					{
						::close(STDOUT_FILENO);
					}
				}
			}
			if (pipe_err)
			{
				if (pipefd[pipe_err_child_wr] != STDERR_FILENO)
				{
					if (::dup2(pipefd[pipe_err_child_wr], STDERR_FILENO) != STDERR_FILENO)
					{
						::std::ostringstream oss;
						oss << "Call to dup2(2) failed for command '" << cmd_ << "' during connection to standard error: " << ::strerror(errno);

						DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
					}
				}
				else
				{
					if (STDERR_FILENO < maxdescs)
					{
						close_fd[STDERR_FILENO] = false;
					}
					else
					{
						::close(STDERR_FILENO);
					}
				}
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
				if (close_fd[fd])
				{
					::close(fd);
				}
			}

			// Run the command
			DCS_DEBUG_TRACE("Going to run: " << cmd_ << ::dcs::debug::to_string(argv, argv+nargs-1) );
			::execvp(cmd_.c_str(), argv);

			// Actually we should delete argv and envp data. As we must not
			// call any non-async-signal-safe functions though we simply exit.
			::std::ostringstream oss;
			oss << "Call to execvp(3) failed for command '" << cmd_ << "': " << ::strerror(errno) << ::std::endl;
			::std::size_t count(oss.str().size());
			::write(STDERR_FILENO, oss.str().c_str(), count);
			::_exit(EXIT_FAILURE);
		}

		// The parent

		if (pipe_in)
		{
			::close(pipefd[pipe_in_child_rd]);
		}
		if (pipe_out)
		{
			::close(pipefd[pipe_out_child_wr]);
		}
		if (pipe_err)
		{
			::close(pipefd[pipe_err_child_wr]);
		}

#ifdef __GNUC__
		if (pipe_in)
		{
			p_in_wrbuf_ = ::boost::make_shared<fd_streambuf_type>(pipefd[pipe_in_parent_wr], ::std::ios::out);
		}
		if (pipe_out)
		{
			p_out_rdbuf_ = ::boost::make_shared<fd_streambuf_type>(pipefd[pipe_out_parent_rd], ::std::ios::in);
		}
		if (pipe_err)
		{
			p_err_rdbuf_ = ::boost::make_shared<fd_streambuf_type>(pipefd[pipe_err_parent_rd], ::std::ios::in);
		}
#else // __GNUC__
		if (pipe_in)
		{
			fd_device_type in_wrdev(pipefd[pipe_in_parent_wr], ::boost::iostreams::close_handle);
			p_in_wrbuf_ = ::boost::make_shared<fd_streambuf_type>(in_wrdev);
		}
		if (pipe_out)
		{
			fd_device_type out_rddev(pipefd[pipe_out_parent_rd], ::boost::iostreams::close_handle);
			p_out_rdbuf_ = ::boost::make_shared<fd_streambuf_type>(out_rddev);
		}
		if (pipe_err)
		{
			fd_device_type err_rddev(pipefd[pipe_err_parent_rd], ::boost::iostreams::close_handle);
			p_err_rdbuf_ = ::boost::make_shared<fd_streambuf_type>(err_rddev);
		}
#endif // __GNUC__
		if (pipe_in)
		{
			p_ios_ = ::boost::make_shared< ::std::ostream >(p_in_wrbuf_.get());
		}
		if (pipe_out)
		{
			p_ois_ = ::boost::make_shared< ::std::istream >(p_out_rdbuf_.get());
		}
		if (pipe_err)
		{
			p_eis_ = ::boost::make_shared< ::std::istream >(p_err_rdbuf_.get());
		}
		// Write to the child process
//		producer(os);
		// Read the input from the child process
//		consumer(is);

		pid_ = pid;
		status_ = running_process_status;

		if (!async_)
		{
			this->wait();
		}
	}

	/// Waits for the termination of this process.
	public: void wait()
	{
		if (status_ == terminated_process_status
			|| status_ == aborted_process_status
			|| status_ == failed_process_status)
		{
			return;
		}

		this->true_wait(true);

		status_ = terminated_process_status;
	}

	/// Returns the life status of this process.
	public: process_status_category status() const
	{
		return status_;
	}

	/// Stops the execution of this process (without terminating it).
	public: void stop()
	{
		// pre: process must be running
		DCS_ASSERT(status_ == running_process_status,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Cannot stop a process that is not running"));

		this->signal(SIGSTOP);
	}

	/// Resumes the execution of this stopped process.
	public: void resume()
	{
		// pre: process must have been stopped
		DCS_ASSERT(status_ == stopped_process_status,
				   DCS_EXCEPTION_THROW(::std::runtime_error,
									   "Cannot resume a process that has not been stopped"));

		this->signal(SIGCONT);
	}

	/// Terminates the execution of this process
	public: void terminate(bool force = false)
	{
//		// pre: process must be running
//		DCS_ASSERT(status_ == running_process_status,
//				   DCS_EXCEPTION_THROW(::std::runtime_error,
//									   "Cannot stop a process that is not running"));

		if (status_ != running_process_status
			&& status_ != resumed_process_status
			&& status_ != stopped_process_status)
		{
			return;
		}

		this->signal(SIGTERM);
		if (force && this->alive())
		{
			this->signal(SIGKILL);
		}
//		this->true_wait(true);
	}

	/// Tells if this process is still running.
	public: bool alive() const
	{
//		// pre: valid process
//		DCS_ASSERT(pid_ != -1,
//				   DCS_EXCEPTION_THROW(::std::runtime_error,
//									   "Invalid PID"));

		// Quick alive test: return FALSE is the process has already terminated
		if (pid_ == -1
			|| status_ == terminated_process_status
			|| status_ == aborted_process_status
			|| status_ == failed_process_status)
		{
			return false;
		}

		if (this->true_alive())
		{
			return true;
		}

		status_ = terminated_process_status;

		return false;
	}

	/// Sends signal \a sig to this process.
	public: void signal(int sig)
	{
		// pre: sig >= 0
		DCS_ASSERT(sig >= 0,
				   DCS_EXCEPTION_THROW(::std::invalid_argument,
									   "Invalid signal number"));

		if (status_ != running_process_status
			&& status_ != resumed_process_status
			&& status_ != stopped_process_status)
		{
			return;
		}

		// signal 0 has a special meaning: it can be used to check if a process
		// exists without actually sending any signal to it.
		// To send such a signal, use method \c alive.
		if (sig == 0)
		{
			if (!this->true_alive())
			{
				sig_ = 0;
				//status_ = terminated_process_status;
			}
			return;
		}

		if (::kill(pid_, sig) == -1)
		{
			::std::ostringstream oss;
			oss << "Call to kill(2) failed for command '" << cmd_ << "' and signal " << sig << ": " << ::strerror(errno);

			DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
		}

		sig_ = sig;
		bool check_alive(false);
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
			case SIGINT:
			default:
				check_alive = true;
				break;
		}

		if (check_alive)
		{
			const ::std::size_t num_trials(5);
			bool is_alive(true);
			for (::std::size_t trial = 0; trial < num_trials && is_alive; ++trial)
			{
				is_alive = this->true_alive();
				if (is_alive)
				{
					::sleep(zzz_secs_);
				}
			}
			if (!is_alive)
			{
				status_ = aborted_process_status;
			}
			else
			{
				//FIXME: What we can do?
				::std::ostringstream oss;
				oss << "Command '" << cmd_ << "' signaled with signal '" << sig_ << "' is still alive";
				dcs::log_warn(DCS_LOGGING_AT, oss.str());
			}
		}
	}

	/// Waits for the termination of this process.
	private: void true_wait(bool block) const
	{
		int wstatus;

		int opts(WUNTRACED | WCONTINUED);

		if (!block)
		{
			opts |= WNOHANG;
		}

		if (::waitpid(pid_, &wstatus, opts) == -1)
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

	/// Tells if this process is still alive.
	private: bool true_alive() const
	{
		// Make sure to remove a <defunct> process, in order to avoid
		// false-positives (i.e., a call to kill(2) which return -1 with
		// errno==ESRCH due to the presence of a <defunct> process).
		this->true_wait(false);

		// From kill(2) man page:
		// "...If sig is 0, then no signal is sent, but error checking is still
		//  performed; this can be used to check for the existence of a process
		//  ID or process group ID..."

		if (::kill(pid_, 0) == -1)
		{
			// Note: if errno == ESRCH => The pid does not exist (see kill(2))
			if (errno != ESRCH)
			{
				::std::ostringstream oss;
				oss << "Call to kill(2) failed for command '" << cmd_ << "' and signal 0: " << ::strerror(errno);

				DCS_EXCEPTION_THROW(::std::runtime_error, oss.str());
			}

			// Set the status to a termination status. It will possibly changed
			// by some higher-level function (e.g., signal)
			status_ = terminated_process_status;

			return false;
		}

		return true;
	}


	private: ::std::string cmd_; ///< The command path
//	private: ::std::vector< ::std::string > args_; ///< The list of command arguments
	private: bool async_; ///< A \c true value means that the parent does not block to wait for child termination
	private: ::pid_t pid_; ///< The process identifier
	private: mutable process_status_category status_; ///< The current status of this process
	private: mutable int sig_; ///< The last signal sent to this process
	private: mutable int exit_status_; ///< The exit status of this process
	private: ::boost::shared_ptr<fd_streambuf_type> p_in_wrbuf_;
	private: ::boost::shared_ptr<fd_streambuf_type> p_out_rdbuf_;
	private: ::boost::shared_ptr<fd_streambuf_type> p_err_rdbuf_;
	private: ::boost::shared_ptr< ::std::ostream > p_ios_;
	private: ::boost::shared_ptr< ::std::istream > p_ois_;
	private: ::boost::shared_ptr< ::std::istream > p_eis_;
}; // posix_process

}} // Namespace dcs::system


#endif // DCS_SYSTEM_POSIX_PROCESS_HPP
