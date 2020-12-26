//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include <cgv/math/fvec.h>



typedef cgv::math::fvec<float, 3> vec3;


class box
{
	//internal storage for lower and upper corner points of the box
	std::pair<vec3,vec3> bounds;

public:

	//creates an empty box like the method clear
	box();

	//construct a box with the gven lower and upper corner points
	box(const vec3& lbound, const vec3& ubound);

	//returns the corner point which is the lower bound of the box in all dimensions
	vec3& lower_bound();

	//returns the corner point which is the lower bound of the box in all dimensions
	const vec3& lower_bound() const;

	//returns the corner point which is the upper bound of the box in all dimensions
	vec3& upper_bound();

	//returns the corner point which is the upper bound of the box in all dimensions
	const vec3& upper_bound() const;
	
	//returns a vector containing the extents of the box in all dimensions
	vec3 extents() const;

	//returns a vector containing the extents of the box in all dimensions divided by 2
	vec3 half_extents() const;

	//returns the center of the box
	vec3 center() const;

	//returns the surface area of the box
	float surface_area() const;

	//returns the volume of the box
	float volume() const;

	//returns the box radius for a given direction vector a 
	//if the box is centered at the origin 
	//then the projection of the box on direction a is contained within  the interval [-r,r]
	float radius(const vec3& a) const;

	//returns true if the box b overlaps with the current one
	bool overlaps(const box& b) const;

	//returns true if the point p is inside this box
	bool is_inside(const vec3& p) const;

	//returns  true if box b is inside this box
	bool is_inside(const box& b) const;
	
	//creates a box which goes from [+infinity,- infinity] in al dimensions
	void clear();
	
	//enlarges the box such that the point p is inside afterwards
	void insert(const vec3& p);

	//enlarges the box such that box b is inside afterwards
	void insert(const box& b);

	//returns the point on or inside the box with the smallest distance to p 
	vec3 closest_point(const vec3& p) const;

	//returns the squared distance between p and the box  
	float sqr_distance(const vec3& p) const;

	//returns the euclidean distance between p and the box 
	float distance(const vec3& p) const;

};
