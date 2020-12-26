//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#include "exercise3.h"

#include "halfedge_mesh_io.h"
#include <cgv/utils/ostream_printf.h>
#include <cgv/gui/file_dialog.h>

using namespace cgv::utils;

// The constructor of this class
exercise3::exercise3():node("Exercise 3") 
{
	show_solid = true;
	show_all_non_empty_cells=true;
	
	auto_recompute_normals = true;
	shp = QUAD;
	data_struc = AABB_TREE;
	clr_mode = FACE_COLOR_MODE;
	nml_mode = HALFEDGE_NORMAL_MODE;
	prms = VERTICES;

	max_angle = 45;
	polymesh = create_tetrahedron();
	recompute_normals();
	polymesh.print_statistics();
	build_aabb_tree_from_vertices_of_halfedge_mesh(polymesh, vertex_tree);
	build_aabb_tree_from_edges_of_halfedge_mesh(polymesh, edge_tree);
	build_aabb_tree_from_triangles_of_halfedge_mesh(polymesh, triangle_tree);
	grid_size =0.05f;
	update_hash_grid_size();
	level = 0;
	
	q[0]=q[1]=q[2]=0;
	p[0]=p[1]=p[2]=0;
	
	traverser_steps=0;
}



// Method that is called whenever a gui element was clicked
void exercise3::on_set(void* member_ptr) {
	post_redraw();
}



// Create the gui elements
void exercise3::create_gui() {

	// Functions for mesh creation
	add_decorator("mesh creation", "heading");
		connect_copy(add_button("load obj from file ")->click,
			rebind(static_cast<exercise3*>(this), &exercise3::load_mesh));
		connect_copy(add_button("store mesh to obj  ")->click,
			rebind(static_cast<exercise3*>(this), &exercise3::store_mesh));
		add_member_control(this, "primitive", shp, "dropdown", 
			"enums='QUAD,CUBE,TETRAHEDRON,DISK,CYLINDER,SPHERE,TORUS,ICOSAEDER,OCTAEDER,ARROW,SADDLE'");

		connect_copy(add_button("create primitive")->click,
			rebind(static_cast<exercise3*>(this), &exercise3::create_primitive));

		add_member_control(this, "render mesh", show_solid, "check");
		add_member_control(this, "data structure", data_struc, "dropdown", "enums='AABB_TREE,HASH_GRID'");
		add_member_control(this, "primitive type", prms, "dropdown", 
			"enums='VERTICES,EDGES,TRIANGLES'");

	// Hash grid functions
	add_decorator("hash grid", "heading");
		connect_copy(add_control("grid size", grid_size, "value_slider", 
			"min=0.01;max=1;ticks=true;log=true")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_hash_grid_size));

		add_member_control(this, "render all non empty cells", show_all_non_empty_cells, "check");

	// Functions to manipulate the ray origin
	add_decorator("ray origin", "heading");
		add_member_control(this, "ox", traverser.origin()[0], "value_slider", 
			"min=-5;max=5;ticks=false");
		add_member_control(this, "oy", traverser.origin()[1], "value_slider", 
			"min=-5;max=5;ticks=false");
		add_member_control(this, "oz", traverser.origin()[2], "value_slider", 
			"min=-5;max=5;ticks=false");

	// Functions to manipulate the ray direction
	add_decorator("ray direction", "heading");
		connect_copy(add_control("dx", traverser.direction()[0], "value_slider", 
			"min=-1;max=1;ticks=false")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_d));
		connect_copy(add_control("dy", traverser.direction()[1], "value_slider", 
			"min=-1;max=1;ticks=false")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_d));
		connect_copy(add_control("dz", traverser.direction()[2], "value_slider", 
			"min=-1;max=1;ticks=false")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_d));

		add_member_control(this, "steps", traverser_steps, "value_slider", 
			"min=0;max=100;ticks=false");

	// Functions related to the AABB tree
	add_decorator("AABB tree", "heading");
		add_member_control(this, "render_tree level", level, "value_slider", 
			"min=0;max=50;ticks=false");

	// Functions to manipulate the query point
	add_decorator("query point", "heading");
		auto qx =add_control("qx", q[0], "value_slider", "min=-1;max=1;ticks=false");
		connect_copy(qx->value_change, rebind(static_cast<exercise3*>(this), &exercise3::update_q));
		connect_copy(add_control("qy", q[1], "value_slider", 
			"min=-1;max=1;ticks=false")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_q));
		connect_copy(add_control("qz", q[2], "value_slider", 
			"min=-1;max=1;ticks=false")->value_change,
			rebind(static_cast<exercise3*>(this), &exercise3::update_q));
}

