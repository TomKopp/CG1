//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "point.h"
#include "grid_utils.h"

//default constructor
point::point(){}
	
//construct a point with given point position v0
point::point(const vec3& v0):v0(v0)
{
}

//construct a point from vertex v of giben halfedge mesh m
point::point(const halfedge_mesh &m, const vertex_handle& v):h(v)
{
	v0 = m.position(v);
}
		
//returns axis aligned bounding box of point
box point::compute_bounds() const
{
	box b;	
	b.insert(v0);
		
	return b;
}

//returns true if point overlap with box b
bool point::overlaps(const box& b) const
{
	vec3 lb = b.lower_bound();
	vec3 ub = b.upper_bound();
	return 
		(v0[0] >= lb[0] && v0[0] <= ub[0]&&
		v0[1] >= lb[1] && v0[1] <= ub[1] &&
		v0[2] >= lb[2] && v0[2] <= ub[2]);		   
}

//returns the point position
vec3 point::closest_point(const vec3& p) const
{
	return v0;
}

//returns the squared distance between the query point p and the current point
float point::sqr_distance(const vec3& p) const
{
	vec3 d = p-closest_point(p);
	return dot(d,d);
}

//returns the euclidean distance between the query point p and the current point
float point::distance(const vec3& p) const
{
	return sqrt(sqr_distance(p));
}

//returns a the position of the point as a reference point which is used to sort the primitive in the AABB tree construction
vec3 point::reference_point() const
{
	return v0;
}
