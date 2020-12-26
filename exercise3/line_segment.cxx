//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "line_segment.h"
#include "grid_utils.h"


//default constructor
line_segment::line_segment()
{
}

//constructs a line segment by the two end points v0, v1 without using the edge handle
line_segment::line_segment(const vec3& v0, const vec3& v1):v0(v0),v1(v1)
{
}
	
//construct a line segment from the edge e of the halfedge mesh m
line_segment::line_segment(const halfedge_mesh& m,const edge_handle& e):h(e)
{
	v0 = m.position(m.origin(e));
	v1 = m.position(m.target(e));	
}

//returns an axis aligned bounding box of the line segment
box line_segment::compute_bounds() const
{
	box b;	
	b.insert(v0);
	b.insert(v1);
	return b;
}
	
//returns true if the line segment overlaps the given box b
bool line_segment::overlaps(const box& b) const
{

	box aabb = compute_bounds();

	if(!b.overlaps(aabb))
		return false;
		
	vec3 o = b.center();
	vec3 u1 = v0-o;
	vec3 u2 = v1-o;
		
	vec3 d1 = v1-v0;
	d1.normalize();
		
	float r = b.radius(d1);
	float lb = dot(u1,d1);
	float ub = dot(u2,d1);
	if(lb > ub) 
		std::swap(lb,ub);
	if(lb > r || ub < -r)
		return false;

	vec3 e1(1,0,0);
	vec3 d2= cross(d1,e1);
	r = b.radius(d2);
	lb = dot(u1,d2);
	ub = dot(u2,d2);
	if(lb > ub) 
		std::swap(lb,ub);
	if(!overlap_intervals(-r,r,lb,ub))
		return false;

	vec3 e2(0,1,0);
	vec3 d3 = cross(d1,e2);
	r = b.radius(d3);
	lb = dot(u1,d3);
	ub = dot(u2,d3);
	if(lb > ub) 
		std::swap(lb,ub);
	if(!overlap_intervals(-r,r,lb,ub))
		return false;

	vec3 e3(0,0,1);
	vec3 d4 = cross(d1,e3);
	r = b.radius(d4);
	lb = dot(u1,d4);
	ub = dot(u2,d4);
		
	if(!overlap_intervals(-r,r,lb,ub))
		return false;


	return true;
		
				   
}

//returns the point with smallest distance topoint p which lies on the line segment
vec3 line_segment::closest_point(const vec3& p) const
{
	//student begin
	//the two endpoints of the line segment are v0,v1
	return vec3(0,0,0);
	//student end
}

//returns the squared distance between point p and the line segment
float line_segment::sqr_distance(const vec3& p) const
{
	vec3 d = p-closest_point(p);
	return dot(d,d);
}

//returns the euclidean distance between point p and the line segment
float line_segment::distance(const vec3& p) const
{
	return sqrt(sqr_distance(p));
}
	
//returns a reference point  which is on the line segment and is used to sort the primitive in the AABB tree construction
vec3 line_segment::reference_point() const
{
	return 0.5f*(v0 + v1);
}



