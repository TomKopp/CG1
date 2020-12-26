//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "triangle.h"
#include "grid_utils.h"
#include <tuple>


//default constructor
triangle::triangle()
{
}
//constructs a triangle using the vertex positions v0,v1 and v2
triangle::triangle(const vec3& v0, const vec3& v1,const vec3& v2): v0(v0),v1(v1),v2(v2)
{
}
//constructs a triangle from  the face f of the given halfedge mesh m
triangle::triangle(const halfedge_mesh&m, const face_handle& f):h(f)
{
	assert(m.is_triangle(f));
	
	halfedge_handle he = m.halfedge(f);
	v0 = m.position(m.origin(he));
	he = m.next(he);
	v1 = m.position(m.origin(he));
	he = m.next(he);
	v2 = m.position(m.origin(he));
}
//returns the smallest axis aligned bounding box of the triangle
box triangle::compute_bounds() const
{
	//student begin
	box b;	
	
	return b;
	//student end
}

std::pair<float,float> interval(const vec3 u0, const vec3& u1, const vec3& u2, const vec3& dir) 
{
	float pmin,pmax;
	pmin=pmax= dot(u0,dir);
	float p1 = dot(u1,dir);
	pmin = std::min(pmin,p1);
	pmax = std::max(pmax,p1);
	float p2 = dot(u2, dir);
	pmin = std::min(pmin,p2);
	pmax = std::max(pmax,p2);
	return std::make_pair(pmin,pmax);		
}
	
bool overlaps_on_dir(const box& b,const vec3& u0,const vec3& u1, const vec3& u2, const vec3& dir) 
{
	float lb,ub;
	std::tie(lb,ub) = interval(u0,u1,u2,dir);
	float r = b.radius(dir);
	return overlap_intervals(-r,r,lb,ub);
}
//returns true if the triangle overlaps the given box b
bool triangle::overlaps(const box& b) const
{
	//student begin
	//carefully look at the interface of the box class their might be alot of useful helper functions
	return false;
	//student end
	
}
//returns the barycentric coordinates of the point with thesmallest distance to point p which lies on the triangle
void triangle::closest_point_barycentric(const vec3& p, float& l0, float& l1, float& l2) const
{
	vec3 edge0 = v1 - v0;
	vec3 edge1 = v2 - v0;
	vec3 v = v0 - p;

	float a = dot(edge0, edge0 );
	float b = dot(edge0, edge1 );
	float c = dot(edge1, edge1 );
	float d = dot(edge0, v );
	float e = dot(edge1, v );

	float det = a*c - b*b;
	float s = b*e - c*d;
	float t = b*d - a*e;

	if ( s + t < det )
	{
		if ( s < 0.f )
		{
			if ( t < 0.f )
			{
				if ( d < 0.f )
				{
					s=-d/a;
					s=std::min(std::max(s,0.0f),1.0f);
					t = 0.f;
				}
				else
				{
					s = 0.f;
					t = -e/c;
					t = std::min(std::max(t,0.0f),1.0f);
                 
				}
			}
			else
			{
				s = 0.f;
				t = -e/c;
				t = std::min(std::max(t,0.0f),1.0f);
			}
		}
		else if ( t < 0.f )
		{
			s =  -d/a;
			s=std::min(std::max(s,0.0f),1.0f);
			t = 0.f;
		}
		else
		{
			float invDet = 1.f / det;
			s *= invDet;
			t *= invDet;
		}
	}
	else
	{
		if ( s < 0.f )
		{
			float tmp0 = b+d;
			float tmp1 = c+e;
			if ( tmp1 > tmp0 )
			{
				float numer = tmp1 - tmp0;
				float denom = a-2*b+c;
				s = numer/denom;
				s=std::min(std::max(s,0.0f),1.0f);
				t = 1-s;
			}
			else
			{
				t = -e/c;
				t=std::min(std::max(t,0.0f),1.0f);
				s = 0.f;
			}
		}
		else if ( t < 0.f )
		{
			if ( a+d > b+e )
			{
				float numer = c+e-b-d;
				float denom = a-2*b+c;
				s = numer/denom;
				s=std::min(std::max(s,0.0f),1.0f);
               
				t = 1-s;
			}
			else
			{
				s =  -e/c;
				s=std::min(std::max(s,0.0f),1.0f);
				t = 0.f;
			}
		}
		else
		{
			float numer = c+e-b-d;
			float denom = a-2*b+c;

			s =  numer/denom;
			s=std::min(std::max(s,0.0f),1.0f);
			t = 1.f - s;
		}
	}
	l0 = 1-s-t;
	l1 = s;
	l2 = t;
}
//returns the point with smallest distance to point p which lies on the triangle
vec3 triangle::closest_point(const vec3& p) const
{
	float l0,l1,l2;
	closest_point_barycentric(p,l0,l1,l2);
	return l0*v0 + l1*v1 +l2* v2;

}
//returns the squared distance between point p and the triangle
float triangle::sqr_distance(const vec3& p) const
{
	vec3 d = p-closest_point(p);
	return dot(d,d);
}
//returns the euclidean distance between point p and the triangle
float triangle::distance(const vec3& p) const
{
	return sqrt(sqr_distance(p));
}
//returns a reference point  which is on the triangle and is used to sort the primitive in the AABB tree construction
vec3 triangle::reference_point() const
{
	return (v0+v1+v2)/3.0f;
}



