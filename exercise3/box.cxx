//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "box.h"
#include "grid_utils.h"
#include <limits>


//creates an empty box like the method clear
box::box()
{
	clear();
}

//construct a box with the gven lower and upper corner points
box::box(const vec3& lbound, const vec3& ubound)
{
	bounds = std::make_pair(lbound,ubound);
}

//returns the corner point which is the lower bound of the box in all dimensions
vec3& box::lower_bound()
{
	return bounds.first;
}

//returns the corner point which is the lower bound of the box in all dimensions
const vec3& box::lower_bound() const
{
	return bounds.first;
}

//returns the corner point which is the upper bound of the box in all dimensions
vec3& box::upper_bound()
{
	return bounds.second;
}

//returns the corner point which is the upper bound of the box in all dimensions
const vec3& box::upper_bound() const
{
	return bounds.second;
}

//returns a vector containing the extents of the box in all dimensions
vec3 box::extents() const
{
	return upper_bound()-lower_bound();
}

//returns a vector containing the extents of the box in all dimensions divided by 2
vec3 box::half_extents() const
{
	return extents()/2.0f;
}
//returns the center of the box
vec3 box::center() const
{
	return (lower_bound()+upper_bound())/2.0f;
}

//returns the surface area of the box
float box::surface_area() const
{
	vec3 e = extents();
	return 2.0f*(e[0]*e[1] + e[1]*e[2] + e[0]*e[2]);   
}

//returns the volume of the box
float box::volume() const
{
	vec3 e = extents();
	return e[0] + e[1]+ e[2];
}

//returns the box radius for a given direction vector a 
//if the box is centered at the origin 
//then the projection of the box on direction a is contained within  the interval [-r,r]
float box::radius(const vec3& a) const
{
	vec3 h = half_extents();
	return h[0]*std::abs(a[0]) + h[1]*std::abs(a[1]) + h[2]*std::abs(a[2]); 	
}

//returns true if the box b overlaps with the current one
bool box:: overlaps(const box& b) const
{
	vec3 lb1 = lower_bound();
	vec3 ub1 = upper_bound();

	vec3 lb2 = b.lower_bound();
	vec3 ub2 = b.upper_bound();
		
	if(!overlap_intervals(lb1[0], ub1[0],lb2[0], ub2[0]))
		return false;
	if(!overlap_intervals(lb1[1], ub1[1],lb2[1], ub2[1]))
		return false;
	if(!overlap_intervals(lb1[2], ub1[2],lb2[2], ub2[2]))
		return false;
		
	return true;
}

//returns true if the point p is inside this box
bool box::is_inside(const vec3& p) const
{
	const vec3& lbound = lower_bound();
	const vec3& ubound = upper_bound();
	if(p[0] < lbound[0] || p[0] > ubound[0] ||
		p[1] < lbound[1] || p[1] > ubound[1] ||
		p[2] < lbound[2] || p[2] > ubound[2])
		return false;
	return true;		
}

//returns  true if box b is inside this box
bool box::is_inside(const box& b) const
{
	return is_inside(b.lower_bound()) && is_inside(b.upper_bound());
}

//creates a box which goes from [+infinity,- infinity] in al dimensions
void box::clear()
{
	const float infty = std::numeric_limits<float>::infinity();
	const vec3 vec_infty = vec3(infty,infty,infty);
	bounds = std::make_pair(vec_infty,-vec_infty);	
}
 
//enlarges the box such that the point p is inside afterwards
void box::insert(const vec3& p)
{
	vec3& lbound = lower_bound();
	vec3& ubound = upper_bound();
	lbound[0] = (std::min)(p[0],lbound[0]);
	lbound[1] = (std::min)(p[1],lbound[1]);
	lbound[2] = (std::min)(p[2],lbound[2]);
	ubound[0] = (std::max)(p[0],ubound[0]);
	ubound[1] = (std::max)(p[1],ubound[1]);
	ubound[2] = (std::max)(p[2],ubound[2]);
}

//enlarges the box such that box b is inside afterwards
void box::insert(const box& b)
{
	insert(b.lower_bound());
	insert(b.upper_bound());
}

//returns the point on or inside the box with the smallest distance to p 
vec3 box::closest_point(const vec3& p) const
{
	vec3 q;
	const vec3& lbound = lower_bound();
	const vec3& ubound = upper_bound();
		
	q[0] = std::min(std::max(p[0],lbound[0]),ubound[0]);
	q[1] = std::min(std::max(p[1],lbound[1]),ubound[1]);
	q[2] = std::min(std::max(p[2],lbound[2]),ubound[2]);
			
	return q;
}

//returns the squared distance between p and the box  
float box::sqr_distance(const vec3& p) const
{
	vec3 d = p-closest_point(p);
	return dot(d,d);
}

//returns the euclidean distance between p and the box 
float box::distance(const vec3& p) const
{
	return sqrt(sqr_distance(p));
}