void exercise3::create_primitive()
{
	
	switch (shp) {
	case QUAD: polymesh = create_quad(); break;
	case CUBE: polymesh = create_cube(); break;
	case TETRAHEDRON: polymesh = create_tetrahedron(); break;
	case DISK: polymesh = create_disk(1,20); break;
	case CYLINDER: polymesh = create_cylinder(0.3f,1,20,10); break;
	case SPHERE:polymesh = create_sphere(1,20,20); break;
	case TORUS: polymesh = create_torus(0.4f,1,20,20); break;
	case ICOSAEDER: polymesh = create_icosaeder(1); break;
	case OCTAEDER: polymesh = create_octaeder(1); break;
	case ARROW: polymesh = create_unit_arrow(); break;
	case SADDLE: polymesh = create_saddle(); break;
	default:
			std::cerr << "unknown shape" << std::endl;
	}
	recompute_normals();
	polymesh.print_statistics();
	polymesh.triangulate();
	polymesh.compute_face_normals();
	polymesh.compute_vertex_normals();
	polymesh.compute_halfedge_normals(max_angle);
	build_aabb_tree_from_vertices_of_halfedge_mesh(polymesh, vertex_tree);
	build_aabb_tree_from_edges_of_halfedge_mesh(polymesh, edge_tree);
	build_aabb_tree_from_triangles_of_halfedge_mesh(polymesh, triangle_tree);
	build_hash_grid_from_vertices_of_halfedge_mesh(polymesh,vertex_hash_grid);
	build_hash_grid_from_edges_of_halfedge_mesh(polymesh,edge_hash_grid);
	build_hash_grid_from_triangles_of_halfedge_mesh(polymesh,triangle_hash_grid);
	post_redraw();

}

void exercise3::load_mesh()
{
	 std::string filename = cgv::gui::file_open_dialog("Load OBJ-Mesh...", "(*.obj)");
	 if(filename !="")
	 {
		
		 load_obj(polymesh,filename);
		 polymesh.auto_center_and_scale();
		 polymesh.triangulate();
		 polymesh.compute_face_normals();
		 polymesh.compute_vertex_normals();
		 polymesh.compute_halfedge_normals(max_angle);
		
		 polymesh.print_statistics();
		
		build_aabb_tree_from_vertices_of_halfedge_mesh(polymesh, vertex_tree);
		build_aabb_tree_from_edges_of_halfedge_mesh(polymesh, edge_tree);
		build_aabb_tree_from_triangles_of_halfedge_mesh(polymesh, triangle_tree);
		build_hash_grid_from_vertices_of_halfedge_mesh(polymesh,vertex_hash_grid);
		build_hash_grid_from_edges_of_halfedge_mesh(polymesh,edge_hash_grid);
		build_hash_grid_from_triangles_of_halfedge_mesh(polymesh,triangle_hash_grid);
	 }
	 post_redraw();
}

void exercise3::store_mesh()
{
	std::string filename = cgv::gui::file_save_dialog("Load OBJ-Mesh...", "(*.obj)");
	 if(filename !="")
	 {
		 store_obj(polymesh,filename);		 
	 }
	 post_redraw();
}

void exercise3::update_d()
{
	traverser.direction().normalize();
	post_redraw();
	update();

}

void exercise3::update_q()
{
	
	switch(prms)
	{
		case VERTICES:
			p = vertex_tree.closest_point(q);
			break;
		case EDGES:
			p = edge_tree.closest_point(q);
			break;
		case TRIANGLES:
			p = triangle_tree.closest_point(q);
			break;
		default:
			break;
	}
	
	post_redraw();
}

void exercise3::update_hash_grid_size()
{
	hash_grid<point> vgrid(grid_size);
	hash_grid<line_segment> egrid(grid_size);
	hash_grid<triangle> tgrid(grid_size);
	traverser.set_cell_extents(grid_size);

	build_hash_grid_from_vertices_of_halfedge_mesh(polymesh,vgrid);
	vertex_hash_grid = vgrid;

	build_hash_grid_from_edges_of_halfedge_mesh(polymesh,egrid);
	edge_hash_grid = egrid;

	build_hash_grid_from_triangles_of_halfedge_mesh(polymesh,tgrid);
	triangle_hash_grid = tgrid;
	post_redraw();
}

