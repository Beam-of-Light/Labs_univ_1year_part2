#include "tree.h"

void tree_node::find_node_for_delete(const size_t& level, size_t& index,
	size_t& max_nodes, size_t& current_level, tree_node*& node_for_delete)
{ /* current_level = 1 because we look for parent and index of his child */
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
			this->branch[i]->find_node_for_delete(level, index, max_nodes, current_level, node_for_delete);
		}
		--current_level;
	}
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

void tree_node::average_num_of_children(size_t& val, size_t& n) const
{
	size_t size = this->branch.size();
	if (size == 0) return;

	val += size;
	++n;

	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->average_num_of_children(val, n);
	}
}

void tree_node::average_num_of_nodes(size_t& val, size_t& n, size_t& node_val) const
{
	size_t size = this->branch.size();
	if (size != 0)
	{
		++n;
		++node_val;
	}
	val += node_val;

	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->average_num_of_nodes(val, n, node_val);
	}
	if (size != 0) --node_val;
}

void tree_node::average_height(size_t& val, size_t& n) const
{
	size_t size = this->branch.size();
	if (size == 0) return;

	++n;
	val += this->height();

	for (size_t i = 0; i < size; ++i)
	{
		this->branch[i]->average_height(val, n);
	}
}

tree_node::tree_node(const int& value)
{
	this->value = value;
}

tree_node::~tree_node()
{
	for (size_t i = 0, size = this->branch.size(); i < size; i++)
	{
		delete this->branch[i];
	}
}

void tree_node::add_node_by_random(const int& value, const double& chance) /* chance = 0.5 */
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

void tree_node::add_node_by_random(tree_node* node, const double& chance) /* chance = 0.5 */
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
	if (level == 0)	throw std::exception("You can't delete a parent in this way");
	else if (this->height() < level) throw std::exception("This level doesn't exist");
	else {
		size_t index, max_nodes = 0, current_level = 1;
		tree_node* node_for_delete = nullptr;
		this->find_node_for_delete(level, index, max_nodes, current_level, node_for_delete);
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

void tree_node::print() const
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

size_t tree_node::num_of_children() const
{
	return size_t(this->branch.size());
}
//
double tree_node::average_num_of_children() const
{
	size_t val = 0, n = 0;
	this->average_num_of_children(val, n);
	
	if (n == 0) return 0;
	return ((double)val / (double)n);
}

size_t tree_node::num_of_nodes() const
{
	size_t size = this->branch.size(), num = 1;
	for (size_t i = 0; i < size; ++i)
	{
		num += this->branch[i]->num_of_nodes();
	}
	return size_t(num);
}

double tree_node::average_num_of_nodes() const
{
	size_t n = 0, val = 0, node_val = 0;
	this->average_num_of_nodes(val, n, node_val);
	
	if (n == 0) return 0;
	return ((double)val / (double)n);
}

size_t tree_node::height() const
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

double tree_node::average_height() const
{
	size_t n = 0, val = 0;
	this->average_height(val, n);

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
	delete this->root;
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
		int deleted_value = temp->value;
		this->root = nullptr;
		for (size_t i = 0, size = temp->branch.size(); i < size; i++)
		{
			this->add_after_delete(temp->branch[i]);
		}
		delete temp;
		return deleted_value;
	}
	else return this->root->delete_node(level);
}

void tree::print() const
{
	if (this->root == nullptr) std::cout << "\nTree is empty\n";
	else root->print();
}

size_t tree::num_of_children() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->num_of_children());
}

double tree::average_num_of_children() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->average_num_of_children());
}

size_t tree::num_of_nodes() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->num_of_nodes());
}

double tree::average_num_of_nodes() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->average_num_of_nodes());
}

size_t tree::height() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return size_t(root->height());
}

double tree::average_height() const
{
	if (this->root == nullptr) throw std::exception("Tree is empty");
	return double(root->average_height());
}
