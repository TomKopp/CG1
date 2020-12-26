//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "halfedge_mesh.h"
#include "box.h"


class point
{
	//internal storage of point position
	vec3 v0;
	//internal storage for a vertex handle
	//this vertex handle can be used to optionally identify the vertex in a halfedge mesh data structure instance
	vertex_handle h;
	

public:
	
	//default constructor
	point();
	
	//construct a point with given point position v0
	point(const vec3& v0);

	//construct a point from vertex v of giben halfedge mesh m
	point(const halfedge_mesh &m, const vertex_handle& v);
		
	//returns axis aligned bounding box of point
	box compute_bounds() const;

	//returns true if point overlap with box b
	bool overlaps(const box& b) const;

	//returns the point position
	vec3 closest_point(const vec3& p) const;

	//returns the squared distance between the query point p and the current point
	float sqr_distance(const vec3& p) const;

	//returns the euclidean distance between the query point p and the current point
	float distance(const vec3& p) const;

	//returns a the position of the point as a reference point which is used to sort the primitive in the AABB tree construction
	vec3 reference_point() const;
};