void exercise3::recompute_normals()
{
	
	polymesh.compute_face_normals();
	polymesh.compute_vertex_normals();
	polymesh.compute_halfedge_normals(max_angle);
	
	post_redraw();
}


inline void render_box(const box& b)
{
	vec3 lb = b.lower_bound();
	vec3 ub = b.upper_bound();
	glBegin(GL_LINE_LOOP);
	glVertex3f(ub[0],ub[1],ub[2]);
	glVertex3f(lb[0],ub[1],ub[2]);
	glVertex3f(lb[0],lb[1],ub[2]);
	glVertex3f(ub[0],lb[1],ub[2]);
	glEnd();
 
	glBegin(GL_LINE_LOOP);
	glVertex3f(ub[0],ub[1],lb[2]);
	glVertex3f(lb[0],ub[1],lb[2]);
	glVertex3f(lb[0],lb[1],lb[2]);
	glVertex3f(ub[0],lb[1],lb[2]);
	glEnd();
 
	glBegin(GL_LINE_LOOP);
	glVertex3f(ub[0],ub[1],ub[2]);
	glVertex3f(ub[0],lb[1],ub[2]);
	glVertex3f(ub[0],lb[1],lb[2]);
	glVertex3f(ub[0],ub[1],lb[2]);
	glEnd();
 
	glBegin(GL_LINE_LOOP);
	glVertex3f(lb[0],ub[1],ub[2]);
	glVertex3f(lb[0],lb[1],ub[2]);
	glVertex3f(lb[0],lb[1],lb[2]);
	glVertex3f(lb[0],ub[1],lb[2]);
	glEnd();
 
	glBegin(GL_LINE_LOOP);
	glVertex3f(ub[0],ub[1],ub[2]);
	glVertex3f(lb[0],ub[1],ub[2]);
	glVertex3f(lb[0],ub[1],lb[2]);
	glVertex3f(ub[0],ub[1],lb[2]);
	glEnd();
 
	glBegin(GL_LINE_LOOP);
	glVertex3f(ub[0],lb[1],ub[2]);
	glVertex3f(lb[0],lb[1],ub[2]);
	glVertex3f(lb[0],lb[1],lb[2]);
	glVertex3f(ub[0],lb[1],lb[2]);
	glEnd();
	
}


// Draw the scene
void exercise3::draw(context& c) 
{
	
	if(show_solid)
		render_solid_mesh();
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	if(data_struc==AABB_TREE)
		render_tree_level();
	if(data_struc == HASH_GRID)
	{
		if(show_all_non_empty_cells)
			render_hash_grid();
		render_grid_traverser();
	}
	
	
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3fv(p);
	glVertex3fv(q);
	glEnd();
	
}


void exercise3::render_grid_traverser()
{
	glColor3f(0,1,0);
	traverser.init();
	render_box(triangle_hash_grid.cell_bounds(*traverser));
	
	for(int i = 0; i < traverser_steps; i++)
	{
		traverser++;
		index3 idx = *traverser;
	
		switch(prms)
		{
		case VERTICES:
			{
				if(vertex_hash_grid.empty(idx))
					glColor3f(0,0,1);
				else
					glColor3f(1,0,0);
				break;
			}
		case EDGES:
			{
				if(edge_hash_grid.empty(idx))
					glColor3f(0,0,1);
				else
					glColor3f(1,0,0);
				break;
			}
		case TRIANGLES:
			{
				if(triangle_hash_grid.empty(idx))
					glColor3f(0,0,1);
				else
					glColor3f(1,0,0);
				break;
			}
		default:
			break;
		};
		
		render_box(triangle_hash_grid.cell_bounds(idx));
	}
}

template <typename primitive>
void render_tree_node(const typename aabb_tree<primitive>::aabb_node* node, int depth_render, int depth=0)
{
	if(depth_render == depth)
	{	
		render_box( node->get_bounds());		
	}
	else
	{
		if(!node->is_leaf())
		{
			typename aabb_tree<primitive>::aabb_split_node *split = 
			(typename aabb_tree<primitive>::aabb_split_node*)node;
			render_tree_node<primitive>(split->left(), depth_render,depth+1);
			render_tree_node<primitive>(split->right(), depth_render,depth+1);
		}
	}
	
}

