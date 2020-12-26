//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "aabb_tree.h"


void build_aabb_tree_from_triangles_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<triangle >& tree)
{
	assert(m.is_triangle_mesh());
	tree.clear();
	auto fend = m.faces_end();
	for(auto fit = m.faces_begin(); fit != fend; ++fit) 
		tree.insert(triangle(m,*fit));
	
	tree.complete();
}

void build_aabb_tree_from_vertices_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<point>& tree)
{
	tree.clear();
	auto vend = m.vertices_end();
	for(auto vit = m.vertices_begin(); vit != vend; ++vit)
		tree.insert(point(m,*vit));
	
	tree.complete();
}

void build_aabb_tree_from_edges_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<line_segment>& tree)
{
	tree.clear();
	auto eend = m.edges_end();
	for(auto eit = m.edges_begin(); eit != eend; ++eit)	
		tree.insert(line_segment(m,*eit));
	
	tree.complete();
}
