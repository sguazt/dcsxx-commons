/**
 * \file dcs/system/process_status_category.hpp
 *
 * \brief Possible life statuses of a system process.
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
 * along with dcsxx-commons. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP
#define DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP


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


#endif // DCS_SYSTEM_PROCESS_STATUS_CATEGORY_HPP
