//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include <cgv/gui/provider.h>
#include <cgv/render/drawable.h>
#include <cgv_gl/gl/gl.h>

#include "halfedge_mesh.h"
#include "aabb_tree.h"
#include "hash_grid.h"
#include "halfedge_mesh_primitives.h"
#include "grid_traverser.h"


using namespace cgv::base;
using namespace cgv::signal;
using namespace cgv::gui;
using namespace cgv::math;
using namespace cgv::render;
using namespace cgv::utils;

class exercise3 : public node, 
				  public drawable, 
				  public provider
{	
	bool show_solid;

	bool show_all_non_empty_cells;


	
	enum Shape { QUAD, CUBE, TETRAHEDRON, DISK, CYLINDER, SPHERE, TORUS, ICOSAEDER, OCTAEDER,ARROW,SADDLE} shp;
	
	enum primitive {VERTICES,EDGES,TRIANGLES} prms;
	
	enum data_structure {AABB_TREE, HASH_GRID} data_struc;

	float max_angle;

	float grid_size;

	bool auto_recompute_normals;

	enum normal_mode {FACE_NORMAL_MODE,VERTEX_NORMAL_MODE,HALFEDGE_NORMAL_MODE} nml_mode;
	
	enum color_mode {FACE_COLOR_MODE,VERTEX_COLOR_MODE} clr_mode;

	vec3 q;
	vec3 p;

	int level;

	halfedge_mesh polymesh;

	aabb_tree<triangle> triangle_tree;
	aabb_tree<point> vertex_tree;
	aabb_tree<line_segment> edge_tree;
	hash_grid<point> vertex_hash_grid;
	hash_grid<line_segment> edge_hash_grid;
	hash_grid<triangle> triangle_hash_grid;
	grid_traverser traverser;
	int traverser_steps;

public:
	// The constructor of this class
	exercise3();
	// Show information in the main window
	void stream_stats(std::ostream& os);
	// Create the gui elements
	void create_gui();
	// Method that is called whenever a gui element was clicked
	void on_set(void* member_ptr);

	void load_mesh();
	
	void store_mesh();

	void create_primitive();
	
	void recompute_normals();

	void update_d();

	void update_q();

	void update_hash_grid_size();

	// Draw the scene
	void draw(context& c);

	void render_solid_mesh();

	void render_tree_level();

	void render_hash_grid();

	void render_grid_traverser();

	
	


};

