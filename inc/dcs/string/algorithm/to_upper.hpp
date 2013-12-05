/**
 * \file dcs/string/algorithm/to_upper.hpp
 *
 * \brief Case-uppering string algorithm.
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

#ifndef DCS_STRING_ALGORITHM_TO_UPPER_HPP
#define DCS_STRING_ALGORITHM_TO_UPPER_HPP


#include <boost/algorithm/string/case_conv.hpp>


namespace dcs { namespace string {

using ::boost::algorithm::to_upper;
using ::boost::algorithm::to_upper_copy;

}} // Namespace dcs::string


#endif // DCS_STRING_ALGORITHM_TO_UPPER_HPP
