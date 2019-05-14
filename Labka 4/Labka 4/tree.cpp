#include "tree.h"


tree_node::tree_node(const int& value)
{
	this->value = value;
}

void tree_node::add_node_by_random(const int& value, const double& chance)
{
	double random = generate_real();
	size_t size = this->branch.size();
	if (random <= chance || size == 0)
	{
		tree_node* temp = new tree_node(value);
		this->branch.push_back(temp);
	} else 
	{
		this->branch[(generate_int(0, (size * size) - 1) / size)]->add_node_by_random(value, chance);
	}
}

size_t tree_node::num_of_children()
{
	return size_t(this->branch.size());
}

double tree_node::avarage_num_of_children()
{
	size_t size = this->branch.size();
	
	static size_t n = 0, val = 0;
	if (size != 0)
	{
		val += size;
		++n;
	}

	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->avarage_num_of_children();
	}
	if (n == 0) return 0;
	return ((double)val / (double)n);
}

size_t tree_node::num_of_nodes()
{
	size_t size = this->branch.size(), num = 1;
	for (size_t i = 0; i < size; ++i)
	{
		num += this->branch[i]->num_of_nodes();
	}
	return size_t(num);
}

double tree_node::avarage_num_of_nodes()
{
	static size_t n = 0, val = 0, node_val = 0;

	size_t size = this->branch.size();
	if (size != 0)
	{
		++n;
		++node_val;
	}
	val += node_val;

	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->avarage_num_of_nodes();
	}
	if (size != 0) --node_val;
	if (n == 0) return 0;
	return ((double)val / (double)n);
}

size_t tree_node::height()
{
	size_t size = this->branch.size(), num, max = 0;
	for (size_t i = 0; i < size; ++i)
	{
		num = 1;
		num += this->branch[i]->height();
		if (max < num) max = num;
	}
	return size_t(max);
}

double tree_node::avarage_height()
{
	static size_t n = 0, val = 0;
	size_t size = this->branch.size();
	
	if (size != 0) 
	{ 
		++n;
		val += this->height();
	}
	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->avarage_height();
	}

	if (n == 0) return 0;
	return ((double)val / (double)n);
}







tree::tree()
{
	this->root = nullptr;
}

tree::~tree()
{
}

void tree::add_node_by_random(const int& value, const double& chance)
{
	if (this->root == nullptr) {
		this->root = new tree_node(value);
	} else {
		this->root->add_node_by_random(value, chance);
	}
}

size_t tree::num_of_children()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->num_of_children());
}

double tree::avarage_num_of_children()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->avarage_num_of_children());
}

size_t tree::num_of_nodes()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->num_of_nodes());
}

double tree::avarage_num_of_nodes()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->avarage_num_of_nodes());
}

size_t tree::height()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->height());
}

double tree::avarage_height()
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->avarage_height());
}
