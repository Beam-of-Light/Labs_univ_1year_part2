#ifndef TREE_H
#define TREE_H
#include "pch.h"

class tree_node
{
private:
	tree_node* find_node_for_delete(const size_t& level, size_t& index);
	void add_after_delete(tree_node* temp);

	int value;
	std::vector<tree_node*> branch;

public:
	tree_node(const int& value);

	void add_node_by_random(const int& value, const double& chance = 0.5);
	void add_node_by_random(tree_node* node, const double& chance = 0.5);
	int delete_node(const size_t& level);
	void print();

	size_t num_of_children();
	double avarage_num_of_children();
	size_t num_of_nodes();
	double avarage_num_of_nodes();
	size_t height();
	double avarage_height();

	friend class tree;
};

class tree
{
private:
	void add_after_delete(tree_node* temp);

	tree_node* root;

public:
	tree();
	~tree();

	void add_node_by_random(const int& value, const double& chance = 0.5);
	void add_node_by_random(tree_node* node, const double& chance = 0.5);
	int delete_node(const size_t& level);
	void print();
	
	size_t num_of_children();
	double avarage_num_of_children();
	size_t num_of_nodes();
	double avarage_num_of_nodes();
	size_t height();
	double avarage_height();
};

#endif /* TREE_H */