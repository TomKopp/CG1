cmake_minimum_required(VERSION 2.8)
project(exercise3)

# Use shared libraries
set(BUILD_SHARED_LIBS 1)

# Set the default build type to be release
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()


# Needed cgv packages
find_package(cgv COMPONENTS gui render math
			 PATHS "${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/cmake")

# Needed cgv libraries
find_package(cgv_gl)

# A viewer shall be created
find_package(cgv_viewer)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Create the plugin
cgv_add_module(exercise3
	../../aabb_tree.cxx
	../../aabb_tree.h
	../../box.cxx
	../../box.h
	../../exercise3.cxx
	../../exercise3.h
	../../grid_traverser.cxx
	../../grid_traverser.h
	../../grid_utils.h
	../../halfedge_mesh.cxx
	../../halfedge_mesh.h
	../../halfedge_mesh_handles.h
	../../halfedge_mesh_io.cxx
	../../halfedge_mesh_io.h
	../../halfedge_mesh_iterators.cxx
	../../halfedge_mesh_iterators.h
	../../halfedge_mesh_primitives.cxx
	../../halfedge_mesh_primitives.h
	../../hash_grid.cxx
	../../hash_grid.h
	../../line_segment.cxx
	../../line_segment.h
	../../main.cxx
	../../obj_reader.cxx
	../../obj_reader.h
	../../point.cxx
	../../point.h
	../../triangle.cxx
	../../triangle.h)


# Set include directories
include_directories(
	.
	${cgv_INCLUDE_DIRS}
	${cgv_gl_INCLUDE_DIRS}
)

target_link_libraries(exercise3 ${cgv_LIBRARIES} ${cgv_gl_LIBRARIES})

# Set the viewer working directory to point at the source files
cgv_set_viewer_workdir("../../")

# Add a viewer
cgv_add_viewer(launch-exercise3
	cg_fltk
	crg_stereo_view
	exercise3)