void exercise3::render_tree_level()
{
	glDisable(GL_LIGHTING);
	glColor3f(0,1,0);
	switch(prms)
	{
		case VERTICES:
			render_tree_node<point>(vertex_tree.get_root(),level);
			break;
		case EDGES:
			render_tree_node<line_segment>(edge_tree.get_root(),level);
			break;
		case TRIANGLES:
			render_tree_node<triangle>(triangle_tree.get_root(),level);
			break;
		default:
			break;
	}

}	

void exercise3::render_hash_grid()
{
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	switch(prms)
	{
	case VERTICES:
		{
			auto cend = vertex_hash_grid.non_empty_cells_end();
			for(auto cit = vertex_hash_grid.non_empty_cells_begin(); cit != cend; ++cit)
				render_box(vertex_hash_grid.cell_bounds(cit->first));
			
			break;
		}
	case EDGES:
		{
			auto cend = edge_hash_grid.non_empty_cells_end();
			for(auto cit = edge_hash_grid.non_empty_cells_begin(); cit != cend; ++cit)
				render_box(edge_hash_grid.cell_bounds(cit->first));
				break;
		}
	case TRIANGLES:
		{
			auto cend = triangle_hash_grid.non_empty_cells_end();
			for(auto cit = triangle_hash_grid.non_empty_cells_begin(); cit != cend; ++cit)
				render_box(triangle_hash_grid.cell_bounds(cit->first));
		}
	default:
		break;
	}
	
}

void  exercise3::render_solid_mesh() 
{
	
	glDisable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	switch(nml_mode)
	{
	case FACE_NORMAL_MODE:
		{
		face_iterator fend = polymesh.faces_end();
		for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
		{
			glBegin(GL_POLYGON);
			if(nml_mode == FACE_NORMAL_MODE)
				glNormal3fv(polymesh.normal(*fit));
			if(clr_mode == FACE_COLOR_MODE)
				glColor3fv(polymesh.color(*fit));

			face_halfedge_iterator hend = polymesh.halfedges_end(*fit);
			for(face_halfedge_iterator hit = polymesh.halfedges_begin(*fit); hit != hend; ++hit)
			{
			//	glTexCoord2fv(polymesh.texcoord(*hit));
			//	glNormal3fv(polymesh.normal(*hit));
				if(clr_mode == VERTEX_COLOR_MODE)
					glColor3fv(polymesh.color(polymesh.origin(*hit)));
				glVertex3fv(polymesh.position(polymesh.origin(*hit)));
			
			}
			glEnd();
		}
		break;
		}
	case VERTEX_NORMAL_MODE:
		{
			face_iterator fend = polymesh.faces_end();
			for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
			{
				glBegin(GL_POLYGON);
				glColor3fv(polymesh.color(*fit));
				if(clr_mode == FACE_COLOR_MODE)
					glColor3fv(polymesh.color(*fit));

				face_vertex_iterator vend = polymesh.vertices_end(*fit);
				for(face_vertex_iterator vit = polymesh.vertices_begin(*fit); vit != vend; ++vit)
				{
					if(clr_mode == VERTEX_COLOR_MODE)
						glColor3fv(polymesh.color(*vit));
					glNormal3fv(polymesh.normal(*vit));
					glVertex3fv(polymesh.position(*vit));
				}
				glEnd();
			}
			break;
		}
	case HALFEDGE_NORMAL_MODE:
	default:
		{
			face_iterator fend = polymesh.faces_end();
			for(face_iterator fit = polymesh.faces_begin(); fit!= fend; ++fit)
			{
				glBegin(GL_POLYGON);
				if(clr_mode == FACE_COLOR_MODE)
					glColor3fv(polymesh.color(*fit));

				face_halfedge_iterator hend = polymesh.halfedges_end(*fit);
				for(face_halfedge_iterator hit = polymesh.halfedges_begin(*fit); hit != hend; ++hit)
				{
				
					glNormal3fv(polymesh.normal(*hit));
					if(clr_mode == VERTEX_COLOR_MODE)
						glColor3fv(polymesh.color(polymesh.origin(*hit)));
					glVertex3fv(polymesh.position(polymesh.origin(*hit)));
				}
				glEnd();
			}
			break;
		}

	}
}


// Show information in the main window
void exercise3::stream_stats(std::ostream& os) {
	//oprintf(os, "Hello world\n");
}
