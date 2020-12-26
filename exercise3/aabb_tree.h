//
// This source code is property of the Computer Graphics and Visualization 
// chair of the TU Dresden. Do not distribute! 
// Copyright (C) 2015-2017 CGV TU Dresden - All Rights Reserved
//
#pragma once

#include "box.h"
#include <queue>
#include <utility>

#include "triangle.h"
#include "line_segment.h"
#include "point.h"


/**
* Axis aligned bounding volume hierachy data structure.
*/
template <typename primitive>
class aabb_tree
{
public:
	typedef std::vector<primitive> primitive_list;
	//iterator type pointing inside the primitive list
	typedef typename primitive_list::iterator primitive_iterator;
	//const iterator type pointing inside the primitive list
	typedef typename primitive_list::const_iterator const_primitive_iterator;
	
	//abstract base class defining the common interface of all aabb tree node
	class aabb_node
	{
	protected:
		//storage of bounding box assosiated with aabb_node
		box bounds;
	public:
		aabb_node() {
		}

		aabb_node(const box& b): bounds(b) {
		}

		//returns the bounding box of the node
		box get_bounds() const
		{
			return bounds;
		}

		virtual int num_primitives() const = 0;
		

		//this method must be implemented to return true for a leaf node and false for a non_lef node
		virtual bool is_leaf() const = 0;
		//virtual destructor
		virtual ~aabb_node() {}

	};
	///a class representing a leaf node of an aabb tree (non split node)
	class aabb_leaf_node: public aabb_node
	{
		
		//internal storage to the range (begin and end pointer) of the primitives associated with the current leaf node
		primitive_iterator primitives_begin,primitives_end;
	public:	
		
		
		//construct a leaf node from 
		aabb_leaf_node(const primitive_iterator& primitives_begin,
			const primitive_iterator& primitives_end,
			const box& b):
				primitives_begin(primitives_begin),primitives_end(primitives_end), aabb_node(b)
		{
		}

		//return always true because its a leaf node
		bool is_leaf() const
		{
			return true;
		}
		//returns the number primitives assosiated with the current leaf
		int num_primitives() const
		{
			return primitives_end-primitives_begin;
		}

		const_primitive_iterator begin() const
		{
			return primitives_begin;
		}

		const_primitive_iterator end() const
		{
			return primitives_end;
		}


	};

	///a class representing a split node of an aabb tree (non leaf node)
	class aabb_split_node: public aabb_node
	{
		//child pointers
		aabb_node* children[2];
	public:	
		//default constructor
		aabb_split_node()
		{
			children[0] = children[1] = nullptr;
		}
		//construct a split node from given left and right child pointers and given bounding box b of the node
		aabb_split_node(aabb_node* left_child, aabb_node* right_child,const box& b): aabb_node(b)
		{
			children[0] = left_child;
			children[1] = right_child;
		}

		//destructor of node, recursively deleted whole subtree
		~aabb_split_node()
		{
			if(left() != nullptr)
				delete left();
			if(right() != nullptr)
				delete right();
		}

		//returns always false because its a split node
		bool is_leaf() const
		{
			return false;
		}
			
		//returns a pointer to the left child node
		aabb_node* left()
		{
			return children[0];
		}
		//returns a pointer to the right child node
		aabb_node* right() 
		{
			return children[1];
		}

		//returns a const pointer to the left child node 
		const aabb_node* left() const
		{
			return children[0];
		}

		//returns a const pointer to the right child node 
		const aabb_node* right() const
		{
			return children[1];
		}

		//counts the number of primitives of the subtree
		int num_primitives() const
		{
			return left()->num_primitives() + right()->num_primitives();	
		}	
	
	};

private:
	//search entry used internally for nearest and k nearest primitive queries
	struct search_entry
	{
		//squared distance to node from query point
		float sqr_distance;
		//node
		const aabb_node* node;
		
		//constructor
		search_entry(float sqr_distance,const aabb_node* node):sqr_distance(sqr_distance),node(node){}
		
		//search entry a < b means a.sqr_distance > b. sqr_distance 
		bool operator<(const search_entry& e) const
		{
			return sqr_distance > e.sqr_distance;
		}
	};

	//result entry for nearest and k nearest primitive queries
	struct result_entry
	{
		//squared distance from query point to primitive
		float sqr_distance;
		//pointer to primitive
		const primitive* prim;
		//default constructor
		result_entry():sqr_distance(std::numeric_limits<float>::infinity()),prim(nullptr){}
		//constructor
		result_entry(float sqr_distance, const primitive* p):sqr_distance(sqr_distance),prim(p){}
		//result_entry are sorted by their sqr_distance using this less than operator 
		bool operator<(const result_entry& e) const
		{
			return sqr_distance < e.sqr_distance;
		}
	};

