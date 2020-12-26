//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include <unordered_map>
#include <array>
#include <vector>
#include "box.h"
#include "grid_utils.h"
#include "triangle.h"
#include "point.h"
#include "line_segment.h"

template <typename primitive >
class hash_grid 
{
public:
	//integer index type
	typedef std::array<int,3> index3;
	//primitive list type stored in each non empty cell
	typedef std::vector<primitive> primitive_list;
	//type of a primitive iterator
	typedef typename primitive_list::iterator primitive_list_iterator;
	//type of a const primitive iterator
	typedef typename primitive_list::const_iterator const_primitive_list_iterator;
	//hash function
	struct grid_hash_func
	{
		size_t operator()(const index3 &idx ) const
		{
			static const int p1 = 131071;
			static const int p2 = 524287;
			static const int p3 = 8191;
			return idx[0]*p1 + idx[1]*p2 + idx[2]*p3;
		}
	};
	//type of internal hash map
	typedef std::unordered_map<index3,primitive_list,grid_hash_func> cell_hash_map_type;
	//non empty cell iterator type
	typedef typename std::unordered_map<index3,primitive_list,grid_hash_func>::iterator non_empty_cell_iterator;
	//const non empty cell iterator type
	typedef typename std::unordered_map<index3,primitive_list,grid_hash_func>::const_iterator const_non_empty_cell_iterator;
	
private:
	//internal hash map storing the data of each non empty grid cell
	//it is a map with a 3 dimensitonsl cell index index as a key and a primitive_list as value type
	cell_hash_map_type cell_hash_map;
	//internal extents of a cell
	vec3 cell_extents;

public:
	//constructor for hash grid with uniform cell extent
	//initial size is used to preallocate memory for the internal unordered map
	hash_grid(const float cell_extent=0.01,const int initial_size=1): cell_hash_map(initial_size)
	{		
		cell_extents[0] =cell_extents[1] =cell_extents[2] = cell_extent;
	}

	//constructor for  hash grid with non uniform cell extents
	//initial size is used to preallocate memory for the internal unordered map
	hash_grid(const vec3& cell_extents,const int initial_size): cell_hash_map(initial_size),cell_extents(cell_extents)
	{	
	}

	//resize hash map with at least count buckets
	void rehash(const int count)
	{
		cell_hash_map.rehash(count);
	}

	
	//converts a position to a grid index 
	index3 pos_2_index(const vec3& pos) const
	{	
		return position_2_cell_index(pos, cell_extents) ;
	}

	//return the center position of a cell specified by its cell key
	vec3 cell_center(const index3& idx) const
	{
		vec3 p;
		for(int d = 0; d < 3; ++d)
			p[d] = (idx[d] + 0.5f)*cell_extents[d];
		
		return p;
	}

	//return the center position of a cell containing give position pos
	vec3 cell_center(const vec3& pos) const
	{
		return cell_center(pos_2_index(pos));
	}
	
	//return the min corner position of a cell specified by its cell key
	vec3 cell_min_position(const index3& key) const
	{
		vec3 p;
		for(int d = 0; d < 3; ++d)
			p[d] = key[d]*cell_extents[d];
		
		return p;
	}

	//return the min corner position of a cell containing the point pos
	vec3 cell_min_position(const vec3& pos) const
	{
		return cell_min_position(pos_2_index(pos));
	}

	//return the max corner position of a cell specified by its cell key
	vec3 cell_max_position(const index3& idx) const 
	{
		vec3 p;
		for(int d = 0; d < 3; ++d)
			p[d] = (idx[d]+1)*cell_extents[d];
		
		return p;
	}

	//return the max corner position of a cell containing the point pos
	vec3 cell_max_position(const vec3& pos) const
	{
		return cell_max_position(pos_2_index(pos));
	}

	//returns bounding box of cell with index idx
	box cell_bounds(const index3& idx) const
	{
		return box(cell_min_position(idx),cell_max_position(idx));		
	}
	
