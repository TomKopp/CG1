//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "box.h"
#include "grid_utils.h"
#include "halfedge_mesh.h"

/*
a 3d line segment primitive which can be used with the aabb_tree and the hash_grid data structure
*/
class line_segment
{
	//internal storage of start point of line segment
	vec3 v0;
	//internal storage of end point of line segment
	vec3 v1;
	//internal storage for an edge handle
	//this edge handle can be used to optionally identify the edge in a halfedge mesh data structure instance
	edge_handle h;
	
public:
	//default constructor
	line_segment();

	//constructs a line segment by the two end points v0, v1 without using the edge handle
	line_segment(const vec3& v0, const vec3& v1);

	//construct a line segment from the edge e of the halfedge mesh m
	line_segment(const halfedge_mesh& m,const edge_handle& e);

	//returns an axis aligned bounding box of the line segment
	box compute_bounds() const;
	
	//returns true if the line segment overlaps the given box b
	bool overlaps(const box& b) const;

	//returns the point with smallest distance topoint p which lies on the line segment
	vec3 closest_point(const vec3& p) const;

	//returns the squared distance between point p and the line segment
	float sqr_distance(const vec3& p) const;

	//returns the euclidean distance between point p and the line segment
	float distance(const vec3& p) const;
	
	//returns a reference point  which is on the line segment and is used to sort the primitive in the AABB tree construction
	vec3 reference_point() const;

};

