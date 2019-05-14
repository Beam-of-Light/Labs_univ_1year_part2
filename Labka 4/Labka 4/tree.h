#ifndef TREE_H
#define TREE_H
#include "pch.h"

class tree_node
{
private:
	int value;
	std::vector<tree_node*> branch;

public:
	tree_node(const int& value);

	void add_node_by_random(const int& value, const double& chance = 0.5);
	void print();

	size_t num_of_children();
	double avarage_num_of_children();
	size_t num_of_nodes();
	double avarage_num_of_nodes();
	size_t height();
	double avarage_height();
};

class tree
{
public:
	tree();
	~tree();

	void add_node_by_random(const int& value, const double& chance = 0.5);
	void print();
	
	size_t num_of_children();
	double avarage_num_of_children();
	size_t num_of_nodes();
	double avarage_num_of_nodes();
	size_t height();
	double avarage_height();

private:
	tree_node* root;
};

#endif /* TREE_H */