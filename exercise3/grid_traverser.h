//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include <array>
#include <cgv/math/fvec.h>

typedef cgv::math::fvec<float, 3> vec3;
typedef std::array<int, 3> index3;


class grid_traverser
{
	//ray origin and direction
	vec3 orig,dir;
	//grid cell extents
	vec3 cell_extents;
	//current cell index
	index3 current;

	//student begin
	//you can additional attributes for incremental calculation here
	//student end


public:
	//default constructor
	grid_traverser();

	//constructs a grid traverser for a given ray with origin o, and ray direction d for a grid with cell extents ce
	grid_traverser(const vec3& o, const vec3&d, const vec3 ce);

	//accessor of ray origin
	vec3& origin();

	//const accessor of ray origin
	const vec3& origin() const;

	//accessor of ray direction
	vec3& direction();
	
	//const accessor of ray direction
	const vec3& direction() const;	

	//set cell extents
	void set_cell_extents(const float& grid_size);	

	//init at origin cell
	void init();

	//step to next cell along ray direction
	void operator++(int);

	//return current cell index
	index3 operator*();
	

	

};
