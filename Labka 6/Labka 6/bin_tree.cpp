#include "bin_tree.h"


void bin_tree::bin_tree_node::change_parent(bin_tree_node* new_child) const
{
	if (this->parent->left == this)
		this->parent->left = new_child;
	else this->parent->right = new_child;
}

void bin_tree::bin_tree_node::del_node_with_2children()
{
	bin_tree_node* find = this->right;
	while (find->left) {
		find = find->left;
	}
	if (find->right == nullptr) {
		find->change_parent();
	}
	else {
		find->change_parent(find->right);
		find->right->parent = find->parent;
	}
	this->_complex = find->_complex;
	delete find;
}

bin_tree::bin_tree_node::bin_tree_node(bin_tree_node* left, bin_tree_node* right, bin_tree_node* parent)
{
	this->left = left;
	this->right = right;
	this->parent = parent;
}

bin_tree::bin_tree_node::bin_tree_node(const node& _complex, bin_tree_node* left, bin_tree_node* right, bin_tree_node* parent)
{
	this->_complex = _complex;
	this->left = left;
	this->right = right;
	this->parent = parent;
}

void bin_tree::bin_tree_node::print() const
{
	if (this->left) {
		this->left->print();
	}
	std::cout << "Value - " << this->_complex.value << "\nz = ";
	_complex.data.print();
	std::cout << std::endl;
	if (this->right) {
		this->right->print();
	}
}


bin_tree::bin_tree_node* bin_tree::find(const complex& data)
{
	bin_tree_node* temp = this->root;
	double value = data.calc_value();
	while (temp) {
		if (data == temp->_complex.data) {
			return temp;
		}
		else if (value >= temp->_complex.value) {
			if (temp->right) {
				temp = temp->right;
			}
			else return nullptr;
		}
		else {
			if (temp->left) {
				temp = temp->left;
			}
			else return nullptr;
		}
	}
}

void bin_tree::bin_tree_node::find_by_value(std::vector<complex>*& result, const double& value, const double& e) const
{
	if (this) {
		if (fabs(this->_complex.value - value) <= e) {
			result->push_back(this->_complex.data);
			this->left->find_by_value(result, value, e);
			this->right->find_by_value(result, value, e);
		}
		if (!(this->_complex.value <= value - e))
			this->left->find_by_value(result, value, e);
		if (!(this->_complex.value > value + e))
			this->right->find_by_value(result, value, e);
	}
}

bin_tree::bin_tree()
{
	this->root = nullptr;
}

void bin_tree::print() const
{
	if (this->root == nullptr) std::cout << "Tree is empty";
	else root->print();
}

void bin_tree::add(const complex& data)
{
	bin_tree_node* new_node = new bin_tree_node(node(data));
	add(new_node);
}
void bin_tree::add(bin_tree_node* new_node)
{
	if (!new_node) new_node = new bin_tree_node;
	if (!this->root) {
		this->root = new_node;
		this->root->parent = this->root;
	}
	else {
		bin_tree_node* temp = this->root;
		while (temp) {
			if (new_node->_complex.value > temp->_complex.value) {
				if (temp->right) {
					temp = temp->right;
				}
				else {
					temp->right = new_node;
					new_node->parent = temp;
					break;
				}
			}
			else if (new_node->_complex.value == temp->_complex.value) {
				new_node->right = temp->right;
				temp->right->parent = new_node;
				temp->right = new_node;
				new_node->parent = temp;
				break;
			}
			else {
				if (temp->left) {
					temp = temp->left;
				}
				else {
					temp->left = new_node;
					new_node->parent = temp;
					break;
				}
			}
		}
	}
}

void bin_tree::add_n_random(size_t n)
{
	for (size_t i = 0; i < n; ++i) {
		add();
	}
}

bool bin_tree::pop(const complex& data)
{
	bin_tree_node* temp = this->find(data);
	if (temp) {
		if (!temp->left) {
			if (!temp->right) {
				temp->change_parent();
				delete temp;
			}
			else {
				temp->change_parent(temp->right);
				temp->right->parent = temp->parent;
				delete temp;
			}
		}
		else {
			if (!temp->right) {
				temp->change_parent(temp->left);
				temp->left->parent = temp->parent;
				delete temp;
			}
			else {
				temp->del_node_with_2children();
			}
		}
	}
	else return false;
}

std::vector<complex>* bin_tree::find_by_value(double value, double e) const
{
	std::vector<complex>* result = new std::vector<complex>;
	this->root->find_by_value(result, value, e);
	return result;
}
