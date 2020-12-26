//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once
#include "box.h"
#include "halfedge_mesh.h"


/*
a triangle primitive which can be used with the aabb_tree and the hash_grid data structure
*/
class triangle
{
	//internal storage of the first vertex position of the triangle
	vec3 v0;
	//internal storage of the second vertex position of the triangle
	vec3 v1;
	//internal storage of the third vertex position of the triangle
	vec3 v2;
	//internal storage of the optional face handle to identify the originating face in a half edge mesh instance
	face_handle h;

public:

	//default constructor
	triangle();
	//constructs a triangle using the vertex positions v0,v1 and v2
	triangle(const vec3& v0, const vec3& v1,const vec3& v2);
	//constructs a triangle from  the face f of the given halfedge mesh m
	triangle(const halfedge_mesh&m, const face_handle& f);
	//returns the axis aligned bounding box of the triangle
	box compute_bounds() const;
	//returns true if the triangle overlaps the given box b
	bool overlaps(const box& b) const;
	//returns the barycentric coordinates of the point with thesmallest distance to point p which lies on the triangle
	void closest_point_barycentric(const vec3& p, float& l0, float& l1, float& l2) const;
	//returns the point with smallest distance to point p which lies on the triangle
	vec3 closest_point(const vec3& p) const;
	//returns the squared distance between point p and the triangle
	float sqr_distance(const vec3& p) const;
	//returns the euclidean distance between point p and the triangle
	float distance(const vec3& p) const;
	//returns a reference point  which is on the triangle and is used to sort the primitive in the AABB tree construction
	vec3 reference_point() const;

};

