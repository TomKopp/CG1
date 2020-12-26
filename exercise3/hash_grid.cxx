//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "hash_grid.h"


void build_hash_grid_from_triangles_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<triangle>& grid)
{
	grid.clear();
	auto fend = m.faces_end();
	for(auto fit = m.faces_begin(); fit != fend; ++fit)
		grid.insert(triangle(m,*fit));
	
}

void build_hash_grid_from_vertices_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<point>& grid)
{
	grid.clear();
	auto vend = m.vertices_end();
	for(auto vit = m.vertices_begin(); vit != vend; ++vit)
		grid.insert(point(m,*vit));
}

void build_hash_grid_from_edges_of_halfedge_mesh(const halfedge_mesh& m, hash_grid<line_segment >& grid)
{
	grid.clear();
	auto eend = m.edges_end();
	for(auto eit = m.edges_begin(); eit != eend; ++eit)
	{
		grid.insert(line_segment(m,*eit));
	}
}
