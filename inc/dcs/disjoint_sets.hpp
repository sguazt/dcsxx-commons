/**
 * \file dcs/disjoint_sets.hpp
 *
 * \brief Implementation of the disjoint-sets (union-find) data structure.
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

#ifndef DCS_DISJOINT_SETS_HPP
#define DCS_DISJOINT_SETS_HPP


#include <boost/function.hpp>
#include <cstddef>
#include <map>
#include <vector>


namespace dcs {

namespace detail { namespace /*<unnamed>*/ {

template <typename T,typename ValueT>
struct identity_hasher
{
	ValueT operator()(T const& t) { return t; }
}; // identity


template <class ParentPA, class Vertex>
Vertex find_representative_with_path_halving(ParentPA p, Vertex v)
{
  Vertex parent = p[v];
  Vertex grandparent = p[parent];
  while (parent != grandparent) {
    p[v] = grandparent;
    v =  grandparent;
    parent = p[v];
    grandparent = p[parent];
  }
  return parent;
}


template <class ParentPA, class Vertex>
Vertex find_representative_with_full_compression(ParentPA parent, Vertex v)
{
  Vertex old = v;
  Vertex ancestor = parent[v];
  while (ancestor != v) {
    v = ancestor;
    ancestor = parent[v];
  }
  v = parent[old];
  while (ancestor != v) {
    parent[old] = ancestor;
    old = v;
    v = parent[old];
  }
  return ancestor;
}

}} // Namespace detail::<unnamed>


struct find_with_path_halving
{
	template <class ParentPA, class Vertex>
	Vertex operator()(ParentPA p, Vertex v)
	{
		return detail::find_representative_with_path_halving(p, v);
	}
};

struct find_with_full_path_compression
{
	template <class ParentPA, class Vertex>
	Vertex operator()(ParentPA p, Vertex v)
	{
		return detail::find_representative_with_full_compression(p, v);
	}
};


template <typename ElementT, typename FinderT = find_with_full_path_compression>
class disjoint_sets
{
	public: typedef ElementT element_type;
	public: typedef ::std::size_t size_type;
	public: typedef size_type (*hash_function_type)(element_type const&);
	public: typedef FinderT finder_type;


	public: disjoint_sets()
	: hash_(detail::identity_hasher<element_type,size_type>())
	{
	}

	public: void make_set(element_type const& e)
	{
		size_type sid(id_map_.size());
		id_map_[hash_(e)] = sid;
		inv_id_map_[sid] = e;
		ranks_.push_back(0);
		parents_.push_back(sid);

	}

	public: size_type find_set(element_type const& e)
	{
		return finder_(parents_, id_map_.at(hash_(e)));
	}

	public: void link_sets(element_type const& e1, element_type const& e2)
	{
		size_type sid1 = find_set(e1);
		size_type sid2 = find_set(e2);
		if (sid1 == sid2)
		{
			return;
		}

		// e1 and e1 are not already in same set. Merge them.
		if (ranks_[sid1] > ranks_[sid2])
		{
			parents_[sid2] = sid1;
		}
		else
		{
			parents_[sid1] = sid2;
			if (ranks_[sid1] == ranks_[sid2])
			{
				ranks_[sid2] += 1;
			}
		}
	}

	public: void union_sets(element_type const& e1, element_type const& e2)
	{
		link_sets(find_set(e1), find_set(e2));
	}


	private: ::std::vector<size_type> ranks_;
	private: ::std::vector<size_type> parents_;
	private: ::std::map<size_type,size_type> id_map_;
	private: ::std::map<size_type,element_type> inv_id_map_;
	private: ::boost::function<size_type(element_type const&)> hash_;
	private: finder_type finder_;
}; // disjoint_sets

} // Namespace dcs

#endif // DCS_DISJOINT_SETS_HPP
