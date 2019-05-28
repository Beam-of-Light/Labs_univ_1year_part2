#ifndef TREE_H
#define TREE_H
#include "pch.h"

class tree_node
{
private:
	void find_node_for_delete(const size_t& level, size_t& index,
		size_t& max_nodes, size_t& current_level, tree_node*& node_for_delete);
	void add_after_delete(tree_node* temp);

	void average_num_of_children(size_t& val, size_t& n) const;
	void average_num_of_nodes(size_t& val, size_t& n, size_t& node_val) const;
	void average_height(size_t& val, size_t& n) const;

	int value;
	std::vector<tree_node*> branch;

public:
	tree_node(const int& value);
	~tree_node();

	void add_node_by_random(const int& value, const double& chance = 0.5);
	void add_node_by_random(tree_node* node, const double& chance = 0.5);
	int delete_node(const size_t& level);
	void print() const;

	size_t num_of_children() const;
	double average_num_of_children() const;
	size_t num_of_nodes() const;
	double average_num_of_nodes() const;
	size_t height() const;
	double average_height() const;

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
	void print() const;
	
	size_t num_of_children() const;
	double average_num_of_children() const;
	size_t num_of_nodes() const;
	double average_num_of_nodes() const;
	size_t height() const;
	double average_height() const;
};

#endif /* TREE_H */