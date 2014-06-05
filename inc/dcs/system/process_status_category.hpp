/**
 * \file dcs/system/process_status_category.hpp
 *
 * \brief Possible life statuses of a system process.
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

#ifndef DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP
#define DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP


namespace dcs { namespace system {

enum process_status_category
{
	aborted_process_status, ///< The process has been terminated (e.g., by a signal)
	failed_process_status, ///< The process has terminated due to an error
	resumed_process_status, ///< The process execution has been resumed
	running_process_status, ///< The process is running
	stopped_process_status, ///< The process execution has been stopped (but can be resumed later)
	terminated_process_status, ///< The process execution is done
	undefined_process_status ///< The process is in an undefined state
};

}} // Namespace dcs::system


#endif // DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP
