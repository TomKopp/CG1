//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "grid_traverser.h"
#include "grid_utils.h"



grid_traverser::grid_traverser():orig(0,0,0),dir(1,0,0),cell_extents(0.1f,0.1f,0.1f)
{
	init();
}

grid_traverser::grid_traverser(const vec3& o, const vec3&d, const vec3 cell_extents):orig(o),dir(d),cell_extents(cell_extents)
{
	dir.normalize();
	init();
}

vec3& grid_traverser::origin()
{
	return orig;
}
const vec3& grid_traverser::origin() const
{
	return orig;
}

vec3& grid_traverser::direction()
{
	return dir;
}

const vec3& grid_traverser::direction() const
{
	return dir;
}

void grid_traverser::set_cell_extents(const float& grid_size)
{
	cell_extents.set(grid_size,grid_size,grid_size);
	init();
}

void grid_traverser::init()
{
	current = position_2_cell_index(orig,cell_extents);
	//student begin
	//you can add some precalculation code here
	//student end
}

void grid_traverser::operator++(int)
{
	
	//student begin
	//traverse one step along the ray
	//update the cell index stored in attribute "current"
	//student end;
		
}

index3 grid_traverser::operator*()
{
	return current;
}

	