	//list of all primitives in the tree
	primitive_list primitives;
	//maximum allowed tree depth to stop tree construction
	int max_depth;
	//minimal number of primitives to stop tree construction
	int min_size;
	//pointer to the root node of the tree
	aabb_node *root;
	//a flag indicating if the tree is constructed
	bool completed;


public:
	//returns a pointer to the root node of the tree
	aabb_node* get_root() 
	{
		assert(is_completed());
		return root;
	}

	//returns a const pointer to the root node of the tree
	const aabb_node* get_root() const
	{
		assert(is_completed());
		return root;
	}

	//constructor of aabb tree 
	//default  maximal tree depth is 20 
	//default minimal size of a node not to be further subdivided in the cnstruction process is two 
	aabb_tree(int max_depth=20, int min_size=2):
		max_depth(max_depth),min_size(min_size),root(nullptr),completed(false)
	{
		
	}

	//copy constructor
	aabb_tree(const aabb_tree& other)
	{
		primitives = other.primitives;
		max_depth = other.max_depth;
		min_size = other.min_size;
		root = copy_tree(other.primitives,other.root);
		completed = other.completed;
	}
	
	//move constructor
	aabb_tree(aabb_tree&& other):root(nullptr),completed(false)
	{
		*this = std::move(other);
	}

	//copy assignment operator
	aabb_tree& operator=(const aabb_tree& other)
	{
		if(this != &other)
		{
			if(root != nullptr)
				delete root;
			primitives = other.primitives;
			max_depth = other.max_depth;
			min_size = other.min_size;
			root = copy_tree(other.primitives,other.root);
			completed = other.completed;
		}
		return *this;
	}

	//move assign operator
	aabb_tree& operator=(aabb_tree&& other)
	{
		if(this != &other)
		{	
			std::swap(primitives,other.primitives);
			std::swap(max_depth, other.max_depth);
			std::swap(min_size, other.min_size);
			std::swap(root,other.root) ;
			std::swap(completed, other.completed);
		}
		return *this;
	}

	//remove all primitives from tree
	void clear()
	{
		primitives.clear();
		if(root != nullptr)
		{
			delete root;
			root = nullptr;
		}
		completed = false;
	}

	//returns true if tree is empty
	bool empty() const
	{
		return primitives.empty();
	}
	
	//insert a primitive into internal primitive list 
	//this method do not construct the tree!
	//call the method complete, after insertion of all primitives
	void insert(const primitive& p)
	{
		primitives.push_back(p);
		completed=false;
	}
	
	//construct the tree from all prior inserted primitives  
	void complete()
	{
		//if tree already constructed -> delete tree
		if(root != nullptr)
			delete root;
		//compute bounding box over all primitives using helper function
		box bounds = compute_bounds(primitives.begin(),primitives.end());
		//initial call to the recursive tree construction method over the whole range of primitives
		root = build(primitives.begin(),primitives.end(),bounds,0);
		//set completed flag to true
		completed=true;
	}

	//returns true if the tree can be used for queries
	//if the tree is not completed call the method complete()
	bool is_completed() const
	{
		return completed;
	}

	//closest primitive computation via linear search
	result_entry closest_primitive_linear_search(const vec3& q) const
	{
		result_entry best;
		
		auto pend = primitives.end();
		for(auto pit = primitives.begin(); pit != pend; ++pit)
		{
			float dist = pit->sqr_distance(q);
			if(dist < best.sqr_distance)
			{
				best.sqr_distance = dist;
				best.prim = &(*pit);
			}
		}
		return best;
	}

	//computes the k nearest neighbor primitives via linear search
	std::vector<result_entry> closest_k_primitives_linear_search(size_t k, const vec3& q) const
	{
		std::priority_queue<result_entry> k_best;
		
		primitive best_p;
		auto pend = primitives.end();
		for(auto pit = primitives.begin(); pit != pend; ++pit)
		{
			float dist = pit->sqr_distance(q);
			if(k_best.size() < k )
			{
				k_best.push(result_entry(dist,*pit));
				return;
			}
			if(k_best.top().sqr_distance > dist)
			{
				k_best.pop();
				k_best.push(result_entry(dist,*pit));
			}				
		}
		std::vector<result_entry> result(k_best.size());
		auto rend = result.end();
		for(auto rit = result.begin(); rit != rend; ++rit)
		{
			*rit = k_best.top();
			k_best.pop();
		}
		return result;

	}
	