	//returns the  bounding box of cell containing the point pos
	box cell_bounds(const vec3& pos) const
	{
		index3 idx = pos_2_index(pos);
		return box(cell_min_position(idx),cell_max_position(idx));		
	}
	
	//returns the extents of a grid cell
	vec3 get_cell_extents() const
	{
		return cell_extents;
	}

	//returns volume of a grid cell
	float cell_volume() const
	{
		float vol = 0;
		for(int d = 0; d < 3; ++d)
			vol *= cell_extents[d];
		return vol;
	}
	
	//removes all non empty cells from the hash grid
	bool empty(const index3& idx) const
	{
		auto it = cell_hash_map.find(idx);
		if(it == cell_hash_map.end())
			return true;
		return false;		
	}


	//inserts primitive p into all overlapping hash grid cells
	//the primitive must implement a method "box compute_bounds()" which returns an axis aligned bounding box
	//and a method "bool overlaps(const box& b)" which returns true if the primitive overlaps the given box b
	void insert(const primitive& p)
	{
		box b = p.compute_bounds();
		vec3 lb = b.lower_bound();
		vec3 ub = b.upper_bound();
		if(lb[0] > ub[0])
			return;
		if(lb[1] > ub[1])
			return;
		if(lb[2] > ub[2])
			return;
		index3 lb_idx = pos_2_index(lb);
		index3 ub_idx = pos_2_index(ub);

		
		
		index3 idx;
		for(idx[0] = lb_idx[0]; idx[0] <=ub_idx[0]; ++idx[0])
			for(idx[1] = lb_idx[1]; idx[1] <=ub_idx[1]; ++idx[1])
				for(idx[2] = lb_idx[2]; idx[2] <=ub_idx[2]; ++idx[2])
					if(p.overlaps(cell_bounds(idx)))
						cell_hash_map[idx].push_back(p);

	}
	

	//remove all cells from hash grid
	void clear()
	{
		cell_hash_map.clear();
	}
	
	//returns true if hashgrid contains no cells
	bool empty() const
	{
		return cell_hash_map.empty();
	}

	//returns the number of non empty cells
	size_t num_cells() const
	{
		return cell_hash_map.size();
	}

	//iterator pointing on the  first cell within the hashgrid
	non_empty_cell_iterator non_empty_cells_begin()
	{
		return cell_hash_map.begin();
	}

	//iterator pointing behind the last cell within the hashgrid
	non_empty_cell_iterator non_empty_cells_end()
	{
		return cell_hash_map.end();
	}

	//const iterator pointing on the first cell within the hashgrid
	const_non_empty_cell_iterator non_empty_cells_begin() const
	{
		return cell_hash_map.begin();
	}

	//const iterator pointing behind the last cell within the hashgrid
	const_non_empty_cell_iterator non_empty_cells_end() const
	{
		return cell_hash_map.end();
	}

	//iterator pointing on the first primitive stored in the cell idx
	primitive_list_iterator primitives_begin(const index3& idx)
	{
		assert(!empty(idx));
		return cell_hash_map[idx].begin();
	}

	//iterator pointing after the last primitive stored in the cell idx
	primitive_list_iterator primitives_end(const index3& idx)
	{
		assert(!empty(idx));
		return cell_hash_map[idx].end();
	}

	//const iterator pointing on the first primitive stored in the cell idx
	const_primitive_list_iterator primitives_begin(const index3& idx) const
	{
		assert(!empty(idx));
		return cell_hash_map[idx].cbegin();
	}

	//const iterator pointing after the last primitive stored in the cell idx
	const_primitive_list_iterator primitives_end(const index3& idx) const
	{
		assert(!empty(idx));
		return cell_hash_map[idx].cend();
	}
};

//helper function to construct a hashgrid data structure from the triangle faces of the halfedge mesh m
void build_hash_grid_from_triangles_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<triangle>& grid);
//helper function to construct a hashgrid data structure from the vertices of the halfedge mesh m
void build_hash_grid_from_vertices_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<point>& grid);
//helper function to construct a hashgrid data structure from the edges of the halfedge mesh m
void build_hash_grid_from_edges_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<line_segment >& grid);




