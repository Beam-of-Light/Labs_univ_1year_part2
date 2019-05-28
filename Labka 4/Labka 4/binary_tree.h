#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "pch.h"


class binary_tree_node
{
protected:
	int value;
	binary_tree_node* left, * right;

	void print() const;
	size_t height() const;

public:
	binary_tree_node(const int& value, binary_tree_node* left, binary_tree_node* right);
	~binary_tree_node();

	friend class binary_tree;
	friend class binary_h_tree;
};






class binary_tree
{
private:
	binary_tree_node* root;

public:
	binary_tree();
	~binary_tree();

	void add(const int& value);
	void print() const;

	friend class binary_h_tree;
};













class binary_h_tree_node
{
private:
	int value;
	binary_h_tree_node* left, * right;
	bool ltag, rtag;

	void print() const;
	size_t height() const;

public:
	binary_h_tree_node(const int& value, binary_h_tree_node* left, binary_h_tree_node* right);

	friend class binary_h_tree;
};



class binary_h_tree
{
private:
	binary_h_tree_node* root;

	binary_h_tree_node* rebuild(const binary_tree_node* bin_tree, binary_h_tree_node* sym_left, binary_h_tree_node* sym_right);

public:
	binary_h_tree();
	~binary_h_tree();

	void rebuild(const binary_tree* bin_tree);
	void print() const;
};
#endif /* BINARY_TREE_H */