	//closest k primitive computation 
	std::vector<result_entry> closest_k_primitives(size_t k,const vec3& q) const
	{
		//student begin
		return closest_k_primitives_linear_search(k,q);
		//student end
	}
	
	//returns the closest primitive and its squared distance to the point q
	result_entry closest_primitive(const vec3& q) const
	{
		assert(is_completed());
		if(root == nullptr)
			return result_entry();
		//student begin
		return closest_primitive_linear_search(q);
		//student end
	
	}

	//return the closest point position on the closest primitive in the tree with respect to the query point q
	vec3 closest_point(const vec3& p) const
	{
		result_entry r = closest_primitive(p);
		return  r.prim->closest_point(p);
	}
	
	//return the squared distance between point p and the nearest primitive in the tree
	float sqr_distance(const vec3& p) const
	{
		result_entry r = closest_primitive(p);
		return r.sqr_distance;
	}

	//return the euclidean distance between point p and the nearest primitive in the tree
	float distance(const vec3& p) const
	{
		return sqrt(sqr_distance(p));
	}


protected:

	//helper function to copy a subtree
	aabb_node* copy_tree(const primitive_list& other_primitives,aabb_node* node)
	{
		if(node == nullptr)
			return nullptr;
		if(node->is_leaf())
		{
			aabb_leaf_node* leaf = (aabb_leaf_node*)node;
			return new aabb_leaf_node(primitives.begin()+(leaf->primitives.begin()-other_primitives.begin()),
				primitives.begin()+(leaf->primitives.end()-other_primitives.begin()));
		}
		else
		{
			aabb_split_node* split = (aabb_split_node*)node;
			return new aabb_split_node(copy_tree(other_primitives,split->left()), 
				copy_tree(other_primitives,split->right()));
		}
	}

	//helper function to compute an axis aligned bounding box over the range of primitives [begin,end)
	box compute_bounds(const_primitive_iterator begin,
		const_primitive_iterator end)
	{
		box bounds;
		for(auto pit = begin; pit != end; ++pit)
			bounds.insert(pit->compute_bounds());
		return bounds;
	}
	
	

	//recursive tree construction initially called from method complete()
	//build an aabb (sub)-tree over the range of primitives [begin,end), 
	//the current bounding box is given by bounds and the current tree depth is given by the parameter depth
	//if depth >= max_depth or the number of primitives (end-begin)  <= min_size a leaf node is constructed
	//otherwise split node is created 
	// to create a split node the range of primitives [begin,end) must be splitted and reordered into two 
	//sub ranges [begin,mid) and [mid,end),
	//therefore sort the range of primitives [begin,end) along the largest bounding box extent by its  reference 
	//point returned by the method reference_point()
	//then choose the median element as mid 
	// the STL routine std::nth_element would be very useful here , you only have to provide a ordering predicate
	//compute the boundg boxed of the two resulting sub ranges and recursivly call build on the two subranges
	//the resulting subtree are used as children of the resulting split node.
	aabb_node* build(primitive_iterator begin, primitive_iterator end, box& bounds, int depth)
	{
		
		if(depth >= max_depth || end-begin <= min_size)
		{	
			return new aabb_leaf_node(begin,end,bounds);
		}

		vec3 e = bounds.extents();
		
		int axis = 0;
		float max_extent = e[0];
		if(max_extent < e[1])
		{
			axis = 1;
			max_extent = e[1];
		}
		if(max_extent < e[2])
		{
			axis = 2;
			max_extent = e[2];
		}
		

		primitive_iterator mid= begin + (end-begin)/2;
		std::nth_element(begin,mid,end,[&axis](const primitive& a, const primitive& b)
			{ return a.reference_point()[axis] < b.reference_point()[axis];});
		
		box lbounds = compute_bounds(begin,mid);
		box rbounds = compute_bounds(mid,end);

		return new aabb_split_node(build(begin,mid,lbounds,depth+1),build(mid,end,rbounds,depth+1),bounds);

	}
};

//helper function to construct an aabb tree data structure from the triangle faces of the halfedge mesh m
void build_aabb_tree_from_triangles_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<triangle >& tree);
//helper function to construct an aabb tree data structure from the vertices of the halfedge mesh m
void build_aabb_tree_from_vertices_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<point>& tree);
//helper function to construct an aabb tree data structure from the edges of the halfedge mesh m
void build_aabb_tree_from_edges_of_halfedge_mesh(const halfedge_mesh& m, aabb_tree<line_segment>& tree);

