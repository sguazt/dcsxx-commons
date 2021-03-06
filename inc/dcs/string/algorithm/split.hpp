/**
 * \file dcs/string/algorithm/split.hpp
 *
 * \brief String splitting algorithm.
 *
 * \author Marco Guazzone (marco.guazzone@gmail.com)
 *
 * <hr/>
 *
 * Copyright 2021 Marco Guazzone (marco.guazzone@gmail.com)
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

#ifndef DCS_STRING_ALGORITHM_SPLIT_HPP
#define DCS_STRING_ALGORITHM_SPLIT_HPP


#include <boost/algorithm/string/split.hpp>
#include <dcs/macro.hpp>
#include <vector>
#ifndef DCS_MACRO_CXX11
# include <functional> // for std::bind1st() and std::equalt_to()
#endif // DCS_MACRO_CXX11


namespace dcs { namespace string {

using ::boost::algorithm::split;

// Alternative split function (with a different prototype)
std::vector<std::string> split(const std::string& s, char delimiter = ' ')
{
	std::vector<std::string> tokens;

	//std::string token;
	//std::istringstream tokenStream(s);
	//while (std::getline(tokenStream, token, delimiter))
	//{
	//	tokens.push_back(token);
	//}
	//return tokens;

#ifdef DCS_MACRO_CXX11
	// Since C++11 we have lambdas
    return boost::algorithm::split(tokens, s, [&delimiter](char c){return c == delimiter;});
#else
	// Until C++11, lambdas were not available
    return boost::algorithm::split(tokens, s, std::bind1st(std::equal_to<char>(), delimiter));
#endif // DCS_MACRO_CXX11
}

}} // Namespace dcs::string


#endif // DCS_STRING_ALGORITHM_SPLIT_HPP
