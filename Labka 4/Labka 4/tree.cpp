#include "tree.h"

tree_node* tree_node::find_node_for_delete(const size_t& level, size_t& index)
{
	static tree_node* node_for_delete;
	static size_t max_nodes = 0, current_level = 1;
	if (current_level == 1 && this->height() < level) throw std::exception("This level doesn't exist");

	size_t size = this->branch.size();
	if (current_level == level)
	{
		for (size_t i = 0, nodes; i < size; i++)
		{
			nodes = this->branch[i]->num_of_nodes();
			if (max_nodes < nodes)
			{
				max_nodes = nodes;
				node_for_delete = this;
				index = i;
			}
		}
	}
	else {
		++current_level;
		for (size_t i = 0; i < size; i++)
		{
			this->branch[i]->find_node_for_delete(level, index);
		}
		--current_level;
	}
	return node_for_delete;
}

void tree_node::add_after_delete(tree_node* temp)
{
	for (size_t i = 0, size = temp->branch.size(); i < size; i++)
	{
		add_after_delete(temp->branch[i]);
	}
	temp->branch.clear();
	this->add_node_by_random(temp);
}

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
	} else {
		this->branch[(generate_int(0, (size * size) - 1) / size)]->add_node_by_random(value, chance);
	}
}

void tree_node::add_node_by_random(tree_node* node, const double& chance)
{
	double random = generate_real();
	size_t size = this->branch.size();
	if (random <= chance || size == 0)
	{
		this->branch.push_back(node);
	} else {
		this->branch[(generate_int(0, (size * size) - 1) / size)]->add_node_by_random(node, chance);
	}
}

int tree_node::delete_node(const size_t& level)
{
	if (level == 0)
	{
		throw std::exception("You can't delete a parent in this way");
	}
	else {
		size_t index;
		tree_node* node_for_delete = this->find_node_for_delete(level, index);
		tree_node* temp = node_for_delete->branch[index];
		int deleted_value = temp->value;

		for (size_t i = 0, size = temp->branch.size(); i < size; i++)
		{
			add_after_delete(temp->branch[i]);
		}

		auto it = node_for_delete->branch.begin() + index;
		node_for_delete->branch.erase(it);
		delete temp;

		return deleted_value;
	}
}

void tree_node::print()
{
	std::cout << this->value;
	size_t h = this->height(), size = this->branch.size();
	if (size == 0) return;

	std::cout << (h > 2 ? "  " : "(");

	--size;
	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->print();
		std::cout << ',';
	}
	this->branch[size]->print();

	std::cout << (h > 2 ? "  " : ")");
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







void tree::add_after_delete(tree_node* temp)
{
	for (size_t i = 0, size = temp->branch.size(); i < size; i++)
	{
		add_after_delete(temp->branch[i]);
	}
	temp->branch.clear();
	this->add_node_by_random(temp);
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

void tree::add_node_by_random(tree_node* node, const double& chance)
{
	if (this->root == nullptr) {
		this->root = node;
	}
	else {
		this->root->add_node_by_random(node, chance);
	}
}

int tree::delete_node(const size_t& level)
{
	if (level == 0)
	{
		tree_node* temp = this->root;
		this->root = nullptr;
		
		for (size_t i = 0, size = temp->branch.size(); i < size; i++)
		{
			this->root->add_after_delete(temp->branch[i]);
		}
	}
	else return this->root->delete_node(level);
}

void tree::print()
{
	if (this->root == nullptr) std::cout << "Tree is empty";
	else root->print();
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
