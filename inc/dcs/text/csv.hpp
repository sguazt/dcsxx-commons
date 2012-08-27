/**
 * \file dcs/text/csv.hpp
 *
 * \brief CSV format reader and writer.
 *
 * Copyright (C) 2009-2010  Distributed Computing System (DCS) Group, Computer
 * Science Department - University of Piemonte Orientale, Alessandria (Italy).
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
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */

#ifndef DCS_TEXT_CSV_HPP
#define DCS_TEXT_CSV_HPP


#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace dcs { namespace text {

using ::std::size_t;


/**
 * \brief CSV format reader.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
class csv_reader
{
	public: csv_reader(std::istream& is, char field_sep=',', char line_sep='\n', char comment='#')
		: is_(is),
		  field_sep_(field_sep),
		  line_sep_(line_sep),
		  comment_(comment)
	{
		  // empty
	}


	public: std::vector<std::string> read_line()
	{
		std::vector<std::string> fields;

		std::string line;

		while (is_.good() && std::getline(is_, line, line_sep_))
		{
			if (!line.empty() && line.find_first_of(comment_) == line.npos)
			{
				std::istringstream iss(line);
				std::string field;
				//size_t n_fields = 0;

				while (std::getline(iss, field, field_sep_))
				{
					fields.push_back(field);
					//++n_fields;
				}

				//++n_lines_;
				//if (n_fields > n_fields_)
				//{
				//	n_fields_ = n_fields;
				//}

				break;
			}
		}

		return fields;
	}


	public: std::vector< std::vector<std::string> > read_all()
	{
		std::vector< std::vector<std::string> > lines;
		std::string line;
		size_t n_lines = 0;

		while (is_.good() && std::getline(is_, line, line_sep_))
		{
			if (line.find_first_of(comment_) == line.npos)
			{
				std::istringstream iss(line);
				std::string field;
				//size_t n_fields = 0;

				while (std::getline(iss, field, field_sep_))
				{
					lines[n_lines].push_back(field);
					//++n_fields;
				}

				++n_lines;
				//++n_lines_;
				//if (n_fields > n_fields_)
				//{
				//	n_fields_ = n_fields;
				//}
			}
		}

		return lines;
	}


	private: std::istream& is_;
	private: char field_sep_;
	private: char line_sep_;
	private: char comment_;
};


/**
 * \brief CSV format writer.
 *
 * \author Marco Guazzone, &lt;marco.guazzone@mfn.unipmn.it&gt;
 */
class csv_writer
{
	public: csv_writer(std::ostream& os, char field_sep=',', char line_sep='\n', char comment='#')
		: os_(os),
		  field_sep_(field_sep),
		  line_sep_(line_sep),
		  comment_(comment)
	{
		// empty
	}


	public: void write_all(std::ostream& os, std::vector< std::vector<std::string> > const& lines)
	{
		typedef std::vector< std::vector<std::string> >::const_iterator line_iterator;
		typedef std::vector<std::string>::const_iterator field_iterator;

		line_iterator line_end(lines.end());

		for (
			line_iterator line_it = lines.begin();
			line_it != line_end;
			++line_it
		) {
			field_iterator field_end(line_it->end());

			for (
				field_iterator field_it = line_it->begin();
				field_it != field_end;
				++field_it
			) {
				os << *field_it;
				if (field_it != field_end)
				{
					os << field_sep_;
				}
			}
			os << line_sep_;
		}
	}


	public: void write_line(std::ostream& os, std::vector<std::string> const& line)
	{
		typedef std::vector<std::string>::const_iterator field_iterator;

		field_iterator field_end(line.end());

		for (
			field_iterator field_it = line.begin();
			field_it != field_end;
			++field_it
		) {
			os << *field_it;
			if (field_it != field_end)
			{
				os << field_sep_;
			}
		}
		os << line_sep_;
	}


	private: std::ostream& os_;
	private: char field_sep_;
	private: char line_sep_;
	private: char comment_;
};


std::istream& read_csv(std::istream& is, std::vector< std::vector<std::string> >& data, char field_sep=',', char line_sep='\n', char comment='#')
{
	csv_reader rd(is, field_sep, line_sep, comment);
	data = rd.read_all();
	return is;
}

std::istream& read_csv_line(std::istream& is, std::vector<std::string>& data, char field_sep=',', char line_sep='\n', char comment='#')
{
	csv_reader rd(is, field_sep, line_sep, comment);
	data = rd.read_line();
	return is;
}

}} // Namespace dcs::text


#endif //DCS_TEXT_CSV_HPP
